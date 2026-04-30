// including the required header files

/** standard C header files */
#include <string.h>
#include <stddef.h>

/** subsystem header files */
#include "t_work.h"

// ===============================================================================
// subsystem functions


int work_init(t_work_t *t_work){
    if (!t_work) return T_WORK_NULL_POINTER;

    // constructing a statically allocated task thread
    Task_Params_init(&(t_work->ti_task_params));
    t_work->ti_task_params.stackSize = DEFAULT_STACK_SIZE;
    t_work->ti_task_params.priority  = DEFAULT_PRIORITY;
    t_work->ti_task_params.stack     = &(t_work->ti_task_stack);
    t_work->ti_task_handle =  Task_construct((&t_work->ti_task_struct), t_work->work_handler,
                                              &(t_work->ti_task_params), NULL);
    if (t_work->ti_task_handle == NULL){
        return T_WORK_TASK_CONSTRUCTION_FAILED;
    }

    // constructing the clock for the work timeout
    Clock_Params_init(&(t_work->ti_clock_params));
    t_work->ti_clock_params.period = 0;
    t_work->ti_clock_params.startFlag = FALSE;
    t_work->ti_clock_handle =  Clock_construct(&(t_work->ti_clock_struct), t_work->clock_handler, 
                                                 t_work->delayed_trigger, &(t_work->ti_clock_params));
    if (t_work->ti_clock_handle == NULL){
        return T_WORK_CLOCK_CONSTRUCTION_FAILED;
    }


    // constructing the semaphore for the work
    Semaphore_Params_init(&(t_work->ti_semaphore_params));
    t_work->ti_semaphore_params.mode = Semaphore_Mode_BINARY;
    t_work->ti_semaphore_handle =  Semaphore_construct(&(t_work->ti_semaphore_struct), 0, 
                                                       &(t_work->ti_semaphore_params));
    if (t_work->ti_semaphore_handle == NULL){
        return T_WORK_SEMAPHORE_CONSTRUCTION_FAILED;
    }


    return T_WORK_SUCCESS;
}


