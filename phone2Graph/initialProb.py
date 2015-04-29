import string

f = open('training.txt', 'r')
g = open('states.txt', 'r')

states={}
count = {}
alphabet = {}

allAlphabet = string.ascii_uppercase
for i in allAlphabet:
    alphabet[i]=0


total = 0
for line in f:
	words=line.split(' ')
	letter= words[0][0].strip('\n')
        if letter in alphabet:
            alphabet[letter] += 1.0
	    total = total + 1

for letter in alphabet:
	alphabet[letter] = alphabet[letter]/total

for letter in alphabet:
	print letter,alphabet[letter]
