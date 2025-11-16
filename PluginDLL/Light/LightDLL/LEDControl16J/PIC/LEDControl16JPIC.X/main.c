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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26Q84
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

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    ADC_Initialize();
    ADC_DisableChannelSequencer();    //Disable scanner
    ADC_SelectContext(CONTEXT_1);
    adc_result_t convertedValue[16];

    while (1)
    {
         convertedValue[0] = ADC_GetSingleConversion(ANA0);
         ADC_EnableChannelScan(CONTEXT_1);
         convertedValue[1] = ADC_GetSingleConversion(ANA1);
         convertedValue[2] = ADC_GetSingleConversion(ANA2);
         convertedValue[3] = ADC_GetSingleConversion(ANA3);
         convertedValue[4] = ADC_GetSingleConversion(ANA4);
         convertedValue[5] = ADC_GetSingleConversion(ANA5);
         convertedValue[6] = ADC_GetSingleConversion(ANA6);
         convertedValue[7] = ADC_GetSingleConversion(ANA7);
         convertedValue[8] = ADC_GetSingleConversion(ANA8);
         convertedValue[9] = ADC_GetSingleConversion(ANA9);
         convertedValue[10] = ADC_GetSingleConversion(ANA10);
         convertedValue[11] = ADC_GetSingleConversion(ANA11);
         convertedValue[12] = ADC_GetSingleConversion(ANA12);
         convertedValue[13] = ADC_GetSingleConversion(ANA13);
         convertedValue[14] = ADC_GetSingleConversion(ANA14);
         convertedValue[15] = ADC_GetSingleConversion(ANA15);
         
       // Add your application code
    }
}
/**
 End of File
*/