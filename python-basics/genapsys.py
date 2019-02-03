# C-G
# A-T

dna_match = ['CG', 'GC', 'AT', 'TA']


def sig(prem, template, threshold):
    l = len(template)
    ll = len(prem)
    i = j = 0
    while(l-i and ll-j):
        sig = 0
        print prem[j], template[i]
        if template[i]+prem[j] in dna_match:
            print template[i]+prem[j]
            sig = 1
            while(template[i+1] and template[i] == template[i+1] and sig < threshold):
                i += 1
                sig += 1
            i += 1
        j += 1
        print('sig =', sig)
    return


def main():
    prem = "ACTGAAGGACTG"
    template = "TCAAAAATTTTTTGCAGGCAT"
    threshold = 3
    sig(prem, template, threshold)


if __name__ == "__main__":
    main()
