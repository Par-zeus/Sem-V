import random

def selective_repeat_arq(total_frames, window_size):
    frames_acknowledged = [False] * total_frames
    frames = list(range(total_frames))
    sent_index = 0  # Start of the sliding window
    print("\nStarting transmission...\n")
    while sent_index < total_frames:
        # Transmit frames within the window
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
                else:
                    print(f"Frame lost: {frames[i]}")
        # Move the window
        while sent_index < total_frames and frames_acknowledged[sent_index]:
            sent_index += 1
    print("All frames have been successfully transmitted!")

total_frames = int(input("Enter the number of frames to send: "))
window_size = int(input("Enter window size: "))
selective_repeat_arq(total_frames, window_size)