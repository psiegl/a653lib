/*
 * Copyright (c) 2022-2023 Airbus Defence and Space
 *
 * This file is part of liba653.
 *
 * liba653 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * liba653 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with liba653; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file      a653Error.h
 * @date      Wed Apr  1 17:08:32 2023
 * @brief     a653 error handling
 * @details
 */

#ifndef __A653_ERROR_H
#define __A653_ERROR_H

#include "a653Type.h"

/* defines */ 

#define MAX_ERROR_MESSAGE_SIZE  128


/* typedefs */ 

typedef A653_INTEGER    ERROR_MESSAGE_SIZE_TYPE;  /* error message size type */

typedef A653_BYTE       ERROR_MESSAGE_TYPE[MAX_ERROR_MESSAGE_SIZE]; 

/* error types */ 
typedef enum ERROR_CODE_VALUE_TYPE {
    DEADLINE_MISSED = 0,        /* deadline missed */
    APPLICATION_ERROR,          /* application error */
    NUMERIC_ERROR,              /* numeric error */
    ILLEGAL_REQUEST,            /* invalid or illegal OS call */
    STACK_OVERFLOW,             /* process stack overflow */
    MEMORY_VIOLATION,           /* Memory violation */
    HARDWARE_FAULT,             /* hardware fault */
    POWER_FAIL                  /* power failure indication */
    } ERROR_CODE_TYPE;

/* error status type */
typedef struct             {
  ERROR_CODE_TYPE         ERROR_CODE;
  ERROR_MESSAGE_TYPE      MESSAGE;
  ERROR_MESSAGE_SIZE_TYPE LENGTH;
  PROCESS_ID_TYPE         FAILED_PROCESS_ID;
  SYSTEM_ADDRESS_TYPE     FAILED_ADDRESS;
} ERROR_STATUS_TYPE;

/* function declarations */

extern void REPORT_APPLICATION_MESSAGE (MESSAGE_ADDR_TYPE  MESSAGE_ADDR,
					MESSAGE_SIZE_TYPE  LENGTH, 
					RETURN_CODE_TYPE * RETURN_CODE);

extern void CREATE_ERROR_HANDLER (SYSTEM_ADDRESS_TYPE ENTRY_POINT, 
				  STACK_SIZE_TYPE     STACK_SIZE, 
				  RETURN_CODE_TYPE  * RETURN_CODE); 

extern void GET_ERROR_STATUS (ERROR_STATUS_TYPE * ERROR_STATUS, 
			      RETURN_CODE_TYPE  * RETURN_CODE);

extern void RAISE_APPLICATION_ERROR (ERROR_CODE_TYPE    ERROR_CODE,
				     MESSAGE_ADDR_TYPE  MESSAGE_ADDR,
				     ERROR_MESSAGE_SIZE_TYPE LENGTH,
				     RETURN_CODE_TYPE * RETURN_CODE);

#endif	/* __A653_ERROR_H */

