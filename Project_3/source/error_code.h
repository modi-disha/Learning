/*
 * error_code.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

typedef enum mem_status
{
	SUCCESS = 0, // no error
	FAILED, // failure case
	OUT_OF_RANGE, //accessing out of range data error
	INVALID_REQUEST
} mem_status;

extern mem_status error;
#endif /* ERROR_CODE_H_ */
