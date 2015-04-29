import string

states = []

allAlpha = list(string.ascii_uppercase)

for letter in allAlpha:
    states.append(letter)

print states

dict3D = {}
dict2D = {}


word="AAA"
t=len(word)-2
for i in range(t):
    '''
    if word[i] not in dict3D:
        dict3D[word[i]] = {}
    if word[i+1] not in dict3D[word[i]]:
        dict3D[word[i]][word[i+1]] = {}
    if word[i+2] not in dict3D[word[i]][word[i+1]]:
        dict3D[word[i]][word[i+1]][word[i+2]] = 0

    dict3D[word[i]][word[i+1]][word[i+2]] += 1.0
    '''
    if word[i] not in dict2D:
        dict2D[word[i]] = {}
    if word[i+1] not in dict2D[word[i]]:
        dict2D[word[i]][word[i+1]] = 0

    dict2D[word[i]][word[i+1]] += 1.0
