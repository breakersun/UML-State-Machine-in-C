#ifndef DEMO_PROCESS_H
#define DEMO_PROCESS_H

#include <stdint.h>

typedef enum
{
  STARTUP_EVT = 1,
  GOOD_ADAPTER_EVT,
  BAD_ADAPTER_EVT,
  LCONTROLLER_ATTACHED_EVT,
  LCONTROLLER_DETACHED_EVT,
  RCONTROLLER_ATTACHED_EVT,
  RCONTROLLER_DETACHED_EVT,
  LCONTROLLER_ERROR_EVT,
  RCONTROLLER_ERROR_EVT,
  HOST_ERRORS_EVT,
  HOST_ERRORS_DISMISSED_EVT,
  LPD_EVT,
  TIMEOUT_EVT,
}process_event_t;

typedef struct
{
  state_machine_t Machine;      //!< Abstract state machine
  uint8_t controller_id;
  uint32_t Set_Time;    //! Set time of a process
  uint32_t Resume_Time; //!< Remaining time when the process is paused
  uint32_t Timer;       //!< Process timer
}process_t;

extern void init_process(process_t* const pProcess);

static inline void parse_cli(process_t* const pProcess, char input)
{
  switch(input)
  {
  case 's':
    pProcess->Machine.Event = STARTUP_EVT;
    break;

  case 'g':
    pProcess->Machine.Event = GOOD_ADAPTER_EVT;
    break;

  case 'b':
    pProcess->Machine.Event = BAD_ADAPTER_EVT;
    break;

  case 'a':
    pProcess->Machine.Event = CONTROLLER_ATTACHED_EVT;
    break;

  case 'd':
    pProcess->Machine.Event = CONTROLLER_DETACHED_EVT;
    break;

  case 'e':
    pProcess->Machine.Event = ERRORS_EVT;
    break;

  case 'f':
    pProcess->Machine.Event = ERRORS_DISMISSED_EVT;
    break;

  case 'l':
    pProcess->Machine.Event = LPD_EVT;
    break;

  default:
    printf("Not a valid event\n");
    break;
  }
}
#endif // DEMO_PROCESS_H
