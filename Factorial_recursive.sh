#! /bin/bash

read -p "Enter a number: " n

if (($n<0)) ;then
	echo Number can\'t be Negetive
	exit
fi


function Fact(){
	if (($1==0));then
		echo 1
	else
		echo $(($1*$(Fact $(($1-1)))))
	fi
}

echo "Factorial of $n is $(Fact $n)"
