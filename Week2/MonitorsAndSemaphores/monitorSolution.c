/* 
@Program: CST – 221 Monitors and Semaphores -Using Monitors
@Author: Mubasher Mehnaz Begum
@Date:   June 14, 2020

@About: Define a simple scenario where Monitors can be used

@Solution: Following is a solution to a senario where in multiple threads access make a credit card transaction. 

*/

#include <stdio.h>
#include <pthread.h>

//Define Monitor by use of mutex
pthread_mutex_t monitor_lock;


// Credit card information

long int cardNumber = 3405672355345679;
double balance = 1500;

//Actions of two ATM's attempting to acces bank account 576009

void *onlinePurchase1(){
		//Lock this purchase
		if (cardNumber == 3405672355345679) {
			pthread_mutex_lock(&monitor_lock);
			//Debit $100 from this card
			printf("Online Purchase 1: Card %ld has credit $%f\n", cardNumber, balance);
			balance = balance - 100; 
			printf("Transaction debited $100 from Card %ld. Total credit available is $%f\n", cardNumber, balance);
			//Transaction is completed, release lock
			printf("Transaction is completed!\n"); 
			pthread_mutex_unlock(&monitor_lock);
		}
		else { 
			printf("The Credit card %ld cannot be accessed right now for Online purchase1, try again later\n", cardNumber);
		} 
}

void *onlinePurchase2(){
		//Lock this purchase
		if (cardNumber == 3405672355345679) {
			pthread_mutex_lock(&monitor_lock);
			//Debit $250 from this card
			printf("Online Purchase 2: Card %ld has credit of $%f\n", cardNumber, balance);
			balance = balance - 250; 
			printf("Transaction debited $250 from Card %ld. Total credit available is $%f\n", cardNumber, balance);
			//Transaction is completed, release lock
			printf("Transaction is completed!\n"); 
			pthread_mutex_unlock(&monitor_lock);
		}
		else {
			printf("The Credit card %ld cannot be accessed right now for Online purchase2, try again later\n", cardNumber);
		} 
}


int main(){
	//Create the two threads variables purchase1 and purchase2
	pthread_t purchase1, purchase2;
	pthread_mutex_init(&monitor_lock, 0);
	pthread_create(&purchase1, 0, onlinePurchase1, 0);
	pthread_create(&purchase2, 0, onlinePurchase2, 0);
	
	//Create the threads
	printf("Starting threads\n");
	pthread_join(purchase1, 0);
	pthread_join(purchase2, 0);

	//report the new state of the bank funds
	printf("Total credit available is $%f\n", balance);

	//exit the program
	return 0;

}


