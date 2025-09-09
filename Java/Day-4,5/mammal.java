class Animal {
    public int age;
    public Animal(int a) {
        age = a;
    }}
    
class Herbivore extends Animal {
    private String type;
    public Herbivore(int a, String t) {
        super(a);
        type = t;
    }
    
    public void displayDetails() {
        System.out.println("Type: " + type);
        System.out.println("Age: " + age);
        System.out.println("Diet: Herbivore");
    }
}

class Carnivore extends Animal {
    private String type;
    public Carnivore(int a, String t) {
        super(a);
        type = t;
    }
    
    public void displayDetails() {
        System.out.println("Type:" + type);
        System.out.println("Age: " + age);
        System.out.println("Diet: Carnivore");
    }}
    
public class mammal {
    public static void main(String[] args) {
        Herbivore deer = new Herbivore(3, "Deer");
        Carnivore tiger = new Carnivore(5, "Tiger");

        System.out.println("--- Herbivore Detils ---");
        deer.displayDetails();

        System.out.println("\n--- Carnivore Details ---");
        tiger.displayDetails();
    }
 }

