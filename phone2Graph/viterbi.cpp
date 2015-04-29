#include <bits/stdc++.h>
using namespace std;

int states = 0;

/////////////Functions

std::vector<std::string> &split(std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

/////////////////////////
int main(){
	map<int, string> stateMap;
	map<string, int> stateToNum;
	
	int temp = 0;
	ifstream ifs("states.txt");
	string line;
	while(getline(ifs,line)){
		stateMap[temp] = line;
		stateToNum[line] = temp;
		temp++;
	}
	states = temp;

	float transitionProb[26][26];
	float initialProb[26];
	float emmissionProb[states][26];
	
	temp = 0;
	//ifstream ifs2("initialProb.txt");
	ifstream ifs2("new_init.txt");
	memset(initialProb, 0.0, sizeof(initialProb));
	while(getline(ifs2,line)){
		int pos = find(line.begin(), line.end(), ' ') - line.begin();
		string alphabet = line.substr(0,pos); 
		initialProb[line[0] - 'A'] = stof(line.substr(pos+1)); //String to float
	}	

	memset(transitionProb, 0.0, sizeof(transitionProb));
	//ifstream ifs3("transitionProb.txt");
	ifstream ifs3("new_trans.txt");
	while(getline(ifs3,line)){
		vector<string> returnVec = split(line, ' ');
		int alphabetStart = returnVec[0][0]-'A';
		int alphabetEnd = returnVec[1][0]-'A';
		transitionProb[alphabetStart][alphabetEnd] = stof(returnVec[2]); //String to float
	}

	memset(emmissionProb, 0.0 , sizeof(emmissionProb));	
	//ifstream ifs4("emissionProb.txt");
	ifstream ifs4("new_emmi.txt");
	while(getline(ifs4,line)){
		vector<string> returnVec = split(line, ' ');
		int alphabet = line[0];
		int state = stateToNum[returnVec[1]];
		emmissionProb[state][alphabet-'A'] = stof(returnVec[2]);
	}

	ifstream ifs5("testingWords.txt");
	//ifstream ifs5("temp.txt");
	int lineNo = 0;
	while(getline(ifs5,line)){
		//cout<<lineNo<<endl;
		lineNo++;
		vector<string> word = split(line, ',');
		int length = word.size();
		float v[length][26];
		int backPtr[length][26];
		for(int i=0;i<26;i++){
			v[0][i] = emmissionProb[stateToNum[word[0]]][i] * initialProb[i];
			backPtr[0][i] = i;
		}
		for (int i = 1; i < word.size(); ++i)
		{
			for (int j = 0; j < 26; ++j)
			{
				float max = 0;
				int prevState = -1;
				for (int k = 0; k < 26; ++k)
				{	
					float tempMax = v[i-1][k]*transitionProb[k][j]*emmissionProb[stateToNum[word[i]]][j];
					if(tempMax>=max) {
						max = tempMax;
						prevState = k;
					}
				}
				v[i][j] = max;
				backPtr[i][j] = prevState;
			}
		}

		float maxValue=v[length-1][0];
		int finalState = 0;
		
		for(int i = 0;i<26;i++){
			if(v[length-1][i] > maxValue){
				maxValue = v[length-1][i];
				finalState = i;
			}
		}

		int tempState = finalState;
		vector<char> all;
		for(int i=length-1; i>=0; i--){
			all.push_back(tempState+'A');
			tempState = backPtr[i][tempState];
		}
		
		for(vector<char>::reverse_iterator it = all.rbegin(); it!=all.rend(); it++){
			cout<<*it<<endl;
		}
	}
}