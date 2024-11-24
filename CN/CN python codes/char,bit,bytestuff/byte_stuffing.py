# ip=goodday, d,g,$

main_string = input('Enter the main string:') 
start = input('Enter the start character:') 
endd = input('Enter the end character:') 
delimiter = input('Enter the delimiter:') 
 
stuffed_string = f'{start}' 
for i in main_string: 
    if i==start or i==endd: 
        stuffed_string+=f'{delimiter}' 
    stuffed_string+=i 
stuffed_string+=f'{endd}' 
print(stuffed_string) 