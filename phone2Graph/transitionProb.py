import string

f = open('training.txt','r')
#f = open('temp.txt', 'r')

dict2D = {}
countFirst = {}

allAlphabet = string.ascii_uppercase
for i in allAlphabet:
    dict2D[i]={}
    countFirst[i]=0
    for j in allAlphabet:
        dict2D[i][j]=0

for line in f:
    words=line.split(' ')
    word = words[0]
    t=len(word)-1
    for i in range(t):
        dict2D[word[i]][word[i+1]] += 1.0
        countFirst[word[i]] += 1.0

for first in dict2D:
    for second in dict2D[first]:
        if countFirst[first] !=0:
            dict2D[first][second] /= countFirst[first]
        else:
            dict2D[first][second]  = 0

for first in dict2D:
    for second in dict2D[first]:
        if dict2D[first][second] != 0:
            print first, second, dict2D[first][second]
