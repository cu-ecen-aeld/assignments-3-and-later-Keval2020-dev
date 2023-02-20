#!/bin/sh

#creating function def
func() {

	 #should be 2 arguments passed 
	
	if [ $# != 2 ]; then
	      
	      echo "Enter 2 Arguments"
	      exit 1 #error
	
	else
	 
	 filesdir=$1
	 searchstr=$2
	  
		if [ -d "$filesdir" ]; then
			files=$(find  "$filesdir"  -type f | wc -l)
			lines=$(grep -r "$searchstr" "$filesdir" | wc -l)
			echo "The number of files are $files and the number of matching lines are $lines"
		else
			echo "directory does not exist"
			exit 1
		fi
	fi
}

func $1 $2
