import itertools

def main():
    with open("cry200.txt.enc") as f:
        data = f.read()
    with open("key") as f:
        key = f.read()
    #for x, y in get_freq(data):
    #    print repr(x), y
    for x, y in get_freq("".join(data.splitlines())):
        print repr(x), y
    print repr(key)
    print len(key)
    print len(data)
    xorred = xor_rot(data, key)
    print xorred
    print len(xorred)
    for x in itertools.permutations(key):
	st = "".join(x)
	if "XOR(" in st:
		print st

def xor_rot(data, key):
    ret = []
    for i, d in enumerate(data):
        ret.append(chr(ord(d) ^ ord(key[i % len(key)])))
    return "".join(ret)

def get_freq(data):
    freq = {}
    for x in data:
        if x not in freq:
            freq[x] = 1
        else:
            freq[x] += 1
    return sorted(freq.items(), key = lambda x: x[1], reverse=True)

if __name__ == "__main__":
    main()
