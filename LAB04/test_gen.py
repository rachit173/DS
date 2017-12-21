import random
f = open('unit.in',"w")
n = random.randint(1,10000)
### f.write(str(n)+"\n") 
for i in range(n):
    f.write(str(random.randint(-1000,1000))+" ")
f.write("\n")
f.close()