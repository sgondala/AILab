import string
f = open('training.txt','r')
g = open('states.txt', 'r')

states = []

allAlpha = list(string.ascii_uppercase)

for line in g:
    states.append(line.strip('\n'))

dict3D = {}
dict2D = {}

for line in f:
    words=line.split(' ')
    t=len(words)-2
    for i in range(t):
        words[i] = words[i].strip('\n')
        words[i+1] = words[i+1].strip('\n')
        words[i+2] = words[i+2].strip('\n')
        if words[i] in states and words[i+1] in states and words[i+2] in states:
            if words[i] not in dict3D:
                dict3D[words[i]] = {}
            if words[i+1] not in dict3D[words[i]]:
                dict3D[words[i]][words[i+1]] = {}
            if words[i+2] not in dict3D[words[i]][words[i+1]]:
                dict3D[words[i]][words[i+1]][words[i+2]] = 0

            dict3D[words[i]][words[i+1]][words[i+2]] += 1.0

            if words[i] not in dict2D:
                dict2D[words[i]] = {}
            if words[i+1] not in dict2D[words[i]]:
                dict2D[words[i]][words[i+1]] = 0

            dict2D[words[i]][words[i+1]] += 1.0

for first in dict3D:
    for second in dict3D[first]:
        for third in dict3D[first][second]:
            dict3D[first][second][third] /= dict2D[first][second]

for first in dict3D:
    for second in dict3D[first]:
        for third in dict3D[first][second]:
            print first, second, third, dict3D[first][second][third]