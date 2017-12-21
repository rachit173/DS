import random
import time
m = 100000
f = open("test.in","w")
f.write(str(m)+"\n")
for i in range(m):
    f.write(str(random.randint(0,1))+" "+str(random.randint(1,100))+"\n")
# for i in range(500):
#     print str(random.randint(1,1))+" "+str(random.randint(1,10000))