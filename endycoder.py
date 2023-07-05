#!/usr/bin/python3
import base64
import urllib.parse
from argparse import ArgumentParser


def main():

    ap = ArgumentParser()
    ap.add_argument('instring')
    ap.add_argument('-t', '--typechain')
    ap.add_argument('-d', '--decode', action="store_true")
    ap.add_argument('-n','--nospace',action="store_true")
    ap.add_argument('-f','--file',action="store_true")
    args = ap.parse_args()

    # TODO Output to file?

    print(f"DEBUG: ARGS: {args}")

    if args.file:
        f = open(args.instring, 'r')
        instring = f.read()
    else:
        instring = args.instring
    
    for t in args.typechain:
        if t.upper() == 'U':
            if args.decode:
               instring = decode_url(instring)
            else:
                instring = encode_url(instring, args.nospace)
        elif t.upper() == 'B':
            if args.decode:
               instring = decode_b64(instring)
            else:
                instring = encode_b64(instring)

    print(instring)

def encode_url(instring, nospace):

    print('ENCODING URL....')
    outstring = urllib.parse.quote(instring, safe='')
    outstring = outstring.replace('.', '%2E')
    outstring = outstring.replace('-','%2D')
    if nospace:outstring = outstring.replace('%20', '%09')
    return outstring

def decode_url(instring):
     
    print('DECODING URL....')
    outstring = urllib.parse.unquote(instring)
    return outstring

def encode_b64(instring):

    print('ENCODING B64....')
    instring_bytes = instring.encode('ascii')
    outstring_bytes = base64.b64encode(instring_bytes)
    outstring = outstring_bytes.decode('ascii')
    return outstring

def decode_b64(instring):

    print('DECODING B64....')
    instring_bytes = instring.encode('ascii')
    outstring_bytes = base64.b64decode(instring_bytes)
    outstring = outstring_bytes.decode('ascii')
    return outstring

if __name__ == '__main__':
    main()