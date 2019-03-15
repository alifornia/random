def func(a, b, c):
    a = "Goodbye"
    b = b[1:-1]
    c['test'] = ['fail']


A = "Hello"
B = [1, 2, 3, 4, 5]
C = {'test': 'pass'}

func(A, B, C)

print(A)   # Hello
print(B)   # [1,2,3,4,5]
print(C)   # {'test': 'fail'}
