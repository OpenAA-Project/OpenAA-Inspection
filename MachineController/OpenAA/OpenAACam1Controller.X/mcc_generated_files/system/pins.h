/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
*/

/*
? [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define GIN1_TRIS                 TRISAbits.TRISA0
#define GIN1_LAT                  LATAbits.LATA0
#define GIN1_PORT                 PORTAbits.RA0
#define GIN1_WPU                  WPUAbits.WPUA0
#define GIN1_OD                   ODCONAbits.ODCA0
#define GIN1_ANS                  ANSELAbits.ANSELA0
#define GIN1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define GIN1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define GIN1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define GIN1_GetValue()           PORTAbits.RA0
#define GIN1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define GIN1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define GIN1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define GIN1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define GIN1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define GIN1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define GIN1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define GIN1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA1 aliases
#define GIN2_TRIS                 TRISAbits.TRISA1
#define GIN2_LAT                  LATAbits.LATA1
#define GIN2_PORT                 PORTAbits.RA1
#define GIN2_WPU                  WPUAbits.WPUA1
#define GIN2_OD                   ODCONAbits.ODCA1
#define GIN2_ANS                  ANSELAbits.ANSELA1
#define GIN2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define GIN2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define GIN2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define GIN2_GetValue()           PORTAbits.RA1
#define GIN2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define GIN2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define GIN2_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define GIN2_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define GIN2_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define GIN2_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define GIN2_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define GIN2_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA2 aliases
#define GIN3_TRIS                 TRISAbits.TRISA2
#define GIN3_LAT                  LATAbits.LATA2
#define GIN3_PORT                 PORTAbits.RA2
#define GIN3_WPU                  WPUAbits.WPUA2
#define GIN3_OD                   ODCONAbits.ODCA2
#define GIN3_ANS                  ANSELAbits.ANSELA2
#define GIN3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define GIN3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define GIN3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define GIN3_GetValue()           PORTAbits.RA2
#define GIN3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define GIN3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define GIN3_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define GIN3_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define GIN3_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define GIN3_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define GIN3_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define GIN3_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 aliases
#define GIN4_TRIS                 TRISAbits.TRISA3
#define GIN4_LAT                  LATAbits.LATA3
#define GIN4_PORT                 PORTAbits.RA3
#define GIN4_WPU                  WPUAbits.WPUA3
#define GIN4_OD                   ODCONAbits.ODCA3
#define GIN4_ANS                  ANSELAbits.ANSELA3
#define GIN4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define GIN4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define GIN4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define GIN4_GetValue()           PORTAbits.RA3
#define GIN4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define GIN4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define GIN4_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define GIN4_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define GIN4_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define GIN4_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define GIN4_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define GIN4_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RB0 aliases
#define CAMOUT_TRIS                 TRISBbits.TRISB0
#define CAMOUT_LAT                  LATBbits.LATB0
#define CAMOUT_PORT                 PORTBbits.RB0
#define CAMOUT_WPU                  WPUBbits.WPUB0
#define CAMOUT_OD                   ODCONBbits.ODCB0
#define CAMOUT_ANS                  ANSELBbits.ANSELB0
#define CAMOUT_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define CAMOUT_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define CAMOUT_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define CAMOUT_GetValue()           PORTBbits.RB0
#define CAMOUT_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define CAMOUT_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define CAMOUT_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define CAMOUT_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define CAMOUT_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define CAMOUT_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define CAMOUT_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define CAMOUT_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB4 aliases
#define CAMIN_TRIS                 TRISBbits.TRISB4
#define CAMIN_LAT                  LATBbits.LATB4
#define CAMIN_PORT                 PORTBbits.RB4
#define CAMIN_WPU                  WPUBbits.WPUB4
#define CAMIN_OD                   ODCONBbits.ODCB4
#define CAMIN_ANS                  ANSELBbits.ANSELB4
#define CAMIN_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define CAMIN_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define CAMIN_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define CAMIN_GetValue()           PORTBbits.RB4
#define CAMIN_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define CAMIN_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define CAMIN_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define CAMIN_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define CAMIN_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define CAMIN_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define CAMIN_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define CAMIN_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RC0 aliases
#define GOUT1_TRIS                 TRISCbits.TRISC0
#define GOUT1_LAT                  LATCbits.LATC0
#define GOUT1_PORT                 PORTCbits.RC0
#define GOUT1_WPU                  WPUCbits.WPUC0
#define GOUT1_OD                   ODCONCbits.ODCC0
#define GOUT1_ANS                  ANSELCbits.ANSELC0
#define GOUT1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define GOUT1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define GOUT1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define GOUT1_GetValue()           PORTCbits.RC0
#define GOUT1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define GOUT1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define GOUT1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define GOUT1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define GOUT1_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define GOUT1_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define GOUT1_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define GOUT1_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 aliases
#define GOUT2_TRIS                 TRISCbits.TRISC1
#define GOUT2_LAT                  LATCbits.LATC1
#define GOUT2_PORT                 PORTCbits.RC1
#define GOUT2_WPU                  WPUCbits.WPUC1
#define GOUT2_OD                   ODCONCbits.ODCC1
#define GOUT2_ANS                  ANSELCbits.ANSELC1
#define GOUT2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define GOUT2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define GOUT2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define GOUT2_GetValue()           PORTCbits.RC1
#define GOUT2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define GOUT2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define GOUT2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define GOUT2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define GOUT2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define GOUT2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define GOUT2_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define GOUT2_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 aliases
#define GOUT3_TRIS                 TRISCbits.TRISC2
#define GOUT3_LAT                  LATCbits.LATC2
#define GOUT3_PORT                 PORTCbits.RC2
#define GOUT3_WPU                  WPUCbits.WPUC2
#define GOUT3_OD                   ODCONCbits.ODCC2
#define GOUT3_ANS                  ANSELCbits.ANSELC2
#define GOUT3_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define GOUT3_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define GOUT3_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define GOUT3_GetValue()           PORTCbits.RC2
#define GOUT3_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define GOUT3_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define GOUT3_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define GOUT3_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define GOUT3_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define GOUT3_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define GOUT3_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define GOUT3_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 aliases
#define GOUT4_TRIS                 TRISCbits.TRISC3
#define GOUT4_LAT                  LATCbits.LATC3
#define GOUT4_PORT                 PORTCbits.RC3
#define GOUT4_WPU                  WPUCbits.WPUC3
#define GOUT4_OD                   ODCONCbits.ODCC3
#define GOUT4_ANS                  ANSELCbits.ANSELC3
#define GOUT4_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define GOUT4_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define GOUT4_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define GOUT4_GetValue()           PORTCbits.RC3
#define GOUT4_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define GOUT4_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define GOUT4_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define GOUT4_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define GOUT4_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define GOUT4_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define GOUT4_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define GOUT4_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RD0 aliases
#define IO_RD0_TRIS                 TRISDbits.TRISD0
#define IO_RD0_LAT                  LATDbits.LATD0
#define IO_RD0_PORT                 PORTDbits.RD0
#define IO_RD0_WPU                  WPUDbits.WPUD0
#define IO_RD0_OD                   ODCONDbits.ODCD0
#define IO_RD0_ANS                  ANSELDbits.ANSELD0
#define IO_RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define IO_RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define IO_RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define IO_RD0_GetValue()           PORTDbits.RD0
#define IO_RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define IO_RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define IO_RD0_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define IO_RD0_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define IO_RD0_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define IO_RD0_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define IO_RD0_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define IO_RD0_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set RD1 aliases
#define IO_RD1_TRIS                 TRISDbits.TRISD1
#define IO_RD1_LAT                  LATDbits.LATD1
#define IO_RD1_PORT                 PORTDbits.RD1
#define IO_RD1_WPU                  WPUDbits.WPUD1
#define IO_RD1_OD                   ODCONDbits.ODCD1
#define IO_RD1_ANS                  ANSELDbits.ANSELD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define IO_RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define IO_RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define IO_RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define IO_RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define IO_RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define IO_RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RD2 aliases
#define IO_RD2_TRIS                 TRISDbits.TRISD2
#define IO_RD2_LAT                  LATDbits.LATD2
#define IO_RD2_PORT                 PORTDbits.RD2
#define IO_RD2_WPU                  WPUDbits.WPUD2
#define IO_RD2_OD                   ODCONDbits.ODCD2
#define IO_RD2_ANS                  ANSELDbits.ANSELD2
#define IO_RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define IO_RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define IO_RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define IO_RD2_GetValue()           PORTDbits.RD2
#define IO_RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define IO_RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define IO_RD2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define IO_RD2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define IO_RD2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define IO_RD2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define IO_RD2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define IO_RD2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RD3 aliases
#define Control_SPI_CS_TRIS                 TRISDbits.TRISD3
#define Control_SPI_CS_LAT                  LATDbits.LATD3
#define Control_SPI_CS_PORT                 PORTDbits.RD3
#define Control_SPI_CS_WPU                  WPUDbits.WPUD3
#define Control_SPI_CS_OD                   ODCONDbits.ODCD3
#define Control_SPI_CS_ANS                  ANSELDbits.ANSELD3
#define Control_SPI_CS_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define Control_SPI_CS_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define Control_SPI_CS_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define Control_SPI_CS_GetValue()           PORTDbits.RD3
#define Control_SPI_CS_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define Control_SPI_CS_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define Control_SPI_CS_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define Control_SPI_CS_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define Control_SPI_CS_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define Control_SPI_CS_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define Control_SPI_CS_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define Control_SPI_CS_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set RF0 aliases
#define PIC_MISO_TRIS                 TRISFbits.TRISF0
#define PIC_MISO_LAT                  LATFbits.LATF0
#define PIC_MISO_PORT                 PORTFbits.RF0
#define PIC_MISO_WPU                  WPUFbits.WPUF0
#define PIC_MISO_OD                   ODCONFbits.ODCF0
#define PIC_MISO_ANS                  ANSELFbits.ANSELF0
#define PIC_MISO_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define PIC_MISO_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define PIC_MISO_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define PIC_MISO_GetValue()           PORTFbits.RF0
#define PIC_MISO_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define PIC_MISO_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define PIC_MISO_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define PIC_MISO_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define PIC_MISO_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define PIC_MISO_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define PIC_MISO_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define PIC_MISO_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define PIC_MOSI_TRIS                 TRISFbits.TRISF1
#define PIC_MOSI_LAT                  LATFbits.LATF1
#define PIC_MOSI_PORT                 PORTFbits.RF1
#define PIC_MOSI_WPU                  WPUFbits.WPUF1
#define PIC_MOSI_OD                   ODCONFbits.ODCF1
#define PIC_MOSI_ANS                  ANSELFbits.ANSELF1
#define PIC_MOSI_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define PIC_MOSI_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define PIC_MOSI_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define PIC_MOSI_GetValue()           PORTFbits.RF1
#define PIC_MOSI_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define PIC_MOSI_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define PIC_MOSI_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define PIC_MOSI_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define PIC_MOSI_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define PIC_MOSI_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define PIC_MOSI_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define PIC_MOSI_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

// get/set RF2 aliases
#define PIC_SCLK_TRIS                 TRISFbits.TRISF2
#define PIC_SCLK_LAT                  LATFbits.LATF2
#define PIC_SCLK_PORT                 PORTFbits.RF2
#define PIC_SCLK_WPU                  WPUFbits.WPUF2
#define PIC_SCLK_OD                   ODCONFbits.ODCF2
#define PIC_SCLK_ANS                  ANSELFbits.ANSELF2
#define PIC_SCLK_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define PIC_SCLK_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define PIC_SCLK_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define PIC_SCLK_GetValue()           PORTFbits.RF2
#define PIC_SCLK_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define PIC_SCLK_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define PIC_SCLK_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define PIC_SCLK_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define PIC_SCLK_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define PIC_SCLK_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define PIC_SCLK_SetAnalogMode()      do { ANSELFbits.ANSELF2 = 1; } while(0)
#define PIC_SCLK_SetDigitalMode()     do { ANSELFbits.ANSELF2 = 0; } while(0)

// get/set RF3 aliases
#define PIC_CS_TRIS                 TRISFbits.TRISF3
#define PIC_CS_LAT                  LATFbits.LATF3
#define PIC_CS_PORT                 PORTFbits.RF3
#define PIC_CS_WPU                  WPUFbits.WPUF3
#define PIC_CS_OD                   ODCONFbits.ODCF3
#define PIC_CS_ANS                  ANSELFbits.ANSELF3
#define PIC_CS_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define PIC_CS_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define PIC_CS_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define PIC_CS_GetValue()           PORTFbits.RF3
#define PIC_CS_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define PIC_CS_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define PIC_CS_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define PIC_CS_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define PIC_CS_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define PIC_CS_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define PIC_CS_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define PIC_CS_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

// get/set RF6 aliases
#define PICTESTLED_TRIS                 TRISFbits.TRISF6
#define PICTESTLED_LAT                  LATFbits.LATF6
#define PICTESTLED_PORT                 PORTFbits.RF6
#define PICTESTLED_WPU                  WPUFbits.WPUF6
#define PICTESTLED_OD                   ODCONFbits.ODCF6
#define PICTESTLED_ANS                  ANSELFbits.ANSELF6
#define PICTESTLED_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define PICTESTLED_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define PICTESTLED_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define PICTESTLED_GetValue()           PORTFbits.RF6
#define PICTESTLED_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define PICTESTLED_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define PICTESTLED_SetPullup()          do { WPUFbits.WPUF6 = 1; } while(0)
#define PICTESTLED_ResetPullup()        do { WPUFbits.WPUF6 = 0; } while(0)
#define PICTESTLED_SetPushPull()        do { ODCONFbits.ODCF6 = 0; } while(0)
#define PICTESTLED_SetOpenDrain()       do { ODCONFbits.ODCF6 = 1; } while(0)
#define PICTESTLED_SetAnalogMode()      do { ANSELFbits.ANSELF6 = 1; } while(0)
#define PICTESTLED_SetDigitalMode()     do { ANSELFbits.ANSELF6 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/