# C-G
# A-T

dna_match = ['CG', 'GC', 'AT', 'TA']


def sig(prem, template, th):
    l = len(template)
    ll = len(prem)
    i = j = 0
    sig = 0
    while(l-i and ll-j):
        sig = 0
        print template[i]+prem[j]
        # if template[i]+prem[j] not in dna_match:
        # print 'not'
        if template[i]+prem[j] in dna_match:
            print 'if'
            sig = 1
            while(template[i+1] and template[i] == template[i+1] and sig < th):
                print 'if th'
                i += 1
                sig += 1
        j += 1
        i += 1
        print('sig =', sig)
    return sig


def main():
    prem = 'ACTGAAGGACTG'
    template = 'TCAATTTTTTGCAGGCAT'
    print 'working'
    sig(prem, template, 3)


if __name__ == "__main__":
    main()
