#ifndef DEMO_PROCESS_H
#define DEMO_PROCESS_H

#include <stdint.h>

typedef enum
{
  STARTUP_EVT = 1,
  GOOD_ADAPTER_EVT,
  BAD_ADAPTER_EVT,
  CONTROLLER_ATTACHED_EVT,
  CONTROLLER_DETACHED_EVT,
  ERRORS_EVT,
  ERRORS_DISMISSED_EVT,
  LPD_EVT,
}process_event_t;

typedef struct
{
  state_machine_t Machine;      //!< Abstract state machine
  uint8_t controller_id;
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
