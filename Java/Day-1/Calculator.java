import java.util.Scanner;
public class Calculator {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double result;
        boolean keepRunning = true;
        System.out.println("Calculator Operations:");
        System.out.println("1. Addition (+)");
        System.out.println("2. Subtraction (-)");
        System.out.println("3. Multiplication (*)");
        System.out.println("4. Division (/)");
        System.out.println("5. Exit\n");
        do {
            System.out.print("\n====MENU====\n");
            System.out.print("\nChoose operation :\n1. Addition (+)\n2. Subtraction (-)\n3. Multiplication (*)\n4. Division (/)\n5. Exit \n ");
            int choice = sc.nextInt();
            if (choice==5){
            System.out.println("Exiting calculator...");
            return;}
            System.out.print("Enter first number: ");
            double n1 = sc.nextDouble();
            System.out.print("Enter second number: ");
            double n2 = sc.nextDouble();
            switch (choice) {
                case 1 -> {
                    result = n1 + n2;
                    System.out.println("Sum of " + n1 + " and "+n2 +" is "+result);
                }
                case 2 -> {
                    result = n1 - n2;
                    System.out.println("Differentence of " + n1 + " from "+n2 +" is "+result);
                }
                case 3 -> {
                    result = n1 * n2;
                    System.out.println("Product of " + n1 + " and "+n2 +" is "+result);
                }
                case 4 -> {
                    if (n2 != 0) {
                        result = n1 / n2;
                        System.out.println("Quotient of " + n1 + " from "+n2 +" is "+result);
                    } else {
                        System.out.println("Error: Division by zero!");
                    }
                }
                case 5 -> {
                    System.out.println("Exiting calculator...");
                    keepRunning = false;
                }
                default -> System.out.println("Invalid choice!.Stop Messing Around");
            }
            System.out.println(); 
        } while (keepRunning);
        sc.close();
    }}
