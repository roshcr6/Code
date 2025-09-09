import java.util.*;
abstract class Employee {
    String name;
    int employeeId;
    double salary;

    Employee(String name, int employeeId, double salary) {
        this.name = name;
        this.employeeId = employeeId;
        this.salary = salary;
    }

    abstract double calculateBonus();
    abstract void displayInfo();
    public abstract String toString();
}

class Manager extends Employee {
    int teamSize;

    Manager(String name, int employeeId, double salary, int teamSize) {
        super(name, employeeId, salary);
        this.teamSize = teamSize;
    }

    @Override
    double calculateBonus() {
        return salary * 0.10;
    }

    @Override
    void displayInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return "Manager: " + name + " | ID: " + employeeId + " | Salary: " + salary + " | Team Size: " + teamSize;
    }
}

class Developer extends Employee {
    List<String> programmingLanguages;

    Developer(String name, int employeeId, double salary, List<String> programmingLanguages) {
        super(name, employeeId, salary);
        this.programmingLanguages = programmingLanguages;
    }

    @Override
    double calculateBonus() {
        return salary * 0.12;
    }

    @Override
    void displayInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return "Developer: " + name + " | ID: " + employeeId + " | Salary: " + salary + " | Languages: " + programmingLanguages;
    }

    void assignTask(String task) {
        System.out.println("Assigning task '" + task + "' to Developer " + name);
    }

    void assignTask(String task, int hours) {
        System.out.println("Assigning task '" + task + "' for " + hours + " hours to Developer " + name);
    }
}


class Intern extends Employee {
    int duration; 
    Intern(String name, int employeeId, double salary, int duration) {
        super(name, employeeId, salary);
        this.duration = duration;
    }

    @Override
    double calculateBonus() {
        return 0; 
    }

    @Override
    void displayInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return "Intern: " + name + " | ID: " + employeeId + " | Salary: " + salary + " | Duration: " + duration + " months";
    }
}

class SeniorManager extends Manager {
    double stockOptions;

    SeniorManager(String name, int employeeId, double salary, int teamSize, double stockOptions) {
        super(name, employeeId, salary, teamSize);
        this.stockOptions = stockOptions;
    }

    @Override
    double calculateBonus() {
        return salary * 0.15 + stockOptions;
    }

    @Override
    void displayInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return "Senior Manager: " + name + " | ID: " + employeeId + " | Salary: " + salary +
                " | Team Size: " + teamSize + " | Stock Options: " + stockOptions;
    }
}

class JuniorDeveloper extends Developer {
    String mentor;

    JuniorDeveloper(String name, int employeeId, double salary, List<String> programmingLanguages, String mentor) {
        super(name, employeeId, salary, programmingLanguages);
        this.mentor = mentor;
    }

    @Override
    double calculateBonus() {
        return salary * 0.08;
    }

    @Override
    void displayInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return "Junior Developer: " + name + " | ID: " + employeeId + " | Salary: " + salary +
                " | Languages: " + programmingLanguages + " | Mentor: " + mentor;
    }
}

public class CompanyRoles {
    public static void main(String[] args) {


        Manager mgr = new Manager("Noel", 101, 98000, 5);
        Developer dev = new Developer("Norah", 102, 72000, Arrays.asList("Java", "Python"));
        Intern intern = new Intern("Riyan", 103, 15000, 6);
        SeniorManager srMgr = new SeniorManager("Sana", 104, 70000, 10, 5000);
        JuniorDeveloper jrDev = new JuniorDeveloper("Roshni", 105, 60000, Arrays.asList("Python"), "Norah");


        Employee[] employees = {mgr, dev, intern, srMgr, jrDev};
        for (Employee emp : employees) {
            emp.displayInfo();
            System.out.println("Bonus: ₹" + emp.calculateBonus());
            System.out.println("--------------------------------------------------");
        }


        dev.assignTask("Implement Feature X");
        dev.assignTask("Fix UI Bug", 4);
    }
}

