import socket
import _thread

HOST="127.0.0.1"
PORT=1100

def dataTransfer(conn):
    while True:
        data = conn.recv(1024)
        if not data:
            break
        print(data)
        conn.send(data)
    conn.close()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST,PORT))
    s.listen(5)
    while True:
        conn, addr=s.accept()
        print("connected ", addr)
        _thread.start_new_thread(dataTransfer, (conn,))

    s.close()
