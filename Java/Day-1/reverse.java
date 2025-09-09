import java.util.Scanner;

public class reverse {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter The Number:");
        int num = sc.nextInt();

        int reverse = 0;

        for (; num != 0; num = num / 10) {
            int digit = num % 10;
            reverse = reverse * 10 + digit;
        }

        System.out.println("Reverse of the Number is " + reverse);
    }
}

