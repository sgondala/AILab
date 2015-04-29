f = open('testing.txt','r')
#f = open('temp.txt', 'r')

for line in f:
    words = line.split(' ')
    l=0
    s=""
    for word in words:
        if l==0 or l==1:
            l += 1
        else:
            s += word.strip('\n') + ','
    print s
