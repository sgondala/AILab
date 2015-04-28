#include "encoding.h"
std::vector<std::string> presentPhonemes;

void pushInteger(std::vector<unsigned int>* v, unsigned int a){//this integer has to be less than 128
	v->push_back((a >> 7) & 1);
	v->push_back((a >> 6) & 1);
	v->push_back((a >> 5) & 1);
	v->push_back((a >> 4) & 1);
	v->push_back((a >> 3) & 1);
	v->push_back((a >> 2) & 1);
	v->push_back((a >> 1) & 1);
	v->push_back((a >> 0) & 1);
}


unsigned int decode(unsigned int one, unsigned int two, unsigned int three, unsigned int four, unsigned int five, unsigned int six, unsigned int seven, unsigned int eight){
	unsigned int current = 0;
	current += one << 7;
	current += two << 6;
	current += three << 5;
	current += four << 4;
	current += five << 3;
	current += six << 2;
	current += seven << 1;
	current += eight << 0;
	return current;
}



/********************************************************************************
 * INPUT: A string of graphemes. e.g., ABC
 * OUTPUT: A vector of int each element containing either 0 or 1
 * FUNCTION: encodes first element as a bit pattern. (At max 8 bits are used) and puts each bit values as int in vector. This is done for all elements in the given string
 * TODO: checking
 * ********************************************************************************/
std::vector<unsigned int> encodeGraphemes(std::string graphemeSequence, int length){
	int l = graphemeSequence.size();
	std::vector<unsigned int> toReturn;
	for(int i = 0; i < l; i++){
		// if(graphemeSequence == "AB") {
		// 	std::cout << (unsigned int) graphemeSequence[i] << std::endl;
		// }
		pushInteger(&toReturn, (unsigned char) graphemeSequence[i]);
	}
	for(int i = l; i < length; i++){
		pushInteger(&toReturn, 0);
	}
	return toReturn;
}




std::string decodeGraphemes(std::vector<unsigned int> *v){
	std::string toReturn;
	for(unsigned int i = 0; i < v->size(); i++){
		char temp = decode((*v)[i], (*v)[i + 1], (*v)[i + 2], (*v)[i + 3], (*v)[i + 4], (*v)[i + 5], (*v)[i + 6], (*v)[i + 7]);
		if(temp != '\0') toReturn += temp;
		i += 7;
	}
	return toReturn;
}



std::string decodePhonemes(std::vector<unsigned int> *v){
	std::cout << "vector is ->";
	for(unsigned int i = 0; i < v->size(); i++){
		std::cout << (*v)[i];
	}
	std::cout << std::endl;
	std::string toReturn;
	for(unsigned int i = 0; i < v->size(); i++){
		int a = decode((*v)[i], (*v)[i + 1], (*v)[i + 2], (*v)[i + 3], (*v)[i + 4], (*v)[i + 5], (*v)[i + 6], (*v)[i + 7]) - 1;
		if(a != -1){
			toReturn += presentPhonemes[a] + " ";
		}
		i += 7;
	}
	toReturn = toReturn.substr(0, toReturn.size() - 1);
	return toReturn;
}

/********************************************************************************
 * INPUT:A string of space separated phonemes. e.g., "A AH0 AE1"
 * OUTPUT: a vector of ints where each int represents a phoneme.
 * FUNCTION: Checks if a phoneme is present in a global vector. If yes, put its index in toReturn vector. Else, add this to the global vector and then return the index.
 * TODO:checking
 * ********************************************************************************/
std::vector<unsigned int> encodePhonemes(std::string phonemeSequence, int length){
	std::string phoneme;
	std::vector<unsigned int> toReturn;
	std::istringstream iss(phonemeSequence);
	std::vector<std::string>::iterator iter;
	while(iss >> phoneme){
		iter = find(presentPhonemes.begin(), presentPhonemes.end(), phoneme);
		if(iter == presentPhonemes.end()){
			pushInteger(&toReturn, presentPhonemes.size() + 1);
			presentPhonemes.push_back(phoneme);
		}
		else{
			pushInteger(&toReturn, (iter - presentPhonemes.begin()) + 1);
		}
	}
	for(int i = toReturn.size()/8; i < length; i++){
		pushInteger(&toReturn, 0);
	}
	return toReturn;
}
