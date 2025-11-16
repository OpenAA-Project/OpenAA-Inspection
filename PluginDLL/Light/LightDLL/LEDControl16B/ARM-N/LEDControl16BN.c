#include "..\LightUnitStruct.h"

sbit STAT     at ODR13_GPIOC_ODR_bit;
sbit DATA     at ODR12_GPIOC_ODR_bit;

sbit I_OuterSW      at IDR1_GPIOA_IDR_bit;       //PA1
sbit O_OuterLED0    at ODR2_GPIOA_ODR_bit;       //PA2
sbit O_OuterLED1    at ODR3_GPIOA_ODR_bit;       //PA3

sbit I_SelectSW0    at IDR15_GPIOA_IDR_bit;       //PA15
sbit I_SelectSW1    at IDR14_GPIOA_IDR_bit;       //PA14
sbit I_SelectSW2    at IDR13_GPIOA_IDR_bit;       //PA13
sbit I_SelectSW3    at IDR9_GPIOC_IDR_bit;       //PC9

sbit O_ADCS         at ODR8_GPIOA_ODR_bit;      //PA8

sbit O_DATACLK      at ODR0_GPIOC_ODR_bit;       //PC0
sbit O_SELECTOR     at ODR1_GPIOC_ODR_bit;       //PC1
sbit O_DATAIN       at ODR2_GPIOC_ODR_bit;       //PC2
sbit O_ENABLE       at ODR4_GPIOC_ODR_bit;       //PC4
sbit O_RESET        at ODR5_GPIOC_ODR_bit;       //PC5

sbit I_SamplingBit  at IDR9_GPIOB_IDR_bit;       //PB9
sbit I_DATAOUT      at IDR8_GPIOB_IDR_bit;       //PB8

sbit O_OUTUART      at ODR5_GPIOB_ODR_bit;       //PB5

sbit O_SPI1_SCK    at ODR5_GPIOA_ODR_bit;       //PA5
sbit O_SPI1_MOSI   at ODR7_GPIOA_ODR_bit;       //PA7
sbit I_SPI1_MISO   at IDR6_GPIOA_IDR_bit;       //PA6

sbit O_SPI2_SCK    at ODR13_GPIOB_ODR_bit;       //PB13
sbit O_SPI2_MOSI   at ODR15_GPIOB_ODR_bit;       //PB15
sbit I_SPI2_MISO   at IDR14_GPIOB_IDR_bit;       //PB14

sbit O_Test        at ODR3_GPIOB_ODR_bit;       //PB13

sbit I_IOSPARE0    at IDR0_GPIOB_IDR_bit;       //PB0
sbit I_IOSPARE1    at IDR1_GPIOB_IDR_bit;       //PB0
sbit I_IOSPARE2    at IDR4_GPIOB_IDR_bit;       //PB0
sbit O_IOSPARE3    at ODR10_GPIOB_ODR_bit;       //PB10         RelayOut
sbit O_AllADStart  at ODR12_GPIOB_ODR_bit;      //PB10
sbit I_AllADReady  at IDR11_GPIOB_IDR_bit;      //PB11

//sbit O_TestBit       at ODR0_GPIOB_ODR_bit;       //PB0

char     USBReadBuff[68];
char     USBWriteBuff[68];
char     PowerCLK;

typedef  int     BOOL;
#define  TRUE             1
#define  FALSE            0
#define  MaxAddr          16
#define  MaxBoardCount    3
#define  IODelivererID    3

struct   BoardInfoStruct
{
    struct        LightUnit   EPROMData[2];
    int           Brightness[MaxAddr];
    int           ADData[MaxAddr];
    long          ADSumData[MaxAddr];
    int           ADSumCount[MaxAddr];
    int           PortSel;        //For SPI of EPROM
    int           BaseCounter;
    int           PWMSelector;    //For SamplingBit to select PWM port
    unsigned char InputData[4];
    unsigned char Gain[MaxAddr];
};

int    BoardCount=MaxBoardCount;
long   int    ContinuousMode=0;
struct   BoardInfoStruct    BoardData[MaxBoardCount];
void    ManageUSB(void);
int    TestMode;
int    ManualMode;
unsigned char  ADRegData[10];

//==============================================================================

BOOL    ReadLightEPRom(int BoardNumber,int PortNumber);
void    WriteLightEPRom(int BoardNumber,int PortNumber);
int     GetStatusSPI2(void);
int     ReadLightEPRomStatus(int BoardNumber,int PortNumber);

void    SelectAD(int BoardNumber);
void    SendGain(int BoardNumber);
void   ReadAD_ChannelReadDirectly(unsigned char rdata[3]);
void   ReadAD_RegisterAndChannel(unsigned char cmd ,unsigned char rdata[] ,int datanumb);
void   WriteAD_RegisterAndChannel(unsigned char cmd ,unsigned char wdata[] ,int datanumb);
void   ScanADData(int BoardNumber);
void    ReadAD_Register(unsigned char RData[10]);

void  OutputTestLED(int BoardNumber ,int ON);

void    RelayON(void);
void    RelayOFF(void);

int  GetFrontVolume(void);

//==============================================================================

void  WaitSlightly(void)
{
    long int  i;
    //for(i=0;i<1000000L;i++){}
    for(i=0;i<3;i++){}
}
void  WaitSlightlySPI(void)
{
    long int  i;
    //for(i=0;i<500000L;i++){}
    for(i=0;i<50000L;i++){}
    //for(i=0;i<100;i++){}
}
void  WaitSlightlyAD(void)
{
    long int  i;
    //for(i=0;i<500;i++){}
    USB_Polling_Proc();
}

//--------------------------------------------------------------------

void  TransferBitData(unsigned int Data , int Addr ,int Cmd ,int Sel)
{
    int    i;
    int    d;
    int      ID=0x0b;
    int      Dummy=0;
    unsigned char    Polarity=0;

    O_RESET=0;
    O_SELECTOR=1;
    O_DATACLK    =0;
    WaitSlightly();
    for(i=0;i<16;i++){
        d=((Data & (0x0001<<i))!=0)?1:0;
        O_DATAIN =d;
        Polarity ^=d;
        WaitSlightly();
        O_DATACLK=1;
        WaitSlightly();
        O_DATACLK=0;
        WaitSlightly();
    }
    for(i=0;i<4;i++){
        d=((Addr & (0x0001<<i))!=0)?1:0;
        O_DATAIN =  d;
        Polarity ^=d;
        WaitSlightly();
        O_DATACLK=1;
        WaitSlightly();
        O_DATACLK=0;
        WaitSlightly();
    }
    for(i=0;i<3;i++){
        d=((Cmd & (0x0001<<i))!=0)?1:0;
        O_DATAIN = d;
        Polarity ^=d;
        WaitSlightly();
        O_DATACLK=1;
        WaitSlightly();
        O_DATACLK=0;
        WaitSlightly();
    }
     for(i=0;i<4;i++){
        d=((Sel & (0x0001<<i))!=0)?1:0;
        O_DATAIN = d;
        Polarity ^=d;
        WaitSlightly();
        O_DATACLK=1;
        WaitSlightly();
        O_DATACLK=0;
        WaitSlightly();
    }
    for(i=0;i<4;i++){
        d=((ID & (0x0001<<i))!=0)?1:0;
        O_DATAIN = d;
        Polarity ^=d;
        WaitSlightly();
        O_DATACLK=1;
        WaitSlightly();
        O_DATACLK=0;
        WaitSlightly();
    }

    O_DATAIN = Polarity;
    WaitSlightly();
    O_DATACLK=1;
    WaitSlightly();
    O_DATACLK=0;
    WaitSlightly();

    O_SELECTOR=0;
}

int GetRegData(unsigned char DataType,int Addr ,int BoardNumber)
{
    int  Ret=0;
    int  i=0;
    TransferBitData(DataType , Addr ,5 ,BoardNumber);

    O_SELECTOR=0;
    WaitSlightly();
    for(i=0;i<16;i++){
        if(I_DATAOUT!=0){
            Ret |=(1<<i);
        }
        O_DATACLK=1;
        WaitSlightly();
        O_DATACLK=0;
        WaitSlightly();
    }
    return Ret;
}

void    ExecuteReset(void)
{
    int  BoardNumber;

    O_RESET    =1;
    WaitSlightly();
    WaitSlightly();
    WaitSlightly();
    WaitSlightly();
    WaitSlightly();
    WaitSlightlyAD();
    WaitSlightlyAD();

    O_RESET      =0;

    WaitSlightly();

    WaitSlightlyAD();
    WaitSlightlyAD();
}

int    GetSelectSW(void)
{
    int Ret= 0;
    if(I_SelectSW0!=0)
        Ret+=1;
    if(I_SelectSW1!=0)
        Ret+=2;
    if(I_SelectSW2!=0)
        Ret+=4;
    if(I_SelectSW3!=0)
        Ret+=8;
    return Ret;
}

void    GetIO(int BoardNumber ,int InputData[4])
{
    int    IOData;
    
    IOData = GetRegData(14,0 ,BoardNumber);
    if(0<=BoardNumber && BoardNumber<BoardCount){
        if((IOData & 0x01)!=0)
            InputData[0]=1;
        else
            InputData[0]=0;
        if((IOData & 0x02)!=0)
            InputData[1]=1;
        else
            InputData[1]=0;
        if((IOData & 0x04)!=0)
            InputData[2]=1;
        else
            InputData[2]=0;
        if((IOData & 0x08)!=0)
            InputData[3]=1;
        else
            InputData[3]=0;
    }
}
void AnalizeData(void)
{
    int IOData,i;
    int UnitNumber;
    int BoardNumber;
    int PortNumber;
    int PatternNumber;
    int LineNumber;
    unsigned int USData;
    int Cmd;
    int Addr;
    unsigned char  rData[1];

    if(USBReadBuff[0]=='V'){
        strcpy(USBWriteBuff,"MEGATRADE LEDControl16BN");
        HID_Write(USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='A'){
         BoardCount=USBReadBuff[1];
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='a'){
         USBWriteBuff[0]=BoardCount;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='B'){
         BoardNumber   =USBReadBuff[1];
         PatternNumber =USBReadBuff[2];
         Addr          =USBReadBuff[3];
         IOData        =USBReadBuff[4]+(USBReadBuff[5]<<8);
         if(PatternNumber==0){
             if(0<=BoardNumber && BoardNumber<BoardCount && 0<=Addr && Addr<MaxAddr){
                 BoardData[BoardNumber].Brightness[Addr]=IOData;
                 TransferBitData(IOData , Addr ,1 ,BoardNumber);
                 }
             TransferBitData(64*Addr , Addr ,0 ,BoardNumber);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='b'){
         BoardNumber   =USBReadBuff[1];
         PatternNumber =USBReadBuff[2];
         Addr          =USBReadBuff[3];
         if(0<=BoardNumber && BoardNumber<BoardCount && 0<=Addr && Addr<MaxAddr){
             IOData = BoardData[BoardNumber].Brightness[Addr];
         }
         else{
                 IOData=0;
         }
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]= (IOData & 0xFF);
         USBWriteBuff[2]=((IOData>>8) & 0xFF);

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='C'){
         BoardNumber  =USBReadBuff[1];
         IOData        =USBReadBuff[2]+(USBReadBuff[3]<<8);
         if(0<=BoardNumber && BoardNumber<BoardCount){
              BoardData[BoardNumber].BaseCounter=IOData;
              TransferBitData(IOData , 0 ,4 ,BoardNumber);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='c'){
         BoardNumber   =USBReadBuff[1];
         if(0<=BoardNumber && BoardNumber<BoardCount){
             IOData = BoardData[BoardNumber].BaseCounter;
         }
         else{
                 IOData=0;
         }
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]= (IOData & 0xFF);
         USBWriteBuff[2]=((IOData>>8) & 0xFF);

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='D'){
         BoardNumber  =USBReadBuff[1];
         IOData       =USBReadBuff[2];
         if(0<=BoardNumber && BoardNumber<BoardCount){
              TransferBitData(IOData , 1 ,2 ,BoardNumber);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }

    else if(USBReadBuff[0]=='F'){
         BoardNumber  =USBReadBuff[1];
         IOData        =USBReadBuff[2];
         if(0<=BoardNumber && BoardNumber<BoardCount){
              BoardData[BoardNumber].PortSel=IOData;
              TransferBitData(IOData , 3 ,2 ,BoardNumber);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='f'){
         BoardNumber   =USBReadBuff[1];
         if(0<=BoardNumber && BoardNumber<BoardCount){
             IOData = BoardData[BoardNumber].PortSel;
         }
         else{
                 IOData=0;
         }
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]= (IOData & 0xFF);

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='G'){
         BoardNumber  =USBReadBuff[1];
         IOData        =USBReadBuff[2];
         if(0<=BoardNumber && BoardNumber<BoardCount){
              BoardData[BoardNumber].PWMSelector=IOData;
              TransferBitData(IOData , 4 ,2 ,BoardNumber);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='g'){
         BoardNumber   =USBReadBuff[1];
         if(0<=BoardNumber && BoardNumber<BoardCount){
             IOData = BoardData[BoardNumber].PWMSelector;
         }
         else{
                 IOData=0;
         }
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]= (IOData & 0xFF);

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='h'){
         BoardNumber   =USBReadBuff[1];

         USBWriteBuff[0]=0x0a;
         if(0<=BoardNumber && BoardNumber<BoardCount){
             for(i=0;i<16;i++){
                 IOData = BoardData[BoardNumber].ADData[i];
                 USBWriteBuff[1+2*i]= (IOData & 0xFF);
                 USBWriteBuff[2+2*i]=((IOData>>8) & 0xFF);
             }
         }

         HID_Write(&USBWriteBuff,64);
    }
     else if(USBReadBuff[0]=='I'){
         IOData        =USBReadBuff[1];
         //O_ENABLE=IOData;
         if(IOData=='1')
             O_ENABLE=1;
         else
             O_ENABLE=0;

         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
     else if(USBReadBuff[0]=='j'){
         BoardNumber   =USBReadBuff[1];
         IOData = GetRegData(14,0 ,BoardNumber);
         if(0<=BoardNumber && BoardNumber<BoardCount){
             if((IOData & 0x01)!=0)
                 BoardData[BoardNumber].InputData[0]=1;
             else
                 BoardData[BoardNumber].InputData[0]=0;
             if((IOData & 0x02)!=0)
                 BoardData[BoardNumber].InputData[1]=1;
             else
                 BoardData[BoardNumber].InputData[1]=0;
             if((IOData & 0x04)!=0)
                 BoardData[BoardNumber].InputData[2]=1;
             else
                 BoardData[BoardNumber].InputData[2]=0;
             if((IOData & 0x08)!=0)
                 BoardData[BoardNumber].InputData[3]=1;
             else
                 BoardData[BoardNumber].InputData[3]=0;

             USBWriteBuff[1]=BoardData[BoardNumber].InputData[0];
             USBWriteBuff[2]=BoardData[BoardNumber].InputData[1];
             USBWriteBuff[3]=BoardData[BoardNumber].InputData[2];
             USBWriteBuff[4]=BoardData[BoardNumber].InputData[3];
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='K'){
         BoardNumber  =USBReadBuff[1];
         PortNumber   =USBReadBuff[2];
         if(0<=BoardNumber && BoardNumber<BoardCount && 0<=PortNumber && PortNumber<2){
             BoardData[BoardNumber].EPROMData[PortNumber].UsageLines=USBReadBuff[3];
             LineNumber=USBReadBuff[4];
             if(0<=LineNumber && LineNumber<DimCountOfLineData){
                 BoardData[BoardNumber].EPROMData[PortNumber].LineData[LineNumber].ColorType = USBReadBuff[5];
                 BoardData[BoardNumber].EPROMData[PortNumber].LineData[LineNumber].MaxCurrent= USBReadBuff[6] + (USBReadBuff[7]<<8);
             }
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='k'){
         BoardNumber  =USBReadBuff[1];
         PortNumber   =USBReadBuff[2];
         LineNumber   =USBReadBuff[3];
         if(0<=BoardNumber && BoardNumber<BoardCount && 0<=PortNumber && PortNumber<2){
             USBWriteBuff[1]=BoardData[BoardNumber].EPROMData[PortNumber].UsageLines;
             if(0<=LineNumber && LineNumber<DimCountOfLineData){
                 USBWriteBuff[2]=BoardData[BoardNumber].EPROMData[PortNumber].LineData[LineNumber].ColorType;
                 USBWriteBuff[3]=BoardData[BoardNumber].EPROMData[PortNumber].LineData[LineNumber].MaxCurrent & 0xFF;
                 USBWriteBuff[4]=(BoardData[BoardNumber].EPROMData[PortNumber].LineData[LineNumber].MaxCurrent>>8) & 0xFF;
             }
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='L'){
         BoardNumber  =USBReadBuff[1];
         PortNumber   =USBReadBuff[2];
         WriteLightEPRom(BoardNumber,PortNumber);
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='l'){
         BoardNumber  =USBReadBuff[1];
         PortNumber   =USBReadBuff[2];
         if(0<=BoardNumber && BoardNumber<BoardCount && 0<=PortNumber && PortNumber<2){
             STAT=1;
             USBWriteBuff[1]=ReadLightEPRomStatus(BoardNumber,PortNumber);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='M'){                //Read from EPROM
         BoardNumber  =USBReadBuff[1];
         PortNumber   =USBReadBuff[2];
         if(ReadLightEPRom(BoardNumber,PortNumber)==TRUE)
             USBWriteBuff[1]=1;
         else
             USBWriteBuff[1]=0;
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='m'){          //Send any DATA in FPGA reg
         BoardNumber  =USBReadBuff[1];
         Addr         =USBReadBuff[2];    //Address
         Cmd          =USBReadBuff[3];
         if(0<=BoardNumber && BoardNumber<BoardCount){
             IOData = GetRegData(Cmd,Addr ,BoardNumber);
         }
         else{
                 IOData=0;
         }
         USBWriteBuff[1]= IOData & 0xFF;
         USBWriteBuff[2]=(IOData>>8)&0xFF;
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='N'){         //Test LED
         BoardNumber  =USBReadBuff[1];
         IOData       =USBReadBuff[2];
         TransferBitData(IOData, 1 ,2 ,BoardNumber);
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='O'){         //Continuous lighting
         ContinuousMode=((long int)USBReadBuff[1])
                      +(((long int)USBReadBuff[2])<<8)
                      +(((long int)USBReadBuff[3])<<16)
                      +(((long int)USBReadBuff[4])<<24);

         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='P'){
         BoardNumber   =USBReadBuff[1];

         USBWriteBuff[0]=0x0a;
         SelectAD(BoardNumber);
         ReadAD_RegisterAndChannel(0x40+USBReadBuff[2] ,&USBWriteBuff[1] ,1);

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='Q'){
         IOData   =USBReadBuff[1];
         TransferBitData(IOData , 1 ,0 ,IODelivererID);
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='q'){
         IOData   =GetRegData(1,0 ,IODelivererID);
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]=IOData;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='R'){
         BoardNumber  =USBReadBuff[1];
         LineNumber   =USBReadBuff[2];
         USData       =((unsigned int)USBReadBuff[3]) + ((unsigned int)USBReadBuff[4]<<8);
         TransferBitData(USData , LineNumber ,2 ,BoardNumber);
         USData       =((unsigned int)USBReadBuff[5]) + ((unsigned int)USBReadBuff[6]<<8);
         TransferBitData(USData , LineNumber ,3 ,BoardNumber);

         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='r'){
         BoardNumber  =USBReadBuff[1];
         LineNumber   =USBReadBuff[2];
         USBWriteBuff[0]=0x0a;
         IOData   =GetRegData(2,LineNumber ,BoardNumber);
         USBWriteBuff[1]=IOData;
         USBWriteBuff[2]=IOData>>8;
         IOData   =GetRegData(3,LineNumber ,BoardNumber);
         USBWriteBuff[3]=IOData;
         USBWriteBuff[4]=IOData>>8;
         IOData   =GetRegData(4,LineNumber ,BoardNumber);
         USBWriteBuff[5]=IOData;
         USBWriteBuff[6]=IOData>>8;

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='S'){
         BoardNumber  =USBReadBuff[1];
         IOData       =((unsigned int)USBReadBuff[2]) + ((unsigned int)USBReadBuff[3]<<8);
         TransferBitData(IOData , 10 ,4 ,BoardNumber);
         USBWriteBuff[0]=0x0a;

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='s'){
         BoardNumber  =USBReadBuff[1];
         USBWriteBuff[0]=0x0a;
         IOData   =GetRegData(5,0 ,BoardNumber);
         USBWriteBuff[1]=IOData;
         USBWriteBuff[2]=IOData>>8;

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='T'){
         if(USBReadBuff[1]!=0)
             RelayON();
         else
             RelayOFF();
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='U'){
         BoardNumber  =USBReadBuff[1];
         USData       =((unsigned int)USBReadBuff[2]) + ((unsigned int)USBReadBuff[3]<<8);
         TransferBitData(USData , 9 ,4 ,BoardNumber);
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='u'){
         BoardNumber  =USBReadBuff[1];
         IOData   =GetRegData(4,0 ,BoardNumber);
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]=IOData;
         USBWriteBuff[2]=IOData>>8;

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='v'){
         IOData   =GetFrontVolume();
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]=IOData;
         USBWriteBuff[2]=IOData>>8;

         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='W'){
         if(USBReadBuff[1]!=0)
             ManualMode=1;
         else
             ManualMode=0;
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
    }
    else if(USBReadBuff[0]=='w'){
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]=ManualMode;

         HID_Write(&USBWriteBuff,64);
    }
   else if(USBReadBuff[0]=='x'){
         BoardNumber  =USBReadBuff[1];
         SelectAD(BoardNumber);
         ReadAD_Register(ADRegData);
         USBWriteBuff[0]=0x0a;
         for(i=0;i<10;i++){
             USBWriteBuff[1+i]=ADRegData[i];
         }
         HID_Write(&USBWriteBuff,64);
    }
}

void    SetIOAttr(void)
{
    GPIO_Digital_Output(&GPIOA_BASE,
                                       _GPIO_PINMASK_2
                                     | _GPIO_PINMASK_3
                                     | _GPIO_PINMASK_5
                                     | _GPIO_PINMASK_7
                                     | _GPIO_PINMASK_8);
    GPIO_Digital_Output(&GPIOB_BASE,   _GPIO_PINMASK_3
                                     | _GPIO_PINMASK_5
                                     | _GPIO_PINMASK_10
                                     | _GPIO_PINMASK_12
                                     | _GPIO_PINMASK_13
                                     | _GPIO_PINMASK_15

                                       );
    GPIO_Digital_Output(&GPIOC_BASE,   _GPIO_PINMASK_0
                                     | _GPIO_PINMASK_1
                                     | _GPIO_PINMASK_2
                                     | _GPIO_PINMASK_4
                                     | _GPIO_PINMASK_5

                                     | _GPIO_PINMASK_12
                                     | _GPIO_PINMASK_13);

    GPIO_Digital_Input (&GPIOA_BASE,   _GPIO_PINMASK_1
                                     | _GPIO_PINMASK_4
                                     | _GPIO_PINMASK_6
                                     | _GPIO_PINMASK_13
                                     | _GPIO_PINMASK_14
                                     | _GPIO_PINMASK_15);

    GPIO_Digital_Input (&GPIOB_BASE,   _GPIO_PINMASK_0
                                     | _GPIO_PINMASK_1
                                     | _GPIO_PINMASK_4
                                     | _GPIO_PINMASK_8
                                     | _GPIO_PINMASK_9
                                     | _GPIO_PINMASK_11
                                     | _GPIO_PINMASK_14 );

    GPIO_Digital_Input (&GPIOC_BASE,   _GPIO_PINMASK_9
                                     );
    ADC_Set_Input_Channel(_ADC_CHANNEL_0);
}

void    ReadSPI2(int Addr ,unsigned char Buff[] ,int Len)
{
    unsigned char   Cmd=3;
    int      i,L;

    O_SPI2_SCK   =0;
    //O_SPI2_SS    =0;
    WaitSlightlySPI();

    for(i=0;i<8;i++){
        if((Cmd&(0x80>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    for(i=0;i<16;i++){
        if((Addr&(0x8000>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    for(L=0;L<Len;L++){
        Buff[L]=0;
        for(i=0;i<8;i++){
            WaitSlightlySPI();
            O_SPI2_SCK=1;
            WaitSlightlySPI();
            if(I_SPI2_MISO==1)
                Buff[L] |= (0x80>>i);
            O_SPI2_SCK=0;
        }
    }
    WaitSlightlySPI();
    //O_SPI2_SS=1;
    WaitSlightlySPI();
}

void    WriteSPI2(int Addr ,unsigned char Buff[] ,int Len)
{
    unsigned char   Cmd=6;
    int      i,L;

    O_SPI2_SCK   =0;
    //O_SPI2_SS    =0;
    WaitSlightlySPI();

    for(i=0;i<8;i++){
        if((Cmd&(0x80>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    WaitSlightlySPI();
   // O_SPI2_SS=1;
    WaitSlightlySPI();
    //O_SPI2_SS    =0;
    WaitSlightlySPI();
    Cmd=2;
    for(i=0;i<8;i++){
        if((Cmd&(0x80>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    for(i=0;i<16;i++){
        if((Addr&(0x8000>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    for(L=0;L<Len;L++){
        if((Buff[L]&(0x8000>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    WaitSlightlySPI();
    //O_SPI2_SS=1;
    WaitSlightlySPI();

    //O_SPI2_SS    =0;
    WaitSlightlySPI();
    Cmd= 4;
    for(i=0;i<8;i++){
        if((Cmd&(0x80>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    WaitSlightlySPI();
    //O_SPI2_SS=1;
    WaitSlightlySPI();
}

int    GetStatusSPI2(void)
{
    unsigned char   Cmd=5;
    int      i;
    int      Ret=0;

    /*
    for(;;){
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
    }
    */

    O_SPI2_SCK   =0;
    //O_SPI2_SS    =0;
    WaitSlightlySPI();

    for(i=0;i<8;i++){
        if((Cmd&(0x80>>i))!=0)
            O_SPI2_MOSI=1;
        else
            O_SPI2_MOSI=0;
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    for(i=0;i<8;i++){
        WaitSlightlySPI();
        O_SPI2_SCK=1;
        WaitSlightlySPI();
        if(I_SPI2_MISO==1)
            Ret |= (0x80>>i);
        O_SPI2_SCK=0;
        WaitSlightlySPI();
    }
    WaitSlightlySPI();
    //O_SPI2_SS=1;
    WaitSlightlySPI();
    return Ret;
}
void    WriteLightEPRom(int BoardNumber,int PortNumber)
{
    int i,Addr;
    unsigned char LightID;

    TransferBitData(1<<PortNumber , 3 ,2 ,BoardNumber);

    LightID=0x47;
    WriteSPI2(0 ,&LightID ,1);
    WriteSPI2(1 ,&BoardData[BoardNumber].EPROMData[PortNumber].UsageLines ,1);
    Addr=2;
    for(i=0;i<DimCountOfLineData;i++){
        while(GetStatusSPI2()!=0){
            WaitSlightlySPI();
        }
        WriteSPI2(Addr ,&BoardData[BoardNumber].EPROMData[PortNumber].LineData[i].ColorType ,1);
        Addr++;
        WriteSPI2(Addr ,(unsigned char *)&BoardData[BoardNumber].EPROMData[PortNumber].LineData[i].MaxCurrent ,2);
        Addr+=2;
    }
}

BOOL    ReadLightEPRom(int BoardNumber,int PortNumber)
{
    int i,Addr;
    unsigned char LightID;

    TransferBitData(1<<PortNumber , 3 ,2 ,BoardNumber);

    ReadSPI2(0 ,&LightID ,1);
    if(LightID!=0x47)
        return FALSE;
    ReadSPI2(1 ,&BoardData[BoardNumber].EPROMData[PortNumber].UsageLines ,1);
    Addr=2;
    for(i=0;i<DimCountOfLineData;i++){
        ReadSPI2(Addr ,&BoardData[BoardNumber].EPROMData[PortNumber].LineData[i].ColorType ,1);
        Addr++;
        ReadSPI2(Addr ,(unsigned char *)&BoardData[BoardNumber].EPROMData[PortNumber].LineData[i].MaxCurrent ,2);
        Addr+=2;
    }
    return TRUE;
}

int     ReadLightEPRomStatus(int BoardNumber,int PortNumber)
{
    TransferBitData(1<<PortNumber , 3 ,2 ,BoardNumber);
    return GetStatusSPI2();
}

//-------------------------------------------------------------------

void    SendGain(int BoardNumber)
{
    unsigned int  HData;
    int      i;
    HData=0;
    for(i=0;i<16;i++){
        if((BoardData[BoardNumber].Gain[i]&0x01)!=0)
            HData |= 0x0001<<i;
    }
    TransferBitData(HData , 5 ,4 ,BoardNumber);

    HData=0;
    for(i=0;i<16;i++){
        if((BoardData[BoardNumber].Gain[i]&0x02)!=0)
            HData |= 0x0001<<i;
    }
    TransferBitData(HData , 6 ,4 ,BoardNumber);
}

void    SelectAD(int BoardNumber)
{
    TransferBitData(1 , 7 ,4 ,BoardNumber);
}

void   ReadAD_ChannelReadDirectly(unsigned char rdata[3])
{
    int  i,t;
    O_SPI1_SCK   =0;
    WaitSlightlyAD();
    //O_SPI1_SS    =0;
    O_ADCS = 1;
    WaitSlightlyAD();

    for(t=0;t<3;t++){
        rdata[t]=0;
        for(i=0;i<8;i++){
            O_SPI1_SCK=1;
            WaitSlightlyAD();
            if(I_SPI1_MISO!=0)
                rdata[t] |= 1<<(7-i);
            O_SPI1_SCK=0;
            WaitSlightlyAD();
        }
    }

    O_ADCS = 0;

    WaitSlightlyAD();
    WaitSlightlyAD();
    WaitSlightlyAD();
}

void   ReadAD_RegisterAndChannel(unsigned char cmd ,unsigned char rdata[] ,int datanumb)
{
    int  i,t;

    O_SPI1_SCK   =0;
    //O_SPI1_SS    =0;
    WaitSlightlyAD();
    O_ADCS = 1;
    WaitSlightlyAD();

    for(i=0;i<8;i++){
        if((cmd&(1<<(7-i)))!=0)
            O_SPI1_MOSI=1;
        else
            O_SPI1_MOSI=0;
        WaitSlightlyAD();
        O_SPI1_SCK=1;
        WaitSlightlyAD();
        O_SPI1_SCK=0;
        WaitSlightlyAD();
    }
    for(t=0;t<datanumb;t++){
        rdata[t]=0;
        for(i=0;i<8;i++){
            O_SPI1_SCK=1;
            WaitSlightlyAD();
            if(I_SPI1_MISO!=0)
                rdata[t] |= 1<<(7-i);
            O_SPI1_SCK=0;
            WaitSlightlyAD();
        }
    }
    O_ADCS = 0;

    WaitSlightlyAD();
    WaitSlightlyAD();
    WaitSlightlyAD();
}

void   WriteAD_RegisterAndChannel(unsigned char cmd ,unsigned char wdata[] ,int datanumb)
{
    int  i,t;

    O_SPI1_SCK   =0;
    //O_SPI1_SS    =0;
    WaitSlightlyAD();
    O_ADCS = 1;
    WaitSlightlyAD();

    for(i=0;i<8;i++){
        if((cmd&(1<<(7-i)))!=0)
            O_SPI1_MOSI=1;
        else
            O_SPI1_MOSI=0;
        WaitSlightlyAD();
        O_SPI1_SCK=1;
        WaitSlightlyAD();
        O_SPI1_SCK=0;
        WaitSlightlyAD();
    }

    for(t=0;t<datanumb;t++){
        for(i=0;i<8;i++){
            if((wdata[t]&(1<<(7-i)))!=0)
                O_SPI1_MOSI=1;
            else
                O_SPI1_MOSI=0;
            WaitSlightlyAD();
            O_SPI1_SCK=1;
            WaitSlightlyAD();
            O_SPI1_SCK=0;
            WaitSlightlyAD();
        }
    }
    O_ADCS = 0;

    WaitSlightlyAD();
    WaitSlightlyAD();
    WaitSlightlyAD();
}

void    ReadAD_Register(unsigned char RData[10])
{
    //unsigned char rdata[1];
    //int      i;

    ReadAD_RegisterAndChannel(0x50 ,RData ,10);
    /*
    for(i=0;i<10;i++){
        ReadAD_RegisterAndChannel(0x40+i ,rdata ,1);
        RData[i]=rdata[0];
    }
    */
}

void    StartAD(void)
{
    unsigned char rdata[1];
    ReadAD_RegisterAndChannel(0x47 ,rdata ,1);
    rdata[0] = 0xfd;
    WriteAD_RegisterAndChannel(0x67,rdata ,1);
    rdata[0] =2;
    WriteAD_RegisterAndChannel(0x68,rdata ,1);
}

void  ScanADData(int BoardNumber)
{
    unsigned char rdata[4];
    int      Adr;
    int      D;

    ReadAD_RegisterAndChannel(0x48 ,rdata ,1);
    if((rdata[0] & 0x01)==0){
        ReadAD_ChannelReadDirectly(rdata);
        if((rdata[0]&0x80)!=0){
            Adr=(rdata[0]&0x1f)-8;
            if(0<=Adr && Adr<MaxAddr){
                D=rdata[1];
                D<<=8;
                D |=rdata[2];
                BoardData[BoardNumber].ADData[Adr]=D;
                //O_TestBit=1;
                return;
            }
        }
    }
    //O_TestBit=0;
}

void  ScanADDataDirectly(int BoardNumber)
{
    unsigned char rdata[4];
    int      Adr;
    long     D;

    ReadAD_ChannelReadDirectly(rdata);
    if((rdata[0]&0x80)!=0){
        Adr=(rdata[0]&0x1f)-8;
        if(0<=Adr && Adr<MaxAddr){
            D=rdata[1];
            D<<=8;
            D |=rdata[2];
            BoardData[BoardNumber].ADSumData[Adr]+=D;
            BoardData[BoardNumber].ADSumCount[Adr]++;
            if(BoardData[BoardNumber].ADSumCount[Adr]==16){
                BoardData[BoardNumber].ADData[Adr] = (BoardData[BoardNumber].ADSumData[Adr]>>4);
                BoardData[BoardNumber].ADSumData[Adr]=0;
                BoardData[BoardNumber].ADSumCount[Adr]=0;
            }
        }
        else{
            O_Test=1;
            WaitSlightlyAD();
            O_Test=0;
        }
    }
}


long int ONTime=0;
#define       MaxONTime    5000000L

void  OutputTestLED(int BoardNumber ,int ON)
{
    if(ON!=0)
        TransferBitData(1 , 1 ,4 ,BoardNumber);
    else
        TransferBitData(0 , 1 ,4 ,BoardNumber);
}

void    RelayON(void)
{
    O_IOSPARE3=1;
}

void    RelayOFF(void)
{
    O_IOSPARE3=0;
}

void    ManageUSB(void)
{
    int      USBByte;

    USB_Polling_Proc();
    USBByte=HID_Read();
    if(USBByte!=0){
        AnalizeData();
    }
}

int ClipMinMax(int n,int MinN ,int MaxN)
{
    if(n<MinN)
        n=MinN;
    if(n>MaxN)
        n=MaxN;
    return n;
}

void SetEnableRangeDirect(int BoardNumber,int LineNumber,int n)
{
    int  HPos,LPos;
    LPos=ClipMinMax((23-n)*32-24-40-100 ,0,1023);
    HPos=ClipMinMax((23-n)*32+24+40-100 ,0,1023);

    TransferBitData(LPos , LineNumber ,2 ,BoardNumber);
    TransferBitData(HPos , LineNumber ,3 ,BoardNumber);
}

void  SWLamp(int ON)
{
    if(ON!=0)
        O_OuterLED0=1;
    else
        O_OuterLED0=0;
}

int  GetFrontSW(void)
{
    if(I_OuterSW==0)
        return 0;
    else
        return 1;
}

void InitialFrontVolume(void)
{
    ADC_Set_Input_Channel(_ADC_CHANNEL_0);
    ADC1_Init();
}

int  GetFrontVolume(void)
{
    return ADC1_Get_Sample(0);
}

void main()
{
    int      i,j,h,brd;
    int      IOData;
    long int      LoopCounter;
    unsigned char wdata[10];
    int      LastVolume;
    int      DiffValue;
    int      InputData[4];

    ContinuousMode=0;
    TestMode=0;
    ManualMode =0;
    InitialFrontVolume();
    HID_Enable(USBReadBuff, USBWriteBuff);

    SetIOAttr();

    for(i=0;i<sizeof(BoardData)/sizeof(BoardData[0]);i++){
        for(j=0;j<2;j++){
            BoardData[i].EPROMData[j].UsageLines=0;
            for(h=0;h<DimCountOfLineData;h++){
                BoardData[i].EPROMData[j].LineData[h].ColorType   =0xFF;
                BoardData[i].EPROMData[j].LineData[h].MaxCurrent  =0;
            }
        }
        for(j=0;j<MaxAddr;j++){
            BoardData[i].Brightness[j]  =0;
            BoardData[i].ADData[j]      =0;
            BoardData[i].Gain[j]        =0;
            BoardData[i].ADSumData[j]   =0;
            BoardData[i].ADSumCount[j]  =0;
        }
        BoardData[i].BaseCounter    =65535;
        BoardData[i].PortSel        =0;
        BoardData[i].PWMSelector    =0;
    }

    O_DATACLK    =0;
    O_SELECTOR   =0;
    O_DATAIN     =0;
    O_ENABLE     =0;
    O_RESET      =0;
    O_OUTUART    =0;

    O_OuterLED0  =0;
    O_OuterLED1  =0;
    O_OUTUART    =0;
    O_IOSPARE3   =0;
    O_AllADStart =0;
    O_Test       =0;

    ONTime       =0;

    ExecuteReset();
    WaitSlightly();

    //O_SPI1_SS    =1;
    O_SPI1_SCK   =0;
    //O_SPI2_SS    =1;
    O_SPI2_SCK   =0;

    //for(i=0;i<BoardCount;i++){
    //    TransferBitData(BoardData[i].BaseCounter , 0 ,2 ,i);
    //}

    //Set A/D Reset = 0
    for(brd=0;brd<BoardCount;brd++){
        TransferBitData(0 , 8 ,4 ,brd);
    }
    for(i=0;i<100;i++){
        WaitSlightlyAD();
    }
    //LED Lamp ON
    for(brd=0;brd<BoardCount;brd++){
        OutputTestLED(brd ,1);
    }

    //Set BaseCounter
    for(brd=0;brd<BoardCount;brd++){
        TransferBitData(65535 , 0 ,4 ,brd);
    }
    //Set A/D Reset = 1
    for(brd=0;brd<BoardCount;brd++){
        TransferBitData(1 , 8 ,4 ,brd);
    }
     //Set SelectPatternAB=0
    for(brd=0;brd<BoardCount;brd++){
        TransferBitData(0 , 10 ,4 ,brd);
    }
    for(brd=0;brd<BoardCount;brd++){
        SelectAD(brd);
        wdata[0]=0xFE;
        WriteAD_RegisterAndChannel(0x67 ,wdata ,1);

        wdata[0]=0x01;
        WriteAD_RegisterAndChannel(0x68 ,wdata ,1);    // A/D signal LED turns ON
    }

    //Test putput
    for(brd=0;brd<BoardCount;brd++){
        for(i=0;i<16;i++){
            //TransferBitData(5 , i ,1 ,brd);        //Output PWM
            TransferBitData(0 , i ,1 ,brd);        //Output PWM
        }
        TransferBitData(0xFFFF , 9 ,4 ,brd);           //Output port enable
    }

    O_ENABLE=0;

    //RelayON();
    
    //Test
    for(brd=0;brd<BoardCount;brd++){
        for(i=0;i<16;i++){
            BoardData[brd].Gain[i]=3;
        }
        SendGain(brd);
    }
    O_AllADStart=1;
         
    for(;;){
        for(brd=0;brd<BoardCount;brd++){
            SelectAD(brd);
            if(I_AllADReady==0){
                ScanADDataDirectly(brd);
            }
        }
        ManageUSB();
        if(GetFrontSW()!=0){
            Data=1;
            SWLamp(1);
            RelayON();
        }
        else{
            Data=0;
            SWLamp(0);
            RelayOFF();
        }
        if(ManualMode==1){
            O_ENABLE=1;
            IOData=GetFrontVolume();
            DiffValue=IOData-LastVolume;
            if(DiffValue<-5 || 5<DiffValue){
                for(brd=0;brd<BoardCount;brd++){
                    for(i=0;i<16;i++){
                        ManageUSB();
                        TransferBitData((50L*(long)IOData)/4096L , i ,1 ,brd);        //Output PWM
                    }
                }
            }
            LastVolume=IOData;
        }
        else{
             GetIO(0 ,InputData);
             if(InputData[0]==0)
                 O_ENABLE=1;
             else
                 O_ENABLE=0;
        }
    }
}