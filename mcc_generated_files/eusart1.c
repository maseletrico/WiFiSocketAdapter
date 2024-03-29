/**
  EUSART1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart1.c

  @Summary
    This is the generated driver implementation file for the EUSART1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25K22
        Driver Version    :  2.1.0
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

/**
  Section: Included Files
*/
#include "eusart1.h"
#include "../main.h"
#include <string.h>

/**
  Section: Macro Declarations
*/

#define EUSART1_TX_BUFFER_SIZE 64
#define EUSART1_RX_BUFFER_SIZE 100

/**
  Section: Global Variables
*/
volatile uint8_t eusart1TxHead = 0;
volatile uint8_t eusart1TxTail = 0;
volatile uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];
volatile uint8_t eusart1TxBufferRemaining;

volatile uint8_t eusart1RxHead = 0;
volatile uint8_t eusart1RxTail = 0;
volatile uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
volatile eusart1_status_t eusart1RxStatusBuffer[EUSART1_RX_BUFFER_SIZE];
volatile uint8_t eusart1RxCount;
volatile eusart1_status_t eusart1RxLastError;

/**
  Section: EUSART1 APIs
*/
void (*EUSART1_FramingErrorHandler)(void);
void (*EUSART1_OverrunErrorHandler)(void);
void (*EUSART1_ErrorHandler)(void);

void EUSART1_DefaultFramingErrorHandler(void);
void EUSART1_DefaultOverrunErrorHandler(void);
void EUSART1_DefaultErrorHandler(void);

void EUSART1_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    EUSART1_SetRxInterruptHandler(EUSART1_Receive_ISR);
    PIE1bits.TX1IE = 0;
    EUSART1_SetTxInterruptHandler(EUSART1_Transmit_ISR);
    // Set the EUSART1 module to the options selected in the user interface.

    // ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; WUE disabled; ABDEN disabled; DTRXP not_inverted; 
    BAUDCON1 = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA1 = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA1 = 0x24;

    // 
    SPBRG1 = 0x22;

    // 
    SPBRGH1 = 0x00;


    EUSART1_SetFramingErrorHandler(EUSART1_DefaultFramingErrorHandler);
    EUSART1_SetOverrunErrorHandler(EUSART1_DefaultOverrunErrorHandler);
    EUSART1_SetErrorHandler(EUSART1_DefaultErrorHandler);

    eusart1RxLastError.status = 0;

    // initializing the driver state
    eusart1TxHead = 0;
    eusart1TxTail = 0;
    eusart1TxBufferRemaining = sizeof(eusart1TxBuffer);

    eusart1RxHead = 0;
    eusart1RxTail = 0;
    eusart1RxCount = 0;

    // enable receive interrupt
    PIE1bits.RC1IE = 1;
}

uint8_t EUSART1_is_tx_ready(void)
{
    return eusart1TxBufferRemaining;
}

uint8_t EUSART1_is_rx_ready(void)
{
    return eusart1RxCount;
}

bool EUSART1_is_tx_done(void)
{
    return TXSTA1bits.TRMT;
}

eusart1_status_t EUSART1_get_last_status(void){
    return eusart1RxLastError;
}

uint8_t EUSART1_Read(void)
{
    uint8_t readValue  = 0;
    
    while(0 == eusart1RxCount)
    {
    }

    eusart1RxLastError = eusart1RxStatusBuffer[eusart1RxTail];

    readValue = eusart1RxBuffer[eusart1RxTail++];
    if(sizeof(eusart1RxBuffer) <= eusart1RxTail)
    {
        eusart1RxTail = 0;
    }
    PIE1bits.RC1IE = 0;
    eusart1RxCount--;
    PIE1bits.RC1IE = 1;

    return readValue;
}

void EUSART1_Write(uint8_t txData)
{
    while(0 == eusart1TxBufferRemaining)
    {
    }

    if(0 == PIE1bits.TX1IE)
    {
        TXREG1 = txData;
    }
    else
    {
        PIE1bits.TX1IE = 0;
        eusart1TxBuffer[eusart1TxHead++] = txData;
        if(sizeof(eusart1TxBuffer) <= eusart1TxHead)
        {
            eusart1TxHead = 0;
        }
        eusart1TxBufferRemaining--;
    }
    PIE1bits.TX1IE = 1;
}


void EUSART1_Transmit_ISR(void)
{

    // add your EUSART1 interrupt custom code
    if(sizeof(eusart1TxBuffer) > eusart1TxBufferRemaining)
    {
        TXREG1 = eusart1TxBuffer[eusart1TxTail++];
        if(sizeof(eusart1TxBuffer) <= eusart1TxTail)
        {
            eusart1TxTail = 0;
        }
        eusart1TxBufferRemaining++;
    }
    else
    {
        PIE1bits.TX1IE = 0;
    }
}

void EUSART1_Receive_ISR(void)
{
    
    eusart1RxStatusBuffer[eusart1RxHead].status = 0;

    if(RCSTA1bits.FERR){
        eusart1RxStatusBuffer[eusart1RxHead].ferr = 1;
        EUSART1_FramingErrorHandler();
    }

    if(RCSTA1bits.OERR){
        eusart1RxStatusBuffer[eusart1RxHead].oerr = 1;
        EUSART1_OverrunErrorHandler();
    }
    
    if(eusart1RxStatusBuffer[eusart1RxHead].status){
        EUSART1_ErrorHandler();
    } else {
        EUSART1_RxDataHandler();
    }
    
    // or set custom function using EUSART1_SetRxInterruptHandler()
}

void EUSART1_RxDataHandler(void){
    // use this default receive interrupt handler code
    eusart1RxBuffer[eusart1RxHead++] = RCREG1;
    if(RCREG1 =='\n'){
        compareStr(eusart1RxBuffer);
        eusart1RxHead =  0;
        lineFeed=true;
    }else if(RCREG1=='<'){//prompt init serial char
        eusart1RxHead =  0;
        eusart1RxBuffer[eusart1RxHead++] = RCREG1;
    }else if(RCREG1=='>'){//prompt final serial char
        eusart1RxHead =  0;
        compareStr(eusart1RxBuffer);
    }
    //buffer overflow
    if(sizeof(eusart1RxBuffer) <= eusart1RxHead)
    {
        eusart1RxHead = 0;
    }
    eusart1RxCount++;
    
}

void EUSART1_DefaultFramingErrorHandler(void){}

void EUSART1_DefaultOverrunErrorHandler(void){
    // EUSART1 error - restart

    RCSTA1bits.CREN = 0;
    RCSTA1bits.CREN = 1;

}

void EUSART1_DefaultErrorHandler(void){
    EUSART1_RxDataHandler();
}

void EUSART1_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART1_FramingErrorHandler = interruptHandler;
}

void EUSART1_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART1_OverrunErrorHandler = interruptHandler;
}

void EUSART1_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART1_ErrorHandler = interruptHandler;
}

void EUSART1_SetTxInterruptHandler(void (* interruptHandler)(void)){
    EUSART1_TxDefaultInterruptHandler = interruptHandler;
}

void EUSART1_SetRxInterruptHandler(void (* interruptHandler)(void)){
    EUSART1_RxDefaultInterruptHandler = interruptHandler;
}


void compareStr (uint8_t str1[]){
    volatile int contLen=0;
    volatile int h=0;
    volatile int i=0;
    volatile int lenStr=0;

    //for(;eusart1RxHead;eusart1RxHead--){
     for(i=0;i<3;i++){
       if(str1[h]=='A' && str1[h+1]=='s' && str1[h+2]=='s' && str1[h+3]=='o'
               && str1[h+8]=='e' && str1[h+9]=='d' && str1[h+10]==']'){
            STATUS_SERIAL_ASSOCIATED = true;
       }
       if(str1[h]=='n' && str1[h+1]=='e' && str1[h+2]=='t' && str1[h+3]=='w'
               && str1[h+8]=='u' && str1[h+9]=='p'){
            STATUS_SERIAL_NETWORK_UP = true;
       }
       if(str1[h]=='R' && str1[h+1]=='e' && str1[h+2]=='a' && str1[h+3]=='d'
               && str1[h+8]=='y'){
            STATUS_SERIAL_READY = true;
       }
       if(str1[h+3]=='p' && str1[h+4]=='r' && str1[h+5]=='o' && str1[h+6]=='g'
               && str1[h+7]=='r' && str1[h+8]=='e' && str1[h+9]=='s'){
            STATUS_SERIAL_IN_PROGRESS = true;
       }
       if(str1[h]=='J' && str1[h+1]=='o' && str1[h+2]=='i' && str1[h+3]=='n'
               && str1[h+8]=='e' && str1[h+9]=='e' && str1[h+10]=='d'){
            STATUS_SERIAL_JOIN_FAILED = true;
       }
       if(str1[h]=='S' && str1[h+1]=='u' && str1[h+2]=='c' && str1[h+3]=='c'
               && str1[h+4]=='e' && str1[h+5]=='s' && str1[h+6]=='s'){
            STATUS_SERIAL_SUCCESS = true;
       }
       if(str1[h]=='S' && str1[h+1]=='S' && str1[h+2]=='I' && str1[h+3]=='D'
               && str1[h+9]=='s' && str1[h+10]=='e' && str1[h+11]=='t'){
            STATUS_SERIAL_SSID_NOT_SET = true;
       }
       if(str1[h]=='S' && str1[h+1]=='e' && str1[h+2]=='t' && str1[h+4]=='O'
               && str1[h+5]=='K'){
            STATUS_SERIAL_SET_OK = true;
       }
       if(str1[h]=='0' && str1[h+1]=='x' && str1[h+2]=='0' && str1[h+3]=='8'){
            STATUS_SERIAL_WEB_OK = true;
       }
       
       h++;
    }
    
 }


/**
  End of File
*/
