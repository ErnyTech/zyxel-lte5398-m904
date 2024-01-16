/*
 * THIS IS AN UNPUBLISHED WORK CONTAINING D2 TECHNOLOGIES, INC. CONFIDENTIAL
 * AND PROPRIETARY INFORMATION.  IF PUBLICATION OCCURS, THE FOLLOWING NOTICE
 * APPLIES: "COPYRIGHT 2005-2007 D2 TECHNOLOGIES, INC. ALL RIGHTS RESERVED"
 *
 * $D2Tech$ $Rev: 48623 $ $Date: 2020-01-09 14:37:04 +0800 (Thu, 09 Jan 2020) $
 */

#ifndef _VHW_H_
#define _VHW_H_

/*
 * This file describes interfaces to the low level hardware of the target
 * processor and the CPLD.
 */

#include <osal_types.h>

/*
 * Define the channel buffer size in samples per processing period
 */
#define VHW_PCM_BUF_SZ          (80)

/*
 * Number of PCM channels supported
 */
#define VHW_NUM_PCM_CH          (1)

/*
 * Define PCM formats
 */
//#define VHW_AUDIO_MULAW
#define VHW_AUDIO_SHIFT            (2)
#define VHW_AUDIO_DCRM

/*
 * This macro returns start address of buffer for a channel 'ch' given data_ptr
 * points to the start address of buffer for ch0.
 * Returns NULL if buffer is not available.
 */
#define VHW_GETBUF(data_ptr, ch)      \
        (ch > (VHW_NUM_PCM_CH - 1)) ? \
         NULL : (((vint *)data_ptr) + (VHW_PCM_BUF_SZ * ch))

extern unsigned char const VHW_driverName[];

/*
 * Function prototypes
 */
extern int VHW_init(
    void);

extern void VHW_start(
    void);

extern void VHW_shutdown(
    void);

extern void VHW_exchange(
    vint **tx_ptr,
    vint **rx_ptr);

#endif
