/**
 * \file
 * \brief   Simple state machine example

 * \author  Nandkishor Biradar
 * \date    14 December 2018

 *  Copyright (c) 2018-2019 Nandkishor Biradar
 *  https://github.com/kiishor

 *  Distributed under the MIT License, (See accompanying
 *  file LICENSE or copy at https://mit-license.org/)
 */

/*
 *  --------------------- INCLUDE FILES ---------------------
 */
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "hsm.h"
#include "showoff_app.h"

/*
 *  --------------------- Global variables ---------------------
 */

//! Instance of process_t
process_t SampleProcess;

//! Create and initialize the array of state machines.
state_machine_t * const State_Machines[] = {(state_machine_t *)&SampleProcess};

//! Semaphore for event synchronization timer, console and main thread.
sem_t Semaphore;


/*
 *  --------------------- Functions ---------------------
 */

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


/** \brief Simulate the user inputs.
 *
 * It waits for the user key (ascii) input from console and pass it to parse_cli
 * to convert it into process_t events. It supports start, stop, pause and resume events.
 */
void* console(void* vargp)
{
  (void)(vargp);
  while(1)
  {
    // Get input from console
    char input  = getchar();

    // ignore new line input
    if((input == '\n' ) ||(input == '\r'))
    {
      continue;
    }

    parse_cli(&SampleProcess, input);
    sem_post(&Semaphore);
  }
}

int main(void)
{
  // Initialize the process state machine.
  init_process(&SampleProcess);

  // Create timer and console thread
  pthread_t console_thread;
  pthread_create(&console_thread, NULL, console, NULL);
  sem_init(&Semaphore, 0, 1);

  while(1)
  {
    sem_wait(&Semaphore);   // Wait for event

    if(dispatch_event(State_Machines, 1, event_logger, result_logger) == EVENT_UN_HANDLED)
    {
      printf("invalid event entered\n");
    }
  }
  return 0;
}
