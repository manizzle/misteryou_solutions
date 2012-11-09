import requests, lxml.html, os
from math import floor
import math
import urllib, urllib2, base64

main_url = "http://misteryou.ru/ppc300/"

def quick_ocr(file_name):
    cmd = "convert %s -colorspace Gray ocr.tif" % file_name
    os.system(cmd)
    cmd = "tesseract ocr.tif out &> /dev/null"
    os.system(cmd)
    with open("out.txt") as f:
        return f.read()
    
def get_eq_true():
    page = lxml.html.parse(main_url)
    img_url = main_url + "img/%s" % os.path.split(page.xpath("//img")[0].values()[0])[-1]
    with open("img.png", "w") as f:
        img_data = requests.get(img_url).content
        f.write(img_data)
    return (quick_ocr("img.png").split()[1],
            page.xpath("//input[@name='trueanswer']")[0].values()[-1])


def send_data(answer, truans):
    payload = {"captchatype" : "refactor",
               "trueanswer" : truans,
               "answer"  : str(answer)
               }
    print payload
    req = requests.post(main_url, data=payload)
    print req.content[3:]

def get_factor(num):
    cmd = "msieve %d 2> /dev/null" % num
    os.system(cmd)
    with open("msieve.log") as f:
        data =[x.split("factor:")[-1].strip() 
               for x in f.read().split("Msieve")[-1].splitlines() 
               if "factor:" in x]
    assert(int(data[0]) * int(data[1]) == num)
    return data[0]
        

def hack():
    eq, truans = get_eq_true()
    print eq
    print truans
    factor = get_factor(int(eq))
    send_data(factor, truans)

if __name__ == "__main__":
    hack()
    
