#ifndef DEMO_PROCESS_H
#define DEMO_PROCESS_H

/*
 *  --------------------- ENUMERATION ---------------------
 */

//! List of process events
typedef enum
{
  TIMEOUT = 1,
}process_event_t;

/*
 *  --------------------- STRUCTURE ---------------------
 */

//! process state machine
typedef struct
{
  state_machine_t Machine;      //!< Abstract state machine
  uint32_t Set_Time;    //! Set time of a process
  uint32_t Resume_Time; //!< Remaining time when the process is paused
  uint32_t Timer;       //!< Process timer
}process_t;

/*
 *  --------------------- External function prototype ---------------------
 */

extern void init_process(process_t* const pProcess, uint32_t processTime);

/*
 *  --------------------- Inline functions ---------------------
 */

 // process APIs

static inline void on_process_timedout(process_t* const pProcess)
{
  pProcess->Machine.Event = TIMEOUT;
}

#endif // DEMO_PROCESS_H
