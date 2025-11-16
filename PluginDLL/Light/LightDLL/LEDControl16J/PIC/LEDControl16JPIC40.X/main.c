/*
 * File:   main.c
 * Author: ms441
 *
 * Created on January 6, 2024, 11:56 PM
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>

//FPGA command
//  Bit7    0:System    1:Data
//  Bit3-6  Select Port
//  Bit0-2  0:Base register 1:High register

//For system
//  Select Port :   0::Read DipSW    1:Reset  2:LED

void    SendFPGA2(unsigned char Cmd, unsigned char Data1, unsigned char Data2)
{
    unsigned char   i;
    unsigned char   j;
    
    PIC_SPI_CS_SetLow();
    for(i=0;i<8;i++){
        if((Cmd & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }
     for(i=0;i<8;i++){
        if((Data1 & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }   
     for(i=0;i<8;i++){
        if((Data2 & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }
    PIC_SPI_CS_SetHigh();
}

void    SendFPGA1(unsigned char Cmd, unsigned char Data1)
{
    unsigned char   i;
    unsigned char   j;
    
    PIC_SPI_CS_SetLow();
    for(i=0;i<8;i++){
        if((Cmd & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }
     for(i=0;i<8;i++){
        if((Data1 & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }   
    PIC_SPI_CS_SetHigh();
}

void    SendFPGA0(unsigned char Cmd)
{
    unsigned char   i;
    unsigned char   j;
    
    PIC_SPI_CS_SetLow();
    for(i=0;i<8;i++){
        if((Cmd & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }
    PIC_SPI_CS_SetHigh();
}

void    ReadFPGA1(unsigned char Cmd, unsigned char *Data1)
{
    unsigned char   i;
    unsigned char   j;
    unsigned char   TmpData;
    
    PIC_SPI_CS_SetLow();
    for(i=0;i<8;i++){
        if((Cmd & (0x80>>i))!=0){
            PIC_SPI_MOSI_SetHigh();
        }
        PIC_SPI_SCK_SetHigh();
        PIC_SPI_SCK_SetLow();
        PIC_SPI_MOSI_SetLow();
    }
    TmpData=0;
     for(i=0;i<8;i++){
         TmpData>>=1;
        PIC_SPI_SCK_SetHigh();
        if(PIC_SPI_MISO_GetValue()!=0){
           TmpData |= 0x80; 
        }
        PIC_SPI_SCK_SetLow();
    }   
    PIC_SPI_CS_SetHigh();
    
    *Data1=TmpData;
}

void    SendAckControl(uint8_t d1 ,uint8_t d2 ,uint8_t d3)
{
    unsigned char   SBuff[4];
    SBuff[0]=0x1E;
    SBuff[1]=d1;
    SBuff[2]=d2;
    SBuff[3]=d3;
    //SPI1_WriteBlock(SBuff, 4);
}

unsigned int    BaseData[16];
unsigned int    HighData[16];
unsigned char   DipSW;

unsigned char   AnalogTable[16]=  {   AN0,AN1,AN2,AN3,AN4,AN5,AN6,AN7,AN8,AN9,AN10,AN11,AN12,AN13,AN14,AN15   };

struct  AnalogStruct
{
    unsigned int    ADData[16];
    uint8_t         CountAverage;
    uint8_t         ONMode;     //1:ON
    unsigned int    TargetAD;
    unsigned int    CurrentAD;
    
}AnalogDim[16];

unsigned int    GetAverage(unsigned char NPort)
{
    unsigned long   AddedD;
    uint8_t     i;
    
    AddedD=0;
    for(i=0;i<16;i++){
        AddedD+=(unsigned long)AnalogDim[NPort].ADData[i];
    }
    return AddedD>>4;
}

void    AdjustAverage(uint8_t ADPort, unsigned int CurrentAD,unsigned int TargetAD ,uint8_t ONMode)
{
    unsigned int Div;
    
    if(TargetAD!=0 && ONMode==1){
        if(CurrentAD>TargetAD){
            Div=(CurrentAD-TargetAD)*0.1;
            HighData[ADPort]+=Div;
            if(HighData[ADPort]>BaseData[ADPort]){
                HighData[ADPort]=BaseData[ADPort];
            }
            SendFPGA2(0x80+(ADPort<<3)+0x01, HighData[ADPort]>>8,HighData[ADPort]);
        }
        else if(CurrentAD<TargetAD){
            Div=(TargetAD-CurrentAD)*0.1;
            if(HighData[ADPort]<Div){
                HighData[ADPort]=0;
            }
            else{
                HighData[ADPort]-=Div;
            }
            SendFPGA2(0x80+(ADPort<<3)+0x01, HighData[ADPort]>>8,HighData[ADPort]);    
        }
    }
    else{
        SendFPGA2(0x80+(ADPort<<3)+0x01, 0xFF,0xFF);
    }
}

int    CheckSPIComm(unsigned char RData[4] ,unsigned char *RCmd)
{
    int i;
    int t;
    int len;
    unsigned int    Data;
    unsigned char   DipSWInfo;
    
    if(Control_SPI_CS_GetValue()==0){
        *RCmd=0;
        for(t=0;t<8;t++){
            for(i=0;i<20000;i++){
                if(SPICLK_GetValue()!=0){
                    break;
                }
            }
            if(i>=20000){
                return -1;
            }
            //while(SPICLK_GetValue()==0);
                        
            *RCmd+=(SPIMOSI_GetValue()==0)?0:(0x01<<t);
                 
           //while(SPICLK_GetValue()!=0);

            for(i=0;i<20000;i++){
                if(SPICLK_GetValue()==0){
                    break;
                }
            }
            if(i>=20000){
                return -2; 
            }
        }
        if(*RCmd==1){    //Light ON
            return 1;
        }
        else
        if(*RCmd==2){    //Light OFF
            return 1;
        }
        else
        if(*RCmd==5){    //Send DIPSW
            DipSWInfo=DipSW+0x10;
            MISOEnable_SetHigh();    //MISO is Active
            for(t=0;t<8;t++){
                if((DipSWInfo&(0x80>>t))==0)
                    SPIMISO_SetLow();
                else
                    SPIMISO_SetHigh();
                for(i=0;i<20000;i++){
                    if(SPICLK_GetValue()!=0){
                        break;
                    }
                }
                if(i>=20000){
                    MISOEnable_SetLow();    //MISO is Z
                    return -1;
                }
                //while(SPICLK_GetValue()==0);
                        
                //RCmd+=(SPIMOSI_GetValue()==0)?0:(0x01<<t);
                 
                //while(SPICLK_GetValue()!=0);

                for(i=0;i<20000;i++){
                    if(SPICLK_GetValue()==0){
                        break;
                    }
                }
                if(i>=20000){
                    MISOEnable_SetLow();    //MISO is Z
                    return -2; 
                }
            }
            MISOEnable_SetLow();    //MISO is Z            
        }
        else
        if(((*RCmd) &0x10)!=0){    //Send CurrentValue
            Data=AnalogDim[(*RCmd)&0x0F].CurrentAD;
            MISOEnable_SetHigh();    //MISO is Active
            for(t=0;t<16;t++){
                if((Data&(0x8000>>t))==0)
                    SPIMISO_SetLow();
                else
                    SPIMISO_SetHigh();
                for(i=0;i<20000;i++){
                    if(SPICLK_GetValue()!=0){
                        break;
                    }
                }
                if(i>=20000){
                    MISOEnable_SetLow();    //MISO is Z
                    return -1;
                }
                //while(SPICLK_GetValue()==0);
                        
                //RCmd+=(SPIMOSI_GetValue()==0)?0:(0x01<<t);
                 
                //while(SPICLK_GetValue()!=0);

                for(i=0;i<20000;i++){
                    if(SPICLK_GetValue()==0){
                        break;
                    }
                }
                if(i>=20000){
                    MISOEnable_SetLow();    //MISO is Z
                    return -2; 
                }
            }
            MISOEnable_SetLow();    //MISO is Z
        }        
        else
        if(((*RCmd) &0x20)!=0){    //Get TaegetValue
            Data=0;
            for(t=0;t<16;t++){
                for(i=0;i<20000;i++){
                    if(SPICLK_GetValue()!=0){
                        break;
                    }
                }
                if(i>=20000){
                    return -1;
                }
                //while(SPICLK_GetValue()==0);
                        
                Data+=(SPIMOSI_GetValue()==0)?0:(0x01<<t);
                 
                //while(SPICLK_GetValue()!=0);

                for(i=0;i<20000;i++){
                    if(SPICLK_GetValue()==0){
                        break;
                    }
                }
                if(i>=20000){
                    return -2; 
                }
            } 
            AnalogDim[(*RCmd)&0x0F].TargetAD=Data;
        }        
        else
        if(*RCmd==3){    //Send Light ON
            for(i=0;i<16;i++){
                AnalogDim[i].ONMode         =1;
            }                     
        }        
        else
        if(*RCmd==4){    //Send Light OFF 
            for(i=0;i<16;i++){
                AnalogDim[i].ONMode         =0;
            }            
        }  
        else
        if(*RCmd==13){    //Send TestLED ON
            SendAckControl(0,0,0);
            SendFPGA0(0x00+0x10+0x01);    //LED ON            
        }        
        else
        if(*RCmd==14){    //Send TestLED OFF 
            SendAckControl(0,0,0);
            SendFPGA0(0x00+0x10+0x00);    //LED OFF           
        } 
        return 4;
    }
    return 0;
}



void main(void) 
{
    unsigned char   i;
    uint8_t         RByte;
    unsigned char   RBuff[4];
    unsigned char   Cmd;
    unsigned char   Port;
    unsigned char   ADPort;
    unsigned char   ADState;
    unsigned int    D;
    unsigned int    LEDOutCounter;
    uint8_t         LEDOut;
    unsigned char   MasterCmd;
    
    SYSTEM_Initialize();
    
    //SPI1_Open(SPI1_DEFAULT);
    //SPI1_SetInterruptHandler(MSSP1_interruptHandler);
    
    OUTNGATE_SetLow();  //ControlPower OFF
    MISOEnable_SetLow();    //MISO is Z
    
    PIC_SPI_CS_SetHigh();
    PIC_SPI_SCK_SetLow();
    PIC_SPI_MOSI_SetLow();
    
    for(i=0;i<16;i++){
        BaseData[i]=5000;
        HighData[i]=4700;
        AnalogDim[i].CountAverage   =0;
        AnalogDim[i].TargetAD       =0;
        AnalogDim[i].ONMode         =1;
    }
    ADPort  =0;
    ADState =0;
    LEDOutCounter   =0;
    LEDOut          =0;
    
    SendFPGA0(0x00+0x08+0x01);   //Reset FPGA
    SendFPGA0(0x00+0x08+0x00);   //Reset FPGA

    ReadFPGA1(0, &DipSW);
    
    SendFPGA0(0x00+0x10+0x01);    //LED ON
    SendFPGA0(0x00+0x10+0x00);    //LED OFF
    //SendFPGA0(0x00+0x10+0x01);    //LED ON
    
    for(i=0;i<16;i++){
        SendFPGA2(0x80+(i<<3)+0x00, BaseData[i]>>8,BaseData[i]);
        SendFPGA2(0x80+(i<<3)+0x01, HighData[i]>>8,HighData[i]);
    }
    
    OUTNGATE_SetHigh();  //ControlPower ON
    
    for(;;){
        //if(Control_SPI_CS_GetValue()==0){
        if(CheckSPIComm(RBuff,&MasterCmd)>0){
            //SPIRxCmd1=SPI1_ExchangeByte(1);
            //SPIRxCmd2=SPI1_ExchangeByte(1);
            //if(SPIRxCmd1!=0){
            //    SPI1_ReadBlock(RBuff, 4);
                Cmd=RBuff[0];
                if(Cmd==1){
                    SendAckControl(0,0,0);
                    SendFPGA0(0x00+0x10+0x01);    //LED ON
                }
                else if(Cmd==2){
                    SendAckControl(0,0,0);
                    SendFPGA0(0x00+0x10+0x00);    //LED OFF
                }
                else if((Cmd & 0x20)!=0){
                    Port=Cmd&0x0F;
                    
                }
                /*
                    SendAckControl(0,0,0);
                    Port=RBuff[1];
                    BaseData[Port]=RBuff[2]+(RBuff[3]<<8);
                    SendFPGA2(0x80+(Port<<3)+0x00, BaseData[Port]>>8,BaseData[Port]);
                }
                else if(Cmd==4){
                    SendAckControl(0,0,0);
                    Port=RBuff[1];
                    HighData[Port]=RBuff[2]+(RBuff[3]<<8);
                    SendFPGA2(0x80+(Port<<3)+0x01, HighData[Port]>>8,HighData[Port]);
                }
                else if(Cmd==5){
                    SendAckControl(0,0,0);
                    Port=RBuff[1];
                    AnalogDim[Port].TargetAD=RBuff[2]+(RBuff[3]<<8);
                }
                */
            //}
        }
        if(ADState==0){
            ADCC_StartConversion(AnalogTable[ADPort]);
            ADState=1;
        }
        else if(ADState==1){
            if(ADCC_IsConversionDone()){
                D=ADCC_GetConversionResult();
                AnalogDim[ADPort].ADData[AnalogDim[ADPort].CountAverage]=D;
                ADState=2;
            }
        }
        else if(ADState==2){
            AnalogDim[ADPort].CountAverage++;
            if(AnalogDim[ADPort].CountAverage>=16){
                AnalogDim[ADPort].CurrentAD =GetAverage(ADPort);
                AdjustAverage(ADPort
                             ,AnalogDim[ADPort].CurrentAD
                             ,AnalogDim[ADPort].TargetAD
                             ,AnalogDim[ADPort].ONMode);
                AnalogDim[ADPort].CountAverage=0;
            }
            ADState=0;
            ADPort++;
            if(ADPort>=16){
                ADPort=0;
            }
        }
        if(LEDOutCounter>=10000){
            LEDOutCounter=0;
            if(LEDOut==0){
                 SendFPGA0(0x00+0x10+0x01);    //LED ON
                 LEDOut=1;
            }
            else{
                 SendFPGA0(0x00+0x10+0x00);    //LED OFF
                 LEDOut=0;
            }
        }
        LEDOutCounter++;
    }
 
    return;
}
