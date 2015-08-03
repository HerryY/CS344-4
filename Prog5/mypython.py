#Name: Marta Wegner
#CS 344
#Assignment #5
#file name: mypython.py

#open files
r1 = open("rand1", 'w')
r2 = open("rand2", 'w')
r3 = open("rand3", 'w')

#import random and string modules
import random, string

files = [r1, r2, r3]

for file in files:
   #generate random strings
   rand  = ''.join(random.choice(string.ascii_lowercase) for n in xrange(10))

   #write strings to files
   file.write(rand)
   file.write('\n')

   file.close()

#open for reading
r1 = open("rand1", 'r')
r2 = open("rand2", 'r')
r3 = open("rand3", 'r')

files = [r1, r2, r3]

#print out contents of files
for file in files:
    line = file.read(10)

    print line

#generate random nums
from random import randint
randNum1 = randint(1,42)
randNum2 = randint(1,42)

#print rand nums
print randNum1
print randNum2

#print sum of rand nums
sum = randNum1 + randNum2
print sum
