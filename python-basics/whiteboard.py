import os
import glob


a = 10
b = 20

if a < b:
    print("{} is less than {}".format(a, b))
elif a == b:
    print("{} is equal to {}".format(a, b))
else:
    print("{} is greater than {}".format(a, b))

for i in range(1, 2):
    print i

while i <= 3:
    print i
    i += 1

os.chdir(".")
for file in glob.glob("t*t.cpp"):
    print(file)
