f = open('training.txt', 'r')
l=[]
for line in f:
    words = line.split(' ')
    i=0
    for word in words:
        if i==0:
            i+=1
            continue
        else:
            if word in l:
                continue
            else:
                #print len(word)
                if(len(word)!=0):
                    l.append(word)

#print l
for word in l:
    print word.strip()
