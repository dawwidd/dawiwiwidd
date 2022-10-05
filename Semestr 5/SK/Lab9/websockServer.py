import websockets
import asyncio

async def echo(websocket, path):
    print("Client connected")
    try:    
        async for message in websocket:
            print(message)
            await websocket.send(message)
    except websockets.exceptions.connectionClosed as exc:
        print("DC")


start_server = websockets.serve(echo, "localhost", 7777)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()