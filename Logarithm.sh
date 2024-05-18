#! /bin/bash

n=$#
if ((n!=1));then
	echo "Wrong number of Arguments passed!"
	exit
fi

a=$(echo "l($1)" | bc -l)
b=$(echo "l(10)" | bc -l)
Res=$(echo "scale=2;$a/$b"| bc -l)
echo "Common Logarithm of $1 is : " $Res
