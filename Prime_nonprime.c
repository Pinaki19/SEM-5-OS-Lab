#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void * check_prime(void * number){
	
	char * result=malloc(20*sizeof(char));

	char * is_prime="PRIME";
	char *not_prime="NOT PRIME";
	
	if(*(long *)number <2){
		strcpy(result,not_prime);
	}else{
		long i;
		long n=*(long *)number;
		for(i=2;i<n;i++){
			if(n%i==0){
				strcpy(result,not_prime);

				pthread_exit(result);
			}
		}

		strcpy(result,is_prime);
	
	}
	
	pthread_exit(result);
}


void main(){

	pthread_t thread_id;
	long n;
	printf("Enter a number: ");
	scanf("%ld",&n);
	pthread_create(&thread_id,NULL,check_prime,(void*) &n);
	char result[50];
	pthread_join(thread_id,(void **)&result);

	printf("\nThe number %ld is %s \n",n,*(char**)result);

}
