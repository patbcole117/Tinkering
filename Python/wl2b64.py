import sys
import base64

if len(sys.argv) == 3:
    b64_file = open(sys.argv[2], "w")
    with open(sys.argv[1], "rb") as text_file:
        for i in text_file:
            b64_file.write(base64.b64encode(i).decode('ascii')+'\n')
    b64_file.close()
else:
    print('\n####\n\nConverts wordlists to base64.\nUSAGE: wl2b64.py <SRC-FILE> <OUT-FILE>\n\n####\n')
