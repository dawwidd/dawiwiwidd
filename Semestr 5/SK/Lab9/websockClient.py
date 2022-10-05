import websockets
import asyncio

async def connection():
    url="ws://127.0.0.1:7777"
    
    async with websockets.connect(url) as ws:
        await ws.send("Siema")

        while True:
            data=await ws.recv()
            print(data)


asyncio.get_event_loop().run_until_complete(connection())