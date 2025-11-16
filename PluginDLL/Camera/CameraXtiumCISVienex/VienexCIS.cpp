#include "CameraXtiumCISVienex.h"
#include "XGeneralFunc.h"
#include "VienexCIS.h"
#include "XCriticalFunc.h"

VienexCIS::VienexCIS(CameraXtiumCISVienex *p)
	:Parent(p)
{
	Sio=NULL;
	RxPoint			=0;
	WaitingMiliSec	=3000;

	CISVienexData.FPGA_VER			=1;

	CISVienexData.SHADING			=0;
	CISVienexData.DARK				=0;
	CISVienexData.SHADING_TARGET_VAL=1023;

	CISVienexData.CL_CONFIG			=0;
	CISVienexData.CL_FREQ			=3;

	CISVienexData.TRIG_CYCLE		=0;
	CISVienexData.SYNC_MODE			=0;

	CISVienexData.LED_ON_1_CYCLE	=0;
	CISVienexData.LED_ON_2_CYCLE	=0;
	CISVienexData.LED_CTRL_1		=0;
	CISVienexData.LED_CTRL_2		=0;
	CISVienexData.CONTINUOUS		=0;
	CISVienexData.LED1_ON			=0;
	CISVienexData.LED2_ON			=0;

	CISVienexData.LINE_ADJUST_DIRECTION	=0;
	CISVienexData.LINE_ADJUST_ON_OFF	=0;

	CISVienexData.D_RANGE		=1;
	CISVienexData.RES_SEL		=1;

	CISVienexData.GAIN_R		=0;
	CISVienexData.OFFSET_R		=0;
	CISVienexData.GAIN_G		=0;
	CISVienexData.OFFSET_G		=0;
	CISVienexData.GAIN_B		=0;
	CISVienexData.OFFSET_B		=0;

	CISVienexData.STAGGERED_SHIFT_DIRECTION	=0;
	CISVienexData.STAGGERED_SHIFT_ON_OFF	=0;
	CISVienexData.BASE_STAGGERED_SHIFT		=0;
	CISVienexData.ADD_STAGGERED_SHIFT_0 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_1 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_2 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_3 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_4 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_5 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_6 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_7 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_8 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_9 =0;
	CISVienexData.ADD_STAGGERED_SHIFT_10=0;
	CISVienexData.ADD_STAGGERED_SHIFT_11=0;
	CISVienexData.ADD_STAGGERED_SHIFT_12=0;
	CISVienexData.ADD_STAGGERED_SHIFT_13=0;
	CISVienexData.ADD_STAGGERED_SHIFT_14=0;
	CISVienexData.ADD_STAGGERED_SHIFT_15=0;
	CISVienexData.ADD_STAGGERED_SHIFT_16=0;
	CISVienexData.ADD_STAGGERED_SHIFT_17=0;

	CISVienexData.REMOVED_PIXELS_0 =0;
	CISVienexData.REMOVED_PIXELS_1 =0;
	CISVienexData.REMOVED_PIXELS_2 =0;
	CISVienexData.REMOVED_PIXELS_3 =0;
	CISVienexData.REMOVED_PIXELS_4 =0;
	CISVienexData.REMOVED_PIXELS_5 =0;
	CISVienexData.REMOVED_PIXELS_6 =0;
	CISVienexData.REMOVED_PIXELS_7 =0;
	CISVienexData.REMOVED_PIXELS_8 =0;
	CISVienexData.REMOVED_PIXELS_9 =0;
	CISVienexData.REMOVED_PIXELS_10=0;
	CISVienexData.REMOVED_PIXELS_11=0;
	CISVienexData.REMOVED_PIXELS_12=0;
	CISVienexData.REMOVED_PIXELS_13=0;
	CISVienexData.REMOVED_PIXELS_14=0;
	CISVienexData.REMOVED_PIXELS_15=0;
	CISVienexData.REMOVED_PIXELS_16=0;
	CISVienexData.REMOVED_PIXELS_17=0;

}

VienexCIS::~VienexCIS(void)
{
	Release();
}


bool	VienexCIS::Release(void)
{
	return true;
}


bool	VienexCIS::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(f->write((const char *)&CISVienexData,sizeof(CISVienexData))!=sizeof(CISVienexData))
		return false;
	return true;
}

bool	VienexCIS::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(f->read((char *)&CISVienexData,sizeof(CISVienexData))!=sizeof(CISVienexData))
		return false;

	//StoreToCamera(Sio);
	return true;
}
bool	VienexCIS::SendCom(QIODevice *f,char *Str)
{
	unsigned long	Len=strlen(Str);
	int	Ret;
	for(int i=0;i<Len;i++){
		char	c=Str[i];
		if(f->write((const char *)&c,1)!=1)
			return false;
		QSerialPort	*s=dynamic_cast<QSerialPort *>(f);
		if(s!=NULL){
			s->flush();
		}
		f->waitForBytesWritten(20);
		GSleep(10);
	}
	return true;
}

void	VienexCIS::SlotReadyRead()
{
	if(Sio!=NULL){
		int	Len=Sio->bytesAvailable();
		if(Sio->read(&RxData[RxPoint],Len)==Len){
			RxPoint+=Len;
		}
	}
}

bool	VienexCIS::ReceiveComm(QIODevice *f,char *Str,unsigned long MaxWaitingMilisec)
{
	int		StrLen=0;
	Str[0]=0;
	for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<MaxWaitingMilisec;){
		f->waitForReadyRead(10);
		//if(f->waitForReadyRead(MaxWaitingMilisec)==false)
		//	return false;
		memcpy(&Str[StrLen],RxData,RxPoint);
		StrLen+=RxPoint;
		Str[StrLen]=0;
		if(strchr(RxData,'\x0a')!=NULL){
			return true;
		}
	}
	return false;
}

bool	VienexCIS::SendCommand(QIODevice *f,int Addr ,DWORD Data)
{
	char	buff[100];
	GSleep(50);
	sprintf(buff,"W,%02X,%04X\n",Addr,Data);
	SendCom(f,buff);
	return true;
}
bool3	VienexCIS::ReqData(QIODevice *f,int Addr ,DWORD &Data)
{
	RxPoint=0;
	char	txbuff[100];
	GSleep(50);
	sprintf(txbuff,"R,%02X\n",Addr,Data);
	SendCom(f,txbuff);

	char	buff[100];
	if(ReceiveComm(f,buff,WaitingMiliSec)==false)
		return false3;
	char	*cp=strchr(buff,',');
	if(cp==NULL){
		if(buff[0]==0x15){
			return none3;
		}
		return false3;
	}
	cp++;
	sscanf(cp,"%x",&Data);
	return true3;
}


bool	VienexCIS::LoadFromCamera(QIODevice *f)
{
	DWORD	Data;
	bool3	r;
	if((r=ReqData(f,0 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.FPGA_VER=Data;
	}

	if((r=ReqData(f,0x36 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.SHADING		=(Data>>5)&0x01;
		CISVienexData.DARK			=(Data>>4)&0x01;
		CISVienexData.GET_SHADING	=(Data>>1)&0x01;
		CISVienexData.GET_DARK		=(Data>>0)&0x01;
		CISVienexData.AVE_NUM		=(Data>>8)&0x07;
	}
	if((r=ReqData(f,0x38 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.SET_MODE			=(Data>>12)&0x01;
		CISVienexData.SHADING_TARGET_VAL=(Data    )&0xFFF;
	}
	if((r=ReqData(f,0x3a ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.SHADING_TARGET_VAL_R	=Data&0xFFF;
	}
	if((r=ReqData(f,0x3c ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.SHADING_TARGET_VAL_G	=Data&0xFFF;
	}
	if((r=ReqData(f,0x3e ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.SHADING_TARGET_VAL_B	=Data&0xFFF;
	}

	if((r=ReqData(f,0x6a ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ODD_IC_MULTIPLIER	=Data;
	}
	if((r=ReqData(f,0x6a ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.EVEN_IC_MULTIPLIER	=Data;
	}


	if ((r = ReqData(f, 0x32, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.CL_CONFIG = (Data >> 4) & 0x0F;
		CISVienexData.CL_FREQ = Data & 0x03;
	}
	if ((r = ReqData(f, 0x6E, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.GRAY_SCALE_R = Data;
	}
	if ((r = ReqData(f, 0x70, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.GRAY_SCALE_G = Data;
	}
	if ((r = ReqData(f, 0x72, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.GRAY_SCALE_B = Data;
	}
	if ((r = ReqData(f, 0x1E, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.TRIG_CYCLE = Data;
	}
	if ((r = ReqData(f, 0x1C, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.SYNC_MODE = Data & 0x03;
	}

	if ((r = ReqData(f, 0x22, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.LED_ON_1_CYCLE = Data;
	}
	if ((r = ReqData(f, 0x24, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.LED_ON_2_CYCLE = Data;
	}
	if ((r = ReqData(f, 0x26, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.LED_CTRL_1 = Data & 0xFF;
	}
	if ((r = ReqData(f, 0x28, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.LED_CTRL_2 = Data & 0xFF;
	}
	if ((r = ReqData(f, 0x20, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.CONTINUOUS = (Data >> 8) & 0x01;
		CISVienexData.LED2_ON = (Data >> 4) & 0x01;
		CISVienexData.LED1_ON = (Data) & 0x01;
	}

	if ((r = ReqData(f, 0x40, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.LINE_ADJUST_DIRECTION = (Data >> 4) & 0x01;
		CISVienexData.LINE_ADJUST_ON_OFF = (Data) & 0x01;
	}
	if ((r = ReqData(f, 0x34, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.D_RANGE = (Data >> 8) & 0x01;
		CISVienexData.RES_SEL = (Data) & 0x01;
	}


	if ((r = ReqData(f, 0x88, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.GAIN_R = (Data >> 8) & 0x0F;
		CISVienexData.OFFSET_R = (Data) & 0x3F;
	}
	if ((r = ReqData(f, 0x8a, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.GAIN_G = (Data >> 8) & 0x0F;
		CISVienexData.OFFSET_G = (Data) & 0x3F;
	}
	if ((r = ReqData(f, 0x8c, Data)) == false3)
		return false;
	if (r == true3) {
		CISVienexData.GAIN_B = (Data >> 8) & 0x0F;
		CISVienexData.OFFSET_B = (Data) & 0x3F;
	}


	if((r=ReqData(f,0x42 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.STAGGERED_SHIFT_DIRECTION	=(Data>>4 )&0x01;
		CISVienexData.STAGGERED_SHIFT_ON_OFF	=(Data    )&0x01;
	}
	if((r=ReqData(f,0x44 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.BASE_STAGGERED_SHIFT	=(Data    )&0x1F;
	}
	if((r=ReqData(f,0x46 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_0	=Data&0x03;
	}
	if((r=ReqData(f,0x48 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_1	=Data&0x03;
	}
	if((r=ReqData(f,0x4a ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_2	=Data&0x03;
	}
	if((r=ReqData(f,0x4c ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_3	=Data&0x03;
	}
	if((r=ReqData(f,0x4e ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_4	=Data&0x03;
	}
	if((r=ReqData(f,0x50 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_5	=Data&0x03;
	}
	if((r=ReqData(f,0x52 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_6	=Data&0x03;
	}
	if((r=ReqData(f,0x54 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_7	=Data&0x03;
	}
	if((r=ReqData(f,0x56 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_8	=Data&0x03;
	}
	if((r=ReqData(f,0x58 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_9	=Data&0x03;
	}
	if((r=ReqData(f,0x5a ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_10=Data&0x03;
	}
	if((r=ReqData(f,0x5c ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_11=Data&0x03;
	}
	if((r=ReqData(f,0x5e ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_12=Data&0x03;
	}
	if((r=ReqData(f,0x60 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_13=Data&0x03;
	}
	if((r=ReqData(f,0x62 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_14=Data&0x03;
	}
	if((r=ReqData(f,0x64 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_15=Data&0x03;
	}
	if((r=ReqData(f,0x66 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_16=Data&0x03;
	}
	if((r=ReqData(f,0x68 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.ADD_STAGGERED_SHIFT_17=Data&0x03;
	}

	if((r=ReqData(f,0x74 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVE_OVERLAPPING_PIXELS_ON_OFF=Data&0x01;
	}
	if((r=ReqData(f,0x76 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_0	= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_1	=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x78 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_2	= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_3	=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x7a ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_4	= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_5	=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x7c ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_6	= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_7	=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x7e ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_8	= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_9	=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x80 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_10	= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_11	=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x82 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_12= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_13=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x84 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_14= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_15=(Data>>8)&0x0F;
	}
	if((r=ReqData(f,0x86 ,Data))==false3)
		return false;
	if(r==true3){
		CISVienexData.REMOVED_PIXELS_16= Data    &0x0F;
		CISVienexData.REMOVED_PIXELS_17=(Data>>8)&0x0F;
	}







	return true;
}

bool	VienexCIS::StoreToCamera(QIODevice *f)
{
	//DWORD	D1E =0;
	//SendCommand(f,0x1E ,D1E);
	//DWORD	D1C =0;
	//SendCommand(f,0x1C ,D1C);
	//DWORD	D32 =(CISVienexData.CL_CONFIG<<4)
	//			+(CISVienexData.CL_FREQ&0x03);
	//SendCommand(f,0x32 ,D32);
	//
	//DWORD	D6E =(CISVienexData.GRAY_SCALE_R);
	//SendCommand(f,0x6E ,D6E);
	//DWORD	D70 =(CISVienexData.GRAY_SCALE_G);
	//SendCommand(f,0x70 ,D70);
	//DWORD	D72 =(CISVienexData.GRAY_SCALE_B);
	//SendCommand(f,0x72 ,D72);
	//
	//D1E =(CISVienexData.TRIG_CYCLE);
	//SendCommand(f,0x1E ,D1E);
	//D1C =(CISVienexData.SYNC_MODE);
	//SendCommand(f,0x1C ,D1C);
	//
	//DWORD	D22 =CISVienexData.LED_ON_1_CYCLE;
	//SendCommand(f,0x22 ,D22);
	//DWORD	D24 =CISVienexData.LED_ON_2_CYCLE;
	//SendCommand(f,0x24 ,D24);
	//DWORD	D26 =CISVienexData.LED_CTRL_1;
	//SendCommand(f,0x26 ,D26);
	//DWORD	D28 =CISVienexData.LED_CTRL_2;
	//SendCommand(f,0x28 ,D28);
	//DWORD	D20 =(CISVienexData.CONTINUOUS<<8)
	//			+(CISVienexData.LED2_ON<<4)
	//			+(CISVienexData.LED1_ON&0x01);
	//SendCommand(f,0x20 ,D20);
	//
	//DWORD	D40 =(CISVienexData.LINE_ADJUST_DIRECTION<<4)
	//			+(CISVienexData.LINE_ADJUST_ON_OFF&0x01);
	//SendCommand(f,0x40 ,D40);
	//
	//DWORD	D34 =(CISVienexData.D_RANGE<<4)
	//			+(CISVienexData.RES_SEL&0x01);
	//SendCommand(f,0x34 ,D34);

	DWORD	D88 =(CISVienexData.GAIN_R<<8)
				+(CISVienexData.OFFSET_R&0x3F);
	SendCommand(f,0x88 ,D88);
	DWORD	D8a =(CISVienexData.GAIN_G<<8)
				+(CISVienexData.OFFSET_G&0x3F);
	SendCommand(f,0x8a ,D8a);
	DWORD	D8c =(CISVienexData.GAIN_B<<8)
				+(CISVienexData.OFFSET_B&0x3F);
	SendCommand(f,0x8c ,D8c);


	//DWORD	D36 =(CISVienexData.SHADING<<5)
	//			+(CISVienexData.DARK<<4)
	//			+(CISVienexData.GET_SHADING<<1)
	//			+(CISVienexData.GET_DARK)
	//			+(CISVienexData.AVE_NUM<<8);
	//SendCommand(f,0x36 ,D36);
	//
	//DWORD	D38 =(CISVienexData.SET_MODE<<12)
	//			+(CISVienexData.SHADING_TARGET_VAL&0xFFF);
	//SendCommand(f,0x38 ,D38);
	//
	//DWORD	D3a =(CISVienexData.SHADING_TARGET_VAL_R&0xFFF);
	//SendCommand(f,0x3a ,D3a);
	//DWORD	D3c =(CISVienexData.SHADING_TARGET_VAL_G&0xFFF);
	//SendCommand(f,0x3c ,D3c);
	//DWORD	D3e =(CISVienexData.SHADING_TARGET_VAL_B&0xFFF);
	//SendCommand(f,0x3e ,D3e);
	//
	//DWORD	D6a =CISVienexData.ODD_IC_MULTIPLIER;
	//SendCommand(f,0x6a ,D6a);
	//DWORD	D6c =CISVienexData.EVEN_IC_MULTIPLIER;
	//SendCommand(f,0x6c ,D6c);


	return true;
}

bool	VienexCIS::LoadFromROMonCamera(QIODevice *f)
{
	DWORD	D04 =0x000+0x10+0x01;
	SendCommand(f,0x04 ,D04);
}


bool	VienexCIS::OpenComm(void)
{
	Sio=new QSerialPort();
	QString	portName=Parent->SerialPortName;
	int		Character=8;
	int		Parity=0;
	int		Stopbit=1;
	int		BPS=19200;

	Sio->setPortName(portName);

	switch(Character){
		case 5:
			Sio->setDataBits(QSerialPort::Data5);
			break;
		case 6:
			Sio->setDataBits(QSerialPort::Data6);
			break;
        case 7:
            Sio->setDataBits(QSerialPort::Data7);
            break;
        case 8:
            Sio->setDataBits(QSerialPort::Data8);
            break;
	}
	switch(Parity){
		case 0:
			Sio->setParity(QSerialPort::NoParity);
            break;
        case 1:
            Sio->setParity(QSerialPort::OddParity);
            break;
        case 2:
            Sio->setParity(QSerialPort::EvenParity);
            break;
	}
	switch(Stopbit){
        case 1:
			Sio->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            Sio->setStopBits(QSerialPort::TwoStop);
            break;
        case 3:
            Sio->setStopBits(QSerialPort::OneAndHalfStop);
			break;
	}
	Sio->setBaudRate(BPS);
	Sio->setFlowControl(QSerialPort::NoFlowControl);

	bool    Ret=false;
	if(Sio->open(QIODevice::ReadWrite)==false){
		delete	Sio;
		Sio=NULL;
		return false;
	}
	else{
		Ret=connect(Sio,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	}
	return true;
}

bool	VienexCIS::CloseComm(void)
{
	if(Sio!=NULL){
		Sio->close();
		delete	Sio;
		Sio=NULL;
	}
	return true;
}
bool	VienexCIS::StoreToCam(void)
{
	if(OpenComm()==false){
		return false;
	}
	StoreToCamera(Sio);
	CloseComm();
	return true;
}
bool	VienexCIS::LoadFromCam(void)
{
	if(OpenComm()==false){
		return false;
	}
	LoadFromCamera(Sio);
	CloseComm();
	return true;
}

bool	VienexCIS::LoadFromROMonCam(void)
{
	if(OpenComm()==false){
		return false;
	}
	LoadFromROMonCamera(Sio);
	CloseComm();
	return true;
}