#include <stdio.h>
#include <unistd.h>
#include "buffer.h"
#define MAX 5
void main(){
	
	int smid=shmget(12345,sizeof(buffer),IPC_CREAT|0666);
	buffer* Buffer=(buffer*) shmat(smid,NULL,0);
	int i=MAX;

	while(i--){
		sem_wait(&Buffer->mutex);
		Buffer->readercnt+=1;
		
		printf("\nTotal readers: %d",Buffer->readercnt);
		if(Buffer->readercnt==1)
			sem_wait(&Buffer->write);
		sem_post(&Buffer->mutex);
		printf("\nReader has read %d ",buff_read(Buffer));
		sleep(2);
		sem_wait(&Buffer->mutex);
		
		Buffer->readercnt-=1;
		
		printf("\nReader left. Total Readers left: %d \n",Buffer->readercnt);
		if(Buffer->readercnt==0)
			sem_post(&Buffer->write);
			
		sem_post(&Buffer->mutex);
		sleep(2);
		
	}
	
	shmdt(Buffer);

}
