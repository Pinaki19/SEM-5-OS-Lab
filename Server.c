#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include "smem.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signum){
	int n=1;
}

void main(){
	
	signal(SIGCONT,handler);
	char input[256];
	int smid=shmget(1235,sizeof(Shared_Buffer),IPC_CREAT|0666);
	printf("%d",smid);
	
	Shared_Buffer * smemaddr=(Shared_Buffer*)smem_attach(smid);
	
	smem_init(smemaddr);
	smemaddr->Spid=getpid();
	
	while(1){
		pause();
		int flag=1;
		strcpy(input,smemaddr->buff);

		if(strcmp(input,"exit")==0)
			break;
		else{
			int l=0,h=strlen(input)-1;
			while(h>l){
				if(input[l++]!=input[h--]){
					flag=0;
					break;
				}
			}
		}
		
		if(flag){
			strcpy(smemaddr->buff,"PALINDROME");
		}else{
			strcpy(smemaddr->buff,"NOT PALINDROME");
		}
		
		kill(smemaddr->Cpid,SIGCONT);
	}

	smem_detach((void*)smemaddr);
	
	smem_destroy(smid);

}

