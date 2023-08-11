import requests,sys

if len(sys.argv) == 1:
    print('\nUSAGE: superpassinject.py <URL> <COOKIE> <INJECT-FILE>\n')
else:
    prefix=sys.argv[1]
    cook={'session':sys.argv[2]}
    wl = (open(sys.argv[3], "r").read()).replace('\n','')
    
    for w in wl:
        url=f"{prefix}{w}"
        r = requests.get(url,cookies=cook)
        print(r.text)

