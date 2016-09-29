#!/usr/bin/env python3
import re
import sys
import string
import random

fin = open("sorteddict.txt","r")
fout = open("gensorted3grams.txt","w")

n = 0
words = list()
word_count = 0
for line in fin:
	line = line.strip()
	words.append(line)
	word_count += 1


a = 0
b = word_count - 1
t = b//80
N = 150000000
while n < N:
	ii2 = -1
	for i in range(80):
		i1 = a
		i2 = random.randint(ii2+1, t*(i+1))
		i3 = random.randint(a, b)
		ii2 = i2
		i4 = random.randint(1, 100000000)//random.randint(1,50000)+1
		#fout.write(str(i1)+" "+str(i2)+" "+str(i3)+" "+"\n")
		fout.write(words[i1]+" "+words[i2]+" "+words[i3]+" "+str(i4)+"\n")
	n += 80
	a += 1
fin.close()
fout.close()
print(n)
