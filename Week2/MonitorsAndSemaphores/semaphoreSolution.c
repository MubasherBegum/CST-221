/* 
@Program: CST – 221 Monitors and Semaphores -Using Semaphores
@Author: Mubasher Mehnaz Begum
@Date:   June 14, 2020

@About: Define a simple scenario where Semaphores can be used

@Solution: Following is a solution to a senario where in multiple threads access make a credit card transaction. 

*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//Define semaphore
sem_t mySemaphore;

// Credit card information

long int cardNumber = 3405672355345679;
double balance = 1500;


void *onlinePurchase1(){
		
	//wait
        sem_wait(&mySemaphore);
	//critical section	
	if (cardNumber == 3405672355345679) {
			//Debit $100 from this card
			printf("Online Purchase 1: Card %ld has credit $%f\n", cardNumber, balance);
			balance = balance - 100; 
			
			sleep(2);
			printf("Transaction debited $100 from Card %ld. Total credit available is $%f\n", cardNumber, balance);
			//Transaction is completed, release lock
			printf("Transaction is completed!\n"); 
			//Signal
			sem_post(&mySemaphore);	
	}
		else { 
			printf("The Credit card %ld cannot be accessed right now for Online purchase1, try again later\n", cardNumber);
		} 
}

void *onlinePurchase2(){
	//wait
        sem_wait(&mySemaphore);
        //critical section	
	if (cardNumber == 3405672355345679) {
			//Debit $250 from this card
			printf("Online Purchase 2: Card %ld has credit of $%f\n", cardNumber, balance);
			balance = balance - 250; 
			
			sleep(2);
			printf("Transaction debited $250 from Card %ld. Total credit available is $%f\n", cardNumber, balance);
			//Transaction is completed, release lock
			printf("Transaction is completed!\n"); 
			//signal
			sem_post(&mySemaphore);
		}
		else {
			printf("The Credit card %ld cannot be accessed right now for Online purchase2, try again later\n", cardNumber);
		} 
}


int main(){
	sem_init(&mySemaphore, 0, 1);
	//Create the two threads variables purchase1 and purchase2
	pthread_t purchase1, purchase2;
	pthread_create(&purchase1, 0, onlinePurchase1, 0);
	
	sleep(2);
	pthread_create(&purchase2, 0, onlinePurchase2, 0);
	
	//Create the threads
	printf("Starting threads\n");
	pthread_join(purchase1, 0);
	pthread_join(purchase2, 0);

	//report the new state of the bank funds
	printf("Total credit available is $%f\n", balance);
	sem_destroy(&mySemaphore);
	//exit the program
	return 0;

}


