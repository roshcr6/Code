import java.io.*;
import java.util.Scanner;

public class CaesarEncrypt {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        int shift = 3; 

        System.out.print("Give Out The Text you Wanna  Encrypt: ");
        String originalText = scanner.nextLine();

        FileWriter inputFile = new FileWriter("input.txt");
        inputFile.write(originalText);
        inputFile.close();
        System.out.println("Original version is been saved as input.txt");

        FileReader readInput = new FileReader("input.txt");
        FileWriter encryptedFile = new FileWriter("encrypted.txt");

        System.out.print("\nEncrypted Text: ");
        int data;
        while ((data = readInput.read()) != -1) {
            char letter = (char) data;

            if (letter >= 'a' && letter <= 'z') {
                letter = (char) ((letter - 'a' + shift) % 26 + 'a');
            } else if (letter >= 'A' && letter <= 'Z') {
                letter = (char) ((letter - 'A' + shift) % 26 + 'A');
            }

            encryptedFile.write(letter);
            System.out.print(letter);
        }
        readInput.close();
        encryptedFile.close();
        System.out.println("\nEncrypted version is been saved as encrypted.txt");

        FileReader readEncrypted = new FileReader("encrypted.txt");
        FileWriter decryptedFile = new FileWriter("decrypted.txt");

        System.out.print("\nDecrypted Text: ");
        while ((data = readEncrypted.read()) != -1) {
            char letter = (char) data;

            if (letter >= 'a' && letter <= 'z') {
                letter = (char) ((letter - 'a' - shift + 26) % 26 + 'a');
            } else if (letter >= 'A' && letter <= 'Z') {
                letter = (char) ((letter - 'A' - shift + 26) % 26 + 'A');
            }

            decryptedFile.write(letter);
            System.out.print(letter);
        }
        readEncrypted.close();
        decryptedFile.close();
        System.out.println("\nDecrypted version is been saved as decrypted.txt");

        scanner.close();
    }
}

