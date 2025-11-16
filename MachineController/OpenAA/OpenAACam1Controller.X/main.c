 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

#define MaxWaitingTime  10000
#define MaxDataLen      16

int GetPICSPIData(int OutData)
{
    int i;
    int k;
    int Data;

    Data=0;
    for(i=0;i<8;i++){
        Data=Data<<1;
        
        if((OutData&0x80)!=0){
            PIC_MISO_SetHigh();
        }
        else{
            PIC_MISO_SetLow();
        }
        OutData=OutData<<1;
        
        for(k=0;k<MaxWaitingTime;k++){
            if(PIC_SCLK_GetValue()!=0){
                goto    L1;
            }
        }
        return -1;
        L1:;
        if(PIC_MOSI_GetValue()!=0){
            Data+=1;
        }
        for(k=0;k<MaxWaitingTime;k++){
            if(PIC_SCLK_GetValue()==0){
                goto    L2;
            }
        }
        return -1;
        L2:;
    }
    return Data;
}

/*  Communicate to RaspberryPI
 *  1 BYTE  Header  0x1E   
 *  1 BYTE  Count of Byte   from Command to Data
 *  1 BYTE  Command   
 *  N BYTE  Data
 *  1 BYTE  Checksum    from Command to Data
 */

int ReceiveFromRaspberryPI(int *Cmd ,unsigned char DataIn[],unsigned char DataOut[])
{
    int n,d,i;
    int Len;
    int DataLen;
    unsigned char   CheckSum;
    
    if(PIC_CS_GetValue()==0){
        d=GetPICSPIData(DataOut[0]);
        if(d!=0x1E){
            return -1;
        }
        
        Len=GetPICSPIData(DataOut[1]);
        if(Len<0){
            return -1;
        }

        d=GetPICSPIData(DataOut[2]);
        if(d<0){
            return -1;
        }
        *Cmd=d;
        CheckSum=d;
        DataLen=Len-1;
        if(DataLen<0 || DataLen>MaxDataLen){
            return -1;
        }
        n=3;
        
        for(i=0;i<DataLen;i++){
            d=GetPICSPIData(DataOut[n]);
            if(d<0){
                return -1;
            }
            DataIn[i]=d;
            CheckSum+=d;
            n++;
        }
        d=GetPICSPIData(DataOut[n]);
        if(d<0){
            return -1;
        }
        if(d!=CheckSum){
            return -1;
        }
        return DataLen;
    }
    return  -1;
}

int GetGIOInport(void)
{
    int d;
    d=((GIN1_GetValue()!=0)?0x01:0)
     +((GIN2_GetValue()!=0)?0x02:0)       
     +((GIN3_GetValue()!=0)?0x04:0)       
     +((GIN4_GetValue()!=0)?0x08:0);
    return d;
}

void    OutputGIOData(int d)
{
    if((d&0x01)!=0)
        GOUT1_SetHigh();
    else
        GOUT1_SetLow();
    
    if((d&0x02)!=0)
        GOUT2_SetHigh();
    else
        GOUT2_SetLow();
    
    if((d&0x04)!=0)
        GOUT3_SetHigh();
    else
        GOUT3_SetLow();
    
    if((d&0x81)!=0)
        GOUT4_SetHigh();
    else
        GOUT4_SetLow(); 
}
//==========================================================================================================
unsigned char   LED_DataW[MaxDataLen];
unsigned char   LED_DataR[MaxDataLen];
int LED_DataLen;

uint16_t AssembleSPICmd(bool write, int regAddr, uint16_t data)
{
    uint16_t assembledCmd = 0;  // Build this to shift through parity calc
    uint16_t parity = 0;        // Parity bit calculated here
    uint16_t packet = 0;        // This will be what we send
    // Set the CMD bit high if this is a write
    if(write){
        assembledCmd |= 0x8000; // Set CMD = 1
    }
    // Move the register address into the correct position
    assembledCmd |= (( regAddr << 10) & 0x7C00);
    // Append the data for a write
    if(write){
        assembledCmd |= (data & 0x01FF);
    }
    // Save this off into the returned variable
    packet = assembledCmd;
    // Calculate the parity bit
    while(assembledCmd > 0){
        // Count the number of 1s in the LSb
        if(assembledCmd & 0x0001){
            parity++;
        }
        // Shift right
        assembledCmd >>= 1;
    }
    // If the LSb is a 0 (even # of 1s), we need to add the odd parity bit
    if(!(parity & 0x0001)){
        packet |= (1 << 9);
    }
    return(packet);
}

bool     AccessToLEDWriteResponse(void)
{
    if((LED_DataR[2]&0x80)!=0)
        return false;
    return true;
}
uint16_t     AccessToLEDReadResponse(bool *PowerCycled ,bool *LED1Error ,bool *LED2Error ,bool *ThermalWarning)
{
    if((LED_DataR[2]&0x80)!=0)
        return 0xFFFF;

    *PowerCycled    =((LED_DataR[2]&0x10)!=0)?true:false;
    *LED2Error      =((LED_DataR[2]&0x08)!=0)?true:false;
    *LED1Error      =((LED_DataR[2]&0x04)!=0)?true:false;
    *ThermalWarning =((LED_DataR[2]&0x02)!=0)?true:false;
    
    return ((LED_DataR[2]&0x01)<<8)+LED_DataR[3];
}

bool    AccessToLEDWriteControlRegister(bool ThermSmplEN, bool VLED1SmplEN ,bool VLED2SmplEN ,bool LED1EN,bool LED2EN)
{
    uint16_t    Data= ((LED1EN==true)?0x01:0)
                    | ((LED2EN==true)?0x02:0)
                    | ((VLED1SmplEN==true)?0x04:0)
                    | ((VLED2SmplEN==true)?0x08:0)
                    | ((ThermSmplEN==true)?0x10:0);
    uint16_t    D=AssembleSPICmd(true, 0x00, Data);
    
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    
    SPI2_Transfer(LED_DataW, LED_DataR, 4);
    if(AccessToLEDWriteResponse()==false)
        return false;
    return true;
}

bool    AccessToLEDReadControlRegister(bool *ThermSmplEN, bool *VLED1SmplEN ,bool *VLED2SmplEN ,bool *LED1EN,bool *LED2EN)
{
    uint16_t    D=AssembleSPICmd(false, 0x00, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *LED1EN     =((W&0x01)!=0)?true:false;
    *LED2EN     =((W&0x02)!=0)?true:false;
    *VLED1SmplEN=((W&0x04)!=0)?true:false;
    *VLED2SmplEN=((W&0x08)!=0)?true:false;
    *ThermSmplEN=((W&0x10)!=0)?true:false;
     
    return true;
}

bool    AccessToLEDReadStatus(bool *PowerCycled ,bool *LED1Error ,bool *LED2Error ,bool *ThermalWarning)
{
    uint16_t    D=AssembleSPICmd(false, 0x01, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    tPowerCycled;
    bool    tLED1Error;
    bool    tLED2Error;
    bool    tThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&tPowerCycled ,&tLED1Error ,&tLED2Error ,&tThermalWarning);

    if(W==0xFFFF)
        return false;
    bool    SPIError;
    SPIError        =((W&0x01)!=0)?true:false;
    *ThermalWarning =((W&0x02)!=0)?true:false;
    *LED1Error      =((W&0x04)!=0)?true:false;
    *LED2Error      =((W&0x08)!=0)?true:false;
    *PowerCycled    =((W&0x10)!=0)?true:false;
     
    return true;
}


bool    AccessToLEDWriteThermWarnLmt(int LimitData)
{
    uint16_t    Data= LimitData&0xFF;
    uint16_t    D=AssembleSPICmd(true, 0x02, Data);
    
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    
    SPI2_Transfer(LED_DataW, LED_DataR, 4);
    if(AccessToLEDWriteResponse()==false)
        return false;
    return true;
}

bool    AccessToLEDReadThermWarnLmt(int *LimitData)
{
    uint16_t    D=AssembleSPICmd(false, 0x02, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *LimitData=W&0xFF;
     
    return true;
}

bool    AccessToLEDWriteLEDPkThDAC(int LED ,int PkThDAC)    //LED1:LED==0
{
    uint16_t    Data= PkThDAC&0xFF;
    int         Address=(LED==0)?0x03:0x04;
    uint16_t    D=AssembleSPICmd(true, Address, Data);
    
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    
    SPI2_Transfer(LED_DataW, LED_DataR, 4);
    if(AccessToLEDWriteResponse()==false)
        return false;
    return true;
}

bool    AccessToLEDReadLEDPkThDAC(int LED ,int *PkThDAC)
{
    int         Address=(LED==0)?0x03:0x04;
    uint16_t    D=AssembleSPICmd(false, Address, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *PkThDAC=W&0xFF;
     
    return true;
}

bool    AccessToLEDWriteLEDTOffDAC(int LED ,int TOffDAC)
{
    uint16_t    Data= TOffDAC&0xFF;
    int         Address=(LED==0)?0x05:0x06;
    uint16_t    D=AssembleSPICmd(true, Address, Data);
    
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    
    SPI2_Transfer(LED_DataW, LED_DataR, 4);
    if(AccessToLEDWriteResponse()==false)
        return false;
    return true;
}

bool    AccessToLEDReadLEDTOffDAC(int LED ,int *TOffDAC)
{
    int         Address=(LED==0)?0x05:0x06;
    uint16_t    D=AssembleSPICmd(false, Address, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *TOffDAC=W&0xFF;
     
    return true;
}

bool    AccessToLEDWriteLEDMaxOffDAC(int LED ,int MaxOffDAC)
{
    uint16_t    Data= MaxOffDAC&0xFF;
    int         Address=(LED==0)?0x07:0x08;
    uint16_t    D=AssembleSPICmd(true, Address, Data);
    
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    
    SPI2_Transfer(LED_DataW, LED_DataR, 4);
    if(AccessToLEDWriteResponse()==false)
        return false;
    return true;
}

bool    AccessToLEDReadLEDMaxOffDAC(int LED ,int *MaxOffDAC)
{
    int         Address=(LED==0)?0x07:0x08;
    uint16_t    D=AssembleSPICmd(false, Address, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *MaxOffDAC=W&0xFF;
     
    return true;
}

bool    AccessToLEDReadVThrm(int *VTherm)
{
    uint16_t    D=AssembleSPICmd(false, 0x09, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *VTherm=W&0xFF;
     
    return true;
}

bool    AccessToLEDReadLEDMostRecent(int LED ,int *MostRecent)
{
    int         Address=(LED==0)?0x0A:0x0D;
    uint16_t    D=AssembleSPICmd(false, Address, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *MostRecent=W&0xFF;
     
    return true;
}

bool    AccessToLEDReadLEDLastON(int LED ,int *LastON)
{
    int         Address=(LED==0)?0x0B:0x0E;
    uint16_t    D=AssembleSPICmd(false, Address, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *LastON=W&0xFF;
     
    return true;
}

bool    AccessToLEDReadLEDLastOFF(int LED ,int *LastOFF)
{
    int         Address=(LED==0)?0x0C:0x0F;
    uint16_t    D=AssembleSPICmd(false, Address, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
    
    *LastOFF=W&0xFF;
     
    return true;
}


bool    AccessToLEDWriteReset(void)
{
    uint16_t    D=AssembleSPICmd(true, 0x10, 0);
    
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    
    SPI2_Transfer(LED_DataW, LED_DataR, 4);
    if(AccessToLEDWriteResponse()==false)
        return false;
    return true;
}

bool    AccessToLEDReadReset(void)
{
    uint16_t    D=AssembleSPICmd(false, 0x10, 0);
    LED_DataW[0]=D;
    LED_DataW[1]=D>>8;
    SPI2_Transfer(LED_DataW, LED_DataR, 4);

    bool    PowerCycled;
    bool    LED1Error;
    bool    LED2Error;
    bool    ThermalWarning;
    uint16_t     W=AccessToLEDReadResponse(&PowerCycled ,&LED1Error ,&LED2Error ,&ThermalWarning);

    if(W==0xFFFF)
        return false;
     
    return true;
}



//==========================================================================================================


int RPI_Cmd;
unsigned char   RPI_InData[MaxDataLen];
unsigned char   RPI_OutData[MaxDataLen];
int RPI_DataLen;

int     LightA,LightB;     

int main(void)
{
    int     TestLED=0;
    unsigned char   OutCheckSum;
    
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    RPI_OutData[0]=0x1B;
    RPI_OutData[1]=1;
    RPI_OutData[2]=0x80;

    while(1)
    {
        RPI_DataLen=ReceiveFromRaspberryPI(&RPI_Cmd ,RPI_InData,RPI_OutData);
        if(RPI_DataLen>=0){
            if(RPI_Cmd==1){
                LightA=RPI_InData[0]+(RPI_InData[1]<<8);
                LightB=RPI_InData[2]+(RPI_InData[3]<<8);
            }
            if(RPI_Cmd==2){
                OutputGIOData(RPI_InData[0]);
            }
        }

        RPI_OutData[3]=GetGIOInport();
        OutCheckSum=RPI_OutData[2];
        OutCheckSum+=RPI_OutData[3];
        RPI_OutData[4]=OutCheckSum;
        
        if(TestLED>1000){
            PICTESTLED_SetHigh();
        }
        else{
            PICTESTLED_SetLow();
        }
        TestLED++;
        if(TestLED>=2000){
            TestLED=0;
        }
    }    
}