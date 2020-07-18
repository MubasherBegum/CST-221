#!/usr/bin/bash

#	@Author: Mubasher Mehnaz Begum
#	@Assignment: CST-221 Security
#   @Description: bash script to manage users
#	The script will take three script arguments: an input filename of users, a group name, and an operation flag
#	The script adds and removes users to a Linux system using the input file provided to the script. 

#	Encrypt a string: echo -n "aaaabbbbccccdddd" | openssl enc -e -aes-256-cbc -a -salt

if [ $(id -u) -ne 0 ]; then
    echo
    echo "Not a superuser."
    echo
    exit 1
fi

#
# Validate argument count
#
if [ "$#" -ne 3 ]; then
    echo
    echo "Three arguments are required(userfile, usergroup, operation -a/-r)"
    echo
    exit 1
fi

#
# variables 
#
userfile=$1
group=$2
operation=$3

#
# Add group 
#
if grep -q $group /etc/group
then
    echo "Group $group exists!"
else
    groupadd $group
    [ $? -eq 0 ] && echo "Group is added" || echo "Failed to add Group"
fi

#
# Add User
#
if [[ "$operation" == "-a" ]]; then

    sed '/^[ \t]*$/d' $userfile | while read -r name pass
    do
        #
        # Assert name is a new user
        #
        egrep "^$name" /etc/passwd >/dev/null
        if [ $? -eq 0 ]; then
            echo "$name exists!"
            exit 1
        else
            adduser $name --disabled-password --gecos "" --ingroup $group
            [ $? -eq 0 ] && echo "Add User successful." || echo "*** Failed to add user. ***"

            usermod $name -p $pass
            [ $? -eq 0 ] && echo "User password successful." || echo "*** Failed to modify user password. ***"
            echo
        fi
    done
fi

#
# Remove User
#
if [[ "$operation" == "-r" ]]; then

    sed '/^[ \t]*$/d' $userfile | while read -r name pass
    do
        deluser $name --remove-home
        echo
    done

    if grep -q $group /etc/group
    then
        delgroup $group --only-if-empty
    else
        echo "*** Group does not exist. ***"
    fi

fi

exit 0
