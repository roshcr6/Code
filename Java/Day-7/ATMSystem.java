import java.io.*;
import java.util.Scanner;

public class ATMSystem {
    private static final Scanner scanner = new Scanner(System.in);

    private static final String[][] defaultAccounts = {
            {"1001", "5000"},
            {"1002", "3000"},
            {"1003", "7000"}
    };

    public static void main(String[] args) {
        initializeAccounts(); 
        while (true) {
            System.out.println("\n=== ATM Menu ===");
            System.out.println("1. Deposit");
            System.out.println("2. Withdraw");
            System.out.println("3. Transfer");
            System.out.println("4. Check Balance");
            System.out.println("5. Exit");
            System.out.print("Choose an option: ");

            int choice;
            try {
                choice = Integer.parseInt(scanner.nextLine());
            } catch (Exception e) {
                System.out.println("Invalid input. Please enter a number.");
                continue;
            }

            switch (choice) {
                case 1 -> deposit();
                case 2 -> withdraw();
                case 3 -> transfer();
                case 4 -> checkBalance();
                case 5 -> {
                    System.out.println("Thank you for using the ATM!");
                    return;
                }
                default -> System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void initializeAccounts() {
        for (String[] account : defaultAccounts) {
            String accNo = account[0];
            int balance = Integer.parseInt(account[1]);

            File file = new File(accNo + ".txt");
            if (!file.exists()) {
                saveBalance(accNo, balance);
            }
        }
    }

    private static void deposit() {
        System.out.print("Enter account number: ");
        String acc = scanner.nextLine();
        int balance = loadBalance(acc);

        if (balance == -1) return;

        System.out.print("Enter amount to deposit: ");
        int amount = Integer.parseInt(scanner.nextLine());
        balance += amount;

        saveBalance(acc, balance);
        System.out.println("Deposit successful! New Balance: " + balance);
    }

    private static void withdraw() {
        System.out.print("Enter account number: ");
        String acc = scanner.nextLine();
        int balance = loadBalance(acc);

        if (balance == -1) return;

        System.out.print("Enter amount to withdraw: ");
        int amount = Integer.parseInt(scanner.nextLine());

        if (amount > balance) {
            System.out.println("Insufficient balance!");
            return;
        }

        balance -= amount;
        saveBalance(acc, balance);
        System.out.println("Withdrawal successful! New Balance: " + balance);
    }

    private static void transfer() {
        System.out.print("Enter sender account number: ");
        String sender = scanner.nextLine();
        int senderBalance = loadBalance(sender);

        if (senderBalance == -1) return;

        System.out.print("Enter receiver account number: ");
        String receiver = scanner.nextLine();
        int receiverBalance = loadBalance(receiver);

        if (receiverBalance == -1) return;

        System.out.print("Enter amount to transfer: ");
        int amount = Integer.parseInt(scanner.nextLine());

        if (amount > senderBalance) {
            System.out.println("Insufficient balance for transfer!");
            return;
        }

        senderBalance -= amount;
        receiverBalance += amount;

        saveBalance(sender, senderBalance);
        saveBalance(receiver, receiverBalance);

        System.out.println("Transfer successful!");
        System.out.println("Sender New Balance: " + senderBalance);
        System.out.println("Receiver New Balance: " + receiverBalance);
    }

    private static void checkBalance() {
        System.out.print("Enter account number: ");
        String acc = scanner.nextLine();
        int balance = loadBalance(acc);

        if (balance != -1) {
            System.out.println("Account " + acc + " Balance: " + balance);
        }
    }

    private static int loadBalance(String acc) {
        try (BufferedReader reader = new BufferedReader(new FileReader(acc + ".txt"))) {
            return Integer.parseInt(reader.readLine());
        } catch (FileNotFoundException e) {
            System.out.println("Account not found!");
        } catch (IOException | NumberFormatException e) {
            System.out.println("Error reading account balance.");
        }
        return -1;
    }

    private static void saveBalance(String acc, int balance) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(acc + ".txt"))) {
            writer.write(String.valueOf(balance));
        } catch (IOException e) {
            System.out.println("Error saving balance.");
        }
    }
}

