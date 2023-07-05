import requests
import base64
import sys

data = {'':'', '':''}

r = requests.post(sys.srgv[1], json=data)

print(r.json())
print(r.text)