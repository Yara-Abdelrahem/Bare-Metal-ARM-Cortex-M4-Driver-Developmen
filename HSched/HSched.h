#ifndef HSCHED_H
#define GHSCHED_H

/*
typedef struct {
    uint32_t prioriy;
    uint32_t cyclictime;
    uint32_t first_delay;
    void (*function)(void);
}Sched_Runnable_cfg_t;
*/

void HSCHED_init();
void HSCHED_start();
void HSCHED_stop();
void scheduler_run();
void scheduler_run(void);

#endif