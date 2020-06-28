/* 
@Program: Program that takes a decimal number between 0 and 4095 as input from a user 
@Author: Mubasher Mehnaz Begum
@Date:   June 28, 2020

@Description: program that takes a decimal number between 0 and 4095 as input from a user that performs the following operations on the input:
a.	Display the number as a 32-bit binary number displaying each binary digit as a 1 or 0 (with the least significant bit on right) on the console. 
b.	Display the number as a 32-bit hexadecimal number on the console. 
c.	Transform the input by shifting the number 16 bits to the left, then mask out (AND) the bottom 16 bits, 
and finally add (OR) the hex number 0x07FF to produce the final resultant number. 
Display the final result in binary, hexadecimal, and decimal to the console.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int i, j, x, final;
unsigned int decimal = -1, transform;
char binary_array [32];



void* displayBinary (){
	//Ensure that only valid numbers are calculated
	if (decimal >= 0 && decimal < 4096){
		unsigned int mask = 1<<31;
		//Loop to print binary number
		for (i = 0; i < 8; i++){
			for (j = 0; j < 4; j++){
				char c = (decimal & mask) == 0 ? '0' : '1';
				binary_array[x++] = c;
				putchar(c);
				mask >>= 1;
			}
			putchar(' ');
		}
		putchar('\n');
	}
}

void* displayHex (){
	//Easy, straightforward manner to print in hexidecimal
	printf("%04x\n", decimal);
}

void* calcDecimal (){
	printf("%s", "The number in binary: ");
	displayBinary();
	printf("%s", "The number in hexadecimal: ");
	displayHex();
}

void* numberTransform (){
	//Shift decimal vaiable 16 bits left
	transform = decimal << 16;
	//Mask out bottom 16 bits
	final = transform & decimal;
	unsigned int addition = 0x07FF;
	//Add new hex number
	final = final | addition;
	printf("New number in decimal: %d\n", final);
	decimal = final;
	//print decimal and print new numbers
	calcDecimal();
}

int main (void){
	
	//Take input from user
	printf("%s", "Please enter a number between 0 and 4095: ");
	scanf("%d", &decimal);

	if (decimal < 0 || decimal > 4095){
		printf("%s", "Only a number within range is accepted.\n");
	}
	else {
		//calculate and print
		calcDecimal();
		numberTransform();
		return 0;
	}
}
