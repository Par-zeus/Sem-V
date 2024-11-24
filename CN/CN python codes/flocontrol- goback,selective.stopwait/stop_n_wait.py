def main():
    n = int(input("Enter the number of frames: "))
    frames = []
    print("Enter data:")
    for i in range(n):
        frames.append(int(input()))
        # frames = list(map(int, input().split()))  # Read all frames in one line
    x = 0  # Frame index pointer
    while x != n:
        print("\nEnter your choice:")
        print("0: Send data")
        print("1: Success")
        print("2: Data lost")
        print("3: Acknowledgement lost")
        print("4: Data received but with error")       
        choice = int(input("Your choice: "))
        if choice == 0:
            print(f"Send data: {frames[x]}")
        elif choice == 1:
            print(f"Data successfully received: {frames[x]}")
            x += 1  # Move to the next frame
        elif choice == 2:
            print("Data lost, please resend data.")
        elif choice == 3:
            print("Acknowledgement lost, please resend data.")
        elif choice == 4:
            print("Erroneous data received, please resend data.")
        else:
            print("Invalid choice, please try again.")
            
if __name__ == "__main__":
    main()