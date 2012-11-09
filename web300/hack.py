import requests, sys, lxml.html

def hex_to_ascii(data):
    return "".join([chr(int(data[y:y+2], 16)) for y in xrange(0, len(data), 2)])

def ascii_to_hex(data):
    return "".join(["%x" % ord(x) for x in data])

def get_rng():
    rng_algo="5368413128644154652843527950542843524333322873545252655628414273282431255371725428655850284558702870492829292929292929292929"
    print hex_to_ascii(rng_algo)
    rng_algo = ascii_to_hex("ShA1(dATe(CRyPT(CRC32(sTRReV(ABs($1%SqrT(eXP(EXp(pI())))))))))")
    print hex_to_ascii(rng_algo)
    rng_seeds = "0\r\n11111111\r\n"
    payload = {"rng_seeds" : rng_seeds,
               "rng_algorithm" : rng_algo}
    headers = {"Content-Type" : "application/x-www-form-urlencoded"}
    req = requests.post("http://securerng.misteryou.ru/", data=payload, headers=headers)
    obj = lxml.html.fromstring(req.text[17:])
    print obj.xpath("//textarea")[0].text

def main():
    if len(sys.argv) == 2:
        print hex_to_ascii(sys.argv[1])
    else:
        get_rng()
    
if __name__ == "__main__":
    main()
