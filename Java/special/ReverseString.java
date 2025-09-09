public class ReverseString {
    // Using loop
    static String reverseLoop(String str) {
        String rev = "";
        for (int i = str.length() - 1; i >= 0; i--) {
            rev += str.charAt(i);
        }
        return rev;
    }

    // Using recursion
    static String reverseRecursion(String str) {
        if (str.isEmpty())
            return str;
        return reverseRecursion(str.substring(1)) + str.charAt(0);
    }

    public static void main(String[] args) {
        String str = "hello";
        System.out.println("Reverse (loop): " + reverseLoop(str));
        System.out.println("Reverse (recursion): " + reverseRecursion(str));
    }
}

