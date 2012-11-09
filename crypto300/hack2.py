tsbox=[86, 3, 13, 122, 14, 2, 75, 28, 29, 5, 77, 19, 34, 6, 74, 8, 83, 38, 127, 41, 40, 15, 1, 31, 89, 88, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 46, 32, 76, 36, 78, 79, 80, 81, 82, 42, 84, 85, 26, 87, 51, 50, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 43, 123, 124, 125, 126, 44, 0, 48, 49, 27, 4, 35, 39, 7, 45, 9, 10, 11, 12, 33, 30, 47, 16, 17, 18, 37, 20, 21, 22, 23, 24, 25]

init=list('<is`th1s`k3y`l0n9`en0ugh?>')

def add_key(sbox, k):
    for i, c in enumerate(k):
        sbox[i], sbox[ord(c)] = sbox[ord(c)], sbox[i]
        for i in xrange(len(sbox)):
            sbox[i] = (sbox[i] + 1) % 128
    return

def brute(idx, key):
    for i in xrange(128):
        key_t = key[:]
        key_t[idx] = chr(i)
        sbox = list(range(128))
        add_key(sbox, key_t)
        print diff(sbox, tsbox), chr(i)
        print "\n"*2
    
def main():
    sbox = list(range(128))
    add_key(sbox, init)
    print sbox
    print tsbox
    print len(sbox) - diff(sbox, tsbox)
    print init

def diff(x, y):
    err = 0
    for idx in xrange(len(x)):
        if y[idx] != x[idx]:
            err += 1
            print "%d bad -> %d" % (idx, y[idx])
        #else:
            #print "%d good -> %d" % (idx, y[idx])
    return err    

if __name__ == "__main__":
    main()
