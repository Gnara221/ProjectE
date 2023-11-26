
/*
**********************************************************************************
*                                  DATA TYPES
*                             (Compiler Specific)
**********************************************************************************
*/

typedef unsigned char BOOLEAN;
typedef unsigned char INT8U;   /* Unsigned  8 bit quantity           */
typedef signed char INT8S;     /* Signed    8 bit quantity           */
typedef unsigned short INT16U; /* Unsigned 16 bit quantity           */
typedef signed short INT16S;   /* Signed   16 bit quantity           */
typedef unsigned int INT32U;   /* Unsigned 32 bit quantity           */
typedef signed int INT32S;     /* Signed   32 bit quantity           */
typedef float FP32;            /* Single precision floating point    */
typedef double FP64;           /* Double precision floating point    */

typedef INT32U OS_STK;    /* Each stack entry is 32-bit wide    */
typedef INT32U OS_CPU_SR; /* Define size of CPU status register */

/*
*********************************************************************************
*                             Processor Specifics
*********************************************************************************
*/

#define OS_CRITICAL_METHOD 3

#if OS_CRITICAL_METHOD == 1
#define OS_ENTER_CRITICAL() ? ? ? ?
#define OS_EXIT_CRITICAL() ? ? ? ?
#endif

#if OS_CRITICAL_METHOD == 2
#define OS_ENTER_CRITICAL() ? ? ? ?
#define OS_EXIT_CRITICAL() ? ? ? ?
#endif

#if OS_CRITICAL_METHOD == 3
#define OS_ENTER_CRITICAL() while(0);
//OS_CPU_SR OS_CPU_SR_Save(OS_CPU_SR cpu_sr);
//void OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#define OS_EXIT_CRITICAL() while(0);
#endif


void OSCtxSw(void);
void OSIntCtxSw(void);
void OSStartHighRdy(void);

                                                 /* See OS_CPU_C.C                                     */
void OS_CPU_SysTickInit(INT32U cnts);
void OS_CPU_SysTickInitFreq (INT32U cpu_freq);

void OS_CPU_SysTickHandler(void);
void OS_CPU_PendSVHandler(void);


#define OS_STK_GROWTH 1 /* Stack growth (0=Up, 1=Down) */

#define OS_TASK_SW() OSCtxSw() //TODO: OSCtxSw() is not defined
