//
// Alonso Cardenas Sillas | 9/6 - Changes made
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

/*
*	Function that reads data from a CSV into a 2-D array.
*/
template <size_t rows, size_t cols>
void readCSV(double(&array)[rows][cols], char* filename) {
	std::ifstream file(filename);
    
	std::string format;
	std::getline(file, format); //get rid of the first line

	for (size_t row = 0; row < rows; ++row)
	{
		std::string line;
		std::getline(file, line);

		if (!file.good())
			break;

		std::stringstream iss(line);

		for (size_t col = 0; col < cols; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');

			std::stringstream convertor(val);
			convertor >> array[row][col];
		}
	}
}

/*
*	Function that displays data values
*/
template <size_t rows, size_t cols>
void displayValues(double(&array)[rows][cols]) {
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; col++) {
			std::cout << array[row][col] << ' ';
		}

		std::cout << std::endl;
	}
}


int main(int argc, char* argv[])
{
	// Your code here
    const int NUM_SAMPLES = 150;
    //[0-151:line][0:SepalLen, 1:SepalWid, 2:PetalLen, 3:PetalWid, 4:Species]
    double data[NUM_SAMPLES][5];
    double label; // Iris Virginica = 1 // NOT Iris Virginica = -1 
    double threshold_value;
    double predicted_labels[NUM_SAMPLES][2];

    double thresholdResult_pair[2]; //[threshold_value, percent_correct]


    // Use readCSV to create data array
    readCSV(data, "iris-2.csv");
	// displayValues
    std::cout << "\n---ground truths---\n" << std::endl;
    displayValues(data);

    for (threshold_value = 0.0; threshold_value < 10; threshold_value += 0.1) {
        double correct = 0.0;
        double percent_correct = 0.0;
    
        // for loop which classifies each element in array using if statement
        for (int i = 0; i < NUM_SAMPLES; i++) {
            double petal_length = data[i][2];
            label = (petal_length > threshold_value) ? 1.0:-1.0 ;
            predicted_labels[i][0] = petal_length;
            predicted_labels[i][1] = label;
        }
        
        //std::cout << "\n---predicted labels---\n" << std::endl;
        //displayValues(predicted_labels);
        
        // compare predicted class with groundtruth.

        for (int i = 0; i < NUM_SAMPLES; i++){
            if ( predicted_labels[i][1] == data[i][4] ) {
                correct++;
            }
        }
        
        std::cout << "\n---\ncorrect: " << correct << std::endl;
        percent_correct = (correct / NUM_SAMPLES) * 100; 
        std::cout << percent_correct << "\% correct" << std::endl;

        if (thresholdResult_pair[1] < percent_correct) {
            thresholdResult_pair[1] = percent_correct;
            thresholdResult_pair[0] = threshold_value;
        }
        std::cout << "\n---\nBest threshold: "<< thresholdResult_pair[0] << std::endl;

    } 
    return 0;
}