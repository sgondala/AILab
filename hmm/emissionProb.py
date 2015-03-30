import string
f = open('training.txt','r')
g = open('states.txt', 'r')

statesNumbers = {}
l=0;
alpha = list(string.ascii_uppercase)
alphaNumbers = {}

for line in g:
    statesNumbers[line.strip('\n')] = l
    l=l+1

k=0
for i in alpha:
    alphaNumbers[i] = k
    k=k+1

#print alphaNumbers

matrix=[[]]
matrix = [[0 for i in xrange(l)] for i in xrange(26)]
single=[]
single = [0 for i in xrange(l)]

for line in f:
    words=line.split(' ')
    #print words[0][0]
    t=len(words)
    for i in range(t):
        words[i] = words[i].strip('\n')
        if i != 0 and i != 1:
            #print words[i].strip('\n'), words[0][i-2], words[0], words
            #print words[0], statesNumbers[words[i]], words[0][i-2], alphaNumbers[words[0][i-2]]
            matrix[alphaNumbers[words[0][i-2]]][statesNumbers[words[i]]] += 1
            single[alphaNumbers[words[0][i-2]]] += 1.0
        else:
            continue

for i in xrange(26):
    for j in xrange(l):
        if single[i]==0:
            matrix[i][j] = 0
        else:
            matrix[i][j] /= single[i]

        print i, j, matrix[i][j]