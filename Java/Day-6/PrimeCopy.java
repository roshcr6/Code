import java.io.*;
import java.util.*;

public class PrimeCopy {
    public static void main(String[] args) throws IOException {
        FileReader fr = new FileReader("numbers.txt");
        Scanner sc = new Scanner(fr);
        FileWriter fw = new FileWriter("primes.txt");

        while (sc.hasNextInt()) {
            int n = sc.nextInt();
            boolean prime = true;

            if (n <= 1) prime = false;
            for (int i = 2; i <= n / 2; i++) {
                if (n % i == 0) { prime = false; break; }
            }

            if (prime) {
                fw.write(n + "\n");

            System.out.print(n+"\n");
            }
        }

        sc.close();
        fr.close();
        fw.close();
        System.out.println("Primes Numbers are saved to primes.txt");
    }
}

