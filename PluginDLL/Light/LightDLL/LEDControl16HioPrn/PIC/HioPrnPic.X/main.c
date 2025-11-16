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
        Device            :  PIC18F57Q43
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
        
void    FPGA_SetCmd(int Cmd)
{
    if((Cmd&0x01)!=0)
        IO_RF2_SetHigh();
    else
        IO_RF2_SetLow();
    if((Cmd&0x02)!=0)
        IO_RF3_SetHigh();
    else
        IO_RF3_SetLow();
    if((Cmd&0x04)!=0)
        IO_RF4_SetHigh();
    else
        IO_RF4_SetLow();
    if((Cmd&0x08)!=0)
        IO_RF5_SetHigh();
    else
        IO_RF5_SetLow();
}

void    FPGA_CLK(int d)
{
    if((d&0x01)!=0)
        IO_RF6_SetHigh();
    else
        IO_RF6_SetLow();    
}
void    FPGA_CS(int d)
{
    if((d&0x01)!=0)
        IO_RF0_SetHigh();
    else
        IO_RF0_SetLow();    
}
void    FPGA_SetRW(int d)
{
    if((d&0x01)!=0)
        IO_RF1_SetHigh();
    else
        IO_RF1_SetLow();       
}

void    FPGA_SetData(unsigned char d)
{
    if((d&0x01)!=0)
        IO_RC0_SetHigh();
    else
        IO_RC0_SetLow();    
    if((d&0x02)!=0)
        IO_RC1_SetHigh();
    else
        IO_RC1_SetLow();    
    if((d&0x04)!=0)
        IO_RC2_SetHigh();
    else
        IO_RC2_SetLow();    
    if((d&0x08)!=0)
        IO_RC3_SetHigh();
    else
        IO_RC3_SetLow();    
    if((d&0x10)!=0)
        IO_RC4_SetHigh();
    else
        IO_RC4_SetLow();    
    if((d&0x20)!=0)
        IO_RC5_SetHigh();
    else
        IO_RC5_SetLow();    
    if((d&0x40)!=0)
        IO_RA5_SetHigh();
    else
        IO_RA5_SetLow();    
    if((d&0x80)!=0)
        IO_RA6_SetHigh();
    else
        IO_RA6_SetLow();    
}
unsigned char    FPGA_GetData(void)
{
    unsigned char d=0;
    
    d=((IO_RD0_GetValue()!=0)?0x01:0)
     +((IO_RD1_GetValue()!=0)?0x02:0)
     +((IO_RD2_GetValue()!=0)?0x04:0)
     +((IO_RD3_GetValue()!=0)?0x08:0)
     +((IO_RD4_GetValue()!=0)?0x10:0)
     +((IO_RD5_GetValue()!=0)?0x20:0)
     +((IO_RD6_GetValue()!=0)?0x40:0)
     +((IO_RD7_GetValue()!=0)?0x80:0);
            
    return d;
}

void    FPGA_GetBuff(int Cmd ,unsigned char data[] ,int DataLen)
{
    int i;
    
    FPGA_CLK(1);
    FPGA_CLK(0);
    FPGA_SetCmd(Cmd);
    FPGA_SetRW(1);
    FPGA_CS(1);
    for(i=0;i<DataLen;i++){
        FPGA_CLK(1);
        FPGA_CLK(0);
        data[i]=FPGA_GetData();
    }
    FPGA_CS(0);
    FPGA_CLK(1);
    FPGA_CLK(0);
}
void    FPGA_SetBuff(int Cmd ,unsigned char data[] ,int DataLen)
{
    int i;
    
    FPGA_SetCmd(Cmd);
    FPGA_SetRW(0);
    FPGA_CS(1);
    for(i=0;i<DataLen;i++){
        FPGA_SetData(data[i]);
        FPGA_CLK(1);
        FPGA_CLK(0);
    }
    FPGA_CS(0);
    FPGA_CLK(1);
    FPGA_CLK(0);    
}

/*
 RPI  Packet
 
 * 1 Byte   0x1E
 * 1 Byte   Command
 * 1 Byte   Data Byte(N)
 * N Byte   Data
 * 1 Byte   Checksum    all packet data without checksum

 * Command      0x80
 * DipSW    Transmission
 * Data byte    0
 * 

 * Command      0x40+Cmd
 * Transmit to FPGA directly
 * 
 * 
 *  * Command    0x20+Cmd
 * Receivet from FPGA directly
 * Data byte    1
 * Data         Received Data byte

 */

bool    GetRPIPacket(unsigned char *Cmd,unsigned char Data[],int *Len ,int MaxBuffLen)
{
    unsigned char   d;
    unsigned char   Checksum;
    unsigned char   DataLen;
    int             i;
    
    if(UART2_is_rx_ready()==true){
        d=UART2_Read();
        if(d!=0x1E){
            return false;
        }
        Checksum=d;
        
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART2_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=UART2_Read();
        *Cmd=d;
        Checksum^=d;
        
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART2_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        DataLen=UART2_Read();
        Checksum^=DataLen;
        
        for(i=0;i<DataLen && i<MaxBuffLen;i++){
            TMR0_Initialize();
            TMR0_StartTimer();
            for(;;){
                if(UART2_is_rx_ready()==true){
                    break;
                }
                if(TMR0_HasOverflowOccured()==true){
                    return false;
                }
            }
            d=UART2_Read();
            Data[i]=d;
            Checksum^=d;
        }
        
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART2_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=UART2_Read();
        if(Checksum!=d){
            return false;
        }
        *Len=DataLen;
        return true;
    }
    return false;
}
bool    SendRPIPacket(unsigned char Cmd,unsigned char Data[],unsigned char DataLen)
{
    unsigned char   d;
    unsigned char   Checksum;
    int             i;
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART2_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=0x1E;
    UART2_Write(d);
    Checksum=d;

    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART2_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=Cmd;
    UART2_Write(d);
    Checksum^=d;
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART2_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=DataLen;
    UART2_Write(d);
    Checksum^=d;
    
    for(i=0;i<DataLen;i++){
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART2_is_tx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=Data[i];
        UART2_Write(d);
        Checksum^=d;
    }
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART2_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    UART2_Write(Checksum);
    return true;
}
bool    DiliverOtherPacket(unsigned char TargetDipSW,unsigned char Cmd,unsigned char Data[],unsigned char DataLen)
{
    unsigned char   d;
    unsigned char   Checksum;
    int             i;
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART1_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=0x1E;
    UART1_Write(d);
    Checksum=d;

    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART1_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=TargetDipSW;
    UART1_Write(d);
    Checksum^=d;
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART1_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=Cmd;
    UART1_Write(d);
    Checksum^=d;
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART1_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    d=DataLen;
    UART1_Write(d);
    Checksum^=d;
    
    for(i=0;i<DataLen;i++){
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART1_is_tx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=Data[i];
        UART1_Write(d);
        Checksum^=d;
    }
    
    TMR0_Initialize();
    TMR0_StartTimer();
    for(;;){
        if(UART1_is_tx_ready()==true){
            break;
        }
        if(TMR0_HasOverflowOccured()==true){
            return false;
        }
    }
    UART1_Write(Checksum);
    return true;
}

bool    GetFromOtherPacket(unsigned char *TargetDipSW,unsigned char *Cmd
                            ,unsigned char Data[],int *Len ,int MaxBuffLen)
{
    unsigned char   d;
    unsigned char   Checksum;
    unsigned char   DataLen;
    int             i;
    
    if(UART1_is_rx_ready()==true){
        d=UART1_Read();
        if(d!=0x1E){
            return false;
        }
        Checksum=d;
         
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART1_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=UART1_Read();
        *TargetDipSW=d;
        Checksum^=d;
               
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART1_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=UART1_Read();
        *Cmd=d;
        Checksum^=d;
        
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART1_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        DataLen=UART1_Read();
        Checksum^=DataLen;
        
        for(i=0;i<DataLen && i<MaxBuffLen;i++){
            TMR0_Initialize();
            TMR0_StartTimer();
            for(;;){
                if(UART1_is_rx_ready()==true){
                    break;
                }
                if(TMR0_HasOverflowOccured()==true){
                    return false;
                }
            }
            d=UART1_Read();
            Data[i]=d;
            Checksum^=d;
        }
        
        TMR0_Initialize();
        TMR0_StartTimer();
        for(;;){
            if(UART1_is_rx_ready()==true){
                break;
            }
            if(TMR0_HasOverflowOccured()==true){
                return false;
            }
        }
        d=UART1_Read();
        if(Checksum!=d){
            return false;
        }
        *Len=DataLen;
        return true;
    }
    return false;
}
void main(void)
{
    unsigned char   Buff[16];
    int             DipSW;
    unsigned char   TestMode;
    int             DataLen;
    unsigned char   Cmd;
    unsigned char   DCmd;
    unsigned char   TargetDipSW;
    
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    
    FPGA_CS(0);
    FPGA_CLK(1);
    FPGA_CLK(0);
    
    FPGA_SetRW(0);
    
    FPGA_GetBuff(3,Buff,1);
    DipSW=Buff[0] & 0x0f;
       
    TestMode=0;
    Buff[0]=TestMode + 0x02; 
    FPGA_SetBuff(3 ,Buff,1);
    
    //IO_RA7_SetHigh();   //For RS485 OutEnable
    
    while (1)
    {
        if(GetRPIPacket(&Cmd,Buff,&DataLen ,16)==true){
            if(Cmd==0x80){
                Buff[0]=DipSW;
                SendRPIPacket(0x71,Buff,1);
            }
            else if((Cmd&0x40)!=0){
                if(DataLen<=sizeof(Buff)){
                    FPGA_SetBuff(Cmd&0x0f ,Buff,DataLen);
                }
            }
            else if((Cmd&0x20)!=0){
                if(DataLen>=1){
                    DataLen=Buff[0];
                    if(DataLen<=sizeof(Buff)){
                        FPGA_GetBuff(Cmd&0x0f ,Buff,DataLen);
                        SendRPIPacket(Cmd,Buff,DataLen);
                    }
                }
            }
            else{
                TargetDipSW =Cmd&0x0f;
                DCmd        =(Cmd>>4)&0x0f;
                if(DiliverOtherPacket(TargetDipSW,DCmd,Buff,DataLen)==true){
                    if(GetFromOtherPacket(&TargetDipSW,&DCmd
                            ,Buff,&DataLen ,16)==true){
                         SendRPIPacket(0x72,Buff,DataLen);
                    }
                }
            }
        }
    }
}
/**
 End of File
*/