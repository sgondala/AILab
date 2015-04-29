#include "training.hpp"
#include "encoding.h"
#include <sstream>
#include <fstream>
#define ETA 0.00000002L
#define LONGEST 28

int main(){
	initialize(LONGEST * 8, LONGEST * 8, LONGEST * 8);
	std::ifstream fp;
	fp.open("outer2.txt");
	std::string line, firstWord;
	int examplesRead;
	for(int i = 0; i < noOutputNeurons; i++){
		outerdelta[i] = 0;
	}
	int descentSteps = 0;
	while(descentSteps++ < 80){
		examplesRead = 0;
		while(getline(fp, line)){
			std::istringstream iss(line);
			iss >> firstWord;
			inputValues = encodeGraphemes(firstWord, LONGEST);
			feedForward();
			actualOutputs = encodePhonemes(line.substr(firstWord.size() + 2), LONGEST);
			// if(firstWord == "AB"){
			// 	for(unsigned int i = 0; i < inputValues.size(); i++){
			// 		std::cout << inputValues[i];
			// 	}
			// 	std::cout << std::endl;

			// 	for(unsigned int i = 0; i < actualOutputs.size(); i++){
			// 		std::cout << actualOutputs[i];
			// 	}
			// 	std::cout << std::endl;

			// }
			for(int i = 0; i < noOutputNeurons; i++){
				outerdelta[i] += (outerOutputs[i] - actualOutputs[i]) * outerOutputs[i] * (1 - outerOutputs[i]);
			}
			if(examplesRead == 4000) break;
			examplesRead++;
//			std::cout << examplesRead << std::endl;
		}
		updateWeights(ETA);
		long double J = 0;
		while(getline(fp, line)){
			std::istringstream iss(line);
			iss >> firstWord;
			inputValues = encodeGraphemes(firstWord, LONGEST);
/*			if(firstWord == "ABARE"){
				for(unsigned int i = 0; i < inputValues.size(); i++){
					std::cout << inputValues[i];
				}
				std::cout << std::endl;
			}*/
			feedForward();
			actualOutputs = encodePhonemes(line.substr(firstWord.size() + 2), LONGEST);
			for(int i = 0; i < noOutputNeurons; i++){
				J += 0.5 * (actualOutputs[i] - outerOutputs[i]) * (actualOutputs[i] - outerOutputs[i]);
			}
			examplesRead++;
			if(examplesRead == 4350) break;
		}
		std::cout << J << std::endl;
//		fseek(fp, 0, SEEK_SET);
		fp.seekg(0, fp.beg);
	}
	std::string string;
	std::cin >> string;
	inputValues = encodeGraphemes(string, LONGEST);
	feedForward();
	std::vector<unsigned int> v;
	for(unsigned int i = 0; i < outerOutputs.size(); i++){
		v.push_back((outerOutputs[i] >= 0.5) ? 1 : 0);
	}
	std::cout << decodePhonemes(&v) << std::endl;
}
