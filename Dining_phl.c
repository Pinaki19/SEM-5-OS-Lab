#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define MAX_ITERATION 10
#define NUM_PHILOSOPHERS 5
#define LEFT_NEIGHBOUR(x) ((x+NUM_PHILOSOPHERS-1)%NUM_PHILOSOPHERS)
#define RIGHT_NEIGHBOUR(x) (x+1)%NUM_PHILOSOPHERS
#define LEFT_FORK(x) (x)
#define RIGHT_FORK(x) (x+1)%NUM_PHILOSOPHERS
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct {
    int state[NUM_PHILOSOPHERS];
    sem_t forks[NUM_PHILOSOPHERS];
    sem_t mutex;
} Shared;

void initialize_shared_data(Shared *shared_data) {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        shared_data->state[i] = THINKING;
        sem_init(&shared_data->forks[i], 1, 1);
    }
    sem_init(&shared_data->mutex, 1, 1);
}

void take_forks(Shared *shared_data, int philosopher_num) {
    int left_fork = LEFT_FORK(philosopher_num);
    int right_fork =  RIGHT_FORK(philosopher_num);

    sem_wait(&shared_data->mutex);
    shared_data->state[philosopher_num] = HUNGRY;
    printf("Philosopher %d is eating. Picked up forks %d and %d.\n", philosopher_num,left_fork, right_fork);
    sem_post(&shared_data->mutex);

    sem_wait(&shared_data->forks[left_fork]);
    sem_wait(&shared_data->forks[right_fork]);
}

void put_forks(Shared *shared_data, int philosopher_num) {
    int left_fork = LEFT_FORK(philosopher_num);
    int right_fork = RIGHT_FORK(philosopher_num);

    sem_wait(&shared_data->mutex);
    shared_data->state[philosopher_num] = THINKING;
    printf("Philosopher %d put down forks %d and %d.\n", philosopher_num, left_fork, right_fork);
    sem_post(&shared_data->mutex);

    sem_post(&shared_data->forks[left_fork]);
    sem_post(&shared_data->forks[right_fork]);
}

void philosopher(Shared *shared_data, int philosopher_num) {
    int left_neighbor = LEFT_NEIGHBOUR(philosopher_num);
    int right_neighbor = RIGHT_NEIGHBOUR(philosopher_num);
	
    int i=MAX_ITERATION;
    while (i--) {
        printf("Philosopher %d is thinking.\n", philosopher_num);
        sleep(1);  

        if (shared_data->state[right_neighbor] == THINKING && shared_data->state[left_neighbor] == THINKING) {
            take_forks(shared_data, philosopher_num);
            sleep(2);  
            put_forks(shared_data, philosopher_num);
        } else {
            printf("Philosopher %d did not get the forks.\n", philosopher_num);
        }
    }
}

int main() {
    
    Shared* shared_data;
    int smid = shmget(IPC_PRIVATE, sizeof(Shared), IPC_CREAT | 0666);
    if (smid < 0) {
        perror("Failed to create shared memory");
        return 1;
    }

    shared_data = (Shared*)shmat(smid, NULL, 0);
    if ((void *)shared_data == (void *)-1) {
        perror("Failed to attach to shared memory");
        return 1;
    }

    initialize_shared_data(shared_data);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            philosopher(shared_data, i);
            return 0;
        } else if (pid < 0) {  
            perror("Failed to fork");
            return 1;
        }
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }
    shmdt((void *)shared_data);
    shmctl(smid, IPC_RMID, NULL);

    return 0;
}
