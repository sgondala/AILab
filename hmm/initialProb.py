f = open('training.txt', 'r')
g = open('states.txt', 'r')

states={}
count = {}

l=0
for line in g:
    states[line.strip('\n')]=l
    l+=1
    #states.append(line.strip('\n'))

total = 0
for line in f:
    words=line.split(' ')
    total = total + 1
    word= words[2].strip('\n')
    if states[word] in count:
        count[states[word]] += 1.0
    else: 
        count[states[word]] = 1.0


#totalMax = 0.0

for state in count:
    count[state] = count[state]/total
    #totalMax += count[state]

for state in count:
    print state, count[state]
#print count
#print totalMax

