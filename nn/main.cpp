#include <bits/stdc++.h>

using namespace std;

int graphemeLength = 5;
int phonemeLength = 7;
int noInputNeurons;
int noHiddenNeurons;
int noOutputNeurons; //currently this only supports 1 hidden layer.
long double eta = 0.5;
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

	for(int i = 0; i < noInputNeurons * noHiddenNeurons; i++){
		weights1[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand() + 1);
		// cout << weights1[i] << endl;
	}
	for(int i = 0; i < noOutputNeurons * noHiddenNeurons; i++){
		weights2[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand() + 1);
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
			tmp += weights2[i*noHiddenNeurons + noOutputNeurons] * input[j];
		}
		long double tmp1 = exp(-tmp);
		outerOutput[i] = 1L/(1L + tmp1);		
		// cout << i << " " << outerOutput[i] << endl;
	}
}

void calculateDelta() {
	for (int i = 0; i < noOutputNeurons; ++i)
	{
		outerDelta[i] = (actualOutput[i] - outerOutput[i])* outerOutput[i] * (1 - outerOutput[i]);
	}

	for (int i = 0; i < noHiddenNeurons; ++i)
	{
		long double tmp = 0;
		for (int j = 0; j < noOutputNeurons; ++j)
		{
			tmp += weights2[j*noHiddenNeurons + i] * outerDelta[j];
		}
		hiddenDelta[i] = tmp*hiddenOutput[i]*(1 - hiddenOutput[i]);
		// cout << i << " " << hiddenDelta[i] << endl;
	}
}

void updateWeights() {
	long double averageChange = 0;
	for (int i = 0; i < noHiddenNeurons; ++i)
	{
		for (int j = 0; j < noInputNeurons; ++j)
		{
			// cout << i << " 1 " << j << " " << weights1[i*noInputNeurons + j] << "\n";
			weights1[i*noInputNeurons + j] += eta * input[j] * hiddenDelta[i];
			// cout << i << " " << j << " ";
			// cout << input[j] << " " << hiddenDelta[i] << " " <<  weights1[i*noInputNeurons + j] << "\n";
			
			averageChange += eta * input[j] * hiddenDelta[i];
		// }
	}

	// for (int i = 0; i < noOutputNeurons; ++i)
	// {
		for (int j = 0; j < noHiddenNeurons; ++j)
		{
			weights2[i*noHiddenNeurons + j] += eta * hiddenOutput[j] * outerDelta[i];
			averageChange += eta * hiddenOutput[j] * outerDelta[i];
		}
	}

	// if(rand() % 10 == 0) 
	// cout << "averageChange: " << averageChange << endl;
}

int main() {
	srand (time(NULL));
	initialize();
	// std::vector<int> v = EncodePhoneme["AE1"];
	std::ifstream fp, fp1;
	fp.open("training.txt");
	fp1.open("testing.txt");
	std::string line, firstWord, phoneme;
	int examplesRead = 0;

	while(getline(fp, line)) {
		// examplesRead++;	
		// if(examplesRead == 1000) break;
		std::istringstream iss(line);
		iss >> firstWord;

		string phonemeString = line.substr(firstWord.size() + 2);
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

		std::vector<int> v2;
		std::istringstream iss1(phonemeString);
		std::vector<std::string>::iterator iter;
		while(iss1 >> phoneme){
			tmpVec = EncodePhoneme[phoneme];
			v2.insert(v2.end(), tmpVec.begin(), tmpVec.end());
		}

		j = firstWord.size();
		tmpVec = std::vector<int>(phonemeLength, 0);
		while(j!=numLength) {
			v2.insert(v2.end(), tmpVec.begin(), tmpVec.end());
			j++;
		}

		// for (std::vector<int>::iterator i = v2.begin(); i != v2.end(); ++i)
		// {
		// 	cout << *i;
		// }
		// cout << endl;
		actualOutput = v2;

		calculateDelta();

		// for (int i = 0; i < noInputNeurons; ++i)
		// {
		// 	cout << input[i];
		// }
		// cout << endl;

		// for (std::vector<int>::iterator i = actualOutput.begin(); i != actualOutput.end(); ++i)
		// {
		// 	cout << *i;
		// }
		// cout << endl;


		updateWeights();

		for(int i = 0; i < noInputNeurons * noHiddenNeurons; i++){
			// weights1[i] = ((rand()> RAND_MAX/2) ? 1 : -1) * 1.0L/(rand()%100 + 1);
			// cout << weights1[i] << endl;
		}
		// std::vector<int> v1 = EncodeGrapheme[];
	}
	int countTotal = 0;
	examplesRead = 0;
	while(getline(fp1, line)) {
		// examplesRead++;
		// if(examplesRead == 0) break;
		std::istringstream iss(line);
		iss >> firstWord;

		string phonemeString = line.substr(firstWord.size() + 2);
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

		std::vector<int> v2;
		std::istringstream iss1(phonemeString);
		std::vector<std::string>::iterator iter;
		while(iss1 >> phoneme){
			tmpVec = EncodePhoneme[phoneme];
			v2.insert(v2.end(), tmpVec.begin(), tmpVec.end());
		}

		j = firstWord.size();
		tmpVec = std::vector<int>(phonemeLength, 0);
		while(j!=numLength) {
			v2.insert(v2.end(), tmpVec.begin(), tmpVec.end());
			j++;
		}

		// for (std::vector<int>::iterator i = v2.begin(); i != v2.end(); ++i)
		// {
		// 	cout << *i;
		// }
		// cout << endl;
		// for (std::vector<long double>::iterator i = outerOutput.begin(); i != outerOutput.end(); ++i)
		// {
		// 	cout << *i << " " ;
		// }
		// cout << endl;

		// bool flag = false;
		long double change = 0L;
		int count = 0;
		for (int i = 0; i < numLength; ++i)
		{
			bool flag1 = false;
			for (int j = 0; j < phonemeLength; ++j)
			{
				int index = i*phonemeLength + j;
				if( abs((long double)v2[index] - outerOutput[index]) >= 0.5) {
					flag1 = true;
				}
			}
			// cout << i << " " << flag1 << endl;
			if(!flag1) 
				countTotal++;
			examplesRead++;
		}

		// cout << change << endl;
		// cout << flag << " " << change << " " << count << endl; 
		// break;
	}
	cout << countTotal << endl;
	cout << examplesRead << endl;
	cout << 100*(countTotal/(float)examplesRead) << endl;

	// // if(!input) return;
	// cout << "Give input\n";
	// cin >> firstWord; 

	// std::vector<int> v1, tmpVec;
	// for (int i = 0; i < firstWord.size(); ++i)
	// {
	// 	tmpVec = EncodeGrapheme[firstWord[i]];
	// 	v1.insert(v1.end(), tmpVec.begin(), tmpVec.end());
	// }
	// int j = firstWord.size();
	// tmpVec = std::vector<int>(graphemeLength, 0);
	// while(j!=numLength) {
	// 	v1.insert(v1.end(), tmpVec.begin(), tmpVec.end());
	// 	j++;
	// }
	// // for (std::vector<int>::iterator i = v1.begin(); i != v1.end(); ++i)
	// // {
	// // 	cout << *i;
	// // }
	// // cout << endl;

	// input = v1;
	// feedForward();

	// for (int i = 0; i < firstWord.size(); ++i)
	// {
	// 	std::vector<int> output;
	// 	for (int j = 0; j < phonemeLength; ++j)
	// 	{
	// 		int index = i*phonemeLength + j;
	// 		output.push_back(((outerOutput[index]) >= 0.5) ? 1 : 0);
	// 	}
	// 	// for (int j = 0; j < output.size(); ++j)
	// 	// {
	// 	// 	cout << output[j];
	// 	// }
	// 	// cout << endl;
	// 	cout << DecodePhoneme[output] << " ";
	}
	cout << endl;

}