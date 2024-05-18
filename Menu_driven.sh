#! /bin/bash
echo "1. Check File or Folder permission."
echo "2. Check Number and List Files and Folders."
echo "3. Check Number of users connected."
echo "4. Check last Modifcation time of a file"
echo "5. Press 5 to exit."
read -p "Enter your Choice: " n
while ((n!=5))
do
case $n in
"1")
	read -p "Enter name of your File or Folder: " File
	if [ -d $File ];then
		echo "Permissions of the Folder $File is: " $( ls -l|grep "$File"|cut -c 2-10) 
	elif [ -a $File ];then 
		echo "Permissions of this File $File is: " $( ls -l |grep "$File"|cut -c 2-10)
	else
		echo "No such File or Folder exists!"
	fi;;

"2")
	Dir=.		#Dir can be taken from user currently it runs on current folder i.e. (.)
	if [ -d $Dir ]; then
		Out=($(cd $Dir && ls ))
		Dirs=()
		Files=()
		for item in "${Out[@]}"
			do
			if [ -d $item ];then
				Dirs+=($item)
			else
				Files+=($item)
			fi
			done
		echo "This Directory has ${#Files[@]} Number of Files and ${#Dirs[@]} Number of Folders"
		echo "The Files are: ${Files[@]}"
		echo "The Foldres are: ${Dirs[@]}"
	fi;;
"3")
	echo "Number of Connected Users are: $(who|wc -l)"
	;;
"4")
	read -p "Enter Filename: " File
	if [ -a $File ];then
		echo  Last modification time of this file is: $(date -r $File|egrep -o "[0-9:]{8}")
	else
		echo Not a valid file.
	fi;;
"5")
	exit 0;;
*)
	echo "Please Give the correct option!";;
esac
read -p "Enter your choice: " n
done
