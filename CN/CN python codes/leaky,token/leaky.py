import time 
import random 
 
class LeakyBucket: 
    def __init__(self, capacity, leak_rate): 
        self.capacity = capacity  # Maximum capacity of the bucket 
        self.leak_rate = leak_rate  # Rate at which packets leak out 
        self.current_level = 0  # Current level of the bucket 
 
    def add_packet(self, packet_size): 
        if self.current_level + packet_size > self.capacity: 
            print(f"Leaky Bucket: Packet of size {packet_size} dropped (bucket full).") 
            return False 
        self.current_level += packet_size 
        print(f"Leaky Bucket: Added packet of size {packet_size}. Current level: {self.current_level}") 
        return True 
 
    def leak(self): 
        if self.current_level > 0: 
            leaked_size = min(self.leak_rate, self.current_level) 
            self.current_level -= leaked_size 
            print(f"Leaky Bucket: Leaked {leaked_size}. Current level: {self.current_level}") 
 
def main(): 
    bucket = LeakyBucket(capacity=10, leak_rate=1) 
    for _ in range(10): 
        packet_size = random.randint(1, 5) 
        bucket.add_packet(packet_size) 
        bucket.leak() 
        time.sleep(1) 
 
if __name__ == "__main__": 
    main() 