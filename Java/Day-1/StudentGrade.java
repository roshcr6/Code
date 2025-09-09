import java.util.Scanner;
public class StudentGrade {
	public static void main (String[] args){
	Scanner sc= new Scanner(System.in);
	System.out.println("Enter The Marks For Subject 1 :");
	int num1 = sc.nextInt();
	System.out.println("Enter The Marks For Subject 2 :");
	int num2 = sc.nextInt();
	System.out.println("Enter The Marks For Subject 3 :");
	int num3 = sc.nextInt();
	System.out.println("Enter The Marks For Subject 4 :");
	int num4 = sc.nextInt();
	System.out.println("Enter The Marks For Subject 5 :");
	int num5 = sc.nextInt();
	int total = num1+num2+num3+num4+num5;
	double percentage = total/5.0;
	System.out.println("Total Marks ="+ total );
	System.out.println("Percentage ="+ percentage );
	if(percentage>=90)
	System.out.println("Grade A+");
	else if(percentage>=80)
	System.out.println("Grade A");
	else if(percentage>=70)
	System.out.println("Grade B");
	else if(percentage>=60)
	System.out.println("Grade C");
	else if(percentage>=50)
	System.out.println("Grade D");
	else
	System.out.println("Failure");
	}
	}
	
