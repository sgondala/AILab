f = open('testing.txt', 'r')

#f = open('temp.txt', 'r')
for line in f:
    words = line.split(' ')
    word = words[0]
    for i in word:
        i = i.strip('\n')
        if len(i)>0:
            print i
