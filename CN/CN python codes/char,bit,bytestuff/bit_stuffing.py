# ip=01111110101111110

mes = input("Enter the message : ")
counter = 0
out = []
output =""
for i in range(len(mes)):
    out.append(mes[i])
    if(mes[i]=="0"):
        counter=0
    if(mes[i]=="1"):
        counter=counter+1
    if(counter==5):
        out.append("0")
        counter=0
for i in out:
    output=output+i
print("Stuffed Message : "+output)