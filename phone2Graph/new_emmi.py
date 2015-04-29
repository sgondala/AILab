import string
g = open('sample.txt','r')
h=open('stat.txt','r')
f = open('oldstat.txt','r')
table=dict()
single=dict()
alpha=list(string.ascii_uppercase)
l=[]
z = []
for line in h.readlines():
	x=line.strip('\n')
	single[x]=0.0
	l.append(x)
for line in f.readlines():
	x=line.strip('\n')
	z.append(x)
for x in l:
	for y in z:
		table[x,y]=0.0

for line in g.readlines():
	arr=line.split()
	word=arr[0]
	for i in range(len(word)):
		table[word[i],arr[i+1]]+=1
		single[word[i]]+=1
for x in l:
	for y in z:
		if single[x]!=0:
			table[x,y]=table[x,y]/single[x]
		else:
			table[x,y]=0.0
		print x,y,table[x,y]
