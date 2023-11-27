//Name: AHAN BANDYOPADHYAY
//Roll No.: 211210008
//Date: 19/9/23
//CSB302 OS LAB6

//Q1. Implement a producer-consumer problem in C. Given the common fixed-size buffer, the task is to make sure that the producer can't add data into the buffer when it is full and the consumer can't remove data from an empty buffer.

//Problem: Given the common fixed-size buffer, the task is to make sure that the producer can’t add data into the buffer when it is full and the consumer can’t remove data from an empty buffer.

//Solution: The producer is to either go to sleep or discard data if the buffer is full. The next time the consumer removes an item from the buffer, it notifies the producer, who starts to fill the buffer again. In the same manner, the consumer can go to sleep if it finds the buffer to be empty. The next time the producer puts data into the buffer, it wakes up the sleeping consumer.

// C program for the above approach

#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10;
int x = 0;

//producer function to produce an item
void producer()
{
	--mutex;
	++full;
	--empty;
	x++;
	printf("\nProducer produces item %d", x);
	++mutex;
}

//consumer function to consume an item
void consumer()
{
	--mutex;
	--full;
	++empty;
	printf("\nConsumer consumes item %d", x);
	x--;
	++mutex;
}

int main()
{
	int n, i;
	
	printf("Menu of operations: \n");
	printf("\nOption 1. Producer function"
		"\nOption 2. Consumer function"
		"\nOption 3. Exit program");

	#pragma omp critical

	for (i = 1; i > 0; i++) {
		printf("\nEnter your option:");
		scanf("%d", &n);

		switch (n) {
		case 1:
			if ((mutex == 1) && (empty != 0)) {producer();}

			else {printf("Buffer is full!");}

			break;

		case 2:
			if ((mutex == 1) && (full != 0)) {consumer();}

			else {printf("Buffer is empty!");}

			break;

		case 3:
			exit(0);

			break;
		}
	}
	
	return 0;
}

