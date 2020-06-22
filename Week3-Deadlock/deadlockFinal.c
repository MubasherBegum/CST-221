/* 
@Program: CST-221 Deadlock Avoidance
@Author: Mubasher Mehnaz Begum
@Date:   June 21, 2020
@About: Consider a scenario in which several processes compete for accessing the same resource (e.g. a file or some memory address). 
When a process is starved due to resource unavailability a timer is used to stop the process after a predetermined time interval. 
Once the process is terminated, it can be restarted, attempting to gain access to the desired resource. 
Create a C program that implements the scenario. Print the necessary process data to show a log of activities: 
which processes are running, what resource they are trying to access, whether the resource is available, and whether the process is starved. 

@Solution: Following program is written using mutex lock and timers. A Mutex is a lock that we set before using a shared resource and release after using it.
When the lock is set, no other thread can access the locked region of code.
So we see that even if thread 2 is scheduled while thread 1 was not done accessing the shared resource and the 
code is locked by thread 1 using mutexes then thread 2 cannot even access that region of code.
So this ensures synchronized access of shared resources in the code. In addition, a timer is also implemented which is 
activated whenever the pthreads are waiting.
*/


/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/* Declare Variables used*/
pthread_t tid[4];
pthread_mutex_t lock;
int counter;
int thread_id [4];
int shared_data = 10;
FILE * file;


//Test method to check process functionality of threads, successful
void* firstTest (){
	pthread_mutex_lock(&lock);
	counter += 1;
	printf("firstTest Process %d accessing counter %d \n", getpid(), counter);
	sleep(3);
	printf("firstTest Process %d exiting.\n", counter);
	pthread_mutex_unlock(&lock);
	return NULL;
}


/* Crtical section of function	*/
void* getCritical (){
	char message [100];
	strcpy(message, "Process %d accessing shared resource, num: %d \n");
	printf(message, getpid(), shared_data);
	sleep((int)0.5);
	fprintf(file, message, getpid(), shared_data);
	pthread_mutex_unlock(&lock);
	return NULL;
}

/* Function - Access shared resources */
void* processFunction (){
	//clock timer for thread stop
	clock_t start_clock = clock();
	char message [100];
	printf("Increment Counter before before entering critical section: %d\n", ++counter);
	fprintf(file, "Increment Counter before before entering critical section : %d\n", ++counter);
	
	//Checking for process starvation
	while (!pthread_mutex_trylock(&lock))
	{
		//Check if process starvation occured
		if ((clock() - start_clock) > 2) 
		{
			strcpy(message, "In Sleep mode as Thread %d is starved.\n");
			printf(message, getpid());
			fprintf(file, message, getpid());
			//process downtime before restart
			printf("Counter increment inside critical selection: %d\n", ++counter);
			fprintf(file, "Counter increment inside critical selection: %d\n", ++counter);
			sleep(4);
			strcpy(message, "Thread %d is in wake up mode.\n");
			printf(message, getpid());
			fprintf(file, message, getpid());
			//reset clock in case of additional starvation
			start_clock = clock();
		}
	}
	//access critical section now
	getCritical();
}

//One method to utilize pthreads to handle shared resource
void* testMethod1 (){
	//Variables to initialize processes
	int i = 0;
	int y = 0;
	file = fopen("outputLog.txt", "w");
	pthread_mutex_init(&lock, NULL);

	//Create and assign the body of each thread
	while (i < 4) {
		pthread_create(&(tid[i]), NULL, &processFunction, NULL);
		i++;
	}
	//Join threads for execution
	while (y < 4) {
		pthread_join(tid[y], NULL);
		y++;
	}
	//Destroy the mutex lock and exit
	pthread_mutex_destroy(&lock);
}

/* Driver method - Create/Join Threads */
int main (void){
	//testing few methods
//	firstTest();
//	testMethod1();

	file = fopen("outputLog.txt", "w");
	pthread_mutex_init(&lock, NULL);
	fork();
	fork();
	
	//create and assign thread, call processFunction
	pthread_t thread;
	pthread_create(&thread, NULL, processFunction(), NULL);
	return 0;

}
