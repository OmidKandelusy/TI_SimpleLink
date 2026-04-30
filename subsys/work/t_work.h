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

/** macro constants used for configurations */
#define DEFAULT_STACK_SIZE 2048
#define DEFAULT_PRIORITY 1


/** subsystem return codes */
#define T_WORK_SUCCESS 0
#define T_WORK_NULL_POINTER -1
#define T_WORK_INVALID_PRIORITY -2
#define T_WORK_TASK_CONSTRUCTION_FAILED -3
#define T_WORK_CLOCK_CONSTRUCTION_FAILED -4
#define T_WORK_SEMAPHORE_CONSTRUCTION_FAILED -5


/**
 * @brief an opaque work object type that wraps the moving parts
 * 
 * @param ti_task_struct the structure repreenting the task object
 * @param ti_task_stack holding the task thread context
 * @param ti_task_params params needed by the task thread library
 * @param ti_task_handle the handle the ti rtos would return on task creation
 * @param work_handler the work handler registered by the user
 * @param delayed_trigger starting the timeout clock for the first time with some delay
 * @param ti_clock_params the meta data needed to createa clock object wit TI rtos
 * @param ti_clock_struct the structure representing the clock object
 * @param ti_clock_handle the clock object handle
 * @param clock_handler internal clock handler used to release the work semaphore
 * @param work_sem_handle internal semaphore handle used to enforce timeout
 * @param ti_semaphore_struct the structure representing the semaphore object
 * @param ti_semaphore_params the semaphore parameters
 * @param ti_semaphore_handle the handle of the semaphore
 */
typedef struct {
    // task thread:
    Task_Struct ti_task_struct;
    uint8_t ti_task_stack[DEFAULT_STACK_SIZE];
    Task_Params ti_task_params;
    Task_Handle ti_task_handle;
    void (*work_handler)(UArg arg0, UArg arg1);
    // clocl:
    uint32_t delayed_trigger;
    Clock_Params ti_clock_params;
    Clock_Struct ti_clock_struct;
    Clock_Handle ti_clock_handle;
    void (*clock_handler)(UArg arg);
    // semaphore:
    Semaphore_Struct ti_semaphore_struct;
    Semaphore_Params ti_semaphore_params;
    Semaphore_Handle ti_semaphore_handle;

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