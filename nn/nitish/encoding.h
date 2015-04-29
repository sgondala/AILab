/*purpose of this file is to do both encoding and decoding the given vectors*/
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
//First the encoding part
// Grapheme to phoneme
//Given A1A2...An we take ascii value of each Ai, put the bytes in a vector as ints and return the vector. This vector will be a vector of ints. This is supposed to contain only 0s or 1s
std::vector<unsigned int> encodeGraphemes(std::string , int);
std::string decodeGraphemes(std::vector<unsigned int> *);
std::vector<unsigned int> encodePhonemes(std::string , int);
std::string decodePhonemes(std::vector<unsigned int> *);
//After all this, each grapheme takes 8 bits and each phoneme takes 8 bits. Each bit is represented by an int. So it will be a vector of ints.


/*
Example program using these functions:





 #include "encoding.h"


int main(){
	std::vector<unsigned int> v = encodeGraphemes("ABEDF");
	std::cout << decodeGraphemes(&v) << std::endl;
	std::vector<unsigned int> va = encodePhonemes("A AE0 BHU");
	va = encodePhonemes("BHU A AE0");
	for(std::vector<unsigned int>::iterator it = va.begin(); it != va.end(); it++){
		std::cout << *it ;
	}
	std::cout << std::endl;
	std::cout << decodePhonemes(&va) << std::endl;
}*/
