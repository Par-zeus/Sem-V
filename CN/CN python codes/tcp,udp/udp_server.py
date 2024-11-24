import socket

def start_udp_server():
    # Create a UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # Bind the socket to a specific host and port
    host = "127.0.0.1"  # localhost
    port = 12345
    server_socket.bind((host, port))
    print(f"UDP Server started. Listening on {host}:{port}")
    while True:
        # Receive data from a client
        data, client_address = server_socket.recvfrom(1024)
        print(f"Received from {client_address}: {data.decode()}")
        if data.decode().lower() == "exit":
            print(f"Client {client_address} disconnected.")
            break
        # Send a response back to the client
        response = input("Server: ")
        server_socket.sendto(response.encode(), client_address)
    # Close the socket
    server_socket.close()

if __name__ == "__main__":
    start_udp_server()