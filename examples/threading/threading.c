#include "threading.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define DEBUG_LOG(msg,...) printf("Dbg: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("Err: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
  struct thread_data *tdata = (struct thread_data *) thread_param;
  
  
  tdata->thread_complete_success = true;
  
  DEBUG_LOG("Lock Acquire Waiting %d ms", tdata->wait_to_obtain_ms);
  usleep(1000 * tdata->wait_to_obtain_ms);
  
  DEBUG_LOG("Getting Lock");
  
  if (pthread_mutex_lock(tdata->mutex) != 0) 
  {
    ERROR_LOG("Lock Ownership transfer failed");
    tdata->thread_complete_success = false;
    return thread_param;
  };
  
  DEBUG_LOG("Relasing lock %d ms", tdata->wait_to_release_ms);
  usleep(1000 * tdata->wait_to_release_ms);
  
  DEBUG_LOG("Releasing lock");
  if (pthread_mutex_unlock(tdata->mutex) != 0) 
  {
    ERROR_LOG("Lock Ownership transfer failed");
    tdata->thread_complete_success = false;
    return thread_param;
  };

    
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{ 
   struct thread_data *tdata1 = (struct thread_data *)malloc(sizeof(struct thread_data));
   
    if (tdata1 == NULL) 
    {
        return false;
    }
		
    
    tdata1->mutex = mutex;
    tdata1->wait_to_obtain_ms = wait_to_obtain_ms;
    tdata1->wait_to_release_ms = wait_to_release_ms;			
		

    return pthread_create(thread, NULL, threadfunc, tdata1) == 0;
}

