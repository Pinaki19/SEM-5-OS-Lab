#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "smem.h"
#include <unistd.h>
#include <signal.h>

void handler(int signum){
	int n=1;
}


void main(){
	signal(SIGCONT,handler);
	char input[256];
	int smid=shmget(1235,sizeof(Shared_Buffer),0);
	
	Shared_Buffer * smemaddr=(Shared_Buffer*)smem_attach(smid);
	
	while(smemaddr->Cpid!=0);

	smemaddr->Cpid=getpid();
	

	while(1){
		printf("Enter your input: ");
		scanf(" %[^\n]s",input);
	
		if(strcmp(input,"exit")==0){
			strcpy(smemaddr->buff,input);
			kill(smemaddr->Spid,SIGCONT);
			break;
		}
			
		else{
		
			strcpy(smemaddr->buff,input);
			kill(smemaddr->Spid,SIGCONT);
		}
		pause();
		printf("The input %s is %s\n",input,smemaddr->buff);
	}

	
	smem_detach((void*)smemaddr);
}



