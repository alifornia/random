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
for key, value in my_dict.iteritems():
    print "My {} is {}".format(key, value)

my_set = {1, 1, 2}
for i in my_set:
    print i

# one liner
squares = [n*n for n in my_list]
print squares

# generator


def sqr_num(nums):
    res = []
    for i in nums:
        res.append(i*i)
    return res


my_lst = [1, 2, 3]


print sqr_num(my_lst)


def sqr_num_gen(nums):
    for i in nums:
        yield (i*i)


my_sqr_num_list = sqr_num_gen(my_lst)


# object!
print my_sqr_num_list

for num in my_sqr_num_list:
    print(num)

# one liners
sqrs = [n*n for n in my_lst]
sqrs_gen = (n*n for n in my_lst)

print sqrs
print sqrs_gen


# OO

class One:
    pass


class Person(object):
    vari = "is"
    von = 1
    nums = 0

    def __init__(self, name, age):
        self.name = name
        self.age = age*self.von
        self.email = name+'@company.com'
        Person.nums += 1  # it's diff from von called by self.

    def info(self):
        return "{} {} {}".format(self.name, self.vari, self.age)

    @classmethod
    def set_von(cls, fake_factor):
        cls.von = fake_factor

    @classmethod
    def from_string(cls, str):
        name, age = str.split('-')
        return cls(name, int(age))


class Developer(Person):
    von = 3

    def __init__(self, name, age, lang):
        super(Person, self).__init__()
        self.lang = lang


class Manager(Person):
    def __init__(self, name, age, developers=None):
        super(Person, self).__init__()
        if developers is None:
            self.developers = []
        else:
            self.developers = developers

    def add_dev(self, dev):
        if dev in self.developers:
            self.developers.append(dev)

    def remove_dev(self, dev):
        if dev in self.developers:
            self.developers.remove(dev)

    def print_dev(self):
        for dev in self.developers:
            print('-->', dev.info())


p1 = Person('ali', 30)
p2 = Person('pirooz', 31)


print(p1.email)
print(p2.email)
print(p1.info())
print(p1.__dict__)
print(Person.nums)

p1.set_von(2)  # class not instant!
print(p2.von)

human1 = 'Dodo-21'
human2 = 'Wei-22'

new_p1 = Person.from_string(human1)
print(new_p1.info())

new_p2 = Developer('Mitch', 15, 'python')
print(new_p2.lang)

mgr1 = Manager('Liu', 20, [new_p2])
mgr1.print_dev()
mgr1.remove_dev(new_p2)
mgr1.print_dev()

print(mgr1.nums)


# some file
os.chdir(".")
for file in glob.glob("t*t.cpp"):
    print(file)
