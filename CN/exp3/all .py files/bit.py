# Bit Stuffing

def bit_stuffing(data,flag="01111110"):
    stuffed_data=""
    consecutive_ones=0
    for bit in data:
        if bit=='1':
            consecutive_ones+=1
            stuffed_data+=bit
            if consecutive_ones==5:
                stuffed_data+='0'
                consecutive_ones=0
        else:
            consecutive_ones=0
            stuffed_data+=bit
    return f"{flag}{stuffed_data}{flag}"
    
    
def bit_unstuffing(frame,flag="01111110"):
    unstuffed_data=""
    consecutive_ones=0
    stuffed_data=frame[len(flag):-len(flag)]
    for bit in stuffed_data:
        if bit=='1':
            consecutive_ones+=1
            unstuffed_data+=bit
        elif bit=='0' and consecutive_ones==5:
            consecutive_ones=0
            continue
        else:
            consecutive_ones=0
            unstuffed_data+=bit
    return unstuffed_data
            
data="0111111111100001"
x=bit_stuffing(data)
print("Frame",x)
y=bit_unstuffing(x)
print("Deframe",y)
            
            
            
            
            
            
            
            
            
            
            
            
            
            