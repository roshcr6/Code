public class FirstNonRepeating {
    public static void main(String[] args) {
        String str = "swiss";

        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (str.indexOf(c) == str.lastIndexOf(c)) {
                System.out.println("First non-repeating character: " + c);
                return;
            }
        }
        System.out.println("No unique character found.");
    }
}

