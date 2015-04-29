import string
f = open('training.txt','r')
#f = open('temp.txt','r')
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

matrix=[[]]
matrix = [[0 for i in xrange(26)] for i in xrange(l)]
single=[]
single = [0 for i in xrange(26)]

for line in f:
    words=line.split(' ')
    t=len(words)
    for i in range(t):
        words[i] = words[i].strip('\n')
        if i != 0 and i != 1:
            matrix[statesNumbers[words[i]]][alphaNumbers[words[0][i-2]]] += 1.0
            single[alphaNumbers[words[0][i-2]]] += 1.0
        else:
            continue

for i in xrange(l):
    for j in xrange(26):
        if single[j]==0:
            matrix[i][j] = 0
        else:
            matrix[i][j] /= single[j]

        if matrix[i][j]!=0:
            print  numToState[i], j, matrix[i][j]
