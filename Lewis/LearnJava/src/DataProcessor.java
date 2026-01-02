import java.util.ArrayList;
import java.util.Scanner;

public class DataProcessor {
    private static final Scanner scanner = new Scanner(System.in);

    public static ArrayList<Integer> InputValues() {
        ArrayList<Integer> list = new ArrayList<Integer>();
        while (true) {
            try {
                int value = Integer.parseInt(scanner.nextLine());
                if (value < 0) {
                    break;
                }
                list.add(value);
            } catch (NumberFormatException e) {
                System.out.println("Something went wrong- you probably inputted a non number");
            }
        }
        return list;
    }

    public static float CalculateMean(ArrayList<Integer> list) {
        float sumOfValues = 0;
        for (int value : list) {
            sumOfValues += value;
        }
        return sumOfValues / list.size();
    }

    public static int CalculateMax(ArrayList<Integer> list) {
        int maxValue = 0;
        for (int value : list) {
            if (maxValue < value) {
                maxValue = value;
            }
        }
        return maxValue;
    }

    public static void OutputValues(ArrayList<Integer> list, float mean, int maxValue) {
        System.out.print("Values: ");
        for (int value : list) {
            System.out.print(value + ", ");
        }
        System.out.println("\n");
        System.out.println("Maximum value is: " + maxValue);
        System.out.println("Mean is: " + mean);
    }
}
