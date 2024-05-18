#! /bin/bash

echo "Enter the numbers: ";
read -a nums

#Createing a partition function to partition around a pivot

function partition(){		#args passed will be left,right
	i=$(($1-1))
	pivot=${nums[$2]}
	for((j=$1;j<$2;j++))
		do
		if ((${nums[$j]}<$pivot));then
			i=$(($i+1))
			t=${nums[$i]}
			nums[$i]=${nums[$j]}
			nums[$j]=$t
		fi

		done
	i=$(($i+1))
	t=${nums[$2]}
	nums[$2]=${nums[$i]}
	nums[$i]=$t
	nums=("${nums[@]}" "$i")	#Turn the result of this computation as a list and send back
	echo ${nums[@]}
}
#Creating a Recursive Quick_sort function

function Quick_sort(){		#args will be left,right
	if (($1<$2));then
		nums=($(partition $1 $2))
		Pos=${nums[-1]}		#Get the Pivot index
		unset nums[-1]		#Now unset that extra value
		nums=($(Quick_sort $1 $(($Pos-1))))
		nums=($(Quick_sort $(($Pos+1)) $2))
		echo ${nums[@]}
	else
		echo ${nums[@]}
	fi

}

echo "The Unseorted array is: ${nums[@]}"
right=$((${#nums[@]}-1))
nums=($(Quick_sort 0 $right))

echo "The sorted array is: ${nums[@]}"
