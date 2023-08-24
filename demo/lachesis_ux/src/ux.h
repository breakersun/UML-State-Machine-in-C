#ifndef DEMO_PROCESS_H
#define DEMO_PROCESS_H

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
 *  --------------------- ENUMERATION ---------------------
 */

//! List of process events
typedef enum
{
  POWER_SHORT_PRESS = 1,
  POWER_LONG_PRESS,
  LEFT_SHORT_PRESS,
  RIGHT_SHORT_PRESS,
}process_event_t;

/*
 *  --------------------- STRUCTURE ---------------------
 */

//! process state machine
typedef struct
{
  state_machine_t Machine;      //!< Abstract state machine
}process_t;

/*
 *  --------------------- External function prototype ---------------------
 */

extern void init_process(process_t* const pProcess);

/** \brief Parses the user keyboard input and calls the respective API,
 *  to trigger the events to state machine.
 *
 * \param pProcess process_t* const instance of process_t state machine.
 * \param input char  user input
 *
 */
static inline void parse_cli(process_t* const pProcess, char input)
{
  switch(input)
  {
  case '1':
    pProcess->Machine.Event = POWER_SHORT_PRESS;
    break;

  case '2':
    pProcess->Machine.Event = POWER_LONG_PRESS;
    break;

  case '3':
    pProcess->Machine.Event = LEFT_SHORT_PRESS;
    break;

  case '4':
    pProcess->Machine.Event = RIGHT_SHORT_PRESS;
    break;

  default:
    printf("Not a valid event\n");
    break;
  }
}

#endif // DEMO_PROCESS_H
