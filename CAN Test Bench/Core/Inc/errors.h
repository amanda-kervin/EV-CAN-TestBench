/*
 * errors.h
 *
 *  Created on: Mar 2, 2024
 *      Author: byo10
 */

#ifndef INC_ERRORS_H_
#define INC_ERRORS_H_
#include "main.h"
#include "shutdown.h"
#include "bms.h"
#include "motor_controller.h"
#include "imd.h"

//Enable/disable flags for various functionality.
#define _ERR_LOGGING_ENABLE 0
#define _ERR_DISPLAY_ENABLE 0
#define _ERR_ARGS_ENABLE 0

//How this thing works, for byron's future memory
#define ERR_SHUTDOWN_MASK 0b00000001
#define ERR_SUSPEND_MASK 0b00000010
#define ERR_LIMP_MASK 0b00000100
#define ERR_DISPLAY_MASK 0b00001000



#define _SHUTDOWN _Shutdown()
#define _SUSPEND(x) _Suspend(x)



//#define throw_error(x) _throw_error(x)
//#define throw_error(x,y,type) _throw_error_ ##type(x,( ##type)y);

typedef enum error_id{
	default_shutdown = 0,
	default_suspend,
	default_limit,
	shutdown_cct_tripped, //shutdown circuit errors
	bms_shutdown_tripped,
	bspd_shutdown_tripped,
	imd_shutdown_cct_tripped,
	coolant_temp_too_high,
	coolant_pressure_too_high,
	peepeepoopoo,
	BMS_Overcurrent,
	BMS_reserved_bits,
	BMS_low_charge_temp

}error_id;



typedef struct error_struct{
	char* msg;
	uint8_t type_info;
	void (*err_handler)(); //function pointer to a dedicated error handler
	uint8_t (*resume_condition)(); //function pointer for some function that decides whether to resume after suspended
}error_struct;

typedef struct error_log_entry_struct{
	uint32_t timestamp;
	error_id id;
	char msg[];
}error_log_entry_struct;







#if _ERR_LOGGING_ENABLE
#define _ERR_LOG_CAPACITY 16


typedef struct error_journal{
	uint8_t num_entries;
	error_log_entry_struct error_log[_ERR_LOG_CAPACITY];
}error_journal;

	void _log_error(error_struct e, char* params);
#endif

void _throw_error(enum error_id id);
void error_loop();


#endif /* INC_ERRORS_H_ */


