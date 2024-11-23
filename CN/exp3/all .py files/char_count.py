# Character Count:

def char_count_frame(datalist):
    frames=[]
    str1=""
    for data in datalist:
        count=len(data)
        frame=f"{count}{data}"
        frames.append(frame)
        str1+=frame
    return frames

def char_count_deframe(frames):
    datalist=[]
    for frame in frames:
        count=int(frame[0])
        data=frame[1:count+1]
        datalist.append(data)
    return datalist

data=["12345","3424ngls"]
print("Frame:",char_count_frame(data))
print("Deframe:",char_count_deframe(char_count_frame(data)))
    



    
