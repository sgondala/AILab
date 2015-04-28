#include "training.hpp"
int noInputNeurons;
int noHiddenNeurons;
int noOutputNeurons; //currently this only supports 1 hidden layer.

std::vector<long double> weightsih;
std::vector<long double> weightsho;
std::vector<long double> hiddenOutputs;
std::vector<long double> outerOutputs;
std::vector<unsigned int> inputValues;
std::vector<long double> outerdelta;
std::vector<long double> hiddendelta;
std::vector<unsigned int> actualOutputs;


void initialize(int a, int b, int c){
	noInputNeurons = a;
	noHiddenNeurons = b;
	noOutputNeurons = c;
	weightsih = std::vector<long double>(noInputNeurons * noHiddenNeurons);
	weightsho = std::vector<long double>(noHiddenNeurons * noOutputNeurons);
	hiddenOutputs = std::vector<long double>(noHiddenNeurons);
	outerOutputs = std::vector<long double>(noOutputNeurons);
	outerdelta = std::vector<long double>(noOutputNeurons);
	hiddendelta = std::vector<long double>(noHiddenNeurons);
	for(int i = 0; i < noInputNeurons * noHiddenNeurons; i++){
		weightsih[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand() + 1);
	}
	for(int i = 0; i < noOutputNeurons * noHiddenNeurons; i++){
		weightsho[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand() + 1);
	}
}


void feedForward(){//by this time, appropriate values must have been put into weightsih, weightsho, inputValues
	long double totalOutput;
	for(int i = 0; i < noHiddenNeurons; i++){
		totalOutput = 0L;
		for(int j = 0; j < noInputNeurons; j++){
			totalOutput += weightsih[(i * noInputNeurons) + j] * inputValues[j];
		}
		hiddenOutputs[i] = 1L/(1 + exp(-totalOutput));
	}
	for(int i = 0; i < noOutputNeurons; i++){
		totalOutput = 0L;
		for(int j = 0; j < noHiddenNeurons; j++){
			totalOutput += weightsho[(i * noHiddenNeurons) + j] * hiddenOutputs[j];
		}
//		outerOutputs[i] = ((1L/(1 + exp(-totalOutput)) >= 0.5) ? 1 : 0);
		outerOutputs[i] = 1L/(1 + exp(-totalOutput));
	}
}


void updateWeights(long double eta){//by this time, feedForward must have been done and actualOutputs must be ready. It must contain only 0s and 1s
//	for(int i = 0; i < noOutputNeurons; i++){
//		outerdelta[i] = (outerOutputs[i] - actualOutputs[i]) * outerOutputs[i] * (1 - outerOutputs[i]);
//	}
	long double averageChange = 0;
	for(int i = 0; i < noHiddenNeurons; i++){
		hiddendelta[i] = 0;
		for(int j = 0; j < noOutputNeurons; j++){
			hiddendelta[i] += (outerdelta[j] * weightsho[j * noHiddenNeurons + i] * hiddenOutputs[i] * (1 - hiddenOutputs[i]));
		}
	}
	for(int j = 0; j < noHiddenNeurons; j++){
		for(int i = 0; i < noInputNeurons; i++){
			weightsih[j * noInputNeurons + i] -= (eta * hiddendelta[j] * hiddenOutputs[i]);
			averageChange += (eta * hiddendelta[j] * inputValues[i]);
		}
	}
	for(int j = 0; j < noOutputNeurons; j++){
		for(int i = 0; i < noHiddenNeurons; i++){
			weightsho[j * noHiddenNeurons + i] -= (eta * outerdelta[j] * outerOutputs[i]);
			averageChange += (eta * outerdelta[j] * hiddenOutputs[i]);
		}
	}
	std::cout << "average change is " << averageChange << std::endl;
}
