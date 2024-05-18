#! /bin/bash
n=$#
if (($#==0));then
	echo No Argument has been passed.
	exit
fi
sum=0
while((n>0))
	do
	sum=$(($sum+$1))
	shift
	n=$(($n-1))
	done
echo "Sum of the given numbers are: $sum"
	


