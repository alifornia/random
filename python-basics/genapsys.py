# C-G
# A-T


def sig(prem, template):
    l = len(template)
    ll = len(prem)
    i = j = 0
    sig = 0
    while(l-i and ll-j):
        sig = 0
        print template[i]+prem[j]

        j += 1
        i += 1
        print('sig =', sig)
    return sig


def main():
    prem = 'ACTGGGGCTA'
    template = 'CCCTTTACCGATCA'
    print 'working'
    sig(prem, template)


if __name__ == "__main__":
    main()
