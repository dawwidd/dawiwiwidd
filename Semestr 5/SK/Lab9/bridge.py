import socket
import websockets
import asyncio

async def connection():
    url="ws://127.0.0.1:7777"
    
    async with websockets.connect(url) as ws:
        await ws.send("Siema")

HOST="127.0.0.1"
PORT=1100

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST,PORT))
    s.listen()
    conn, addr = s.accept()
    
    with conn:
        print("connected ", addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(data)
            asyncio.get_event_loop().run_until_complete(connection())
        conn.close()
    s.close()