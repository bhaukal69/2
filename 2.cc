import csv

data=[]
with open("examples.csv") as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        data.append(row)
        print(row)
#     for row in csv.reader(csvFile):
#         data.append(tuple(row))

print(data)

def domain():
    d=[]
    for i in range(len(data[0])):
        l=[]
        for ele in data:
            if ele[i] not in l:
                l.append(ele[i])
        d.append(l)
    return d

D=domain()
print(D)

def consistent(h1,h2):
    for x,y in zip(h1,h2):
        if x!='?' and x!=y:
            return False
    return True

def candidate_elemination():
    G = {('?',) * (len(data[0])-1)}
    S = ['Φ'] * (len(data[0])-1)
    count = 0
    print("\nG[0]:", G)
    print("\nS[0]:", S)
    for item in data:
        inp, res = item[:-1], item[-1]
        count += 1
        if res == "Yes":
            i = 0
            G = {g for g in G if consistent(g, inp)}
            for s, x in zip(S,inp):
                if s != x:
                    if S[i] == 'Φ':
                        S[i] = x
                    else:
                        S[i] = '?'
#                     S[i]='?' if S[i]!='0' else x
                i+=1
        else:
            Gprev=G.copy()
            for g in Gprev:
                for i in range(len(g)):
                    if g[i]=='?':
#                         print(inp, S)
                        for val in D[i]:
#                             print(val," ", inp[i], " ", S[i])
                            if val!=inp[i] and val==S[i]:
                                g_new=g[:i]+(val,)+g[i+1:]
#                                 print("\n",g_new)
                                G.add(g_new)
                    else:
                        G.add(g)
                    G.difference_update([h for h in G if any([consistent(h,g1) for g1 in G if h!=g1])])
        print("\nG[{}]:".format(count), G)
        print("\nS[{}]:".format(count), S)

candidate_elemination()
