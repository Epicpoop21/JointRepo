void main() {
    ArrayList<Integer> list = DataProcessor.InputValues();
    int maxValue = DataProcessor.CalculateMax(list);
    float mean = DataProcessor.CalculateMean(list);
    DataProcessor.OutputValues(list, mean, maxValue);
}
