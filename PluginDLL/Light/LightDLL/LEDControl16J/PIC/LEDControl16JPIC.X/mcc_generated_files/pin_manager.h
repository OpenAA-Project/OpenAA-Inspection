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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26Q84
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

// get/set ANA0 aliases
#define ANA0_TRIS                 TRISAbits.TRISA0
#define ANA0_LAT                  LATAbits.LATA0
#define ANA0_PORT                 PORTAbits.RA0
#define ANA0_WPU                  WPUAbits.WPUA0
#define ANA0_OD                   ODCONAbits.ODCA0
#define ANA0_ANS                  ANSELAbits.ANSELA0
#define ANA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ANA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ANA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ANA0_GetValue()           PORTAbits.RA0
#define ANA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ANA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ANA0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define ANA0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define ANA0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define ANA0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define ANA0_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define ANA0_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set ANA1 aliases
#define ANA1_TRIS                 TRISAbits.TRISA1
#define ANA1_LAT                  LATAbits.LATA1
#define ANA1_PORT                 PORTAbits.RA1
#define ANA1_WPU                  WPUAbits.WPUA1
#define ANA1_OD                   ODCONAbits.ODCA1
#define ANA1_ANS                  ANSELAbits.ANSELA1
#define ANA1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ANA1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ANA1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ANA1_GetValue()           PORTAbits.RA1
#define ANA1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ANA1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ANA1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define ANA1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define ANA1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define ANA1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define ANA1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define ANA1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set ANA2 aliases
#define ANA2_TRIS                 TRISAbits.TRISA2
#define ANA2_LAT                  LATAbits.LATA2
#define ANA2_PORT                 PORTAbits.RA2
#define ANA2_WPU                  WPUAbits.WPUA2
#define ANA2_OD                   ODCONAbits.ODCA2
#define ANA2_ANS                  ANSELAbits.ANSELA2
#define ANA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ANA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ANA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ANA2_GetValue()           PORTAbits.RA2
#define ANA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ANA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ANA2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ANA2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ANA2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ANA2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ANA2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define ANA2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set ANA3 aliases
#define ANA3_TRIS                 TRISAbits.TRISA4
#define ANA3_LAT                  LATAbits.LATA4
#define ANA3_PORT                 PORTAbits.RA4
#define ANA3_WPU                  WPUAbits.WPUA4
#define ANA3_OD                   ODCONAbits.ODCA4
#define ANA3_ANS                  ANSELAbits.ANSELA4
#define ANA3_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define ANA3_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define ANA3_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define ANA3_GetValue()           PORTAbits.RA4
#define ANA3_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define ANA3_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define ANA3_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define ANA3_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define ANA3_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define ANA3_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define ANA3_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define ANA3_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set ANA4 aliases
#define ANA4_TRIS                 TRISAbits.TRISA5
#define ANA4_LAT                  LATAbits.LATA5
#define ANA4_PORT                 PORTAbits.RA5
#define ANA4_WPU                  WPUAbits.WPUA5
#define ANA4_OD                   ODCONAbits.ODCA5
#define ANA4_ANS                  ANSELAbits.ANSELA5
#define ANA4_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define ANA4_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define ANA4_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define ANA4_GetValue()           PORTAbits.RA5
#define ANA4_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define ANA4_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define ANA4_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define ANA4_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define ANA4_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define ANA4_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define ANA4_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define ANA4_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set IO_RA6 aliases
#define IO_RA6_TRIS                 TRISAbits.TRISA6
#define IO_RA6_LAT                  LATAbits.LATA6
#define IO_RA6_PORT                 PORTAbits.RA6
#define IO_RA6_WPU                  WPUAbits.WPUA6
#define IO_RA6_OD                   ODCONAbits.ODCA6
#define IO_RA6_ANS                  ANSELAbits.ANSELA6
#define IO_RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define IO_RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define IO_RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define IO_RA6_GetValue()           PORTAbits.RA6
#define IO_RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define IO_RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define IO_RA6_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define IO_RA6_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define IO_RA6_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define IO_RA6_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define IO_RA6_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define IO_RA6_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set ANA5 aliases
#define ANA5_TRIS                 TRISAbits.TRISA7
#define ANA5_LAT                  LATAbits.LATA7
#define ANA5_PORT                 PORTAbits.RA7
#define ANA5_WPU                  WPUAbits.WPUA7
#define ANA5_OD                   ODCONAbits.ODCA7
#define ANA5_ANS                  ANSELAbits.ANSELA7
#define ANA5_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define ANA5_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define ANA5_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define ANA5_GetValue()           PORTAbits.RA7
#define ANA5_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define ANA5_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define ANA5_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define ANA5_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define ANA5_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define ANA5_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define ANA5_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define ANA5_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set ANA6 aliases
#define ANA6_TRIS                 TRISBbits.TRISB0
#define ANA6_LAT                  LATBbits.LATB0
#define ANA6_PORT                 PORTBbits.RB0
#define ANA6_WPU                  WPUBbits.WPUB0
#define ANA6_OD                   ODCONBbits.ODCB0
#define ANA6_ANS                  ANSELBbits.ANSELB0
#define ANA6_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define ANA6_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define ANA6_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define ANA6_GetValue()           PORTBbits.RB0
#define ANA6_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define ANA6_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define ANA6_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define ANA6_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define ANA6_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define ANA6_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define ANA6_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define ANA6_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set ANA7 aliases
#define ANA7_TRIS                 TRISBbits.TRISB4
#define ANA7_LAT                  LATBbits.LATB4
#define ANA7_PORT                 PORTBbits.RB4
#define ANA7_WPU                  WPUBbits.WPUB4
#define ANA7_OD                   ODCONBbits.ODCB4
#define ANA7_ANS                  ANSELBbits.ANSELB4
#define ANA7_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define ANA7_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define ANA7_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define ANA7_GetValue()           PORTBbits.RB4
#define ANA7_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define ANA7_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define ANA7_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define ANA7_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define ANA7_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define ANA7_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define ANA7_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define ANA7_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set ANA8 aliases
#define ANA8_TRIS                 TRISBbits.TRISB5
#define ANA8_LAT                  LATBbits.LATB5
#define ANA8_PORT                 PORTBbits.RB5
#define ANA8_WPU                  WPUBbits.WPUB5
#define ANA8_OD                   ODCONBbits.ODCB5
#define ANA8_ANS                  ANSELBbits.ANSELB5
#define ANA8_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define ANA8_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define ANA8_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define ANA8_GetValue()           PORTBbits.RB5
#define ANA8_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define ANA8_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define ANA8_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define ANA8_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define ANA8_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define ANA8_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define ANA8_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define ANA8_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set ANA9 aliases
#define ANA9_TRIS                 TRISBbits.TRISB6
#define ANA9_LAT                  LATBbits.LATB6
#define ANA9_PORT                 PORTBbits.RB6
#define ANA9_WPU                  WPUBbits.WPUB6
#define ANA9_OD                   ODCONBbits.ODCB6
#define ANA9_ANS                  ANSELBbits.ANSELB6
#define ANA9_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define ANA9_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define ANA9_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define ANA9_GetValue()           PORTBbits.RB6
#define ANA9_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define ANA9_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define ANA9_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define ANA9_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define ANA9_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define ANA9_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define ANA9_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define ANA9_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set ANA10 aliases
#define ANA10_TRIS                 TRISBbits.TRISB7
#define ANA10_LAT                  LATBbits.LATB7
#define ANA10_PORT                 PORTBbits.RB7
#define ANA10_WPU                  WPUBbits.WPUB7
#define ANA10_OD                   ODCONBbits.ODCB7
#define ANA10_ANS                  ANSELBbits.ANSELB7
#define ANA10_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define ANA10_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define ANA10_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define ANA10_GetValue()           PORTBbits.RB7
#define ANA10_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define ANA10_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define ANA10_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define ANA10_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define ANA10_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define ANA10_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define ANA10_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define ANA10_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set ANA11 aliases
#define ANA11_TRIS                 TRISCbits.TRISC0
#define ANA11_LAT                  LATCbits.LATC0
#define ANA11_PORT                 PORTCbits.RC0
#define ANA11_WPU                  WPUCbits.WPUC0
#define ANA11_OD                   ODCONCbits.ODCC0
#define ANA11_ANS                  ANSELCbits.ANSELC0
#define ANA11_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define ANA11_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define ANA11_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define ANA11_GetValue()           PORTCbits.RC0
#define ANA11_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define ANA11_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define ANA11_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define ANA11_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define ANA11_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define ANA11_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define ANA11_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define ANA11_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set ANA12 aliases
#define ANA12_TRIS                 TRISCbits.TRISC1
#define ANA12_LAT                  LATCbits.LATC1
#define ANA12_PORT                 PORTCbits.RC1
#define ANA12_WPU                  WPUCbits.WPUC1
#define ANA12_OD                   ODCONCbits.ODCC1
#define ANA12_ANS                  ANSELCbits.ANSELC1
#define ANA12_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define ANA12_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define ANA12_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define ANA12_GetValue()           PORTCbits.RC1
#define ANA12_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define ANA12_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define ANA12_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define ANA12_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define ANA12_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define ANA12_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define ANA12_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define ANA12_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set ANA13 aliases
#define ANA13_TRIS                 TRISCbits.TRISC2
#define ANA13_LAT                  LATCbits.LATC2
#define ANA13_PORT                 PORTCbits.RC2
#define ANA13_WPU                  WPUCbits.WPUC2
#define ANA13_OD                   ODCONCbits.ODCC2
#define ANA13_ANS                  ANSELCbits.ANSELC2
#define ANA13_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ANA13_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ANA13_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ANA13_GetValue()           PORTCbits.RC2
#define ANA13_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ANA13_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ANA13_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ANA13_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ANA13_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ANA13_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ANA13_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define ANA13_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set ANA14 aliases
#define ANA14_TRIS                 TRISCbits.TRISC6
#define ANA14_LAT                  LATCbits.LATC6
#define ANA14_PORT                 PORTCbits.RC6
#define ANA14_WPU                  WPUCbits.WPUC6
#define ANA14_OD                   ODCONCbits.ODCC6
#define ANA14_ANS                  ANSELCbits.ANSELC6
#define ANA14_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define ANA14_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define ANA14_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define ANA14_GetValue()           PORTCbits.RC6
#define ANA14_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define ANA14_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define ANA14_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define ANA14_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define ANA14_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define ANA14_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define ANA14_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define ANA14_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set ANA15 aliases
#define ANA15_TRIS                 TRISCbits.TRISC7
#define ANA15_LAT                  LATCbits.LATC7
#define ANA15_PORT                 PORTCbits.RC7
#define ANA15_WPU                  WPUCbits.WPUC7
#define ANA15_OD                   ODCONCbits.ODCC7
#define ANA15_ANS                  ANSELCbits.ANSELC7
#define ANA15_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define ANA15_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define ANA15_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define ANA15_GetValue()           PORTCbits.RC7
#define ANA15_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define ANA15_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define ANA15_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define ANA15_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define ANA15_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define ANA15_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define ANA15_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define ANA15_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

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