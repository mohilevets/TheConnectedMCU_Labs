/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "user.h"           /* User funct/params, such as InitApp             */
#include "OLED.h"
#include "stdio.h"
#include <math.h>

#define X_MAX 128
#define Y_MAX 28
#define X_center 64
#define Y_center 14

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{
    uint8_t pattern[5]= {0x0, 0x11, 0x99, 0xbb, 0xff};
    char buffer[32];
    int x,y,x_factor,y_factor,y_kill;
    int n, i=0;
    /* Initialize I/O 
     * and Peripherals
     * for application */
    InitApp();
    
    OledDvrInit();
    
    OledSetDrawColor(1);
    OledSetDrawMode(modOledSet);
    OledSetFillPattern(OledGetStdPattern(3));
    
    /*OledSetCursor(0,0);
    OledPutString("Hello,");
    OledSetCursor(0,1);
    OledPutString("World!");
    */
    x=0;
    y=0;
    y_kill=2;
    while (1) {
        
        
        /*
        OledSetCursor(0, 3);
        sprintf(buffer, "%7d", i);
        OledPutString(buffer);
        
        
        */ 
        //my
        OledSetDrawColor(1);
        //OledMoveTo(100,20);
       // OledDrawPixel();
        
        if (i>5){
            
            i=1;
            x=x+1;
            
            
            if (x>50) {
                x=1;
                y=y+y_kill;
                y_kill=y_kill+1;
                if (y>15){
                    y=1;
                    y_kill=2;
                //    x=1;            

                }
            }
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
      
      //diagonals
      /*
      OledMoveTo(X_center,Y_center);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      OledMoveTo(X_center,Y_center);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center,Y_center);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(X_center,Y_center);
      OledLineTo(X_center+x_factor,Y_center-y_factor);
      */
       //  
      
      
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
      
      
      //diagonals corners
      /*
      OledMoveTo(0,0);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      OledMoveTo(128,28);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(0,28);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(128,0);
      OledLineTo(X_center+x_factor,Y_center-y_factor);
      
       */
      
      
      OledSetDrawColor(0);
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
      
      //diagonals corners
      /*
      OledMoveTo(0,0);
      OledLineTo(X_center-x_factor,Y_center-y_factor);
      
      OledMoveTo(128,28);
      OledLineTo(X_center+x_factor,Y_center+y_factor);
      
      OledMoveTo(0,28);
      OledLineTo(X_center-x_factor,Y_center+y_factor);
      
      OledMoveTo(128,0);
      OledLineTo(X_center+x_factor,Y_center-y_factor);
      
       */
      
      //OledMoveTo((X_MAX/2)-x_factor,(Y_MAX/2)-y_factor);
      //OledDrawRect(x_factor,y_factor);
      
      
      
        
        
        
        i++;
        
        //
        
        /*
        OledMoveTo(96,16);
        OledSetDrawColor(0);
        x = 96 + 15*cos(i/80.0);
        y = 16 + 15*sin(i/80.0);
        OledLineTo(x, y);

        OledSetDrawColor(1);
        OledMoveTo(96,16);
        x = 96 + 15*cos((i+1)/80.0);
        y = 16 + 15*sin((i+1)/80.0);
        OledLineTo(x, y);
        OledUpdate();
        i++;
        
        */
        //OledDrawPixel(11,11);
        OledUpdate();
    }

}
