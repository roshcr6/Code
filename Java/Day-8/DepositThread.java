public class DepositThread {

    static class BankAccount {
        private int balance;

        public BankAccount(int initialBalance) {
            this.balance = initialBalance;
        }

        public synchronized void updateBalance(int amount) {
            String threadName = Thread.currentThread().getName();
            balance += amount;
            System.out.printf("%s: applied %+d -> balance (immediate): %d%n", threadName, amount, balance);
            try {
                Thread.sleep(1500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            System.out.printf("%s: balance (after 1500ms): %d%n", threadName, balance);
        }

        public int getBalance() {
            return balance;
        }
    }

    static class Deposit implements Runnable {
        private final BankAccount account;
        private final int times;
        private final int amount;

        public Deposit(BankAccount account, int times, int amount) {
            this.account = account;
            this.times = times;
            this.amount = amount;
        }

        @Override
        public void run() {
            for (int i = 0; i < times; i++) {
                account.updateBalance(amount);
            }
        }
    }

    static class Withdraw implements Runnable {
        private final BankAccount account;
        private final int times;
        private final int amount;

        public Withdraw(BankAccount account, int times, int amount) {
            this.account = account;
            this.times = times;
            this.amount = amount;
        }

        @Override
        public void run() {
            for (int i = 0; i < times; i++) {
                account.updateBalance(-amount);
            }
        }
    }

    public static void main(String[] args) {
        BankAccount account = new BankAccount(1000);
        Thread depositThread = new Thread(new Deposit(account, 5, 200), "DepositThread");
        Thread withdrawThread = new Thread(new Withdraw(account, 5, 150), "WithdrawThread");

        depositThread.start();
        withdrawThread.start();

        try {
            depositThread.join();
            withdrawThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("Final balance: " + account.getBalance());
    }
}

