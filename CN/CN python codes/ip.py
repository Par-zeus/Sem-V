#get class, subnet mask & subnet address fr IP
#193.162.5.3: class C
#subnet: 255.255.255.0

def get_ip_class(ip):
    first_octet=int(ip.split('.')[0])
    if 0<=first_octet<=127:
        return 'A'
    elif 128<=first_octet<=191:
        return 'B'
    elif 192<=first_octet<=223:
        return 'C'
    elif 224<=first_octet<=239:
        return 'D'
    else:
        return 'E'

def get_subnet_mask(ipclass):
    if ip_class == 'A':
        return '255.0.0.0'
    elif ip_class == 'B':
        return '255.255.0.0'
    elif ip_class == 'C':
        return '255.255.255.0'
    else:
        return 'N/A'
    
def get_subnet_address(ip, subnet_mask): 
    ip_parts = list(map(int, ip.split('.'))) 
    mask_parts = list(map(int, subnet_mask.split('.'))) 
    subnet_address_parts = [str(ip_parts[i] & mask_parts[i]) for i in range(4)] 
    return '.'.join(subnet_address_parts) 
 
ip_address = input("Enter an IP address: ") 
ip_class = get_ip_class(ip_address) 
subnet_mask = get_subnet_mask(ip_class) 
if subnet_mask != 'N/A': 
    subnet_address = get_subnet_address(ip_address, subnet_mask) 
else:
    subnet_address = 'N/A' 

print(f"IP Class: {ip_class}") 
print(f"Subnet Mask: {subnet_mask}") 
print(f"Subnet Address: {subnet_address}") 