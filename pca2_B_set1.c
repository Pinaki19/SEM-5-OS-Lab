#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t mutex[11];

typedef struct {
	int thread_no;
	int start,end;
	int arr[100],total;
}Range;

void display(Range* myrange){
	
	int i;
	int end=(myrange->start==0)? myrange->end+2:myrange->start+myrange->end;
	printf("\nPrimes between %d and %d are:",myrange->start,end);
	for(i=0;i<myrange->total;i++){
		printf("   %d",myrange->arr[i]);
	}
	printf("\n");
	
}

void * find_prime(void * arg){
	Range * this_range=(Range*)arg;
	volatile int thread_no=this_range->thread_no;
	int i,j,flag=0;
	int start=this_range->start,end=this_range->end;
//	printf("start: %d end: %d\n",this_range->start,this_range->end);
	if (start<2 && end==0){
		sem_wait(&mutex[thread_no]);
		sem_post(&mutex[thread_no+1]);
		pthread_exit(NULL);
	}
	start=(start<2)? 2:start;
	   for(i=start;i<=start+end;i++){
		flag=1;
		for(j=2;j<i&&flag;j++){
			if(i%j==0){
				flag=0;
			}

		}
		if(flag){
			this_range->arr[this_range->total]=i;
			this_range->total+=1;
		}
 	   }
	sem_wait(&mutex[thread_no]);
	int next=thread_no+1;
	display(this_range);

	sem_post(&mutex[next]);
	pthread_exit(NULL);
}

void main(){
	
	int i,n;
	printf("Enter the number: ");
	scanf("%d",&n);
	if(n<10){
		printf("Enter positive number: ");
		return;
	}

	int parts=n/10;
	int left=n%10;
	Range ranges[10];
	pthread_t threads[10];
	for(i=0;i<10;i++){
		if(i==0){
			sem_init(&mutex[i],0,1);
		}else{
			sem_init(&mutex[i],0,0);
		}
		ranges[i].thread_no=i;
		ranges[i].start= parts*i;
		ranges[i].end=(i==9)? parts-1+left:parts-1;
		ranges[i].total=0;
	}
	for(i=0;i<10;i++)
		pthread_create(&threads[i],NULL,find_prime,&ranges[i]);
	pthread_exit(NULL);	
}
