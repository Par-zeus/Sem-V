import time 
import random 
 
class TokenBucket: 
    def __init__(self, capacity, token_rate): 
        self.capacity = capacity  # Maximum capacity of the token bucket 
        self.token_rate = token_rate  # Rate at which tokens are generated 
        self.current_tokens = 0  # Current number of tokens 
        self.last_time = time.time()  # Last time tokens were added 
 
    def add_tokens(self): 
        current_time = time.time() 
        elapsed = current_time - self.last_time 
        new_tokens = int(elapsed * self.token_rate)
        self.current_tokens = min(self.capacity, self.current_tokens + new_tokens) 
        self.last_time = current_time 
        print(f"Token Bucket: Current tokens: {self.current_tokens}") 
 
    def consume_token(self, packet_size): 
        if packet_size > self.current_tokens: 
            print(f"Token Bucket: Packet of size {packet_size} dropped (not enough tokens).") 
            return False 
        self.current_tokens -= packet_size 
        print(f"Token Bucket: Packet of size {packet_size} sent. Remaining tokens: {self.current_tokens}") 
        return True 
 
def main(): 
    bucket = TokenBucket(capacity=10, token_rate=2) 
    for _ in range(15): 
        bucket.add_tokens() 
        packet_size = random.randint(1, 5) 
        bucket.consume_token(packet_size) 
        time.sleep(1) 
 
if __name__ == "__main__": 
    main() 