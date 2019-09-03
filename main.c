/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25K22
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/memory.h"
#include <string.h>
#include "main.h"




#define BUFFER_SIZE 20



void main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    OSCILLATOR_Initialize();
    
    TMR0_Initialize();
    TMR0_StartTimer();
    EUSART1_Initialize();
    
    
    //Pin Setup
    PIN_MANAGER_Initialize();
    
    RF_LED_SetLow();
    
    SW1_SetDigitalInput();
    SW2_SetDigitalInput();
    RF_RESET_SetDigitalInput();
    
    
    pressCounter=0;
    //clear wifi network configured
    while(!SW2_PORT){
        //while key pressed for 3 seconds
        if(pressCounter>=3000){
            //LED_RF_BlinkOnce();
            adapterStatus='N';
            DATAEE_WriteByte(STATUS_ADDRESS,adapterStatus);
            adapterStatus = DATAEE_ReadByte(STATUS_ADDRESS);
            RF_LED_SetHigh();
            clearSetupMem=true;
            break;
        }
    }
    //wait the user release SW2
    if(clearSetupMem){
         while(!SW2_PORT){}
         clearSetupMem=false;
    }
    
    //Reset AMW007
    RF_RESET_SetLow();
    __delay_ms(500);
    RF_RESET_SetHigh();
    
    LED_RF_BlinkOnce();
    
    __delay_ms(1000);
    
    AMW007_Init();
    
     //Read Adapter staus
    adapterStatus = DATAEE_ReadByte(STATUS_ADDRESS);
    //if not status save the first status
    if(adapterStatus!='N' && adapterStatus!='S'){
        adapterStatus='N';
        DATAEE_WriteByte(STATUS_ADDRESS,adapterStatus);
        adapterStatus = DATAEE_ReadByte(STATUS_ADDRESS);
    }
    //if the adapter is configured turn off the LED
    if(adapterStatus=='S'){
        cleanBuffer();
        send_string(NETWORK_UP);
        STATUS_SERIAL_IN_PROGRESS=false;
        while(!STATUS_SERIAL_IN_PROGRESS){};
        STATUS_SERIAL_IN_PROGRESS=false;
        blinkLED(80,100);
        STATUS_SERIAL_ASSOCIATED=false;
        while(!STATUS_SERIAL_ASSOCIATED){};
        //stop blink LED
        LED_RF_BLINK=false;
        RF_LED_SetLow();
    }else if(adapterStatus=='N'){
        //blinkLED(80,250);
        RF_LED_SetHigh();
    }
 
    
    while (1)
    {
        if(!SW1_PORT && !sw1Debounce){
            STATUS_SERIAL_IN_PROGRESS=false;
            send_string(SETUP_WEB);
            sw1Debounce = true;
            dbCounter=0;
            AMW007_READY=false;
            while(!STATUS_SERIAL_IN_PROGRESS){};
            STATUS_SERIAL_IN_PROGRESS=false;
            blinkLED(50,1250);
            //waiting for the setup web completed
            lineFeed=false;
            while(!lineFeed){};
            adapterStatus='S';
            DATAEE_WriteByte(STATUS_ADDRESS,adapterStatus);
            adapterStatus = DATAEE_ReadByte(STATUS_ADDRESS);
            if(adapterStatus=='S'){
                LED_RF_BLINK=false;
                LED_RF_DOUBLE_BLINK=true;
            }else{
                RF_LED_SetHigh();
            }
            count1ms=0x00;  
            
        }
        
        if(!SW2_PORT && !sw2Debounce){
            send_string(NETWORK_UP);
            sw2Debounce = true;
            db2Counter=0;
            AMW007_READY=false;
            blinkLED(500,500);
            while(statusSerial==0){};
            if(statusSerial!=STATUS_SERIAL_ASSOCIATED){
                //Associated success
                adapterStatus='S';
                DATAEE_WriteByte(STATUS_ADDRESS,adapterStatus);
                adapterStatus = DATAEE_ReadByte(STATUS_ADDRESS);
                blinkLED(100,600);
                
            }else if(statusSerial!=STATUS_SERIAL_SUCCESS){
                //WLAN network is already up
                
                //Stop blink LED
                LED_RF_BLINK=false;
            }else if(statusSerial!=STATUS_SERIAL_SSID_NOT_SET){
                //SSID not set
                //Stop blink LED
                LED_RF_BLINK=false;
                RF_LED_SetHigh();
            }
            
            
        }
       
    }
}

bool answerReady(){
    volatile uint8_t rxData;
    volatile uint8_t rxDataBuffer[100];
    volatile uint8_t rxDataCounter = 0x00;
    volatile uint8_t rxDataLen = 0x00;
    
    if(EUSART1_is_rx_ready())
    {
        rxData =  EUSART1_Read();
        if(rxData =='\r'){
            rxDataCounter=0x00;

              
        }else{
            rxDataBuffer[rxDataCounter]=rxData;
            rxDataCounter++;
            if(rxDataCounter>=100){
               rxDataCounter=0x00; 
            }
            return false;
        }
    }
    return false;
}


void cleanBuffer(){
    volatile uint8_t rxData;
    volatile uint8_t rxDataBuffer[100];
    volatile uint8_t rxDataCounter = 0x00;
    volatile uint8_t rxDataLen = 0x00;
  
    for(rxDataCounter=0;rxDataCounter>=100;rxDataCounter++){
        rxDataBuffer[rxDataCounter]=0x00;
    }
    
}

void blinkLED(uint16_t intervalOn, uint16_t intervalOff){
    intervalLedOn=intervalOn;
    intervalLedOff=intervalOff;
    count1ms=0x00;    
    LED_RF_BLINK=true;
}

void send_string(const char *x)
 {
    while(*x)
     {
        EUSART1_Write(*x++); 
     }
     EUSART1_Write(13);
    EUSART1_Write(10);
 }

void AMW007_Init()
{
    STATUS_SERIAL_SET_OK=false;
    send_string(ECHO_OFF);
//    while(!STATUS_SERIAL_SET_OK){};
//    STATUS_SERIAL_SET_OK=false;
    
    send_string(PROMPT_DISABLE);
//    while(!STATUS_SERIAL_SET_OK){};
//    STATUS_SERIAL_SET_OK=false;
    
    send_string(PRINT_LEVEL_0);
//    while(!STATUS_SERIAL_SET_OK){};
    STATUS_SERIAL_SET_OK=false;
    
    send_string(HEADER_ENABLED);
//    while(!STATUS_SERIAL_SET_OK){};
    STATUS_SERIAL_SET_OK=false;
   
         
}

void LED_RF_BlinkOnce(){
    //Blink LED once
    RF_LED_SetHigh();
    __delay_ms(250);
    RF_LED_SetLow();
}

/**
 End of File
*/