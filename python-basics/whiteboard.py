import os
import glob

# absolute basics
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

for num in xrange(1, 20):
    if num % 3 == 0 and num % 5 == 0:
        print('fizzbuzz')
    elif num % 3 == 0:
        print('fizz')
    elif num % 5 == 0:
        print('buzz')
    else:
        print(num)
a, b = 1, 1
for i in xrange(1, 10):
    print a
    a, b = b, a+b

my_list = [10, 20, 30, 40, 50]
for i in my_list:
    print i

my_tuple = (1, 2, 3, 4, 5)
for i in my_tuple:
    print i

my_dict = {'name': 'ali', 'age': 30, 'job': 'fucking ur gf'}
for key, value in my_dict.items():
    print "My {} is {}".format(key, value)

my_set = {1, 1, 2}
for i in my_set:
    print i

squares = [n*n for n in my_list]
print squares
# some file
os.chdir(".")
for file in glob.glob("t*t.cpp"):
    print(file)
