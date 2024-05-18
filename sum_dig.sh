#! /bin/bash

read -p "Enter a number: " num
Num=$num
if [[ $((num)) != $num ]] ; then
	echo  "This is not a number"
	exit
fi

if ((num < 0 )); then
	echo "Negetive number is not alowed."
	exit
fi
rem=0
while (( num > 0 ))
	do 
	rem=$(($rem + $num % 10))
	num=$(($num / 10))
	done
echo "Sum of digits of the number $Num is $rem"

