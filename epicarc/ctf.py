import socket, sys, struct

server="159.253.22.174"
port=3137
def main():
    shared = [0x5f, 0x68, 0x61, 0x63, 0x6b, 0x6d, 0x65, 0x5f]
    msg = [0x46, 0x6c, 0x61, 0x67, 
           0x52, 0x65, 0x71, 0x75,
           0x65, 0x73, 0x74, 0x3a,
           0x6f, 0x6d, 0x6b, 0x65,
           0x73, 0x65, 0x79]
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server,port))
    init = s.recv(17)
    print repr(init)
    block_1 = s.recv(8)
    block_2 = s.recv(2)
    block_3 = s.recv(4)
    print repr(block_1), len(block_1)
    block_1 = "".join([chr(ord(block_1[i]) ^ shared[i]) for i in xrange(8)])
    print repr(block_1), len(block_1)
    print repr(block_2), len(block_2)
    print repr(block_3), len(block_3)
    # create new key
    msg += map(lambda x: ord(x), block_3)
    msg += [0] + shared
    assert(len(msg) == 32)
    print len(msg)
    msg = run_key(msg, block_1, 25)
    msg_str = "".join(map(lambda x: chr(x), msg))
    print repr(msg_str)
    assert(len(msg_str) == 32)
    s.send(msg_str)
    encr = s.recv(40)
    print repr(encr), len(encr)
    encr = map(lambda x: ord(x), encr)
    print len(encr)
    print "".join(map(lambda x: chr(x), run_key(encr, block_1)))
    s.close()

def run_key(msg_t, key, limit=None):
    msg = msg_t[:]
    # loop new block_1 key xor over msg
    msg_ctr = 0
    v6 = 0
    v8 = 0
    v9 = 0
    v10 = 0
    v11 = 0
    while True:
        if (v6 == 8):
            v6 = 0
        msg[msg_ctr] = msg[msg_ctr] ^ ord(key[v6])
        msg_ctr += 1

        v8 = v6 + 1
        if (v8 == 8):
            v8 = 0
        try:
            msg[msg_ctr] = msg[msg_ctr] ^ ord(key[v8])
        except:
            return msg
        msg_ctr += 1
        
        v9 = v8 + 1
        if (v9 == 8):
            v9 = 0
        msg[msg_ctr] = msg[msg_ctr] ^ ord(key[v9])    
        msg_ctr += 1

        v10 = v9 + 1
        if (v10 == 8):
            v10 = 0
        msg[msg_ctr] = msg[msg_ctr] ^ ord(key[v10])
        msg_ctr += 1
        
        v11 = v10 + 1
        if (v11 == 8):
            v11 = 0
        msg[msg_ctr] = msg[msg_ctr] ^ ord(key[v11])
        msg_ctr += 1

        v6 = v11 + 1
        
        if (limit and msg_ctr >= limit):
            return msg
        elif msg_ctr >= len(msg):
            return msg

if __name__ == "__main__":
        main()
