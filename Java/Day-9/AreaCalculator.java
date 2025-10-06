import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class AreaCalculator extends Application {

    private ComboBox<String> shapeList;
    private TextField tf1, tf2, resultField;
    private Label l1, l2;

    @Override
    public void start(Stage stage) {
        stage.setTitle("Area Calculator");

        shapeList = new ComboBox<>();
        shapeList.getItems().addAll("Circle", "Rectangle", "Triangle");
        shapeList.setValue("Circle");

        l1 = new Label("Radius:");
        l2 = new Label("Value 2:");
        tf1 = new TextField();
        tf2 = new TextField();
        tf2.setVisible(false);
        l2.setVisible(false);

        resultField = new TextField();
        resultField.setEditable(false);

        Button calculateBtn = new Button("Calculate");
        Button clearBtn = new Button("Clear");


        GridPane grid = new GridPane();
        grid.setPadding(new Insets(15));
        grid.setVgap(10);
        grid.setHgap(10);

        grid.add(new Label("Shape:"), 0, 0);
        grid.add(shapeList, 1, 0);
        grid.add(l1, 0, 1);
        grid.add(tf1, 1, 1);
        grid.add(l2, 0, 2);
        grid.add(tf2, 1, 2);
        grid.add(calculateBtn, 0, 3);
        grid.add(clearBtn, 1, 3);
        grid.add(new Label("Area:"), 0, 4);
        grid.add(resultField, 1, 4);

        shapeList.setOnAction(e -> {
            String shape = shapeList.getValue();
            switch (shape) {
                case "Circle" -> {
                    l1.setText("Radius:");
                    l2.setVisible(false);
                    tf2.setVisible(false);
                }
                case "Rectangle" -> {
                    l1.setText("Length:");
                    l2.setText("Breadth:");
                    l2.setVisible(true);
                    tf2.setVisible(true);
                }
                case "Triangle" -> {
                    l1.setText("Base:");
                    l2.setText("Height:");
                    l2.setVisible(true);
                    tf2.setVisible(true);
                }
            }
            tf1.clear();
            tf2.clear();
            resultField.clear();
        });

        calculateBtn.setOnAction(e -> {
            try {
                String shape = shapeList.getValue();
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

                resultField.setText(String.format("%.2f", area));
            } catch (NumberFormatException ex) {
                resultField.setText("Invalid Input");
            } catch (Exception ex) {
                resultField.setText("Error: " + ex.getMessage());
            }
        });


        clearBtn.setOnAction(e -> {
            tf1.clear();
            tf2.clear();
            resultField.clear();
        });

        Scene scene = new Scene(grid, 350, 250);
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
//javac --module-path /home/s3csd/Downloads/openjfx-21.0.8_linux-x64_bin-sdk/javafx-sdk-21.0.8/lib --add-modules javafx.controls AreaCalculator.java
