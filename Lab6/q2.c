//Name: AHAN BANDYOPADHYAY
//Roll No.: 211210008
//Date: 19/9/23
//CSB302 OS LAB6

//Q2.Write a C/C++ program to implement the producer-consumer problem using semaphores,
//where the consumer cannot consume until the buffer is full and the producer cannot produce until the buffer is empty.
//The buffer should have a fixed size of 10.

#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

typedef int semaphore;  //Semaphores ae a special kind of int
sem_t mutex; //Controls access to critical region 1
sem_t empty;  //Counts empty buffer slots N
sem_t  full;  //Counts full buffer slots 0
int count = 0; //What we're putting in

#define BUFFER_SIZE 10

sem_t mutex, full, empty;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int item = 1;

void *producer(void *arg) {
	if(item == 11)
		printf("Buffer Full\n");
	else{
		sem_wait(&empty);
		sem_wait(&mutex);

		buffer[in] = item;
		printf("Produced: %d\n", item);
		item++;
		in = (in + 1) % BUFFER_SIZE;

		sem_post(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *arg) {
	if(item == 0)
		printf("Buffer Empty\n");
	else{
		sem_wait(&full);
		sem_wait(&mutex);

		printf("Consumed: %d\n", item);
		item--;
		out = (out + 1) % BUFFER_SIZE;

		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    int choice;
    printf("Choose an operation:\n");
    printf("1. Start Producer\n");
    printf("2. Start Consumer\n");
    printf("3. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                pthread_create(&producer_thread, NULL, producer, NULL);
                break;
            case 2:
                pthread_create(&consumer_thread, NULL, consumer, NULL);
                break;
            case 3:
                sem_destroy(&mutex);
                sem_destroy(&full);
                sem_destroy(&empty);
                return 0;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
