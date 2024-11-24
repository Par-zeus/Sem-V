# ip=2,abc,def

n = int(input('Enter the number of frames: ')) 
frames = [] 
for i in range(n): 
    frame = input(f'Enter frame number {i+1}: ') 
    frames.append(frame) 
stuff_string = '' 
for i in frames: 
    length = len(i) + 1  # Include the length of the length digit itself 
    stuff_string += str(length) 
    stuff_string += i 
print("Stuffed string:", stuff_string) 