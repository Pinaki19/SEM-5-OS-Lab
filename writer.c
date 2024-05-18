#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "buffer.h"
#define MAX 5
void main(){
	
	int smid=shmget(12345,sizeof(buffer),IPC_CREAT|0666);
	buffer* Buffer=(buffer*) shmat(smid,NULL,0);
	srand(time(NULL));
	buff_init(Buffer);
	int i=MAX;
	while(i--){
		printf("\nWriter is waiting to Write");
		sem_wait(&Buffer->write);
		int d=rand()%10000 + 100;
		printf("\nWriter wrote %d \n",d);
		buff_write(Buffer,d);
		sem_post(&Buffer->write);
		sleep(2);
	}
	
	shmdt(Buffer);
	
	shmctl(smid,IPC_RMID,0);

}
