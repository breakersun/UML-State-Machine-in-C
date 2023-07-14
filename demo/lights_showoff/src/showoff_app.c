/**
 * \file
 * \brief Simple finite state machine example

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

#include "hsm.h"
#include "showoff_app.h"

/*
 *  --------------------- ENUMERATION ---------------------
 */

//! List of states the process state machine
typedef enum
{
  POWERDOWN_STATE,
  PATTERN_1_STATE,
  PATTERN_2_STATE,
  PATTERN_3_STATE,
}process_state_t;

/*
 *  --------------------- Function prototype ---------------------
 */

static state_machine_result_t powerdown_handler(state_machine_t* const State);
static state_machine_result_t powerdown_entry(state_machine_t* const State);
static state_machine_result_t powerdown_exit(state_machine_t* const State);

static state_machine_result_t pattern1_handler(state_machine_t* const State);
static state_machine_result_t pattern1_entry(state_machine_t* const State);
static state_machine_result_t pattern1_exit(state_machine_t* const State);

static state_machine_result_t pattern2_handler(state_machine_t* const State);
static state_machine_result_t pattern2_entry(state_machine_t* const State);
static state_machine_result_t pattern2_exit(state_machine_t* const State);

static state_machine_result_t pattern3_handler(state_machine_t* const State);
static state_machine_result_t pattern3_entry(state_machine_t* const State);
static state_machine_result_t pattern3_exit(state_machine_t* const State);
/*
 *  --------------------- Global variables ---------------------
 */

static const state_t Process_States[] =
{
  [POWERDOWN_STATE] = {
    .Handler = powerdown_handler,
    .Entry   = powerdown_entry,
    .Exit    = powerdown_exit,
    .Id      = POWERDOWN_STATE,
  },

  [PATTERN_1_STATE] = {
    .Handler = pattern1_handler,
    .Entry   = pattern1_entry,
    .Exit    = pattern1_exit,
    .Id      = PATTERN_1_STATE,
  },

  [PATTERN_2_STATE] = {
    .Handler = pattern2_handler,
    .Entry   = pattern2_entry,
    .Exit    = pattern2_exit,
    .Id      = PATTERN_2_STATE,
  },

  [PATTERN_3_STATE] = {
    .Handler = pattern3_handler,
    .Entry   = pattern3_entry,
    .Exit    = pattern3_exit,
    .Id      = PATTERN_3_STATE,
  }
};

/*
 *  --------------------- Functions ---------------------
 */

void init_process(process_t* const pProcess)
{
  pProcess->Machine.State = &Process_States[POWERDOWN_STATE];
  pProcess->Machine.Event = 0;

  powerdown_entry((state_machine_t *)pProcess);
}

static state_machine_result_t powerdown_entry(state_machine_t* const pState)
{
  (void)pState;
  printf("Entering to powerdown state\n");
  printf("Supported events:\n");
  printf("'1' : Power Short Press\n");
  return EVENT_HANDLED;
}

static state_machine_result_t powerdown_handler(state_machine_t* const pState)
{
  switch(pState->Event)
  {
  case POWER_SHORT_PRESS:
    return switch_state(pState, &Process_States[PATTERN_1_STATE]);
  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t powerdown_exit(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  (void)pProcess;
  printf("Exiting from powerdown state\n");
  printf("\n");
  return EVENT_HANDLED;
}

static state_machine_result_t pattern1_entry(state_machine_t* const pState)
{
  (void)(pState);
  printf("Entering to pattern1 state\n");
  printf("Supported events:\n");
  printf("'1' : Power Short Press\n");
  printf("'2' : Power Long Press\n");
  printf("'3' : Left Press\n");
  printf("'4' : Right Press\n");
  return EVENT_HANDLED;
}

static state_machine_result_t pattern1_handler(state_machine_t* const pState)
{
  switch(pState->Event)
  {
  case POWER_SHORT_PRESS:
      break;

  case POWER_LONG_PRESS:
    return switch_state(pState, &Process_States[POWERDOWN_STATE]);

  case LEFT_SHORT_PRESS:
    return switch_state(pState, &Process_States[PATTERN_3_STATE]);

  case RIGHT_SHORT_PRESS:
    return switch_state(pState, &Process_States[PATTERN_2_STATE]);

  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t pattern1_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from pattern1 state\n");
  printf("\n");
  return EVENT_HANDLED;
}

static state_machine_result_t pattern2_entry(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  printf("Entering to pattern2 state\n");
  printf("Supported events:\n");
  printf("'1' : Power Short Press\n");
  printf("'2' : Power Long Press\n");
  printf("'3' : Left Press\n");
  printf("'4' : Right Press\n");
  return EVENT_HANDLED;
}

static state_machine_result_t pattern2_handler(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  switch(pState->Event)
  {
  // case STOP:
  //   return switch_state(pState, &Process_States[powerdown_STATE]);
  //
  // case RESUME:
  //   return switch_state(pState, &Process_States[PATTERN_1_STATE]);

  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t pattern2_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from pattern2 state\n");
  printf("\n");
  return EVENT_HANDLED;
}


static state_machine_result_t pattern3_entry(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  printf("Entering to pattern3 state\n");
  printf("Supported events:\n");
  printf("'1' : Power Short Press\n");
  printf("'2' : Power Long Press\n");
  printf("'3' : Left Press\n");
  printf("'4' : Right Press\n");
  return EVENT_HANDLED;
}

static state_machine_result_t pattern3_handler(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  switch(pState->Event)
  {
  // case STOP:
  //   return switch_state(pState, &Process_States[powerdown_STATE]);
  //
  // case RESUME:
  //   return switch_state(pState, &Process_States[PATTERN_1_STATE]);

  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t pattern3_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from pattern3 state\n");
  printf("\n");
  return EVENT_HANDLED;
}
