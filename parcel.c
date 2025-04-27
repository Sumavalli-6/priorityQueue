#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parcel structure
struct Parcel {
    char name[100];
    int priority; // 1 = Urgent, 2 = Normal, 3 = Low
    struct Parcel* next;
};

struct Parcel* front = NULL; // Front of the queue

// Create a new parcel
struct Parcel* createParcel(char name[], int priority) {
    struct Parcel* newParcel = (struct Parcel*)malloc(sizeof(struct Parcel));
    strcpy(newParcel->name, name);
    newParcel->priority = priority;
    newParcel->next = NULL;
    return newParcel;
}

// Add parcel based on priority
void enqueue(char name[], int priority) {
    struct Parcel* newParcel = createParcel(name, priority);

    if (front == NULL || priority < front->priority) {
        newParcel->next = front;
        front = newParcel;
    } else {
        struct Parcel* temp = front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newParcel->next = temp->next;
        temp->next = newParcel;
    }
}

// Remove parcel with highest priority
void dequeue() {
    if (front == NULL) {
        printf("No parcels to deliver.\n");
    } else {
        printf("Delivering Parcel: %s (Priority: %d)\n", front->name, front->priority);
        struct Parcel* temp = front;
        front = front->next;
        free(temp);
    }
}

// Show all parcels
void display() {
    if (front == NULL) {
        printf("No parcels in queue.\n");
    } else {
        struct Parcel* temp = front;
        printf("Parcel List:\n");
        while (temp != NULL) {
            printf("Parcel: %s | Priority: %d\n", temp->name, temp->priority);
            temp = temp->next;
        }
    }
}

// Main program
int main() {
    enqueue("Parcel1", 2); // Normal
    enqueue("Parcel2", 1); // Urgent
    enqueue("Parcel3", 3); // Low
    enqueue("Parcel4", 1); // Urgent

    display(); // Show all parcels

    printf("\nDelivering parcels:\n");
    dequeue(); // Deliver highest priority parcel
    dequeue();

    printf("\nParcels left in queue:\n");
    display(); // Show remaining parcels

    return 0;
}
