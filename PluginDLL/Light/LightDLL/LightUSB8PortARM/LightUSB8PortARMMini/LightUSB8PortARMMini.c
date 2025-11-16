
#define BitCount        8

sbit STAT     at ODR13_GPIOC_ODR_bit;
sbit DATA     at ODR12_GPIOC_ODR_bit;

sbit LEDClock     at ODR0_GPIOA_ODR_bit;       //PA0
sbit LEDDin       at ODR1_GPIOA_ODR_bit;       //PA1
sbit LEDStrobe    at ODR2_GPIOA_ODR_bit;       //PA2
sbit LEDEnable    at ODR3_GPIOA_ODR_bit;       //PA3
sbit LEDReset     at ODR4_GPIOA_ODR_bit;       //PA4

#define        ClearWDT       (WWDG_CR = 0b11111100)

char     USBReadBuff[68];
char     USBWriteBuff[68];

typedef  unsigned char    BYTE;
const        int                LEDBarCount=8;
const        int                LEDColumnCount=64;

char data_[256];

int     LEDBrightness[LEDBarCount][LEDColumnCount];
int     TurnedOn;
int     LED_ON;

void    TransferAll(void);
void    TransferBar(int BarNumber);
void    OutputLighting(int modeOn);
void    OutputLED(int brd ,int colum ,int value);
void    OutBit(int hbit, int bitdata);
void    StartLED(void);
void    Strobe(int H);
void    Clock(int H);
void    Reset(int H);
void    Enable(int H);
void    Din(int H);
void    OutBits(int d,int bitnumb);

void  WaitLoop(void)
{
    int  i;
    for(i=0;i<300;i++){}
    ClearWDT;
}

void        TransferAll(void)
{
    int i;
    for(i=0;i<LEDBarCount;i++){
        TransferBar(i);
    }
}

void        TransferBar(int BarNumber)
{
    int i;
    for(i=0;i<LEDColumnCount;i++){
        OutputLED(BarNumber ,i,LEDBrightness[BarNumber][i]);
        ClearWDT;
    }
}

void        OutputLED(int brd ,int colum ,int value)
{
        WaitLoop();
        Enable(0);
        Reset(1);
        WaitLoop();
        Reset(0);
        WaitLoop();
        Clock(0);
        WaitLoop();
        Strobe(1);
        WaitLoop();
        OutBits(brd,8);

        WaitLoop();
        OutBits(colum,8);
        WaitLoop();
        OutBits(value,8);

        WaitLoop();
        Clock(0);
        WaitLoop();
        Strobe(0);
        WaitLoop();

        Reset(0);
        Enable(1);
        WaitLoop();

        return;
}

void        OutputLighting(int modeOn)
{
        if(TurnedOn!=modeOn){
                Enable(modeOn);
                TurnedOn=modeOn;
        }
}

void        OutBit(int hbit, int bitdata)
{
     switch(hbit){
         case 0: if(bitdata==1)
                     LEDClock=1;
                 else
                     LEDClock=0;
                 break;
         case 1: if(bitdata==1)
                     LEDDin=1;
                 else
                     LEDDin=0;
                 break;
         case 2: if(bitdata==1)
                     LEDStrobe=1;
                 else
                     LEDStrobe=0;
                 break;
         case 3: if(bitdata==1)
                     LEDEnable=1;
                 else
                     LEDEnable=0;
                 break;
         case 4: if(bitdata==1)
                     LEDReset=1;
                 else
                     LEDReset=0;
                 break;
         }
    WaitLoop();
}

void        StartLED(void)
{
    Strobe(0);
    Clock(0);
    Enable(1);
    Enable(0);
    Enable(1);
    Reset(1);
    WaitLoop();
    Reset(0);
    Enable(0);
    Enable(1);
}


void    Strobe(int H)
{
    OutBit(2, H);
}

void    Clock(int H)
{
        OutBit(0, H);
}

void    Reset(int H)
{
        OutBit(4, H);
}

void    Enable(int H)
{
        OutBit(3, H);
}

void    Din(int H)
{
        OutBit(1, H);
}

void    OutBits(int d,int bitnumb)
{
     int    i;
        WaitLoop();
        for(i=bitnumb-1;i>=0;i--){
                if((d&(((BYTE)0x01)<<i))!=0)
                        Din(1);
                else
                        Din(0);
                WaitLoop();
                WaitLoop();
                Clock(1);
                WaitLoop();
                WaitLoop();
                Clock(0);
                WaitLoop();
        }
}

//=====================================================================

void AnalizeData(int DataLen)
{
    int ptn,i,j;
    int BarNumber;
    int LEDNumber;
    int Value;

    if(USBReadBuff[0]=='V'){
        strcpy(USBWriteBuff,"MEGATRADE LightUSBPort8ARM Ver1.0");
        HID_Write(USBWriteBuff,64);
        ClearWDT;
    }
    else if(USBReadBuff[0]=='A'){
         if(USBReadBuff[1]=='1'){
             LED_ON=1;
             Enable(1);
         }
         else{
             LED_ON=0;
             Enable(0);
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
         STAT=1;
         ClearWDT;
    }
    else if(USBReadBuff[0]=='B'){
         BarNumber=USBReadBuff[1];
         LEDNumber=USBReadBuff[2];
         if(0<=BarNumber && BarNumber<LEDBarCount){
             for(j=0;j<32 && (j+LEDNumber)<LEDColumnCount;j++){
                 Value    =USBReadBuff[3+j];
                 LEDBrightness[BarNumber][LEDNumber+j]=Value;
             }
         }
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
         ClearWDT;
    }
    else if(USBReadBuff[0]=='C'){
         TransferAll();
         USBWriteBuff[0]=0x0a;
         HID_Write(&USBWriteBuff,64);
         ClearWDT;
    }
    else if(USBReadBuff[0]=='E'){
         BarNumber=USBReadBuff[1];
         LEDNumber=USBReadBuff[2];
         USBWriteBuff[0]=0x0a;
         USBWriteBuff[1]=BarNumber;
         USBWriteBuff[2]=LEDNumber;
         USBWriteBuff[3]=LEDBrightness[BarNumber][LEDNumber];
         HID_Write(&USBWriteBuff,64);
         ClearWDT;
    }
}

void main()
{
    int    USBByte;
    unsigned short     Ret;
    long     int      i;
    int      k;

     //‚±‚ê‚Íæ“ª‚É‹LÚ‚·‚é‚×‚«
    HID_Enable(USBReadBuff, USBWriteBuff);

    GPIO_Digital_Output(&GPIOA_BASE,   _GPIO_PINMASK_0
                                     | _GPIO_PINMASK_1
                                     | _GPIO_PINMASK_2
                                     | _GPIO_PINMASK_3
                                     | _GPIO_PINMASK_4 );
    GPIO_Digital_Output(&GPIOB_BASE,   _GPIO_PINMASK_12);
    GPIO_Digital_Output(&GPIOC_BASE,   _GPIO_PINMASK_12
                                     | _GPIO_PINMASK_13
                                     | _GPIO_PINMASK_0
                                     | _GPIO_PINMASK_1
                                     | _GPIO_PINMASK_2);

    StartLED();
/*
    while (1) {
        WaitLoop();
        LEDClock=0;
        WaitLoop();
        LEDClock=1;
    }
    while (1) {
        WaitLoop();
        LEDDin=0;
        WaitLoop();
        LEDDin=1;
    }
    while (1) {
        WaitLoop();
        LEDStrobe=0;
        WaitLoop();
        LEDStrobe=1;
    }
    while (1) {
        WaitLoop();
        LEDEnable=0;
        WaitLoop();
        LEDEnable=1;
    }
    while (1) {
        WaitLoop();
        LEDReset=0;
        WaitLoop();
        LEDReset=1;
    }
  */




    //RCC_APB1ENR.B11 = 1;            // Enable clock gating for Watchdog Timer 0 module
    //WWDG_CFR = 0x1FE;                   // Write window value to be compared to the downcounter
    ClearWDT;

    while (1) {
        DATA=1;
        USB_Polling_Proc();
        USBByte=HID_Read();
        if(USBByte!=0){
            AnalizeData(USBByte);
        }
    }
}