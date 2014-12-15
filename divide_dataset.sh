#!/bin/sh
cd $1
total_files="$(find *.fast5 -maxdepth 1|wc -l)"
training_count=$((total_files * 3/5)) 
test_count=$((total_files * 4/5))
validation_count=$((total_files))
mkdir validation
mkdir test
mkdir training
#echo $training_count
count=0
input_files=*.fast5
for input_file in $input_files
do
	
	if [ $count -lt $training_count ]
	then
		mv $input_file training/$input_file
	elif [ $count -lt $test_count ]
	then
		mv $input_file test/$input_file
	else
		mv $input_file validation/$input_file
	fi
	count=$((count+1))
done
#while [ $total_files -gt 0 ] 
#do
	#echo $total_files
	#total_files=$((total_files-1))
	#$total_files = $total_files - 1
	
#done