#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
extern std::vector<long double> outerOutputs;
extern std::vector<unsigned int> inputValues;
extern std::vector<unsigned int> actualOutputs;
void initialize(int, int, int);
void feedForward();
void updateWeights(long double);
extern int noInputNeurons;
extern int noHiddenNeurons;
extern int noOutputNeurons; //currently this only supports 1 hidden layer.
extern std::vector<long double> outerdelta;
