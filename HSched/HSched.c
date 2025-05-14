#include "../lib/std_types.h"
#include "../lib/BIT_MATH.h"
#include "HSched.h"
#include "HSchedConfig.h"
#include "../SYSTICK/inc/SYSTICK.h"

extern Task_t tasks[Num_Tasks];
uint32_t SCHED_u32CyclicNumOfCalls = 0 ;
void HSCHED_start()
{
    SystickStart();
}

void HSCHED_stop()
{
    SystickStop();
}

void scheduler_run(void) {
    for (int i = 0; i < Num_Tasks; i++) {
        if (tasks[i].function != NULL)
        {
            if (tasks[i].first_delay == 0)
            {
                if (SCHED_u32CyclicNumOfCalls % tasks[i].cyclictime ==0)
                {
                    tasks[i].function();
                }else{}
            }
            
            else{
                tasks[i].first_delay--;
            }   
        }
    }
    SCHED_u32CyclicNumOfCalls++;
}
void HSCHED_init()
{
    Systickinit();
    Systick_Cyclic_Function((STK_Cbf_t)scheduler_run,1);
}

