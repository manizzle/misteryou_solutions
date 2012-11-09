import requests, lxml.html

def get_eq_true():
    page = lxml.html.parse("http://misteryou.ru/ppc100/")
    return (page.xpath("//div//text()")[1].strip().split(),
            page.xpath("//input[@name='trueanswer']")[0].values()[-1])


def send_data(answer, truans):
    payload = {"captchatype" : "hugecaptcha",
               "trueanswer" : truans,
               "answer"  : str(answer)
               }
    print payload
    req = requests.post("http://misteryou.ru/ppc100/", data=payload)
    import pdb; pdb.set_trace()
    print unicode(req.text, errors="replace")

def hack():
    eq, truans = get_eq_true()
    print eq
    send_data(str(int(eq[0]) + int(eq[-1])), truans)

if __name__ == "__main__":
    hack()
    
