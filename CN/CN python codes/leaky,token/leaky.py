# leaky_c.py
import socket, random, time

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 12345))
print("Connected to the server. Sending packets...")

try:
    for _ in range(10):
        size = random.randint(1, 5)
        print(f"Sending packet of size {size} to server.")
        client.send(str(size).encode())
        print(f"Server response: {client.recv(1024).decode()}")
        time.sleep(2)
except KeyboardInterrupt:
    print("\nClient exiting...")
finally:
    client.send("exit".encode())
    client.close()


# leaky_s.py
import socket, time

class LeakyBucket:
    def __init__(self, capacity=10, rate=2):
        self.capacity, self.rate, self.level = capacity, rate, 0
    
    def process(self, size):
        result = ""
        if self.level + size <= self.capacity:
            self.level += size
            result = f"Leaky Bucket: Added packet of size {size}. Current level: {self.level}"
        else:
            result = f"Leaky Bucket: Packet of size {size} dropped (bucket full)."
            
        leaked = min(self.rate, self.level)
        self.level -= leaked
        return f"{result}\nLeaky Bucket: Leaked {leaked}. Current level: {self.level}"

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)
print("Server is waiting for a client to connect...")

conn, addr = server.accept()
print(f"Connected to client at {addr}")
bucket = LeakyBucket()

while True:
    data = conn.recv(1024).decode()
    if data == "exit": break
    size = int(data)
    print(f"Received packet of size {size} from client.")
    result = bucket.process(size)
    print(result)
    response = "Packet of size " + str(size) + (" added successfully." if "Added" in result else " dropped (bucket full).")
    conn.send(response.encode())
    time.sleep(1)

print("Client disconnected. Exiting...")
conn.close()
server.close()
