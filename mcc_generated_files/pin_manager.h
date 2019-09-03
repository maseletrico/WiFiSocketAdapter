/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RF_LED aliases
#define RF_LED_TRIS                 TRISAbits.TRISA2
#define RF_LED_LAT                  LATAbits.LATA2
#define RF_LED_PORT                 PORTAbits.RA2
#define RF_LED_ANS                  ANSELAbits.ANSA2
#define RF_LED_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RF_LED_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RF_LED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RF_LED_GetValue()           PORTAbits.RA2
#define RF_LED_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RF_LED_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RF_LED_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define RF_LED_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RF_WAKE aliases
#define RF_WAKE_TRIS                 TRISBbits.TRISB1
#define RF_WAKE_LAT                  LATBbits.LATB1
#define RF_WAKE_PORT                 PORTBbits.RB1
#define RF_WAKE_WPU                  WPUBbits.WPUB1
#define RF_WAKE_ANS                  ANSELBbits.ANSB1
#define RF_WAKE_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RF_WAKE_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RF_WAKE_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RF_WAKE_GetValue()           PORTBbits.RB1
#define RF_WAKE_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RF_WAKE_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RF_WAKE_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define RF_WAKE_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define RF_WAKE_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define RF_WAKE_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set RF_EN aliases
#define RF_EN_TRIS                 TRISBbits.TRISB2
#define RF_EN_LAT                  LATBbits.LATB2
#define RF_EN_PORT                 PORTBbits.RB2
#define RF_EN_WPU                  WPUBbits.WPUB2
#define RF_EN_ANS                  ANSELBbits.ANSB2
#define RF_EN_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RF_EN_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RF_EN_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RF_EN_GetValue()           PORTBbits.RB2
#define RF_EN_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RF_EN_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RF_EN_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define RF_EN_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define RF_EN_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define RF_EN_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set RF_RESET aliases
#define RF_RESET_TRIS                 TRISBbits.TRISB3
#define RF_RESET_LAT                  LATBbits.LATB3
#define RF_RESET_PORT                 PORTBbits.RB3
#define RF_RESET_WPU                  WPUBbits.WPUB3
#define RF_RESET_ANS                  ANSELBbits.ANSB3
#define RF_RESET_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RF_RESET_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RF_RESET_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RF_RESET_GetValue()           PORTBbits.RB3
#define RF_RESET_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RF_RESET_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RF_RESET_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define RF_RESET_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define RF_RESET_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define RF_RESET_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set SW1 aliases
#define SW1_TRIS                 TRISCbits.TRISC0
#define SW1_LAT                  LATCbits.LATC0
#define SW1_PORT                 PORTCbits.RC0
#define SW1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SW1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SW1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SW1_GetValue()           PORTCbits.RC0
#define SW1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SW1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set SW2 aliases
#define SW2_TRIS                 TRISCbits.TRISC1
#define SW2_LAT                  LATCbits.LATC1
#define SW2_PORT                 PORTCbits.RC1
#define SW2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SW2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SW2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SW2_GetValue()           PORTCbits.RC1
#define SW2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SW2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/