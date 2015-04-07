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
	word= words[2].strip('\n')
	if word in states:
		if word in count:
			count[word] += 1.0
			total = total + 1
		else: 
			count[word] = 1.0
			total = total + 1

for state in count:
	count[state] = count[state]/total
	#totalMax += count[state]

for state in count:
	print state,count[state]
#print count
#print totalMax

