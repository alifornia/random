# C-G
# A-T

dna_match = ['CG', 'GC', 'AT', 'TA']


def sig(prem, template, threshold):
    l = len(template)
    ll = len(prem)
    i = j = 0
    while(l-i and ll-j):
        sig = 0
        if template[i]+prem[j] in dna_match:
            sig = 1
            while(template[i+1] and template[i] == template[i+1] and sig < threshold):
                i += 1
                sig += 1
        j += 1
        i += 1
        print('sig =', sig)
    return


def main():
    prem = 'ACTGAAGGACTG'
    template = 'TCAATTTTTTGCAGGCAT'
    print 'working'
    sig(prem, template, 3)


if __name__ == "__main__":
    main()
