#! /bin/bash

read -p "Enter a Year to check: " Year
if (($Year <= 0)); then
	echo Not a valid Year
	exit
fi

if (($Year % 400 == 0 )) ; then
	echo "The Year $Year is a Leap year."
elif (($Year % 100 == 0)) ; then
	echo "The Year $Year is not a Leap Year."
elif (($Year % 4 == 0)) ; then
	echo "The Year $Year is a Leap Year."
fi
