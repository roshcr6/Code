public class EqualIgnoreCase {
    public static void main(String[] args) {
        String s1 = "Java";
        String s2 = "java";

        if (s1.equalsIgnoreCase(s2))
            System.out.println("Strings are equal (ignoring case)");
        else
            System.out.println("Strings are not equal");
    }
}

