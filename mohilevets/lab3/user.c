/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include <sys/attribs.h>
#include "ADC.h"
#include "ADC.c"

volatile uint32_t G_i;
volatile uint32_t Delay_max_adc = 200;
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/
void InitTimer2AndOC5(void) {
    T2CON = 0; // clear timer settings to defaults
    T2CONbits.TCKPS = 7; // divide clock by 256 with prescaler
    TMR2 = 0;
    // Set period for timer
    PR2 = PWM_PERIOD_COUNTS-1;    
    // Set initial duty cycle to 50%
    OC5R = PWM_PERIOD_COUNTS/2;
    // Set reload duty cycle to 50%
    OC5RS = PWM_PERIOD_COUNTS/2;
    // Configure OC5 control register
    OC5CONbits.ON = 1;
    OC5CONbits.OC32 = 0;    // 16 bit mode
    OC5CONbits.OCTSEL = 0; // Select timer 2
    OC5CONbits.OCM = 6; // Select PWM mode without fault pin
    // Map OC5 signal to pin G6
    RPG6R = 11; // Select OC5
    // Start Timer 2
    T2CONbits.ON = 1;
}

void InitTimer3(void) {
    T3CON = 0; // clear timer settings to defaults
    T3CONbits.TCKPS = 0; // divide clock by 256 with prescaler
    TMR3 = 0;
    PR3 = 10000; // 100 MHz / (256 * 10 Hz)
    
    IPC3bits.T3IP = 2; // Priority level 3
    IPC3bits.T3IS = 0;
    
    IFS0bits.T3IF = 0; // Clear interrupt request flag
    IEC0bits.T3IE = 1; // Enable timer interrupt
    
    T3CONbits.ON = 1; // Start Timer 2
}

void __ISR(_TIMER_3_VECTOR, IPL2AUTO) ISR_Timer_3 (void) {
    static int LED_state = 1;
    //static int Delay_max_adc = 200;
    //static int i = 0;
   
    
    if (G_i<Delay_max_adc){
        G_i=G_i+1;
    } else {
   //      Delay_max_adc=ReadPotentiometerWithADC()*4000;
        G_i=0;
        LEDHeartbeat();
        
        LD4_PORT_BIT = LED_state;
        LED_state = 1-LED_state;
    }
    // Toggle LED2
    
    
    
    // Reset interrupt flag
    IFS0bits.T3IF = 0;
}


void AdjustLED1Brightness(void) {
    unsigned int pot_pos = 0, on_time_counts=0;
    Delay_max_adc=ReadPotentiometerWithADC();
    // Read ADC
    //pot_pos = ReadPotentiometerWithADC();
    // Convert value to on-time (counts)
   // on_time_counts = (pot_pos*PWM_PERIOD_COUNTS)/MAX_ADC_VALUE;
    // Update OC5
    //OC5RS = on_time_counts;
}

void LEDHeartbeat(void) {
    static int on_time_counts = 0;  // static to retain value across calls
    static int step = 1;            // static to retain value across calls
    
    // change duty cycle
    on_time_counts += step;  
    // Check for underflow and overflow
    if (on_time_counts < 0) {
        on_time_counts = 0;
        step = 1;
    } else if (on_time_counts > PWM_PERIOD_COUNTS-1) {
        on_time_counts = PWM_PERIOD_COUNTS-1;
        step = -1;
    }
    // Update OC2 duty cycle
    OC5RS = on_time_counts;
}

void InitGPIO(void) {
    /* Setup functionality and port direction */
    // LED output
    // Disable analog mode
    ANSELGbits.ANSG6 = 0;
    ANSELBbits.ANSB11 = 0;
    ANSELGbits.ANSG15 = 0;
    // Set directions to output
    TRISGbits.TRISG6 = 0;
    TRISBbits.TRISB11 = 0;
    TRISGbits.TRISG15 = 0;
    TRISDbits.TRISD4 = 0;

    // Turn off LEDs for initialization
    LD1_PORT_BIT = 0;
    LD2_PORT_BIT = 0;
    LD3_PORT_BIT = 0;
    LD4_PORT_BIT = 0;

    // Button inputs
    // Disable analog mode
    ANSELAbits.ANSA5 = 0;
    // Set directions to input
    TRISAbits.TRISA5 = 1;
    TRISAbits.TRISA4 = 1;
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    initWiFIREadc();
    InitTimer2AndOC5();
    InitTimer3();
    
    // Set Interrupt Controller for multi-vector mode
    INTCONSET = _INTCON_MVEC_MASK;
    // Globally enable interrupts
    __builtin_enable_interrupts();
    // Enable peripherals which can generate an interrupt
    
}