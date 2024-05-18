#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"
#include <unistd.h>
sem_t mutex,full,empty;

void * producer_function(void * mybuffer){
	int item=0;
	while(1){
		item++;
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer_insert((Buffer*)mybuffer,item);
		printf("Producer added %d at index: %d\n",item,((Buffer*)mybuffer)->rear);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void * consumer_function(void * mybuffer){
	int item,front;
	while(1){
		sleep(3);
		sem_wait(&full);
		sem_wait(&mutex);
		item=buffer_consume((Buffer*)mybuffer);
		front=((Buffer*)mybuffer)->front;
		if(front>0)
			printf("\n\nConsumed item : %d from index: %d\n",item,((Buffer*)mybuffer)->front-1);
		else
			printf("\n\nConsumed item : %d from index: %d\n",item,((Buffer*)mybuffer)->size-1);
		sem_post(&mutex);
		sem_post(&empty);
	}
}

void main(){
	

	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,5);

	pthread_t producer_id,consumer_id;
	
	Buffer mybuffer;
	
	if((buffer_init(&mybuffer,5))==0){
		printf("\nTry again! Failed to create Buffer!\n");
	}
	
	pthread_create(&producer_id,NULL,producer_function,(void *)&mybuffer);
	pthread_create(&consumer_id,NULL,consumer_function,(void*)&mybuffer);

	pthread_join(producer_id,NULL);

	pthread_join(consumer_id,NULL);



}
