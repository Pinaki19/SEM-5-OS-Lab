#! /bin/bash
read -p "Enter number of terms: " n
if (($n<=0));then
	exit
fi
Fibo_series=(0 1)
i=2
while (($i<$n))
	do
	Fibo_series+=($((Fibo_series[$i-1]+Fibo_series[$i-2])))
	i=$(($i+1))
	done

echo ${Fibo_series[@]:0:$n}
