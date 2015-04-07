f = open('outputReal.txt', 'r')
g = open('outputMine.txt', 'r')

fWords=[]
gWords=[]

for line in f:
    fWords.append(line)

for line in g:
    gWords.append(line)

total = 0
correct = 0.0

for i in range(len(fWords)):
    total += 1
    if fWords[i].strip('\n') == gWords[i].strip('\n'):
        correct += 1

print correct/total
