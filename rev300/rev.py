
def get_key(c):
    key='xah7nmrcfpdku0gy62vb4lwzio5j38et1qs9'
    l = len(key)
    return key[((((ord(c) - 99) ^ 0xfe) - 39) ^ 0x34) % l]


