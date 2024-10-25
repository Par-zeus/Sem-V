#include <stdio.h>

// Function to simulate the leaky bucket algorithm
void leakyBucket(int incomingPacketSize, int bucketSize, int outputRate) {
    int bucketContent = 0;
    int time = 0;

    printf("Time\tIncoming\tBucket_Content\tSent\tDropped\n");
    while (incomingPacketSize > 0 || bucketContent > 0) {
        int sent = (bucketContent > outputRate) ? outputRate : bucketContent; // Amount to send
        int dropped = 0;

        if (incomingPacketSize > 0) {
            // If incoming data fits in the bucket, add it
            if (bucketContent + incomingPacketSize <= bucketSize) {
                bucketContent += incomingPacketSize;
            } else {
                // If incoming data exceeds bucket size, drop the extra
                dropped = incomingPacketSize - (bucketSize - bucketContent);
                bucketContent = bucketSize; // Fill the bucket to its max size
            }
        }

        // Display current status
        printf("%d\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t%d\n", time, incomingPacketSize, bucketContent, sent, dropped);

        // Remove data from the bucket at the output rate
        bucketContent -= sent;

        // Simulate next time step
        incomingPacketSize = 0; // No more incoming data after the first iteration
        time++;
    }
}

int main() {
    int incomingPacketSize, bucketSize, outputRate;

    // Example values for the algorithm
    incomingPacketSize = 10;   // Size of incoming data
    bucketSize = 15;           // Size of the bucket
    outputRate = 5;            // Rate at which data leaves the bucket

    leakyBucket(incomingPacketSize, bucketSize, outputRate);

    return 0;
}
