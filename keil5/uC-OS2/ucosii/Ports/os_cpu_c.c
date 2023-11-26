#include  <ucos_ii.h>
OS_STK *OSTaskStkInit (void  (*task)(void *pd),
                       void   *pdata,
                       OS_STK *ptos,
                       INT16U  opt){return 0;}
void OSStartHighRdy(void){}
void OSCtxSw(void){}
void OSIntCtxSw(void){}
void OSTickISR(void){}
void OSTaskCreateHook(OS_TCB *a){}
void OSTaskDelHook(OS_TCB *a){}
void OSTaskSwHook(){}
void OSTaskIdleHook(){}
void OSTaskStatHook(){}
void OSTimeTickHook(){}
void OSInitHookBegin(){}
void OSInitHookEnd(){}
void OSTCBInitHook(OS_TCB *a){}
void OSTaskReturnHook(OS_TCB *a){}
