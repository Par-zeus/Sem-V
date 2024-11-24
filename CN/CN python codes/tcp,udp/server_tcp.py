import socket

def start_server():
    # Create a socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Bind the socket to a specific host and port
    host = "127.0.0.1"  # localhost
    port = 12345
    server_socket.bind((host, port))
    # Start listening for incoming connections
    server_socket.listen(5)  # Allow up to 5 clients to queue
    print(f"Server started. Listening on {host}:{port}")
    # Accept a client connection
    client_socket, client_address = server_socket.accept()
    print(f"Connection established with {client_address}")
    # Communication loop
    while True:
        # Receive data from the client
        data = client_socket.recv(1024).decode()
        if not data or data.lower() == "exit":
            print("Client disconnected.")
            break
        print(f"Client: {data}")
        # Send a response to the client
        response = input("Server: ")
        client_socket.send(response.encode())
    # Close the connection
    client_socket.close()
    server_socket.close()

if __name__ == "__main__":
    start_server()