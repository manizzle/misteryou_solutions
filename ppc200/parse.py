import hashlib
match="287d3298b652c159e654b61121a858e0"
f = open("keylogger_report_08_10_2012.txt")
l = f.readlines()
key = ""
for x in [t+1 for t,f in enumerate(l) if "Password" in f][:-1]:
    data = l[x].split()
    if "Key" in data[0]:
        key += data[1].strip()
print len(key)
for good in [49989267, 66104429, 
             69880983, 87348948]:
    copy = str(key)
    copy += "%08d" % good
    m = hashlib.md5()
    m.update(copy)
    print m.hexdigest()
    if m.hexdigest() == match:
        print "good"
        y = hashlib.sha1()
        y.update(copy)
        print y.hexdigest()
        break
print len(key)
print len(copy)
