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
        Device            :  PIC18F47Q43
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

// get/set AN0 aliases
#define AN0_TRIS                 TRISAbits.TRISA0
#define AN0_LAT                  LATAbits.LATA0
#define AN0_PORT                 PORTAbits.RA0
#define AN0_WPU                  WPUAbits.WPUA0
#define AN0_OD                   ODCONAbits.ODCA0
#define AN0_ANS                  ANSELAbits.ANSELA0
#define AN0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define AN0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define AN0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define AN0_GetValue()           PORTAbits.RA0
#define AN0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define AN0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define AN0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define AN0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define AN0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define AN0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define AN0_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define AN0_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set AN1 aliases
#define AN1_TRIS                 TRISAbits.TRISA1
#define AN1_LAT                  LATAbits.LATA1
#define AN1_PORT                 PORTAbits.RA1
#define AN1_WPU                  WPUAbits.WPUA1
#define AN1_OD                   ODCONAbits.ODCA1
#define AN1_ANS                  ANSELAbits.ANSELA1
#define AN1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define AN1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define AN1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define AN1_GetValue()           PORTAbits.RA1
#define AN1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define AN1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define AN1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define AN1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define AN1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define AN1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define AN1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define AN1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set AN2 aliases
#define AN2_TRIS                 TRISAbits.TRISA2
#define AN2_LAT                  LATAbits.LATA2
#define AN2_PORT                 PORTAbits.RA2
#define AN2_WPU                  WPUAbits.WPUA2
#define AN2_OD                   ODCONAbits.ODCA2
#define AN2_ANS                  ANSELAbits.ANSELA2
#define AN2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define AN2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define AN2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define AN2_GetValue()           PORTAbits.RA2
#define AN2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define AN2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define AN2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define AN2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define AN2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define AN2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define AN2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define AN2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set AN3 aliases
#define AN3_TRIS                 TRISAbits.TRISA3
#define AN3_LAT                  LATAbits.LATA3
#define AN3_PORT                 PORTAbits.RA3
#define AN3_WPU                  WPUAbits.WPUA3
#define AN3_OD                   ODCONAbits.ODCA3
#define AN3_ANS                  ANSELAbits.ANSELA3
#define AN3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define AN3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define AN3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define AN3_GetValue()           PORTAbits.RA3
#define AN3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define AN3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define AN3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define AN3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define AN3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define AN3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define AN3_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define AN3_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set AN4 aliases
#define AN4_TRIS                 TRISAbits.TRISA4
#define AN4_LAT                  LATAbits.LATA4
#define AN4_PORT                 PORTAbits.RA4
#define AN4_WPU                  WPUAbits.WPUA4
#define AN4_OD                   ODCONAbits.ODCA4
#define AN4_ANS                  ANSELAbits.ANSELA4
#define AN4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define AN4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define AN4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define AN4_GetValue()           PORTAbits.RA4
#define AN4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define AN4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define AN4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define AN4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define AN4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define AN4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define AN4_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define AN4_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set AN5 aliases
#define AN5_TRIS                 TRISAbits.TRISA5
#define AN5_LAT                  LATAbits.LATA5
#define AN5_PORT                 PORTAbits.RA5
#define AN5_WPU                  WPUAbits.WPUA5
#define AN5_OD                   ODCONAbits.ODCA5
#define AN5_ANS                  ANSELAbits.ANSELA5
#define AN5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define AN5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define AN5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define AN5_GetValue()           PORTAbits.RA5
#define AN5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define AN5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define AN5_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define AN5_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define AN5_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define AN5_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define AN5_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define AN5_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set AN6 aliases
#define AN6_TRIS                 TRISAbits.TRISA6
#define AN6_LAT                  LATAbits.LATA6
#define AN6_PORT                 PORTAbits.RA6
#define AN6_WPU                  WPUAbits.WPUA6
#define AN6_OD                   ODCONAbits.ODCA6
#define AN6_ANS                  ANSELAbits.ANSELA6
#define AN6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define AN6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define AN6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define AN6_GetValue()           PORTAbits.RA6
#define AN6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define AN6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define AN6_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define AN6_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define AN6_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define AN6_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define AN6_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define AN6_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set AN7 aliases
#define AN7_TRIS                 TRISAbits.TRISA7
#define AN7_LAT                  LATAbits.LATA7
#define AN7_PORT                 PORTAbits.RA7
#define AN7_WPU                  WPUAbits.WPUA7
#define AN7_OD                   ODCONAbits.ODCA7
#define AN7_ANS                  ANSELAbits.ANSELA7
#define AN7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define AN7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define AN7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define AN7_GetValue()           PORTAbits.RA7
#define AN7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define AN7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define AN7_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define AN7_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define AN7_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define AN7_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define AN7_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define AN7_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set PIC_SPI_CS aliases
#define PIC_SPI_CS_TRIS                 TRISBbits.TRISB0
#define PIC_SPI_CS_LAT                  LATBbits.LATB0
#define PIC_SPI_CS_PORT                 PORTBbits.RB0
#define PIC_SPI_CS_WPU                  WPUBbits.WPUB0
#define PIC_SPI_CS_OD                   ODCONBbits.ODCB0
#define PIC_SPI_CS_ANS                  ANSELBbits.ANSELB0
#define PIC_SPI_CS_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define PIC_SPI_CS_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define PIC_SPI_CS_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define PIC_SPI_CS_GetValue()           PORTBbits.RB0
#define PIC_SPI_CS_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define PIC_SPI_CS_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define PIC_SPI_CS_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define PIC_SPI_CS_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define PIC_SPI_CS_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define PIC_SPI_CS_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define PIC_SPI_CS_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define PIC_SPI_CS_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set PIC_SPI_SCK aliases
#define PIC_SPI_SCK_TRIS                 TRISBbits.TRISB1
#define PIC_SPI_SCK_LAT                  LATBbits.LATB1
#define PIC_SPI_SCK_PORT                 PORTBbits.RB1
#define PIC_SPI_SCK_WPU                  WPUBbits.WPUB1
#define PIC_SPI_SCK_OD                   ODCONBbits.ODCB1
#define PIC_SPI_SCK_ANS                  ANSELBbits.ANSELB1
#define PIC_SPI_SCK_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define PIC_SPI_SCK_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define PIC_SPI_SCK_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define PIC_SPI_SCK_GetValue()           PORTBbits.RB1
#define PIC_SPI_SCK_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define PIC_SPI_SCK_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define PIC_SPI_SCK_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define PIC_SPI_SCK_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define PIC_SPI_SCK_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define PIC_SPI_SCK_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define PIC_SPI_SCK_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define PIC_SPI_SCK_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set PIC_SPI_MOSI aliases
#define PIC_SPI_MOSI_TRIS                 TRISBbits.TRISB2
#define PIC_SPI_MOSI_LAT                  LATBbits.LATB2
#define PIC_SPI_MOSI_PORT                 PORTBbits.RB2
#define PIC_SPI_MOSI_WPU                  WPUBbits.WPUB2
#define PIC_SPI_MOSI_OD                   ODCONBbits.ODCB2
#define PIC_SPI_MOSI_ANS                  ANSELBbits.ANSELB2
#define PIC_SPI_MOSI_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define PIC_SPI_MOSI_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define PIC_SPI_MOSI_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define PIC_SPI_MOSI_GetValue()           PORTBbits.RB2
#define PIC_SPI_MOSI_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define PIC_SPI_MOSI_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define PIC_SPI_MOSI_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define PIC_SPI_MOSI_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define PIC_SPI_MOSI_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define PIC_SPI_MOSI_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define PIC_SPI_MOSI_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define PIC_SPI_MOSI_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set PIC_SPI_MISO aliases
#define PIC_SPI_MISO_TRIS                 TRISBbits.TRISB3
#define PIC_SPI_MISO_LAT                  LATBbits.LATB3
#define PIC_SPI_MISO_PORT                 PORTBbits.RB3
#define PIC_SPI_MISO_WPU                  WPUBbits.WPUB3
#define PIC_SPI_MISO_OD                   ODCONBbits.ODCB3
#define PIC_SPI_MISO_ANS                  ANSELBbits.ANSELB3
#define PIC_SPI_MISO_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define PIC_SPI_MISO_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define PIC_SPI_MISO_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define PIC_SPI_MISO_GetValue()           PORTBbits.RB3
#define PIC_SPI_MISO_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define PIC_SPI_MISO_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define PIC_SPI_MISO_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define PIC_SPI_MISO_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define PIC_SPI_MISO_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define PIC_SPI_MISO_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define PIC_SPI_MISO_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define PIC_SPI_MISO_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set AN8 aliases
#define AN8_TRIS                 TRISCbits.TRISC0
#define AN8_LAT                  LATCbits.LATC0
#define AN8_PORT                 PORTCbits.RC0
#define AN8_WPU                  WPUCbits.WPUC0
#define AN8_OD                   ODCONCbits.ODCC0
#define AN8_ANS                  ANSELCbits.ANSELC0
#define AN8_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define AN8_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define AN8_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define AN8_GetValue()           PORTCbits.RC0
#define AN8_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define AN8_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define AN8_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define AN8_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define AN8_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define AN8_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define AN8_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define AN8_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set AN9 aliases
#define AN9_TRIS                 TRISCbits.TRISC1
#define AN9_LAT                  LATCbits.LATC1
#define AN9_PORT                 PORTCbits.RC1
#define AN9_WPU                  WPUCbits.WPUC1
#define AN9_OD                   ODCONCbits.ODCC1
#define AN9_ANS                  ANSELCbits.ANSELC1
#define AN9_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define AN9_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define AN9_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define AN9_GetValue()           PORTCbits.RC1
#define AN9_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define AN9_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define AN9_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define AN9_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define AN9_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define AN9_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define AN9_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define AN9_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set AN10 aliases
#define AN10_TRIS                 TRISCbits.TRISC2
#define AN10_LAT                  LATCbits.LATC2
#define AN10_PORT                 PORTCbits.RC2
#define AN10_WPU                  WPUCbits.WPUC2
#define AN10_OD                   ODCONCbits.ODCC2
#define AN10_ANS                  ANSELCbits.ANSELC2
#define AN10_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define AN10_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define AN10_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define AN10_GetValue()           PORTCbits.RC2
#define AN10_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define AN10_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define AN10_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define AN10_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define AN10_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define AN10_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define AN10_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define AN10_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set AN11 aliases
#define AN11_TRIS                 TRISCbits.TRISC3
#define AN11_LAT                  LATCbits.LATC3
#define AN11_PORT                 PORTCbits.RC3
#define AN11_WPU                  WPUCbits.WPUC3
#define AN11_OD                   ODCONCbits.ODCC3
#define AN11_ANS                  ANSELCbits.ANSELC3
#define AN11_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define AN11_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define AN11_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define AN11_GetValue()           PORTCbits.RC3
#define AN11_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define AN11_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define AN11_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define AN11_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define AN11_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define AN11_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define AN11_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define AN11_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set Control_SPI_CS aliases
#define Control_SPI_CS_TRIS                 TRISCbits.TRISC4
#define Control_SPI_CS_LAT                  LATCbits.LATC4
#define Control_SPI_CS_PORT                 PORTCbits.RC4
#define Control_SPI_CS_WPU                  WPUCbits.WPUC4
#define Control_SPI_CS_OD                   ODCONCbits.ODCC4
#define Control_SPI_CS_ANS                  ANSELCbits.ANSELC4
#define Control_SPI_CS_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define Control_SPI_CS_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define Control_SPI_CS_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define Control_SPI_CS_GetValue()           PORTCbits.RC4
#define Control_SPI_CS_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define Control_SPI_CS_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define Control_SPI_CS_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define Control_SPI_CS_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define Control_SPI_CS_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define Control_SPI_CS_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define Control_SPI_CS_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define Control_SPI_CS_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set SPIMISO aliases
#define SPIMISO_TRIS                 TRISCbits.TRISC5
#define SPIMISO_LAT                  LATCbits.LATC5
#define SPIMISO_PORT                 PORTCbits.RC5
#define SPIMISO_WPU                  WPUCbits.WPUC5
#define SPIMISO_OD                   ODCONCbits.ODCC5
#define SPIMISO_ANS                  ANSELCbits.ANSELC5
#define SPIMISO_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SPIMISO_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SPIMISO_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SPIMISO_GetValue()           PORTCbits.RC5
#define SPIMISO_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SPIMISO_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SPIMISO_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define SPIMISO_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define SPIMISO_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define SPIMISO_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define SPIMISO_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define SPIMISO_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set SPIMOSI aliases
#define SPIMOSI_TRIS                 TRISCbits.TRISC6
#define SPIMOSI_LAT                  LATCbits.LATC6
#define SPIMOSI_PORT                 PORTCbits.RC6
#define SPIMOSI_WPU                  WPUCbits.WPUC6
#define SPIMOSI_OD                   ODCONCbits.ODCC6
#define SPIMOSI_ANS                  ANSELCbits.ANSELC6
#define SPIMOSI_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SPIMOSI_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SPIMOSI_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SPIMOSI_GetValue()           PORTCbits.RC6
#define SPIMOSI_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SPIMOSI_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SPIMOSI_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define SPIMOSI_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define SPIMOSI_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define SPIMOSI_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define SPIMOSI_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define SPIMOSI_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set SPICLK aliases
#define SPICLK_TRIS                 TRISCbits.TRISC7
#define SPICLK_LAT                  LATCbits.LATC7
#define SPICLK_PORT                 PORTCbits.RC7
#define SPICLK_WPU                  WPUCbits.WPUC7
#define SPICLK_OD                   ODCONCbits.ODCC7
#define SPICLK_ANS                  ANSELCbits.ANSELC7
#define SPICLK_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define SPICLK_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define SPICLK_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define SPICLK_GetValue()           PORTCbits.RC7
#define SPICLK_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define SPICLK_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define SPICLK_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define SPICLK_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define SPICLK_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define SPICLK_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define SPICLK_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define SPICLK_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set AN12 aliases
#define AN12_TRIS                 TRISDbits.TRISD0
#define AN12_LAT                  LATDbits.LATD0
#define AN12_PORT                 PORTDbits.RD0
#define AN12_WPU                  WPUDbits.WPUD0
#define AN12_OD                   ODCONDbits.ODCD0
#define AN12_ANS                  ANSELDbits.ANSELD0
#define AN12_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define AN12_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define AN12_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define AN12_GetValue()           PORTDbits.RD0
#define AN12_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define AN12_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define AN12_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define AN12_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define AN12_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define AN12_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define AN12_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define AN12_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set OUTNGATE aliases
#define OUTNGATE_TRIS                 TRISDbits.TRISD1
#define OUTNGATE_LAT                  LATDbits.LATD1
#define OUTNGATE_PORT                 PORTDbits.RD1
#define OUTNGATE_WPU                  WPUDbits.WPUD1
#define OUTNGATE_OD                   ODCONDbits.ODCD1
#define OUTNGATE_ANS                  ANSELDbits.ANSELD1
#define OUTNGATE_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define OUTNGATE_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define OUTNGATE_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define OUTNGATE_GetValue()           PORTDbits.RD1
#define OUTNGATE_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define OUTNGATE_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define OUTNGATE_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define OUTNGATE_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define OUTNGATE_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define OUTNGATE_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define OUTNGATE_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define OUTNGATE_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set MISOEnable aliases
#define MISOEnable_TRIS                 TRISDbits.TRISD2
#define MISOEnable_LAT                  LATDbits.LATD2
#define MISOEnable_PORT                 PORTDbits.RD2
#define MISOEnable_WPU                  WPUDbits.WPUD2
#define MISOEnable_OD                   ODCONDbits.ODCD2
#define MISOEnable_ANS                  ANSELDbits.ANSELD2
#define MISOEnable_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define MISOEnable_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define MISOEnable_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define MISOEnable_GetValue()           PORTDbits.RD2
#define MISOEnable_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define MISOEnable_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define MISOEnable_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define MISOEnable_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define MISOEnable_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define MISOEnable_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define MISOEnable_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define MISOEnable_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set TestOut aliases
#define TestOut_TRIS                 TRISDbits.TRISD3
#define TestOut_LAT                  LATDbits.LATD3
#define TestOut_PORT                 PORTDbits.RD3
#define TestOut_WPU                  WPUDbits.WPUD3
#define TestOut_OD                   ODCONDbits.ODCD3
#define TestOut_ANS                  ANSELDbits.ANSELD3
#define TestOut_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define TestOut_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define TestOut_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define TestOut_GetValue()           PORTDbits.RD3
#define TestOut_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define TestOut_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define TestOut_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define TestOut_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define TestOut_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define TestOut_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define TestOut_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define TestOut_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set IO_RD4 aliases
#define IO_RD4_TRIS                 TRISDbits.TRISD4
#define IO_RD4_LAT                  LATDbits.LATD4
#define IO_RD4_PORT                 PORTDbits.RD4
#define IO_RD4_WPU                  WPUDbits.WPUD4
#define IO_RD4_OD                   ODCONDbits.ODCD4
#define IO_RD4_ANS                  ANSELDbits.ANSELD4
#define IO_RD4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define IO_RD4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define IO_RD4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define IO_RD4_GetValue()           PORTDbits.RD4
#define IO_RD4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define IO_RD4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define IO_RD4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define IO_RD4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define IO_RD4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define IO_RD4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define IO_RD4_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define IO_RD4_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set RD5 procedures
#define RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define RD5_GetValue()              PORTDbits.RD5
#define RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define RD5_SetPullup()             do { WPUDbits.WPUD5 = 1; } while(0)
#define RD5_ResetPullup()           do { WPUDbits.WPUD5 = 0; } while(0)
#define RD5_SetAnalogMode()         do { ANSELDbits.ANSELD5 = 1; } while(0)
#define RD5_SetDigitalMode()        do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set RD6 procedures
#define RD6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define RD6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define RD6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define RD6_GetValue()              PORTDbits.RD6
#define RD6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define RD6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define RD6_SetPullup()             do { WPUDbits.WPUD6 = 1; } while(0)
#define RD6_ResetPullup()           do { WPUDbits.WPUD6 = 0; } while(0)
#define RD6_SetAnalogMode()         do { ANSELDbits.ANSELD6 = 1; } while(0)
#define RD6_SetDigitalMode()        do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set RD7 procedures
#define RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define RD7_GetValue()              PORTDbits.RD7
#define RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define RD7_SetPullup()             do { WPUDbits.WPUD7 = 1; } while(0)
#define RD7_ResetPullup()           do { WPUDbits.WPUD7 = 0; } while(0)
#define RD7_SetAnalogMode()         do { ANSELDbits.ANSELD7 = 1; } while(0)
#define RD7_SetDigitalMode()        do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set AN13 aliases
#define AN13_TRIS                 TRISEbits.TRISE0
#define AN13_LAT                  LATEbits.LATE0
#define AN13_PORT                 PORTEbits.RE0
#define AN13_WPU                  WPUEbits.WPUE0
#define AN13_OD                   ODCONEbits.ODCE0
#define AN13_ANS                  ANSELEbits.ANSELE0
#define AN13_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define AN13_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define AN13_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define AN13_GetValue()           PORTEbits.RE0
#define AN13_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define AN13_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define AN13_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define AN13_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define AN13_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define AN13_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define AN13_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define AN13_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set AN14 aliases
#define AN14_TRIS                 TRISEbits.TRISE1
#define AN14_LAT                  LATEbits.LATE1
#define AN14_PORT                 PORTEbits.RE1
#define AN14_WPU                  WPUEbits.WPUE1
#define AN14_OD                   ODCONEbits.ODCE1
#define AN14_ANS                  ANSELEbits.ANSELE1
#define AN14_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define AN14_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define AN14_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define AN14_GetValue()           PORTEbits.RE1
#define AN14_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define AN14_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define AN14_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define AN14_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define AN14_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define AN14_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define AN14_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define AN14_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set AN15 aliases
#define AN15_TRIS                 TRISEbits.TRISE2
#define AN15_LAT                  LATEbits.LATE2
#define AN15_PORT                 PORTEbits.RE2
#define AN15_WPU                  WPUEbits.WPUE2
#define AN15_OD                   ODCONEbits.ODCE2
#define AN15_ANS                  ANSELEbits.ANSELE2
#define AN15_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define AN15_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define AN15_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define AN15_GetValue()           PORTEbits.RE2
#define AN15_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define AN15_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define AN15_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define AN15_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define AN15_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define AN15_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define AN15_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define AN15_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

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