public class WordCount {
    public static void main(String[] args) {
        String str = "Java is a powerful language";
        String[] words = str.trim().split("\\s+");
        System.out.println("Word count: " + words.length);
    }
}

