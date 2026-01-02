#include <iostream>
#include <vector>

std::vector<unsigned int> InputValues();
void OutputValues(std::vector<unsigned int>& numList, int maxValue, float mean);
float CalcMean(std::vector<unsigned int>& numList);
int CalcMax(std::vector<unsigned int>& numList);
void StartLoop();

int main() {
	StartLoop();
}

std::vector<unsigned int> InputValues()
{
	std::vector<unsigned int> numList;
	int inputBuffer = 0;

	//Loops and adds values inputted to the vector
	while (true) {
		std::cout << "Enter number: ";
		std::cin >> inputBuffer;

		//Break out of loop is values is udner 0
		if (inputBuffer < 0) {
			break;	
		}

		numList.push_back(inputBuffer);
	}
	return numList;
}

void OutputValues(std::vector<unsigned int>& numList, int maxValue, float mean)
{
	//Outputs the values
	std::cout << "\n";
	std::cout << "Values to be calculated are: ";
	int i = 0;
	for (int value : numList) {
		if (i == numList.size() - 1) {
			std::cout << value;
		}
		else {
			std::cout << value << ", ";
		}
		i++;
	}
	std::cout << "\n \n";
	std::cout << "Maximum values is: " << maxValue << "\n";
	std::cout << "Mean of the values is: " << mean << "\n";
}

float CalcMean(std::vector<unsigned int>& numList)
{
	//Adds all values together and divides by number of values
	float total = 0;
	for (int num : numList) {
		total += num;
	}
	return total / numList.size();
}

int CalcMax(std::vector<unsigned int>& numList)
{
	//Loops through all values and sees if each value is bigger
	int max = 0;
	for (int num : numList) {
		if (num > max) {
			max = num;
		}
	}
	return max;
}

void StartLoop()
{
	std::string runningAgain;
	while (true) {
		std::vector<unsigned int> numList = InputValues();

		int maxValue = CalcMax(numList);
		float mean = CalcMean(numList);

		OutputValues(numList, maxValue, mean);

		std::cout << "Do you want to run again? [Y/n] ";
		std::cin >> runningAgain;
		;
		if (std::tolower(runningAgain[0]) == 'n') {
			break;
		}
	}
}
