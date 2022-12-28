#!/bin/bash

make

for FILE in $(find tests/ | grep ".imp")
do
	FILE_NAME="$( echo "$FILE" | awk '{ print substr( $0, 1, length($0) - 4 ) }' )"
	OUTPUT_FILE="$( echo $FILE_NAME ).mr"
	CORRECT_FILE="$( echo $FILE_NAME )_correct.out"
	
	# error tests
	if [[ $FILE == *"error"* ]]; 
	then
		echo "Launching test for $FILE"
		./kompilator $FILE $OUTPUT_FILE > $OUTPUT_FILE
		
		DIFF=$( diff $OUTPUT_FILE $CORRECT_FILE )
		if [ "$DIFF" == "" ]
		then
			echo -e "\033[0;32mTest for $FILE completed!\033[0m"
		else
			echo -e "\033[0;31mTest for $FILE failed!\033[0m"
		fi
	fi
done