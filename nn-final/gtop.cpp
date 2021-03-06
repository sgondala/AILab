#include <bits/stdc++.h>

using namespace std;

int graphemeLength = 5;
int phonemeLength = 7;
int noInputNeurons;
int noHiddenNeurons;
int noOutputNeurons; //currently this only supports 1 hidden layer.
long double eta = 0.1;
int numLength = 28;

std::vector<long double> weights1;
std::vector<long double> weights2;
std::vector<long double> hiddenOutput;
std::vector<long double> outerOutput;
std::vector<int> input;

std::map<char, std::vector<int> > EncodeGrapheme;
std::map<string, std::vector<int> > EncodePhoneme;
std::map<std::vector<int>, char > DecodeGrapheme;
std::map<std::vector<int>, string > DecodePhoneme;

std::vector<long double> outerDelta;
std::vector<long double> hiddenDelta;
std::vector<int> actualOutput;

std::vector<int> intToBinary(int n, int length) {
	std::vector<int> ret;
	while(true) {
		if(n==1 || n==0) {
			ret.push_back(n);
			while(ret.size() != length) ret.push_back(0);
			reverse(ret.begin(), ret.end());
			return ret;
		}
		if(n%2 == 0) {
			ret.push_back(0);
			n = n/2;
		}
		else {
			ret.push_back(1);
			n = n/2;
		}		
	}
}


void initialize() {
	int i = 1;
	for(char c='A'; c<='Z'; c++) {
		std::vector<int> v = intToBinary(i, graphemeLength);
		EncodeGrapheme[c] = v;
		DecodeGrapheme[v] = c;
		i++;
	}

	i=1;
	ifstream ifs("states.txt");
	string line;
	while(getline(ifs,line)){
		std::vector<int> v = intToBinary(i, phonemeLength);
		EncodePhoneme[line] = v;
		DecodePhoneme[v] = line;
		i++;
	}

	noInputNeurons = graphemeLength*numLength;
	noOutputNeurons = phonemeLength*numLength;
	noHiddenNeurons = (noInputNeurons + noOutputNeurons)/2;

	weights1 = std::vector<long double>(noInputNeurons*noHiddenNeurons);
	weights2 = std::vector<long double>(noHiddenNeurons*noOutputNeurons);
	outerOutput = std::vector<long double>(noOutputNeurons);
	hiddenOutput = std::vector<long double>(noHiddenNeurons);
	outerDelta = std::vector<long double>(noOutputNeurons);
	hiddenDelta = std::vector<long double>(noHiddenNeurons);

	ifstream if1("gtop-weights.txt");
	for(int i = 0; i < noInputNeurons * noHiddenNeurons; i++){
		getline(if1,line);
		weights1[i] = stof(line);
		// weights1[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand() + 1);
		// cout << weights1[i] << endl;
	}
	for(int i = 0; i < noOutputNeurons * noHiddenNeurons; i++){
		getline(if1,line);
		weights2[i] = stof(line);
		// cout << line << " " << weights2[i] << endl;
		// weights2[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand() + 1);
	}
}

void feedForward() {// input vector should be set before calling this
	for (int i = 0; i < noHiddenNeurons; ++i)
	{
		long double tmp = 0L;
		for (int j = 0; j < noInputNeurons; ++j)
		{
			tmp += weights1[i*noInputNeurons + j] * input[j];
		}
		long double tmp1 = exp(-tmp);
		hiddenOutput[i] = 1L/(1L + tmp1);
		// cout << i << " " << hiddenOutput[i] << endl;
		// printf("%.9lf\n", (double)tmp1);
	}

	for (int i = 0; i < noOutputNeurons; ++i)
	{
		long double tmp = 0L;
		for (int j = 0; j < noHiddenNeurons; ++j)
		{
			tmp += weights2[i*noHiddenNeurons + j] * hiddenOutput[j];
		}
		long double tmp1 = exp(-tmp);
		outerOutput[i] = 1L/(1L + tmp1);
		// cout << i << " " << outerOutput[i] << endl;
	}
}

int main() {
	srand (time(NULL));
	initialize();
	string firstWord;
	while(true) {
	cout << "Give input\n";
	cin >> firstWord; 

	std::vector<int> v1, tmpVec;
	for (int i = 0; i < firstWord.size(); ++i)
	{
		tmpVec = EncodeGrapheme[firstWord[i]];
		v1.insert(v1.end(), tmpVec.begin(), tmpVec.end());
	}
	int j = firstWord.size();
	tmpVec = std::vector<int>(graphemeLength, 0);
	while(j!=numLength) {
		v1.insert(v1.end(), tmpVec.begin(), tmpVec.end());
		j++;
	}
	// for (std::vector<int>::iterator i = v1.begin(); i != v1.end(); ++i)
	// {
	// 	cout << *i;
	// }
	// cout << endl;

	input = v1;

	feedForward();

	for (int i = 0; i < firstWord.size(); ++i)
	{
		std::vector<int> output;
		for (int j = 0; j < phonemeLength; ++j)
		{
			int index = i*phonemeLength + j;
			output.push_back(((outerOutput[index]) >= 0.5) ? 1 : 0);
		}
		// for (int j = 0; j < output.size(); ++j)
		// {
		// 	cout << output[j];
		// }
		// cout << endl;
		if(DecodePhoneme.count(output) == 0) {			
			output[0] = 0;
			if(DecodePhoneme.count(output) == 0) output[0] = 1;
		}
		cout << DecodePhoneme[output] << endl;
	}
	cout << endl;
		
	}
}