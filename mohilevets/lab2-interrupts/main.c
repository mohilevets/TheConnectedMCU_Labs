#ifdef __XC32
    #include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */

int32_t main(void)
{

    InitApp();
    while(1){
        TASK_Scan_LEDs();
    }
}
