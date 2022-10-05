import socket

HOST="192.168.1.9"
PORT=1100

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    while True:
        message = input()
        s.send(message.encode())
        data = s.recv(message)
        print(data)
        if message=="exit":
            break
    
    s.close()
