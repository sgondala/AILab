f = open('training.txt','r')
g = open('states.txt', 'r')

states = []

for line in g:
    states.append(line.strip('\n'))

dict2D = {}
countStates = {}

laa = []
for line in f:
    words=line.split(' ')
    t=len(words)-1
    for i in range(t):
        words[i] = words[i].strip('\n')
        words[i+1] = words[i+1].strip('\n')
        if words[i] in states and words[i+1] in states:
            laa.append(words[i+1])    
            if words[i] in countStates:
                countStates[words[i]] += 1.0
                if words[i+1] in dict2D[words[i]]:
                    dict2D[words[i]][words[i+1]] += 1.0
                else:
                    dict2D[words[i]][words[i+1]] = 1.0
            else:
                countStates[words[i]] = 1.0
                dict2D[words[i]] = {}
                dict2D[words[i]][words[i+1]] = 1.0

for first in dict2D:
    for second in dict2D[first]:
        dict2D[first][second] /= countStates[first]

for first in dict2D:
    for second in dict2D[first]:
        print first, second, dict2D[first][second]
