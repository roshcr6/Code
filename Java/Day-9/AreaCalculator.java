import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class AreaCalculator extends JFrame implements ActionListener {
    private JComboBox<String> shapeList;
    private JTextField tf1, tf2, resultField;
    private JLabel l1, l2;
    private JButton calculateBtn;

    public AreaCalculator() {
        setTitle("Area Calculator");
        setSize(350, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        shapeList = new JComboBox<>(new String[]{"Circle", "Rectangle", "Triangle"});
        l1 = new JLabel("Value 1:");
        l2 = new JLabel("Value 2:");
        tf1 = new JTextField();
        tf2 = new JTextField();
        resultField = new JTextField();
        resultField.setEditable(false);
        calculateBtn = new JButton("Calculate");
        
        add(new JLabel("Shape:"));
        add(shapeList);
        add(l1);
        add(tf1);
        add(l2);
        add(tf2);
        add(new JLabel(""));
        add(calculateBtn);
        add(new JLabel("Area:"));
        add(resultField);

        shapeList.addActionListener(this);
        calculateBtn.addActionListener(this);
        tf2.setVisible(false);
        l2.setVisible(false);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == shapeList) {
            String shape = (String) shapeList.getSelectedItem();
            if (shape.equals("Circle")) {
                l1.setText("Radius:");
                l2.setVisible(false);
                tf2.setVisible(false);
            } else if (shape.equals("Rectangle")) {
                l1.setText("Length:");
                l2.setText("Breadth:");
                l2.setVisible(true);
                tf2.setVisible(true);
            } else {
                l1.setText("Base:");
                l2.setText("Height:");
                l2.setVisible(true);
                tf2.setVisible(true);
            }
        } else if (e.getSource() == calculateBtn) {
            try {
                String shape = (String) shapeList.getSelectedItem();
                double v1 = Double.parseDouble(tf1.getText());
                double area = 0;
                if (shape.equals("Circle")) {
                    area = Math.PI * v1 * v1;
                } else {
                    double v2 = Double.parseDouble(tf2.getText());
                    if (shape.equals("Rectangle")) {
                        area = v1 * v2;
                    } else if (shape.equals("Triangle")) {
                        area = 0.5 * v1 * v2;
                    }
                }
                resultField.setText(String.valueOf(area));
            } catch (NumberFormatException ex) {
                resultField.setText("Invalid Input");
            } catch (Exception ex) {
                resultField.setText("Error: " + ex.getMessage());
            }
        }
    }

    public static void main(String[] args) {
        new AreaCalculator().setVisible(true);
    }
}
