import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class PerfectNumberChecker extends Application {

    @Override
    public void start(Stage stage) {
        stage.setTitle("Perfect Number Checker");

        Label l1 = new Label("Enter Number:");
        TextField inputField = new TextField();

        Label l2 = new Label("Result:");
        TextField resultField = new TextField();
        resultField.setEditable(false);

        Button checkBtn = new Button("Check");

        GridPane grid = new GridPane();
        grid.setPadding(new Insets(15));
        grid.setHgap(10);
        grid.setVgap(10);
        grid.add(l1, 0, 0);
        grid.add(inputField, 1, 0);
        grid.add(l2, 0, 1);
        grid.add(resultField, 1, 1);
        grid.add(checkBtn, 1, 2);


        checkBtn.setOnAction(e -> {
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
        });

        Scene scene = new Scene(grid, 350, 150);
        stage.setScene(scene);
        stage.show();
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
        launch(args);
    }
}

    //java --module-path /home/s3csd/Downloads/openjfx-21.0.8_linux-x64_bin-sdk/javafx-sdk-21.0.8/lib --add-modules javafx.controls PerfectNumberChecker.java
