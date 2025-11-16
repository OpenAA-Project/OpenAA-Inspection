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
#include "..\..\XLightInBoard.h"
/*
                         Main application
 */

struct LightPattern CurrentPatternData;
int             DipSW;
bool            RegTestLED;
bool            RegPLSEnable;
bool            RegPulseOutMode;

void    FPGA_SetCmd(int Cmd)
{
    if((Cmd&0x01)!=0)
        IO_RA3_SetHigh();
    else
        IO_RA3_SetLow();
    if((Cmd&0x02)!=0)
        IO_RA4_SetHigh();
    else
        IO_RA4_SetLow();
    if((Cmd&0x04)!=0)
        IO_RA5_SetHigh();
    else
        IO_RA5_SetLow();
}

void    FPGA_SetAddress(int Address)
{
    if(Address>=0){
        if((Address&0x01)!=0)
            IO_RA1_SetHigh();
        else
            IO_RA1_SetLow();
        if((Address&0x02)!=0)
            IO_RC0_SetHigh();
        else
            IO_RC0_SetLow();
        if((Address&0x04)!=0)
            IO_RC1_SetHigh();
        else
            IO_RC1_SetLow();
        if((Address&0x08)!=0)
            IO_RC2_SetHigh();
        else
            IO_RC2_SetLow(); 
    }
}

void    FPGA_CLK(int d)
{
    if((d&0x01)!=0)
        IO_RE0_SetHigh();
    else
        IO_RE0_SetLow();    
}
void    FPGA_CS(int d)
{
    if((d&0x01)!=0)
        IO_RE1_SetHigh();
    else
        IO_RE1_SetLow();    
}
void    FPGA_SetRW(int d)
{
    if((d&0x01)!=0)
        IO_RE2_SetHigh();
    else
        IO_RE2_SetLow();       
}

void    FPGA_SetData(unsigned char d)
{
    if((d&0x01)!=0)
        IO_RD0_SetHigh();
    else
        IO_RD0_SetLow();    
    if((d&0x02)!=0)
        IO_RD1_SetHigh();
    else
        IO_RD1_SetLow();    
    if((d&0x04)!=0)
        IO_RD2_SetHigh();
    else
        IO_RD2_SetLow();    
    if((d&0x08)!=0)
        IO_RD3_SetHigh();
    else
        IO_RD3_SetLow();    
    if((d&0x10)!=0)
        IO_RD4_SetHigh();
    else
        IO_RD4_SetLow();    
    if((d&0x20)!=0)
        IO_RD5_SetHigh();
    else
        IO_RD5_SetLow();    
    if((d&0x40)!=0)
        IO_RD6_SetHigh();
    else
        IO_RD6_SetLow();    
    if((d&0x80)!=0)
        IO_RD7_SetHigh();
    else
        IO_RD7_SetLow();    
}
unsigned char    FPGA_GetData(void)
{
    unsigned char d=0;
    
    d=((IO_RF0_GetValue()!=0)?0x01:0)
     +((IO_RF1_GetValue()!=0)?0x02:0)
     +((IO_RF2_GetValue()!=0)?0x04:0)
     +((IO_RF3_GetValue()!=0)?0x08:0)
     +((IO_RF4_GetValue()!=0)?0x10:0)
     +((IO_RF5_GetValue()!=0)?0x20:0)
     +((IO_RF6_GetValue()!=0)?0x40:0)
     +((IO_RF7_GetValue()!=0)?0x80:0);
            
    return d;
}

void    FPGA_GetBuff(int Cmd ,int Address ,unsigned char data[] ,int DataLen)
{
    int i;
    
    FPGA_CS(0);
    FPGA_CLK(1);
    FPGA_CLK(0);
    
    FPGA_SetCmd(Cmd);
    FPGA_SetAddress(Address);
    FPGA_SetRW(1);
    FPGA_CS(1);
    for(i=0;i<DataLen;i++){
        FPGA_CLK(1);
        FPGA_CLK(0);
        data[i]=FPGA_GetData();
    }
    FPGA_CS(0);
}
void    FPGA_SetBuff(int Cmd ,int Address ,unsigned char data[] ,int DataLen)
{
    int i;
    
    FPGA_CS(0);  
    FPGA_CLK(1);
    FPGA_CLK(0);

    FPGA_SetCmd(Cmd);
    FPGA_SetAddress(Address);
    FPGA_SetRW(0);
    FPGA_CS(1);   
    for(i=0;i<DataLen;i++){
        FPGA_SetData(data[i]);
        FPGA_CLK(1);
        FPGA_CLK(0);
    }
    FPGA_CS(0);
}

void    FPGA_SetLightBaseCounter(int n)
{
    unsigned char data[2];
    data[0]=CurrentPatternData.LineData[n].BaseCounter&0xFF;
    data[1]=(CurrentPatternData.LineData[n].BaseCounter>>8)&0xFF;
    FPGA_SetBuff(0,n ,data ,2);
}

void    FPGA_SetLightHighCounter(int n)
{
    unsigned char data[2];
    data[0]=CurrentPatternData.LineData[n].HighCounter&0xFF;
    data[1]=(CurrentPatternData.LineData[n].HighCounter>>8)&0xFF;
    FPGA_SetBuff(1,n ,data ,2);
}

void    FPGA_SetLightMask(void)
{
    unsigned char data[2];
    
    data[0]=((CurrentPatternData.LineData[0].Mask==true)?0x01:0)
           +((CurrentPatternData.LineData[1].Mask==true)?0x02:0)
           +((CurrentPatternData.LineData[2].Mask==true)?0x04:0)
           +((CurrentPatternData.LineData[3].Mask==true)?0x08:0)
           +((CurrentPatternData.LineData[4].Mask==true)?0x10:0)
           +((CurrentPatternData.LineData[5].Mask==true)?0x20:0)
           +((CurrentPatternData.LineData[6].Mask==true)?0x40:0)
           +((CurrentPatternData.LineData[7].Mask==true)?0x80:0);
    data[1]=((CurrentPatternData.LineData[8].Mask==true)?0x01:0)
           +((CurrentPatternData.LineData[9].Mask==true)?0x02:0)
           +((CurrentPatternData.LineData[10].Mask==true)?0x04:0)
           +((CurrentPatternData.LineData[11].Mask==true)?0x08:0)
           +((CurrentPatternData.LineData[12].Mask==true)?0x10:0)
           +((CurrentPatternData.LineData[13].Mask==true)?0x20:0)
           +((CurrentPatternData.LineData[14].Mask==true)?0x40:0)
           +((CurrentPatternData.LineData[15].Mask==true)?0x80:0);
    
    FPGA_SetBuff(3,-1 ,data ,2);
}

void    FPGA_SetMode(void)
{
    unsigned char data;
    
    data =((RegTestLED==true)?0x08:0)
         +((RegPLSEnable==true)?0x04:0)
         +((RegPulseOutMode==true)?0x02:0);
    FPGA_SetBuff(2,-1,&data ,1);
}

void    FPGA_LightON(bool ONMode)
{
    unsigned char data;
    
    data =((RegTestLED==true)?0x08:0)
         +((ONMode==true)?0x04:0)
         +((RegPulseOutMode==true)?0x02:0);
    FPGA_SetBuff(2,-1,&data ,1);
}

adc_result_t     GetADFromLight(int Address,bool SelEN)
{
    if(Address>=0){
        if((Address&0x01)!=0)
            IO_RB0_SetHigh();
        else
            IO_RB0_SetLow();
        if((Address&0x02)!=0)
            IO_RB1_SetHigh();
        else
            IO_RB1_SetLow();
        if((Address&0x04)!=0)
            IO_RB2_SetHigh();
        else
            IO_RB2_SetLow();
        if((Address&0x08)!=0)
            IO_RB3_SetHigh();
        else
            IO_RB3_SetLow(); 
    }
    IO_RB4_SetLow(); 
    IO_RB5_SetLow(); 
    if(SelEN==0)
        IO_RB4_SetHigh();
    else
        IO_RB5_SetHigh();
    
    adc_result_t D=ADCC_GetConversionResult();
    return D;
}


void main(void)
{
    unsigned char   Buff[16];
    int             DataLen;
    int             i;
    unsigned char   Cmd;
    unsigned char   DCmd;
    
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    
    
    for(i=0;i<16;i++){
        CurrentPatternData.LineData[i].BaseCounter  =0x2000;
        CurrentPatternData.LineData[i].HighCounter  =0x1000;
        CurrentPatternData.LineData[i].Mask         =true;
    }
    
    FPGA_CS(0);
    FPGA_SetRW(0);
    
    Buff[0]=0x01;
    FPGA_SetBuff(2 ,-1 ,Buff ,1);
    
    Buff[0]=0x00;
    FPGA_SetBuff(2 ,-1 ,Buff ,1);
    
    RegTestLED=true;
    RegPLSEnable=false;
    RegPulseOutMode=true;
    FPGA_SetMode();

    FPGA_GetBuff(5 ,-1 ,Buff ,1);
    DipSW=Buff[0];
    
    for(i=0;i<16;i++){
        FPGA_SetLightBaseCounter(i);
        FPGA_SetLightHighCounter(i);
    }
    FPGA_SetLightMask();

    FPGA_LightON(true);
    
    while (1)
    {
        for(i=0;i<16;i++){
            GetADFromLight(i,true);
        }
        for(i=0;i<16;i++){
            GetADFromLight(i,false);
        }
        // Add your application code
    }
}
/**
 End of File
*/