# token_c.py

import socket
import random
import time

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 12345))  # Connect to the server

    print("Connected to the server. Sending packets...")
    try:
        for _ in range(10):  # Simulate sending 10 packets
            packet_size = random.randint(1, 5)  # Random packet size between 1 and 5
            print(f"Sending packet of size {packet_size} to server.")
            client_socket.send(str(packet_size).encode())  # Send packet size to server

            response = client_socket.recv(1024).decode()  # Receive server response
            print(f"Server response: {response}")
            time.sleep(2)  # Simulate a delay between packet sends
    except KeyboardInterrupt:
        print("\nClient exiting...")
    finally:
        client_socket.send("exit".encode())  # Inform server to exit
        client_socket.close()

if __name__ == "__main__":
    main()


# token_s.py
import socket
import time

class TokenBucket:
    def __init__(self, capacity, token_rate):
        self.capacity = capacity  # Maximum capacity of the token bucket
        self.token_rate = token_rate  # Rate at which tokens are generated
        self.current_tokens = 0  # Current number of tokens
        self.last_time = time.time()  # Last time tokens were added

    def add_tokens(self):
        current_time = time.time()
        elapsed = current_time - self.last_time
        new_tokens = int(elapsed * self.token_rate)  # Add tokens based on elapsed time
        self.current_tokens = min(self.capacity, self.current_tokens + new_tokens)
        self.last_time = current_time
        print(f"Token Bucket: Current tokens: {self.current_tokens}")

    def consume_token(self, packet_size):
        if packet_size > self.current_tokens:
            print(f"Token Bucket: Packet of size {packet_size} dropped (not enough tokens).")
            return False
        self.current_tokens -= packet_size
        print(f"Token Bucket: Packet of size {packet_size} sent. Remaining tokens: {self.current_tokens}")
        return True

def main():
    bucket = TokenBucket(capacity=10, token_rate=2)  # Configure bucket settings

    # Setting up the socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 12345))
    server_socket.listen(1)  # Allow 1 client
    print("Server is waiting for a client to connect...")

    conn, addr = server_socket.accept()
    print(f"Connected to client at {addr}")

    while True:
        data = conn.recv(1024).decode()  # Receive packet size
        if not data or data.lower() == "exit":
            print("Client disconnected. Exiting...")
            break

        packet_size = int(data)
        print(f"Received packet of size {packet_size} from client.\n")

        # Add tokens based on elapsed time
        bucket.add_tokens()

        # Process the packet based on token availability
        if bucket.consume_token(packet_size):
            response = f"Packet of size {packet_size} sent successfully.\n\n"
        else:
            response = f"Packet of size {packet_size} dropped (not enough tokens).\n\n"

        # Send response to the client
        conn.send(response.encode())

    conn.close()
    server_socket.close()

if __name__ == "__main__":
    main()

