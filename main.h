/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/tmr0.h"
// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

#define false 0
#define true 1

uint8_t STATUS_ADDRESS = 0x02; 

uint8_t sw1Debounce = false;
uint8_t sw2Debounce = false;
uint8_t statusSerial = 0x00;
const uint8_t txData[] = "networp_up";
uint16_t count1ms=0x00, dbCounter=0x00,db2Counter=0x00,pressCounter=0x00;
bool LED_RF_BLINK=false;
bool LED_RF_DOUBLE_BLINK=false;
bool AMW007_READY=false;
bool clearSetupMem=false;

bool STATUS_SERIAL_READY            = false;
bool STATUS_SERIAL_WEB_SETUP        = false;
bool STATUS_SERIAL_ASSOCIATED       = false;
bool STATUS_SERIAL_IN_PROGRESS      = false;
bool STATUS_SERIAL_JOIN_FAILED      = false;
bool STATUS_SERIAL_NETWORK_UP       = false;
bool STATUS_SERIAL_SUCCESS          = false;
bool STATUS_SERIAL_SSID_NOT_SET     = false;
bool STATUS_SERIAL_SET_OK           = false;
bool STATUS_SERIAL_WEB_OK           = false;
bool lineFeed = false;

uint8_t adapterStatus;
uint16_t intervalLedOn,intervalLedOff;

const char  *NETWORK_UP = {"network_up"};
const char  *SETUP_WEB = {"setup web"};
const char  *RETURN = {"\r"};
const char  *AMW_READY = {"Ready"};
const char  *ASSOCIATED = {"[Associated]"};
const char  *IN_PROGRESS = {"In progress"};
const char  *JOIN_FAILED = {"Join failed"};
const char  *WEB_SETUP_STARTED = {"Web setup started"};
const char  *PRINT_LEVEL_0 = {"set system.print_level 3"};
const char  *HEADER_ENABLED = {"set system.cmd.header_enabled 1"};
const char  *PROMPT_DISABLE = {"set system.cmd.prompt_enabled 0"};
const char  *ECHO_OFF = {"set system.cmd.echo off"};
const char  *ECHO_ON = {"set system.cmd.echo on"};

/*
 
set system.print_level 0-> Turn off all debug & informational prints
set system.cmd.header_enabled 1 -> Enable a response header (described below)
set system.cmd.prompt_enabled 0 -> Turn off the user prompt
set system.cmd.echo off > Turn off  character echo


 */

uint8_t i=0;
uint8_t temp=0; 
// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */

void blinkLED (uint16_t intervalOn, uint16_t intervalOff);
void send_string (const char *x);
bool answerReady (void);
void cleanBuffer(void);
void AMW007_Init(void);
void LED_RF_BlinkOnce(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

