#! /usr/bin/bash

read -p "Enter a year: " year

regex="^[0-9]+$"

function leap(){
	
	if (( $1%400==0 ));then
		echo "Leap year"
	elif (( $1%4==0 && $1%100!=0 ));then
		echo "Leap year"
	else
		echo "Not Leap year"
	fi

}

if [[ $year =~ $regex ]];then
	leap "$year"
else
	echo "Input not valid"
fi
