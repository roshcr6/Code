import java.util.Scanner;
public class attendance {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.print("Total students: ");
        int total=sc.nextInt();
        System.out.print("Present attended: ");
        int n=sc.nextInt();
        int[] attended=new int[n];
        System.out.println("Enter roll numbers:");
        for(int i=0;i<n;i++) 
        attended[i]=sc.nextInt();
        System.out.print("Check roll number: ");//checking checking tring tring
        int roll=sc.nextInt();
        boolean found=false;
        for(int i=0;i<n;i++) 
        if(attended[i]==roll) 
        found=true;
        if (found)
        System.out.println("Student attended.");
        else 
        System.out.println("Student absent.");
        for(int i=0;i<n-1;i++)//sort sort bubbling sort
            for(int j=0;j<n-1-i;j++)
                if(attended[j]>attended[j+1]){
                    int t=attended[j];
                    attended[j]=attended[j+1];
                    attended[j+1]=t;
                }
        System.out.print("Sorted attendance: ");
        for(int i=0;i<n;i++) 
        System.out.print(attended[i]+" ");
        int m = total-n;
        System.out.print("Total number of absentees :"+ m);//bumkers list
        System.out.println("\nAbsentees: ");
        for(int i=1;i<=total;i++){
            boolean present=false;
            for(int j=0;j<n;j++) 
            if(attended[j]==i) 
            present=true;
            if(!present) 
            System.out.print(i+" ");
        }
        
    }
}

