#!/bin/bash

#All of them uses training.txt to generate training data

all: prepare
	g++ -std=c++11 viterbi.cpp
	./a.out > outputMine.txt
	python accuracy.py


prepare:
	python initialProb.py > initialProb.txt
	python transitionProb.py > transitionProb.txt
	python emissionProb.py > emissionProb.txt
	python testingWords.py > testingWords.txt
	python testingOutActual.py > outputReal.txt
