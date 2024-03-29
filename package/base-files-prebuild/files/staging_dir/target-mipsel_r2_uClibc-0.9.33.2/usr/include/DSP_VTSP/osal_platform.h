/*
 * THIS IS AN UNPUBLISHED WORK CONTAINING D2 TECHNOLOGIES, INC. CONFIDENTIAL
 * AND PROPRIETARY INFORMATION.  IF PUBLICATION OCCURS, THE FOLLOWING NOTICE
 * APPLIES: "COPYRIGHT 2004-2006 D2 TECHNOLOGIES, INC. ALL RIGHTS RESERVED"
 *
 * $D2Tech$ $Rev: 48623 $ $Date: 2020-01-09 14:37:04 +0800 (Thu, 09 Jan 2020) $
 */

#ifndef _OSAL_PLATFORM_H_
#define _OSAL_PLATFORM_H_

/*
 * Exactly one of the following must be defined
 */

#if ( \
        defined(OSAL_LKM) + \
        defined(OSAL_PTHREADS) \
        != 1)

#if defined(OSAL_LKM)
#warning "OSAL_LKM is defined, ..."
#endif

#if defined(OSAL_PTHREADS)
#warning "OSAL_PTHREADS is defined, ..."
#endif

#error "Define proper OSAL abstraction, and choose only one"

#endif

/*
 * Set up definitions and includes
 * depending on the OSAL define
 * to minimize build rules.
 */

#define OSAL_IPC_FOLDER             "/var/tmp/osal/"
#define OSAL_INLINE                 inline
#define OSAL_STACK_SZ_LARGE         (8000)
#define OSAL_STACK_SZ_SMALL         (1000)

#define OSAL_NET_SOCK_INVALID_ID    (-1)

#if defined(OSAL_LKM)

#define OSAL_KERNEL_COMPAT_2_6_23 




/*
 * First the includes for the Kernel and module functions
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/random.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/stat.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/socket.h>
#include <linux/in.h>
#include <linux/in6.h>
#include <linux/net.h>
#include <linux/slab.h>
#include <linux/sem.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>
#include <asm/mach-generic/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/processor.h>
#include <asm/unistd.h>
#include <sched/rt.h>
#include <linux/proc_fs.h>




/*
 * OS specific type defines
 */
typedef int        OSAL_Fid;
typedef int        OSAL_SelectId; 
typedef int        OSAL_NetSockId;
typedef int        OSAL_FileId;
typedef fd_set     OSAL_SelectSet;

typedef struct {
    int *x509_ptr;
    int *pKey_ptr;
} OSAL_NetSslCert;

typedef struct {
    int *ssl_ptr;
    int *ctx_ptr;
    OSAL_NetSslCert *cert_ptr;
    int            (*certValidateCB)(int, void *);
} OSAL_NetSslId;

#define OSAL_NET_INADDR_ANY        (INADDR_ANY)
#define OSAL_NET_IN6ADDR_ANY       (IN6ADDR_ANY_INIT)
#define OSAL_NET_INADDR_LOOPBACK   (INADDR_LOOPBACK)

typedef enum {
    OSAL_TASK_PRIO_VTSPR = 90,
    OSAL_TASK_PRIO_ENC30 = 80,
    OSAL_TASK_PRIO_ENC20 = 82,
    OSAL_TASK_PRIO_ENC10 = 84,
    OSAL_TASK_PRIO_DEC30 = 81,
    OSAL_TASK_PRIO_DEC20 = 83,
    OSAL_TASK_PRIO_DEC10 = 85,
    OSAL_TASK_PRIO_NRT   = 0
} OSAL_TaskPrio;

typedef enum {
    OSAL_SEMB_UNAVAILABLE = 0,
    OSAL_SEMB_AVAILABLE   = 1
} OSAL_SemBState;

long OSAL_syscall3(
    long num,
    long arg0,
    long arg1,
    long arr2);


#endif /* OSAL_LKM */

#if defined(OSAL_PTHREADS)

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <semaphore.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <netdb.h>
#include <sys/types.h>
#include <linux/if.h>
#include <linux/rtnetlink.h>
#include <linux/pfkeyv2.h>
#ifdef OSAL_NET_ENABLE_SSL
#include <openssl/ssl.h>
#endif
#include <linux/ipsec.h>
#include <stdarg.h>
#include <regex.h>

/*
 * OS specific type defines
 */
typedef int         OSAL_Fid;
typedef int         OSAL_SelectId;
typedef int         OSAL_NetSockId;
typedef int         OSAL_FileId;
typedef fd_set      OSAL_SelectSet;
typedef regex_t     OSAL_Regex;
typedef regmatch_t  OSAL_Regmatch;

#ifdef OSAL_NET_ENABLE_SSL
/*
 * Certification for SSL
 */
typedef struct {
    X509     *x509_ptr;         /* X509 Certificate */
    EVP_PKEY *pKey_ptr;         /* Private key*/
} OSAL_NetSslCert;

typedef struct {
    SSL             *ssl_ptr;
    SSL_CTX         *ctx_ptr;
    OSAL_NetSslCert *cert_ptr;  /* Pointer to OSAL_NetSslCert */
    int            (*certValidateCB)(int, X509_STORE_CTX *);
                                /* Certificate validate callback function */
} OSAL_NetSslId;
#else
typedef struct {
    int *x509_ptr;
    int *pKey_ptr;
} OSAL_NetSslCert;

typedef struct {
    int *ssl_ptr;
    int *ctx_ptr;
    OSAL_NetSslCert *cert_ptr;
    int            (*certValidateCB)(int, void *);
} OSAL_NetSslId;
#endif

#define OSAL_NET_INADDR_ANY        (INADDR_ANY)
#define OSAL_NET_IN6ADDR_ANY       (IN6ADDR_ANY_INIT)
#define OSAL_NET_INADDR_LOOPBACK   (INADDR_LOOPBACK)

#define OSAL_NET_SOCK_INVALID_ID    (-1)

typedef enum {
    OSAL_TASK_PRIO_VTSPR = 0,
    OSAL_TASK_PRIO_ENC30 = 0,
    OSAL_TASK_PRIO_ENC20 = 0,
    OSAL_TASK_PRIO_ENC10 = 0,
    OSAL_TASK_PRIO_DEC30 = 0,
    OSAL_TASK_PRIO_DEC20 = 0,
    OSAL_TASK_PRIO_DEC10 = 0,
    OSAL_TASK_PRIO_NRT   = 0,
    OSAL_TASK_PRIO_NIC   = 0
} OSAL_TaskPrio;

typedef enum {
    OSAL_SEMB_UNAVAILABLE = 0,
    OSAL_SEMB_AVAILABLE   = 1
} OSAL_SemBState;

#define OSAL_ENTRY\
    int main(int argc, char *argv_ptr[])\
    {\
        OSAL_logMsg(\
                "\n\n"\
                "    ====================================== \n"\
                "                                           \n"\
                "               D2 Technologies             \n"\
                "         IP Communication Products         \n"\
                "                www.d2tech.com             \n\n"\
                "    Starting %s ...                        \n\n",\
                argv_ptr[0]);
#define OSAL_EXIT\
    }


#endif /* OSAL_PTHREADS */

#endif /* _OSAL_PLATFORM_H_ */
