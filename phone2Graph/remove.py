f = open('dataset.txt','r')
for line in f:
	words = line.split(' ')
	if(words[0].isalpha()):
		if(len(words[0]) == len(words) - 2):
			print line, 