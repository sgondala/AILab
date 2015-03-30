f = open('training.txt','r')
g = open('states.txt', 'r')

statesNumbers = {}
l=0;

for line in g:
    statesNumbers[line.strip('\n')] = l
    l=l+1

matrix=[[]]
matrix = [[0 for i in xrange(l)] for i in xrange(l)]
single=[]
single = [0 for i in xrange(l)]

for line in f:
    words=line.split(' ')
    t=len(words)-1
    for i in range(t):
        if words[i] in statesNumbers and words[i+1] in statesNumbers:
            matrix[statesNumbers[words[i]]][statesNumbers[words[i+1]]] += 1
            single[statesNumbers[words[i]]] +=1.0

for i in range(l):
    for j in range(l):
        if single[i]==0:
            matrix[i][j]=0
        else:
            matrix[i][j]/=single[i]
        
        print i,j, matrix[i][j]
    
