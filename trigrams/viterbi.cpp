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
		//cout<< line <<" "<< temp <<endl;
		stateMap[temp] = line;
		stateToNum[line] = temp;
		temp++;
	}
	states = temp;
	
	float transitionProb[states][states];
	float initialProb[states];
	float emmissionProb[26][states];
	float transProb3[states][states][states];

	temp = 0;
	ifstream ifs2("initialProb.txt");
	memset(initialProb, 0, sizeof(initialProb));
	while(getline(ifs2,line)){
		//cout<<"Line is "<<line<<endl;
		//line = line.substr(1); //only for akhil's
		int pos = find(line.begin(), line.end(), ' ') - line.begin();
		string state = line.substr(0,pos); 
		//cout<<state<<"_"<<line.substr(pos+1)<<endl;
		initialProb[stateToNum[state]] = stof(line.substr(pos+1)); //String to float
	}	
	
	memset(transitionProb, 0, sizeof(transitionProb));
	ifstream ifs3("transitionProb.txt");
	while(getline(ifs3,line)){
		vector<string> returnVec = split(line, ' ');
		int stateNumStart = stateToNum[returnVec[0]];
		int stateNumEnd = stateToNum[returnVec[1]];
		transitionProb[stateNumStart][stateNumEnd] = stof(returnVec[2]); //String to float
	}

	memset(emmissionProb, 0.0 , sizeof(emmissionProb));	
	ifstream ifs4("emissionProb.txt");
	while(getline(ifs4,line)){
		vector<string> returnVec = split(line, ' ');
		//cout<<returnVec[0]<<"_"<<returnVec[1]<<"_"<<returnVec[2]<<endl;
		//int alphabet = returnVec[0][0]- 'A'; //Akhil
		int alphabet = stoi(returnVec[0]);
		int state = stateToNum[returnVec[1]];
		//cout<<alphabet<<"_"<<state<<"_"<<endl;
		emmissionProb[alphabet][state] = stof(returnVec[2]);
	}

	memset(transProb3, 0.0 , sizeof(transProb3));	
	ifstream ifs6("emissionProb.txt");
	while(getline(ifs6,line)){
		vector<string> returnVec = split(line, ' ');
		transProb3[stateToNum[returnVec[0]]][stateToNum[returnVec[1]]][stateToNum[returnVec[2]]] = stof(returnVec[3]);
	}	

	ifstream ifs5("testingWords.txt");
	
	while(getline(ifs5,line)){
		string word;
		word = line;
		int length = word.length();
		float v[length][states];
		int backPtr[length][states];
		for(int i=0;i<states;i++){
			v[0][i] = emmissionProb[word[0]-'A'][i] * initialProb[i];
			backPtr[0][i] = i;
		}

		for (int i = 1; i < word.length(); ++i)
		{
			for (int j = 0; j < states; ++j)
			{
				float max = 0;
				int prevState = -1;
				for (int k = 0; k < states; ++k)
				{	//Changed a bit
					if(i==1){ 
						float tempMax = v[i-1][k]*transitionProb[k][j]*emmissionProb[word[i]-'A'][j];
						if(tempMax>max) {
							max = tempMax;
							prevState = k;
						}
					}
					else{
						for(int l=0; l<states; l++){
							float tempMax = v[i-2][k]*v[i-1][l]*transProb3[k][l][j]*emmissionProb[word[i]-'A'][j];
							if(tempMax>max) {
								max = tempMax;
								prevState = l;
							}							
						}
					}
				}
				v[i][j] = max;
				backPtr[i][j] = prevState;
			}
		}

		float maxValue=v[length-1][0];
		int finalState = 0;
		
		for(int i = 0;i<states;i++){
			//cout<<maxValue<<"_"<<v[length-1][i]<<endl;
			if(v[length-1][i] > maxValue){
				maxValue = v[length-1][i];
				finalState = i;
			}
		}

		//cout<<finalState<<"_"<<stateMap[finalState]<<endl;
		int tempState = finalState;
		vector<string> all;
		for(int i=length-1; i>=0; i--){
			//cout<<tempState<<" ";
			all.push_back(stateMap[tempState]);
			tempState = backPtr[i][tempState];
		}
		
		for(vector<string>::reverse_iterator it = all.rbegin(); it!=all.rend(); it++){
			cout<<*it<<endl;
		}
	}
}