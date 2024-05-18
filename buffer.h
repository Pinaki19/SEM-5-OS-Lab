#pragma once
#include <stdlib.h>

typedef struct {
	int size,front,rear;
	int * data;
}Buffer;


int buffer_init(Buffer * buffer,int size){
	buffer->size=size;
	buffer->front=-1;
	buffer->rear=-1;

	buffer->data=(int *) malloc(size*sizeof(int));
	if(buffer->data==NULL)
		return 0;
	return 1;

}


void buffer_insert(Buffer * buffer, int item){
	if((buffer->rear+1)%buffer->size == buffer->front)
		return;

	if(buffer->front<0)
		buffer->front+=1;
	buffer->rear+=1;
	buffer->rear%=buffer->size;
	buffer->data[buffer->rear]=item;
}


int buffer_consume(Buffer * buffer){
	if(buffer->front<0)
		return -1;

	int d=buffer->data[buffer->front];
	buffer->front+=1;
	buffer->front%=buffer->size;
	return d;

}


void buffer_destroy(Buffer* buffer){
	free(buffer->data);
	buffer->size=0;
	buffer->front=-1;
	buffer->rear=-1;
}
