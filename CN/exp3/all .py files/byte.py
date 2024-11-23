# Byte Stuffing

def byte_stuffing(data,flag='FLAG',esc='ESC'):
    stuffed_data=data.replace(esc,esc+esc)
    stuffed_data=stuffed_data.replace(flag,esc+flag)
    return f"{flag}{stuffed_data}{flag}"

def byte_unstuffing(frame,flag='FLAG',esc='ESC'):
    stuffed_data=frame[len(flag):-len(flag)]
    unstuffed_data=stuffed_data.replace(esc+flag,flag)
    unstuffed_data=unstuffed_data.replace(esc+esc,esc)
    return unstuffed_data

data="ESC FLAG World"
x=byte_stuffing(data)
print("Frame:",x)
y=byte_unstuffing(x)
print("Deframe:",y)