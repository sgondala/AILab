f = open('testing.txt', 'r')

for line in f:
    words = line.split(' ')
    for word in words[1:]:
        word = word.strip('\n')
        if len(word)>0:
            print word
