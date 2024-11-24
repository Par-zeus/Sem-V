import socket

def start_client():
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Connect to the server
    host = "127.0.0.1"  # localhost
    port = 12345
    client_socket.connect((host, port))
    print(f"Connected to server at {host}:{port}")
    # Communication loop
    while True:
        # Send data to the server
        message = input("Client: ")
        client_socket.send(message.encode())
        if message.lower() == "exit":
            print("Disconnected from server.")
            break
        # Receive a response from the server
        response = client_socket.recv(1024).decode()
        print(f"Server: {response}")
    # Close the connection
    client_socket.close()

if __name__ == "__main__":
    start_client()