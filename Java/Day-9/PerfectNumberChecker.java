import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PerfectNumberChecker extends JFrame implements ActionListener {
    JTextField inputField, resultField;
    JButton checkBtn;

    public PerfectNumberChecker() {
        setTitle("Perfect Number Checker");
        setSize(350, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(3, 2));

        inputField = new JTextField();
        resultField = new JTextField();
        resultField.setEditable(false);
        checkBtn = new JButton("Check");

        add(new JLabel("Enter Number:"));
        add(inputField);
        add(new JLabel("Result:"));
        add(resultField);
        add(new JLabel());
        add(checkBtn);

        checkBtn.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        try {
            int num = Integer.parseInt(inputField.getText());
            if (num <= 0) {
                resultField.setText("Enter a positive number");
                return;
            }
            if (isPerfect(num)) {
                resultField.setText(num + " is a perfect number");
            } else {
                resultField.setText("Sum of digits: " + sumDigits(num));
            }
        } catch (NumberFormatException ex) {
            resultField.setText("Invalid Input");
        }
    }

    private boolean isPerfect(int n) {
        int sum = 0;
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) sum += i;
        }
        return sum == n;
    }

    private int sumDigits(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

    public static void main(String[] args) {
        new PerfectNumberChecker().setVisible(true);
    }
}
