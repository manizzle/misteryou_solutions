import socket

HOST="93.191.13.142"
#HOST="127.0.0.1"
PORT = 7777 or int(sys.argv[1])

''' using cry300.py 
  flaw of how keys are mixed
  into a linear sbox 
  allows you to leak the entire
  stage 1 sbox'''
def getbyte(position):
    data = chr(position) + "a"*31 + "\x00" + "a"*31
    addr = (HOST, PORT)
    f = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    f.sendto(data, addr)
    ret, ret_addr = f.recvfrom(4096)
    return [int(ret[y:y+2], 16) for y in xrange(0, len(ret), 2)][0]

'''Subtracts circularly from a number
 given a total size'''
def circle_sub(data, sub, size):
    new_data = []
    for d in data:
        if (d - sub) < 0:
            new_data.append(size - (sub - d))
        else:
            new_data.append(d - sub)
    return new_data

''' Another weakness of this crypto
is that the length of the key
can be determined by the deterministic
behaviour of adding 1 in sequence to a 
completely linear and sequenced sbox'''
def find_key_length(keys):
    for i in xrange(0, len(keys) - 2):
        if (keys[i] + 1 == keys[i+1] and \
                keys[i] + 2 == keys[i+2]):
            return i
            
def getkey(decrypt, klen):
    return "".join([chr(x) for x in decrypt[:klen]])

def add_key(sbox, k):
    for i, c in enumerate(k):
        sbox[i], sbox[ord(c)] = sbox[ord(c)], sbox[i]
        for i in xrange(len(sbox)):
            sbox[i] = (sbox[i] + 1) % 128
    return

''' This attack assumes
 the key has all unique bytes
 otherwise initial key add will
 swap too much, might be harder
 to break key'''
def main():
    sbox1 = [getbyte(i) for i in xrange(128)]
    '''My key being mixed in will
    increment all bytes by 32
    by add_key() definition
    and cry300.py input definition
    filter this out '''
    print sbox1
    sbox2 = circle_sub(sbox1, 32, 128)
    print sbox2
    klen = find_key_length(sbox2)
    print klen
    sbox3 = circle_sub(sbox2, klen, 128)
    print sbox3
    key = getkey(sbox3, klen)
    print repr(key)
    print key
    print len(key)
    test_sbox = list(range(128))
    add_key(test_sbox, key)
    print test_sbox
    print sbox2

if __name__ == "__main__":
    main()
