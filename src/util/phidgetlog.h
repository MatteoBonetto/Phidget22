#ifndef _PHIDGETLOG_H_
#define _PHIDGETLOG_H_

#ifndef EXTERNALPROTO
/*
 * This file is part of libphidget22
 *
 * Copyright (c) 2015-2022 Phidgets Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#endif

#ifndef EXTERNALPROTO
	#include "constants.h"
	#include "types.gen.h"
#endif

#include "phidgetlog.gen.h"

API_PRETURN_HDR PhidgetLog_enableNetwork(const char *address, int port);
API_PRETURN_HDR PhidgetLog_disableNetwork(void);

#ifndef EXTERNALPROTO

	#define LOGF_STDERR	  0x08000
	#define LOGF_DEBUGGER 0x10000

void PhidgetLogInit(void);
void PhidgetLogFini(void);

void logStackTrace(Phidget_LogLevel, const char *);

void PhidgetLog_flushDups(void);

PhidgetReturnCode PhidgetLog_logv(const char *file, int line, const char *func,
								  const char *src, Phidget_LogLevel level, const char *fmt, va_list va);

	/* logs to visual studio output... or info  */
	#define logvs(...) \
		PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_INFO | LOGF_DEBUGGER, __VA_ARGS__)

	#ifdef NDEBUG
		#define logdebug(...)
		#define logcrit(...) PhidgetLog_loge(NULL, 0, __func__, NULL, PHIDGET_LOG_CRITICAL, __VA_ARGS__)
		#define logerr(...)	 PhidgetLog_loge(NULL, 0, __func__, NULL, PHIDGET_LOG_ERROR, __VA_ARGS__)
		#define logwarn(...) PhidgetLog_loge(NULL, 0, __func__, NULL, PHIDGET_LOG_WARNING, __VA_ARGS__)
		#define loginfo(...) PhidgetLog_loge(NULL, 0, __func__, NULL, PHIDGET_LOG_INFO, __VA_ARGS__)
		#define logverbose(...)
	#else
		#define logcrit(...)	PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_CRITICAL, __VA_ARGS__)
		#define logerr(...)		PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_ERROR, __VA_ARGS__)
		#define logwarn(...)	PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_WARNING, __VA_ARGS__)
		#define loginfo(...)	PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_INFO, __VA_ARGS__)
		#define logdebug(...)	PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_DEBUG, __VA_ARGS__)
		#define logverbose(...) PhidgetLog_loge(__FILE__, __LINE__, __func__, NULL, PHIDGET_LOG_VERBOSE, __VA_ARGS__)
	#endif /* NDEBUG */

	#define LOGBUFFER_STR					 "%s%*D"
	#define LOGBUFFER_ARGS(datalen, databuf) ((datalen) ? "0x" : "(empty)"), (int)(datalen), (databuf), " 0x"

#endif /* EXTERNALPROTO */

#endif /* _PHIDGETLOG_H_ */
