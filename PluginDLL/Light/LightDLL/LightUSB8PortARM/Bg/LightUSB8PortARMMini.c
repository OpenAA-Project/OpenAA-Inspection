
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

const        int                LEDCountInSheet=8;
const        int                LEDPatternCount=16;

char data_[256];



int     LEDBrightness[8][64];
int	BoardCount;

void	TransferBar(int BarNumber);


void  WaitLoop(void)
{
    int  i;
    for(i=0;i<100;i++){}
    ClearWDT;
}

void	TransferAll(void)
{
    int i;
    for(i=0;i<BoardCount;i++){
        TransferBar(i);
    }
}

void	TransferBar(int BarNumber)
{
    int i;
    for(i=0;i<ColumnCount;i++){
        OutputLED(BarNumber ,i,LEDBrightness[BarNumber][i]);
        ClearWDT;
    }
}

bool	OutputLED(int brd ,int colum ,int value)
{
	WaitLoop();
	Enable(false);
	Reset(true);
	WaitLoop();
	Reset(false);
	WaitLoop();
	Clock(false);
	WaitLoop();
	Strobe(true);
	WaitLoop();
	OutBits(brd,8);

	WaitLoop();
	OutBits((BYTE)colum,8);
	WaitLoop();
	OutBits((BYTE)value,8);

	WaitLoop();
	Clock(false);
	WaitLoop();
	Strobe(false);
	WaitLoop();

	Reset(false);
	Enable(true);
	WaitLoop();

	return true;
}

bool	OutputLighting(bool modeOn)
{
	if(TurnedOn!=modeOn){
		Enable(modeOn);
		TurnedOn=modeOn;
	}
	return true;
}

void	OutBit(int bit, bool data)
{
     switch(bit){
         case 0: if(data==true)
                     LEDClock=1;
                 else
                     LEDClock=0;
                 break;
         case 1: if(data==true)
                     LEDDin=1;
                 else
                     LEDDin=0;
                 break;
         case 2: if(data==true)
                     LEDStrobe=1;
                 else
                     LEDStrobe=0;
                 break;
         case 3: if(data==true)
                     LEDEnable=1;
                 else
                     LEDEnable=0;
                 break;
         case 4: if(data==true)
                     LEDReset=1;
                 else
                     LEDReset=0;
                 break;
         }
    WaitLoop();
}

void	Start(void)
{
    Strobe(false);
    Clock(false);
    Enable(true);
    Enable(false);
    Enable(true);
    Reset(true);
    WaitLoop();
    Reset(false);
    Enable(false);
    Enable(true);
}


void    Strobe(bool H)
{
    OutBit(2, H);
}

void    Clock(bool H)
{
	OutBit(0, H);
}

void    Reset(bool H)
{
	OutBit(4, H);
}

void    Enable(bool H)
{
	OutBit(3, H);
}

void    Din(bool H)
{
	OutBit(1, H);
}


//=====================================================================

void AnalizeData(int DataLen)
{
    int ptn,i;
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
             Enable(true);
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
         Value    =USBReadBuff[3];
         LEDBrightness[BarNumber][LEDNumber]=Value;
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

    Start();

    RCC_APB1ENR.B11 = 1;            // Enable clock gating for Watchdog Timer 0 module
    WWDG_CFR = 0x1FE;                   // Write window value to be compared to the downcounter
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

