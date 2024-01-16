/*
 * THIS IS AN UNPUBLISHED WORK CONTAINING D2 TECHNOLOGIES, INC. CONFIDENTIAL
 * AND PROPRIETARY INFORMATION.  IF PUBLICATION OCCURS, THE FOLLOWING NOTICE
 * APPLIES: "COPYRIGHT 2004-2009 D2 TECHNOLOGIES, INC. ALL RIGHTS RESERVED"
 *
 * $D2Tech$ $Rev: 35436 $ $Date: 2016-07-28 08:14:13 +0800 (Thu, 28 Jul 2016) $
 *
 */


#ifndef _VTSP_EVENT_H_
#define _VTSP_EVENT_H_

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

VTSP_Return VTSP_infcLineStatus(
    uvint           infc);

VTSP_Return VTSP_getEvent(
    vint            infc,
    VTSP_EventMsg  *msg_ptr,
    uint32          timeout);

VTSP_Return VTSP_putEvent(
    vint            infc,
    VTSP_EventMsg  *msg_ptr,
    uint32          timeout);

#ifdef VTSP_ENABLE_SLIC_QUEUE
VTSP_Return VTSP_getSlicEvent(
    vint            infc,
    VTSP_EventMsg  *msg_ptr,
    uint32          timeout);
#endif

#ifdef __cplusplus
}
#endif

#endif

