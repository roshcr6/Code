public class StringCompare {
    public static void main(String[] args) {
        String s1 = "Java";
        String s2 = "java";

        // With equals()
        if (s1.equals(s2))
            System.out.println("Strings are equal");
        else
            System.out.println("Strings are not equal");

        // Without equals() (manual check)
        boolean isEqual = true;
        if (s1.length() != s2.length()) {
            isEqual = false;
        } else {
            for (int i = 0; i < s1.length(); i++) {
                if (s1.charAt(i) != s2.charAt(i)) {
                    isEqual = false;
                    break;
                }
            }
        }
        System.out.println("Manual check: " + (isEqual ? "Equal" : "Not equal"));
    }
}

