f = open('testing.txt','r')

for line in f:
    words = line.split(' ')
    print words[0]
