class BankAccount {
    private int balance = 0;

    public synchronized void updateBalance(int amount) {

        balance += amount;


        System.out.println(Thread.currentThread().getName() + 
                           " updated balance: " + balance);

        try {

            Thread.sleep(1500);
        } catch (InterruptedException e) {

            Thread.currentThread().interrupt();
        }


        System.out.println(Thread.currentThread().getName() + 
                           " balance after sleep: " + balance);
    }

    public int getBalance() {
        return balance;
    }
}

public class BankSimulation {
    public static void main(String[] args) {

        BankAccount account = new BankAccount();

        Thread depositThread = new Thread(() -> {
            for (int i = 0; i < 5; i++) {
                account.updateBalance(100); 
                try {
                    Thread.sleep(500); 
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }, "DepositThread");


        Thread withdrawThread = new Thread(() -> {
            for (int i = 0; i < 5; i++) {
                account.updateBalance(-50); 
                try {
                    Thread.sleep(700); 
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }, "WithdrawThread");

        depositThread.start();
        withdrawThread.start();
    }
}

