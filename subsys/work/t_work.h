#ifndef TASK_WORK_HEADER_G
#define TASK_WORK_HEADER_G
// ====================================================================================
// including the requried header files

/** standard C header files */
#include <stdint.h>
#include <stdlib.h>

/** TI RTOS task thread */
#include <ti/sysbios/knl/Task.h>

/** TI RTOS system clock driver */
#include <ti/sysbios/knl/Clock.h>

/** TI RTOS semaphor library */
#include <ti/sysbios/knl/Semaphore.h>


// ====================================================================================
// typede declarations and macros

/**
 * @brief an opaque work object type that wraps the moving parts
 * 
 * @param ti_task_param params needed by the task thread library
 * @param ti_task_handle the handle the ti rtos would return on task creation
 * @param work_handler the work handler registered by the user
 * @param delayed_trigger starting the timeout clock for the first time with some delay
 * @param ti_clock_params the meta data needed to createa clock object wit TI rtos
 * @param clock_handler internal clock handler used to release the work semaphore
 * @param work_sem_handle internal semaphore handle used to enforce timeout
 */
typedef struct {
    // task thread:
    Task_Params ti_task_param;
    Task_Handle ti_task_handle;
    void (work_handler*)(UArg arg0, UArg arg1);
    // clocl:
    uint32_t delayed_trigger;
    Clock_Params ti_clock_params;
    void clock_handler(UArg arg);
    // semaphore:
    Semaphore_Handle work_sem_handle;

} t_work_t;


// ====================================================================================
// exposed APIs

/**
 * @brief initializes a t_work object
 * 
 * @param [in] t_work address to the t_work object to be initialized
 * 
 * @return SUCCESS if succeed; a negative error code otherwise
 */
int work_init(t_work_t *t_work);

/**
 * @brief mmediately starts a t_work object
 * 
 * @param [in] t_work address to the t_work object to start
 * 
 * @return SUCCESS if succeed; a negative error code otherwise
 */
int work_start(t_work_t *t_work);

/**
 * @brief schedules a t_work to start at a certain delay from now
 * 
 * @param [in] t_work address to the t_work object to be scheduled
 * @param [in] timeout_ticks the delay to start in ticks
 * 
 * @return SUCCESS if succeed; a negative error code otherwise
 */
int work_schedule(t_work_t *t_work, uint32_t timeout_ticks);

/**
 * @brief stops a t_work object
 * 
 * @param [in] t_work address to the t_work object to be stopped
 * 
 * @return SUCCESS if succeed; a negative error code otherwise
 */
int work_cancel(t_work_t * t_work);


#endif