// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#include <stdint.h>          /* For uint32_t definition                       */
#include <sys/attribs.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "user.h"            /* variables/params used by user.c               */
#include "OLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "UART.h"

#define X_MAX 128
#define Y_MAX 28
#define X_center 64
#define Y_center 14


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/

volatile int x,y,x_factor,y_factor,y_kill;
volatile    int n, i=0;

void InitGPIO(void) {
    // LED output
    // Disable analog mode for G6
    ANSELGbits.ANSG6 = 0;
    // Set direction to output for G6
    TRISGbits.TRISG6 = 0;

    // Initialize outputs for other LEDs
    ANSELBbits.ANSB11 = 0;
    ANSELGbits.ANSG15 = 0;

    TRISBbits.TRISB11 = 0;
    TRISGbits.TRISG15 = 0;
    TRISDbits.TRISD4 = 0;

    // Turn off LEDs for initialization
    LD1_PORT_BIT = 0;
    LD2_PORT_BIT = 0;
    LD3_PORT_BIT = 0;
    LD4_PORT_BIT = 0;

    // Initilalize input for BTN1
    // Disable analog mode
    ANSELAbits.ANSA5 = 0;
    // Set direction to input
    TRISAbits.TRISA5 = 1;

    // Initialize input for BTN2
    TRISAbits.TRISA4 = 1;
}

void InitBIOSGPIO(void) {
    /* Setup functionality and port direction */
    // LED outputs
    // Disable analog mode
    // Set directions to output
    TRISE = 0;
   
    // Test LEDs
    LATE = 0xff;        
    
    // Turn off LEDs for initialization
    LATE = 0;

    // Button inputs
    ANSELGbits.ANSG7 = 0;
    
    
    
    ANSELEbits.ANSE8 = 0;
    ANSELEbits.ANSE8 = 0;
 
    ANSELCbits.ANSC1 = 0;
    
    // Set directions to input
    TRISGbits.TRISG7 = 1;
    TRISDbits.TRISD5 = 1;
    TRISFbits.TRISF1 = 1;
    TRISAbits.TRISA2 = 1; 
    
    TRISEbits.TRISE8 = 1;
    TRISEbits.TRISE9 = 1;
    TRISAbits.TRISA14 = 1;
    TRISCbits.TRISC1 = 1; 
    
    /*
    #define BIOS_SW1_PORT_BIT       PORTEbits.RE8
#define BIOS_SW2_PORT_BIT       PORTEbits.RE9
#define BIOS_SW3_PORT_BIT       PORTAbits.RA14
#define BIOS_SW4_PORT_BIT       PORTCbits.RC1*/
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    InitBIOSGPIO();
    
    OledHostInit();
    OledDspInit();
    OledDvrInit();
    
    // TODO: Add UART4 Initialization call here
    UART4_init();
}

void Task1(void * pvParameters) {
    int n=0; 
    char buff[20];
    
    x=0;
    y=0;
    y_kill=2;
    
    while (1) {
       
        // TODO: Take mutex here
        
        xSemaphoreTake(xMutexOLED, portMAX_DELAY);
         
        // TODO: Give mutex here
        
        if (i>5){
            
            i=1;
            x=x+1;
            
            
            if (x>50) {
                x=1;
                
            }
        
       
        
        
       
        
        OledSetDrawColor(1);
        
            //OledSetCursor(x,y);
            /*OledSetDrawColor(1);
            OledMoveTo(x,y);
            OledDrawRect(i,i);
        
            OledSetDrawColor(0);
            OledMoveTo(x-1,y-1);
            OledDrawRect(i,i);*/
        }
      x_factor=x;
      y_factor=x;
      OledMoveTo(X_center-x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center+y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      //diagonals
      OledMoveTo(X_center-y,Y_center-y);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      OledMoveTo(X_center+y,Y_center+y);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center-y,Y_center+y);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+y,Y_center-y);
      OledLineTo(X_center+x_factor,Y_center-y_factor);
       //
      
      
      OledSetDrawColor(0);
      x_factor=x-1;
      y_factor=x-1;
      OledMoveTo(X_center-x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center+y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      OledMoveTo(X_center-(y-y_kill),Y_center-(y-y_kill));
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      OledMoveTo(X_center+(y-y_kill),Y_center+(y-y_kill));
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center-(y-y_kill),Y_center+(y-y_kill));
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+(y-y_kill),Y_center-(y-y_kill));
      OledLineTo(X_center+x_factor,Y_center-y_factor);
       
       
        
        
      
      
      OledSetDrawColor(1);
      x_factor=y;
      y_factor=y;
      OledMoveTo(X_center-x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center+y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      /*
      x_factor=y-y_kill;
      y_factor=y-y_kill;
      OledMoveTo(X_center-x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center+y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      */
      OledUpdate();   
        
        
        i++; 
        
        xSemaphoreGive(xMutexOLED);
        
        
        
        
        
        vTaskDelay(1);     
    }
}

void Task2(void * pvParameters) {
    int n=0; 
   
    char buff[20];
   
    while (1) {
        // TODO: Add trigger code here    
        //sprintf(buff, "lol: %d", n++);
        // TODO: Take mutex here
        
        xSemaphoreTake(xMutexOLED, portMAX_DELAY);
        //OledSetCursor(0,2);
        //OledPutString(buff);
       
        
      /*  OledSetDrawColor(0);
      x_factor=y-y_kill-1;
      y_factor=y-y_kill-1;
      OledMoveTo(X_center-x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center+y_factor);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center+x_factor,Y_center-y_factor);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
        
      */
        
      
      
      
      if (BIOS_SW3_PORT_BIT==1)
        {
            sprintf(buff, "%d", y_kill);
            OledSetCursor(0,0);
            OledPutString(buff);
            
            
            
            y=y+y_kill;
                y_kill=y_kill+1;
                if (y>15){
                    y=1;
                    y_kill=2;
                //    x=1;            

                }
        }
      
        
        // TODO: Give mutex here
        xSemaphoreGive(xMutexOLED);
        
         vTaskDelay(500);
    }
}

// TODO: Define function ClockTask here

// TODO: Define SerialInTask here

void DelayMs(int t) {
    volatile long int count = t*33356;
    
    while (count--)
        ;
}