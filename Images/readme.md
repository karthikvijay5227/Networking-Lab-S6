#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BUCKET_CAPACITY 10  // Maximum bucket size
#define OUTPUT_RATE 1       // Packets per second

int main() {
    int bucket_size = 0;  // Current bucket size

    while (true) {
        // Generate incoming packets randomly
        int incoming_packets = rand() % 5;

        printf("Incoming packets: %d\n", incoming_packets);

        // Add incoming packets to the bucket
        bucket_size += incoming_packets;

        // Check if the bucket is overflowing
        if (bucket_size > BUCKET_CAPACITY) {
            printf("Bucket overflow! Dropping packets: %d\n", bucket_size - BUCKET_CAPACITY);
            bucket_size = BUCKET_CAPACITY;  // Reset bucket size to maximum capacity
        }

        // Process outgoing packets
        if (bucket_size > 0) {
            int outgoing_packets = bucket_size < OUTPUT_RATE ? bucket_size : OUTPUT_RATE;

            printf("Outgoing packets: %d\n", outgoing_packets);

            // Subtract outgoing packets from the bucket
            bucket_size -= outgoing_packets;
        }

        sleep(1);  // Wait for 1 second
    }

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BUCKET_CAPACITY 10  // Maximum bucket size
#define OUTPUT_RATE 1       // Packets per second

void processIncomingPackets(int *bucket_size) {
    int incoming_packets;
    printf("Enter the number of incoming packets: ");
    scanf("%d", &incoming_packets);

    printf("Incoming packets: %d\n", incoming_packets);

    *bucket_size += incoming_packets;

    if (*bucket_size > BUCKET_CAPACITY) {
        printf("Bucket overflow! Dropping packets: %d\n", *bucket_size - BUCKET_CAPACITY);
        *bucket_size = BUCKET_CAPACITY;
    }
}

void processOutgoingPackets(int *bucket_size) {
    if (*bucket_size > 0) {
        int outgoing_packets = *bucket_size < OUTPUT_RATE ? *bucket_size : OUTPUT_RATE;

        printf("Outgoing packets: %d\n", outgoing_packets);

        *bucket_size -= outgoing_packets;
    } else {
        printf("No outgoing packets.\n");
    }
}

int main() {
    int bucket_size = 0;

    while (true) {
        printf("\n");
        printf("1. Process incoming packets\n");
        printf("2. Process outgoing packets\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                processIncomingPackets(&bucket_size);
                break;
            case 2:
                processOutgoingPackets(&bucket_size);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }

        sleep(1);  // Wait for 1 second
    }

    return 0;
}


