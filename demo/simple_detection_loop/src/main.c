#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "hsm.h"
#include "demo_process.h"

//! Instance of process_t
process_t SampleProcess;

//! Create and initialize the array of state machines.
state_machine_t * const State_Machines[] = {(state_machine_t *)&SampleProcess};

//! Semaphore for event synchronization timer, console and main thread.
sem_t Semaphore;

//! Callback function to log the events dispatched by state machine framework.
void event_logger(uint32_t stateMachine, uint32_t state, uint32_t event)
{
  printf("State Machine: %d, State: %d, Event: %d\n", stateMachine, state, event);
}

//! Callback function to log the result of event processed by state machine
void result_logger(uint32_t state, state_machine_result_t result)
{
  printf("Result: %d, New State: %d\n", result, state);
}

/** \brief Simulate the timer ISR.
 *
 * This is an one second timer. When process is active it prints the remaining time on console.
 * It also generates the timeout event when process time expires.
 */
void* timer(void* vargp)
{
    (void)(vargp);
    while(1)
    {
      sleep(1);

      if(SampleProcess.Timer > 0)
      {
        SampleProcess.Timer--;

        printf("\rRemaining process time: %d ", SampleProcess.Timer);

        if(SampleProcess.Timer == 0)
        {
          printf("\n");
          on_process_timedout(&SampleProcess);  // Generate the timeout event
          sem_post(&Semaphore);   // signal to main thread
        }
      }
    }
    return NULL;
}

int main(void)
{
  // Initialize the process state machine.
  init_process(&SampleProcess, 10);

  // Create timer and console thread
  pthread_t timer_thread;
  pthread_create(&timer_thread, NULL, timer, NULL);
  sem_init(&Semaphore, 0, 1);

  while(1)
  {
    sem_wait(&Semaphore);   // Wait for event
    #if STATE_MACHINE_LOGGER
    if(dispatch_event(State_Machines, 1, event_logger, result_logger) == EVENT_UN_HANDLED)
    #else
    if(dispatch_event(State_Machines, 1) == EVENT_UN_HANDLED)
    #endif
    {
      printf("invalid event entered\n");
    }
  }
  return 0;
}
