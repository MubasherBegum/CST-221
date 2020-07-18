#!/usr/bin/bash

#	@Author: Mubasher Mehnaz Begum
#	@Assignment: CST-221 Security
#   @Description: Write bash script to test for password strength and determine if its weak
#	I.	Minimum length of 8 characters
#	II.	Must contain at least one numeric character
#	III.	Must contain at least one of the following non-alphabetic characters: @, #, $, %, &, *, +, -, =


count=0

echo 'Enter Password'
read password;

length=${#password}

#Check if password is less than 8 characters	
if [[ "$length" -lt "8" ]]; then
	
	echo 'Password should be greater than 8 characters.'
else
	let "count++"

fi
#Check if password has at least one number
if [[ "$password" =~ [0-9] ]]; then

	let "count++"
else	
	echo 'Password should contain atleast one numeric character.'
fi
#Check if Password has one alpha-numeric characters
if [[ $password == *[\@\#\$\%\&\*\+\-\=]* ]]; then
	let "count++"
else
	echo 'Password should contain atleast one special character.'
fi
#If it passed all checks
if [ $count == 3 ]; then
	echo 'Password meets all the required criteria.'
fi

