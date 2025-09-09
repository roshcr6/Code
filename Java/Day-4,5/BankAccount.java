import java.util.Scanner;

public class BankAccount {
    private String accountNumber;
    private String accountHolderName;
    private double balance;

    public BankAccount(String accountNumber, String accountHolderName, double balance) {
        this.accountNumber = accountNumber;
        this.accountHolderName = accountHolderName;
        this.balance = balance;
        System.out.println("New account created:");
        displayDetails();
    }


    public BankAccount(String accountNumber, String accountHolderName) {
        this(accountNumber, accountHolderName, 0);
    }

    public void deposit(double amount) {
        if (amount > 0) balance += amount;
        else System.out.println("Invalid amount.");
    }

    public void withdraw(double amount) {
        if (amount > 0 && amount <= balance) balance -= amount;
        else System.out.println("Invalid amount or insufficient balance.");
    }

    public double getBalance() {
        return balance;
    }

    public void displayDetails() {
        System.out.println("Account: " + accountNumber);
        System.out.println("Holder: " + accountHolderName);
        System.out.println("Balance: " + balance);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);


        System.out.println("Creating default accounts...");
        BankAccount account1 = new BankAccount("12345", "Rock", 1000);
        BankAccount account2 = new BankAccount("67890", "Brock");


        BankAccount currentAccount = account2;

        while (true) {
            System.out.println("\n--- Bank Account Menu ---");
            System.out.println("Current active account:");
            currentAccount.displayDetails();
            System.out.println("\n1. Switch Account");
            System.out.println("2. Create New Account");
            System.out.println("3. Deposit Money");
            System.out.println("4. Withdraw Money");
            System.out.println("5. Display Account Details");
            System.out.println("6. Exit");
            System.out.print("Choose an option: ");

            int choice = sc.nextInt();
            sc.nextLine(); 

            switch (choice) {
                case 1:

                    System.out.println("Choose account to switch:");
                    System.out.println("1. Account 1 (Rock)");
                    System.out.println("2. Account 2 (Broke)");
                    System.out.print("Enter choice: ");
                    int accChoice = sc.nextInt();
                    sc.nextLine();
                    if (accChoice == 1) {
                        currentAccount = account1;
                    } else if (accChoice == 2) {
                        currentAccount = account2;
                    } else {
                        System.out.println("Invalid account choice.");
                    }
                    break;

                case 2:
                    System.out.print("Enter account number: ");
                    String accNum = sc.nextLine();
                    System.out.print("Enter account holder name: ");
                    String accHolder = sc.nextLine();
                    System.out.print("Enter initial balance (or 0): ");
                    double initBalance = sc.nextDouble();
                    sc.nextLine();
                    BankAccount newAccount = new BankAccount(accNum, accHolder, initBalance);
                    currentAccount = newAccount; 
                    break;

                case 3:
                    System.out.print("Enter amount to deposit: ");
                    double depositAmt = sc.nextDouble();
                    sc.nextLine();
                    currentAccount.deposit(depositAmt);
                    break;

                case 4:
                    System.out.print("Enter amount to withdraw: ");
                    double withdrawAmt = sc.nextDouble();
                    sc.nextLine();
                    currentAccount.withdraw(withdrawAmt);
                    break;

                case 5:
                    currentAccount.displayDetails();
                    break;

                case 6:
                    System.out.println("Exiting. Goodbye!");
                    sc.close();
                    System.exit(0);

                default:
                    System.out.println("Invalid choice. Try again.");
            }
        }
    }
}

