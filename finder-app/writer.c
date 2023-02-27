//Creator : KD 
//Date : 25/02/23

#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <sys/stat.h>



//argc - Number of arguments passed
//argv - list of pointer arguments

int main( int argc , char * argv[] )
{
  struct stat *Buffer = NULL;

    //Number of arguments are okay 	
    if (argc == 3)
    {
    	syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);    
 	
 	
 	if (stat(argv[1], Buffer) == 0) //check if directory
 	{
           syslog(LOG_ERR, "%s is not a valid path", argv[1]);
                   
           return 1;
 	}
 	else 
 	{
	   FILE * fp;
 	   fp = fopen(argv[1], "w+");
           fputs(argv[2], fp);
           fclose(fp);

           return 0;
	}		 
		  
    }
    else 
    {
       //Log as error
    	syslog(LOG_USER, "invalid argument, should receive filesdir and searchstr");
      	return 1;
    
    }
    
}



