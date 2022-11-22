//
// Alonso Cardenas Sillas | 9/6 - Changes made
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <time.h>

const int NUM_SAMPLES = 150;
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

template <size_t w_i>
void printStatus(int iteration, double (&weights)[w_i], double error, int correct){
    std::cout << "Iteration ";
    std::cout << iteration;
    std::cout << ": Weights are [";
    for ( int i = 0; i < w_i; i++) {
        std::cout << weights[i];
    }
    std::cout << "], classification was ";
    if (error > 0.1 || error < -0.1) { //floating point fix
        std::cout << "ERROR!";
    } else {
        std::cout << "CORRECT!";
    }
    std::cout << std::endl;
    std::cout << "Correct " << correct << "out of 150" << std::endl;
}

template <size_t w_i, size_t x_i>
double updateWeights(double (&weights)[w_i], double alpha, double (&input)[x_i], double error) {
    for (int i = 0; i < w_i; i++) {
        weights[i] = weights[i] + (alpha * input[i] * error); 
    }
}

template <size_t attr_rows, size_t x_i, size_t w_i>
void perceptron(double(&attributes)[attr_rows][x_i], double(&weights)[w_i], double theta, double alpha) {
    // for loop which classifies each element in array using if statement
    //iterations 
    int maxCorrect = 0;
    int error=0;
    for (int i = 0; i < attr_rows; i++) {
        double isIris = 0;
        double inputs[x_i-1];
        double sum[attr_rows];
        //std::array<int,4> A = {10,20,30,40};
        //std::array<int,4> B = A;
        // values and weights
        for (int j = 0; j < x_i-1; j++) {
            inputs[j] = attributes[i][j];
            // sum x_i * w_i
            sum[i] += inputs[j] * weights[j];
        }
        
        // if true, then Iris Virginica else NOT Iris
        isIris = (sum[i] > theta) ? 1.0 : -1.0;
        
        //error will be either 1 or 0
        double output = attributes[i][4] - isIris;
        if (output > 0.1 || output < -0.1) {error = 1;} else {error = 0; maxCorrect++;}
        printStatus(i, weights, error, maxCorrect);
        updateWeights(weights, alpha, inputs, error);
    }
    
}

double init() {
    double result = (rand()%11/10.0)-0.5; //get a number between -0.5 and 0.5
    return result;
}

int main(int argc, char* argv[])
{
	// Your code here
    srand(time(0)); 
    // [0-151:line][0:SepalLen, 1:SepalWid, 2:PetalLen, 3:PetalWid, 4:Species]
    double data[NUM_SAMPLES][5]; 
    double label; // Iris Virginica = 1 // NOT Iris Virginica = -1 
    double threshold; 
    double learning = 0.05; 

    // set weights to random numbers from -0.5 to 0.5
    double weights[4] = {init(), init(), init(), init()}; 
    double predicted_labels[NUM_SAMPLES][2]; 

    double thresholdResult_pair[2]; //[threshold, percent_correct]


    // Use readCSV to create data array
    readCSV(data, "iris-2.csv");
	// displayValues
    std::cout << "\n---ground truths---\n" << std::endl;
    displayValues(data);
    /*
    for (threshold = 0.0; threshold < 10; threshold += 0.1) {
        double correct = 0.0;
        double percent_correct = 0.0;

        // for loop which classifies each element in array using if statement
        */
        perceptron(data, weights, threshold, learning);
        /*
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

        if (thresholdResult_pair[1] < correct) {
            thresholdResult_pair[1] = correct;
            thresholdResult_pair[0] = threshold;
        }
        std::cout << out << std::endl;
        std::cout << "\n---\nMost correct: "<< thresholdResult_pair[1] << std::endl;
        std::cout << "\n---\nBest threshold: "<< thresholdResult_pair[0] << std::endl;
    } 
    */
    return 0;
}
