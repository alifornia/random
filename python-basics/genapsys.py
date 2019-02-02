# C-G
# A-T

dna_match = ['CG', 'GC', 'AT', 'TA']


def sig(prem, template):
    l = len(template)
    ll = len(prem)
    i = j = 0
    sig = 0
    while(l-i and ll-j):
        sig = 0
        print template[i]+prem[j]
        if template[i]+prem[j] in dna_match:
            print 'if'
        j += 1
        i += 1
        print('sig =', sig)
    return sig


def main():
    prem = 'ACTGGGGCTA'
    template = 'TCCCTTTACCGATCA'
    print 'working'
    sig(prem, template)


if __name__ == "__main__":
    main()
