def wstr(num, s):
    if(num <= 0):
        return s[::-1]
    i = 0
    while(lst[i] <= num):
        i += 1
    c = chr(ord('A')+i-1)
    s += c
    return wstr(num-lst[i-1], s)


lst = [1]
for i in range(1, 26):
    lst.append(lst[i-1]*(i+1)+(i+1))
print(lst)
s = ""
print(wstr(20, s))
