# CLIENT:

import socket
import time

# Client Configuration  
HOST = '127.0.0.1'  # Server IP
PORT = 65432      # Server Port
TIMEOUT = 2         # Timeout in seconds
MAX_RETRIES = 3     # Maximum retries
FRAMES = ["Frame1", "Frame2", "Frame3", "Frame4"]  # Frames to send

def sender(frames):
    """Sender (Client) implementation."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((HOST, PORT))
        print("Sender: Connected to Receiver")
        
        for frame in frames:
            print(f"\nSender: Starting transmission for '{frame}'")
            retries = 0
            while retries < MAX_RETRIES:
                print(f"Sender: Sending '{frame}'")
                client_socket.sendall(frame.encode())
                
                client_socket.settimeout(TIMEOUT)
                try:
                    # Wait for acknowledgment
                    ack = client_socket.recv(1024).decode()
                    print(f"Sender: Received '{ack}', proceeding to next frame")
                    break
                except socket.timeout:
                    retries += 1
                    print(f"Sender: No ACK received for '{frame}', retrying... (Attempt {retries}/{MAX_RETRIES})")
            else:
                print(f"Sender: Max retries reached for '{frame}', moving to the next frame.")

if __name__ == "__main__":
    sender(FRAMES)