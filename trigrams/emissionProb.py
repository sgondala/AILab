import string
f = open('training.txt','r')
g = open('states.txt', 'r')

statesNumbers = {}
l=0;
alpha = list(string.ascii_uppercase)
alphaNumbers = {}

numToState = {}

for line in g:
    statesNumbers[line.strip('\n')] = l
    numToState[l] = line.strip('\n')
    l=l+1

k=0
for i in alpha:
    alphaNumbers[i] = k
    k=k+1

#print alphaNumbers

matrix=[[]]
matrix = [[0 for i in xrange(26)] for i in xrange(l)]
single=[]
single = [0 for i in xrange(l)]

for line in f:
    words=line.split(' ')
    #print words[0][0]
    t=len(words)
    for i in range(t):
        words[i] = words[i].strip('\n')
        #print i, words[i]
        if i != 0 and i != 1:
            #print words[i].strip('\n'), words[0][i-2], words[0], words
            #print words[0], statesNumbers[words[i]], words[0][i-2], alphaNumbers[words[0][i-2]]
            #print words[i]
            #print line, words[0][i-2], words[i]
            #matrix[alphaNumbers[words[0][i-2]]][statesNumbers[words[i]]] += 1.0
            #single[alphaNumbers[words[0][i-2]]] += 1.0

            matrix[statesNumbers[words[i]]][alphaNumbers[words[0][i-2]]] += 1.0
            single[statesNumbers[words[i]]] += 1.0
        else:
            #print i, words[i]
            continue

for i in xrange(l):
    for j in xrange(26):
        if single[i]==0:
            matrix[i][j] = 0
        else:
            matrix[i][j] /= single[i]

        if matrix[i][j]!=0:
            print j, numToState[i], matrix[i][j]
            #print matrix[i][j]
