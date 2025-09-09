import java.util.Scanner;

public class matrix {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter the number of rows: ");
        int rows = sc.nextInt();
        System.out.print("Enter the number of columns: ");
        int cols = sc.nextInt();
        
        int firstMatrix[][] = new int[rows][cols];
        int secondMatrix[][] = new int[rows][cols];
        int sum[][] = new int[rows][cols];
        int transpose[][] = new int[cols][rows];
        
        System.out.println("Enter the elements of the first matrix:");//1st Matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                firstMatrix[i][j] = sc.nextInt();
            }
        }
        
        System.out.println("First matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                
                System.out.print(firstMatrix[i][j] + "\t"); }
            System.out.println();
        }
        
        System.out.println("Enter the elements of the second matrix:");//2nd Matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                secondMatrix[i][j] = sc.nextInt();
            }
        }
        
        System.out.println("Second matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
               
                System.out.print(secondMatrix[i][j] + "\t"); }
            System.out.println();
        }
        
        System.out.println("Sum of the matrices:");//matrix sum
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sum[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
                System.out.print(sum[i][j] + "\t"); }
            System.out.println();
        }
        
        System.out.println("Transpose of the sum matrix:");//transpose matrix
        for (int a = 0; a < cols; a++) { 
            for (int j = 0; j < rows; j++) {
                transpose[a][j] = sum[j][a];
                System.out.print(transpose[a][j] + "\t"); 
            }
            System.out.println();
        }
        
        sc.close();
    }
  }
