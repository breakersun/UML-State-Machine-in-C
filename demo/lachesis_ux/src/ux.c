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

#include <stdint.h>
#include <stdio.h>

#include "hsm.h"
#include "ux.h"

/*
 *  --------------------- ENUMERATION ---------------------
 */

//! List of states the process state machine
typedef enum
{
  POWERUP,
  GOOD_ADAPTER,
  WRONG_ADAPTER,
  WORKING,
  ERRORS,
}process_state_t;


static state_machine_result_t powerup_handler(state_machine_t* const State);
static state_machine_result_t powerup_entry(state_machine_t* const State);
static state_machine_result_t powerup_exit(state_machine_t* const State);

static state_machine_result_t wrong_adapter_handler(state_machine_t* const State);
static state_machine_result_t wrong_adapter_entry(state_machine_t* const State);
static state_machine_result_t wrong_adapter_exit(state_machine_t* const State);

static state_machine_result_t good_adapter_handler(state_machine_t* const State);
static state_machine_result_t good_adapter_entry(state_machine_t* const State);
static state_machine_result_t good_adapter_exit(state_machine_t* const State);

static state_machine_result_t working_handler(state_machine_t* const State);
static state_machine_result_t working_entry(state_machine_t* const State);
static state_machine_result_t working_exit(state_machine_t* const State);

static state_machine_result_t errors_handler(state_machine_t* const State);
static state_machine_result_t errors_entry(state_machine_t* const State);
static state_machine_result_t errors_exit(state_machine_t* const State);
/*
 *  --------------------- Global variables ---------------------
 */

static const state_t Process_States[] =
{
  [POWERUP] = {
    .Handler = powerup_handler,
    .Entry   = powerup_entry,
    .Exit    = powerup_exit,
    .Id      = POWERUP,
  },

  [WRONG_ADAPTER] = {
    .Handler = wrong_adapter_handler,
    .Entry   = wrong_adapter_entry,
    .Exit    = wrong_adapter_exit,
    .Id      = WRONG_ADAPTER,
  },

  [GOOD_ADAPTER] = {
    .Handler = good_adapter_handler,
    .Entry   = good_adapter_entry,
    .Exit    = good_adapter_exit,
    .Id      = GOOD_ADAPTER,
  },

  [WORKING] = {
    .Handler = working_handler,
    .Entry   = working_entry,
    .Exit    = working_exit,
    .Id      = WORKING,
  },

  [ERRORS] = {
    .Handler = errors_handler,
    .Entry   = errors_entry,
    .Exit    = errors_exit,
    .Id      = ERRORS,
  }
};

/*
 *  --------------------- Functions ---------------------
 */

void init_process(process_t* const pProcess)
{
  pProcess->Machine.State = &Process_States[POWERUP];
  pProcess->Machine.Event = 0;
  pProcess->Set_Time = 10;
  pProcess->Resume_Time = 0;

  powerup_entry((state_machine_t *)pProcess);
}

static state_machine_result_t powerup_entry(state_machine_t* const pState)
{
  (void)pState;
  printf("Powering Up!\n");
  printf("Supported events:\n");
  printf("g: GOOD_ADAPTER_EVT\n");
  printf("b: BAD_ADAPTER_EVT\n");
  printf("\n");
  return EVENT_HANDLED;
}

static state_machine_result_t powerup_handler(state_machine_t* const pState)
{
  switch(pState->Event)
  {
  case GOOD_ADAPTER_EVT:
    return switch_state(pState, &Process_States[GOOD_ADAPTER]);
    break;
  case BAD_ADAPTER_EVT:
    return switch_state(pState, &Process_States[WRONG_ADAPTER]);
    break;
  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t powerup_exit(state_machine_t* const pState)
{
  (void)pState;
  printf("Exiting from POWERUP state\n");
  return EVENT_HANDLED;
}

static state_machine_result_t good_adapter_entry(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  printf("Entering to [GOOD_ADAPTER] state\n");
  printf("Supported no events\n");
  printf("[UI] LED GOOD ADAPTER\n");
  pProcess->Timer = 2;
  return EVENT_HANDLED;
}
static state_machine_result_t good_adapter_handler(state_machine_t* const pState)
{
  switch(pState->Event)
  {
    case TIMEOUT_EVT:
      return switch_state(pState, &Process_States[WORKING]);
    break;
  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t good_adapter_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from GOOD_ADAPTER state\n");
  return EVENT_HANDLED;
}

static state_machine_result_t wrong_adapter_entry(state_machine_t* const pState)
{
  (void)(pState);
  printf("Entering to [WRONG_ADAPTER] state\n");
  printf("Supported no events\n");
  printf("[UI] LED WRONG ADAPTER\n");
  return EVENT_HANDLED;
}

static state_machine_result_t wrong_adapter_handler(state_machine_t* const pState)
{
  switch(pState->Event)
  {
  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t wrong_adapter_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from WRONG_ADAPTER state\n");
  return EVENT_HANDLED;
}

static state_machine_result_t working_entry(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  printf("Entering to [WORKING] state\n");
  printf("Supported events:\n");
  printf("e: ERRORS_EVT\n");
  printf("d: CONTROLLER_DETACHED_EVT\n");
  printf("l: LPD_EVT\n");
  printf("\n");
  return EVENT_HANDLED;
}

static state_machine_result_t working_handler(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  switch(pState->Event)
  {
  case LCONTROLLER_ATTACHED_EVT:
    break;

  case LCONTROLLER_DETACHED_EVT:
    break;

  case HOST_ERRORS_EVT:
    return switch_state(pState, &Process_States[ERRORS]);

  case LPD_EVT:
    printf("[UI] : LED WATER WARNING\n");
    break;

  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t working_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from WORKING state\n");
  return EVENT_HANDLED;
}

static state_machine_result_t errors_entry(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  printf("Entering to [ERRORS] state\n");
  printf("Supported events:\n");
  printf("f: ERRORS_DISMISSED_EVT\n");
  printf("l: LPD_EVT\n");
  printf("\n");
  return EVENT_HANDLED;
}

static state_machine_result_t errors_handler(state_machine_t* const pState)
{
  process_t* const pProcess = (process_t*)pState;
  switch(pState->Event)
  {
  case HOST_ERRORS_DISMISSED_EVT:
    return switch_state(pState, &Process_States[WORKING]);

  case LPD_EVT:
    printf("[UI] : LED WATER WARNING\n");
    break;

  default:
    return EVENT_UN_HANDLED;
  }
  return EVENT_HANDLED;
}

static state_machine_result_t errors_exit(state_machine_t* const pState)
{
  (void)(pState);
  printf("Exiting from ERRORS state\n");
  return EVENT_HANDLED;
}
