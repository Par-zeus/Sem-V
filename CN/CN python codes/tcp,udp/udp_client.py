import socket

def start_udp_client():
    # Create a UDP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # Define the server address and port
    server_address = ("127.0.0.1", 12345)
    print(f"Connected to server at {server_address[0]}:{server_address[1]}")
    while True:
        # Send data to the server
        message = input("Client: ")
        client_socket.sendto(message.encode(), server_address)
        if message.lower() == "exit":
            print("Disconnected from server.")
            break
        # Receive a response from the server
        data, _ = client_socket.recvfrom(1024)
        print(f"Server: {data.decode()}")
    # Close the socket
    client_socket.close()

if __name__ == "__main__":
    start_udp_client()
