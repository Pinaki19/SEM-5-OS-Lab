#pragma once
#include <sys/types.h>
#define BUFFER_SIZE 256


typedef struct {
	pid_t Spid,Cpid;
	char buff[BUFFER_SIZE];

}Shared_Buffer;


void smem_init(Shared_Buffer * smem){
	smem->Spid=0;
	smem->Cpid=0;
	strcpy(smem->buff,"\0");
}


void* smem_attach(int smid){
	return shmat(smid,NULL,0);
}


void smem_detach(void * smemaddr){
	shmdt(smemaddr);

}

void smem_destroy(int smid){
	
	shmctl(smid,IPC_RMID,NULL);
}

