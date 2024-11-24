# STOP AND WAIT

# SENDER:

import random
import socket

HOST='127.0.0.1'
PORT=65432
def reciever():
    with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST,PORT))
        server_socket.listen()
        print("Reciever: Waiting for connection")
        conn,addr=server_socket.accept()
        with conn:
            print(f"Reciever:connected by {addr}")
            while True:
                data=conn.recv(1024).decode()
                if not data:
                    break
                print(f"Reciever:reciever{data}")
                
                if random.random()<0.1:
                    print("Reciever:ACK drop")
                    continue
                
                ack=f"Ack {data}"
                conn.sendall(ack.encode())
                print(f"Reciever:sent{ack}")
                
            
if __name__=="__main__":
    reciever()


