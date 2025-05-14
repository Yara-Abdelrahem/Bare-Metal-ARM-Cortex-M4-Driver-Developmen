#ifndef HSCHEDCONFIG_H
#define GHSCHEDCONFIG_H
#define Num_Tasks 2
#include "../SYSTICK/inc/SYSTICK.h"
//typedef void (*STK_Cbf_t)(void);

typedef struct {
    uint32_t prioriy;
    uint32_t cyclictime;
    uint32_t first_delay;
    void (*function)(void);
}Sched_Runnable_cfg_t;


typedef struct {
    STK_Cbf_t function;
    //void (*function)(void); // Task function
    uint32_t priority;      // Task priority (1 = highest)
    uint32_t cyclictime;      // How often the task runs (e.g., every 1000ms)
    uint32_t first_delay;      // Last time the task ran
} Task_t;

#endif