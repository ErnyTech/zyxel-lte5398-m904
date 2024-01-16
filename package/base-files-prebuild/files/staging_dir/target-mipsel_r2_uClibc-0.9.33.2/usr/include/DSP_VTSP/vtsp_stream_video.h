/*
 * THIS IS AN UNPUBLISHED WORK CONTAINING D2 TECHNOLOGIES, INC. CONFIDENTIAL
 * AND PROPRIETARY INFORMATION.  IF PUBLICATION OCCURS, THE FOLLOWING NOTICE
 * APPLIES: "COPYRIGHT 2004-2008 D2 TECHNOLOGIES, INC. ALL RIGHTS RESERVED"
 *
 * $D2Tech$ $Rev: 33415 $ $Date: 2015-09-16 14:55:14 +0800 (Wed, 16 Sep 2015) $
 *
 */


#ifndef _VTSP_STREAM_VIDEO_H_
#define _VTSP_STREAM_VIDEO_H_

#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

VTSP_Return VTSP_streamVideoStart(
    uvint                 infc,
    VTSP_StreamVideo     *stream_ptr);
VTSP_Return VTSP_streamVideoEnd(
    uvint           infc,
    uvint           streamId);
VTSP_Return VTSP_streamVideoModify(
    uvint                 infc,
    VTSP_StreamVideo     *stream_ptr);
VTSP_Return VTSP_streamVideoModifyDir(
    uvint           infc,
    uvint           streamId,
    VTSP_StreamDir  dir);
VTSP_Return VTSP_streamVideoRequestKeyFrame(
    uvint           infc,
    uvint           streamId);
VTSP_Return VTSP_streamVideoSendFir(
    vint           infc,
    vint           streamId);

VTSP_Return VTSP_streamVideoModifyEncoder(
    uvint            infc,
    uvint            streamId,
    uvint            coder);

VTSP_Return VTSP_streamVideoModifyConf(
    uvint           infc,
    uvint           streamId,
    uint32          confMask);
VTSP_Return VTSP_streamVideoQuery(
    uvint           infc,
    uvint           streamId);

VTSP_Return VTSP_streamVideoLipSync(
    uvint           infc,
    uvint           streamId,
    vint            audioVideoSkew);

VTSP_Return VTSP_streamVideoRequestResolution(
    uvint           infc,
    uvint           streamId,
    vint            width,
    vint            height);

VTSP_Return VTSP_rtcpCnameVideo(
    uvint       infc,
    const char *name_ptr);

VTSP_Return VTSP_rtcpFeedbackMaskVideo(
    uvint               infc,
    VTSP_RtcpTemplate   *rtcpConfig_ptr);

VTSP_Return VTSP_setAllStreamTosVideo(
    uvint infc,
    VTSP_RtpTemplate   *rtpConfig_ptr);

#ifdef __cplusplus
}
#endif

#endif



