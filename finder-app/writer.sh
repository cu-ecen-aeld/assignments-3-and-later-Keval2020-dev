#!/bin/bash

#creating function def
func() {
        #should be 2 arguments passed 
	
	if [ $# != 2 ]; then
	      
	      echo "Enter 2 Arguments"
	      exit 1 #error
	
	fi

	      mkdir -p "$(dirname "$1")"
	      touch "$1"
		
	      if [ ! -f "$1" ]; then 
		  echo "Creation of File failed"
		  exit 1
	      fi
		
		
		echo "$2" > "$1"

}

#calling a function with argument parameters
func $1 $2
