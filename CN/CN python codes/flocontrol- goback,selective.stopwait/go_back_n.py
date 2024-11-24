import random

def go_back_n(total_frames, window_size):
    sent_index = 0  # Start of the sliding window
    frames_acknowledged = [False] * total_frames
    frames = list(range(total_frames))
    print("\nStarting transmission...\n")   
    sent = 0
    loop = True
    while sent_index < total_frames:
        for i in range(sent_index, min(sent_index + window_size, total_frames)):
            if not frames_acknowledged[i]:
                print(f"Sending frame: {frames[i]}")
        # Simulate ACK responses
        for i in range(sent_index, min(sent_index + window_size, total_frames)):
            if not frames_acknowledged[i]:
                # Randomly decide if the frame is acknowledged or lost
                is_acknowledged = random.choice([True, False])
                if is_acknowledged:
                    frames_acknowledged[i] = True
                    print(f"ACK received for frame: {frames[i]}")
                    sent_index += 1
                else:
                    print(f"Frame lost: {frames[i]}")
                    break
    print("All frames have been successfully transmitted!")

total_frames = int(input("Enter the number of frames to send: "))
window_size = int(input("Please enter the Window Size: "))
go_back_n(total_frames, window_size)