#! /bin/bash

read -p "Enter a username: " User
egrep -q "^$User:" /etc/passwd
if (($?==0));then
	echo "User Exists!"
else
	echo User Does not Exists!
fi
