/* 
 * THIS IS AN UNPUBLISHED WORK CONTAINING D2 TECHNOLOGIES, INC. CONFIDENTIAL  
 * AND PROPRIETARY INFORMATION.  IF PUBLICATION OCCURS, THE FOLLOWING NOTICE  
 * APPLIES: "COPYRIGHT 2004-2009 D2 TECHNOLOGIES, INC. ALL RIGHTS RESERVED"  
 *  
 * $D2Tech$ $Rev: 4321 $ $Date: 2007-10-08 13:53:12 -0400 (Mon, 08 Oct 2007) $
 */


#ifndef _OSAL_CONSTANT_H_
#define _OSAL_CONSTANT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OSAL_NO_WAIT        (0)
#define OSAL_WAIT_FOREVER   (~0)

typedef enum OSAL_Status {
    OSAL_FAIL = 0,
    OSAL_SUCCESS = 1
} OSAL_Status;

typedef enum OSAL_Boolean {
    OSAL_FALSE = 0,
    OSAL_TRUE = 1
} OSAL_Boolean;

/*
 * NULL pointer
 */
#ifndef NULL
#define NULL (void *)0
#endif

#ifdef __cplusplus
}
#endif

#endif

