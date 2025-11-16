#include "DisplacementMeterILResource.h"
#include "DisplacementMeterForm.h"
#include "ui_DisplacementMeterForm.h"
#include "qextserialport.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XSequenceRepairLocal.h"

DisplacementMeterForm::DisplacementMeterForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::DisplacementMeterForm)
{
    ui->setupUi(this);
	CommPort	=6;
	sio			=NULL;
	oMeasured	=NULL;

	SysMeasuredNo	=187;
}

DisplacementMeterForm::~DisplacementMeterForm()
{
    delete ui;
}
void	DisplacementMeterForm::Prepare(void)
{
	OpenPort(CommPort);

	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				oMeasured		=new SignalOperandInt(this,SysMeasuredNo,/**/"DisplacementMeter:oMeasured");
				Param->SetSpecialOperand(oMeasured);
			}
		}
	}

}

bool	DisplacementMeterForm::OpenPort(int port)
{
	CommPort	=port;

	if(sio==NULL){
		int	Character=8;
		int	Parity=0;
		int	Stopbit=1;
		int	BPS	=9600;
		char *portName;
		PortSettings portSet;

		switch(CommPort){
			case 0:
				portName=/**/"COM1";
				break;
			case 1:
				portName=/**/"COM1";
				break;
			case 2:
				portName=/**/"COM2";
				break;
			case 3:
				portName=/**/"COM3";
				break;
			case 4:
				portName=/**/"COM4";
				break;
			case 5:
				portName=/**/"COM5";
				break;
			case 6:
				portName=/**/"COM6";
				break;
			case 7:
				portName=/**/"COM7";
				break;
			case 8:
				portName=/**/"COM8";
				break;
			case 9:
				portName=/**/"COM9";
				break;
			case 10:
				portName=/**/"COM10";
				break;
		}
		switch(Character){
			case 5:
				portSet.DataBits=DATA_5;
				break;
			case 6:
				portSet.DataBits=DATA_6;
				break;
			case 7:
				portSet.DataBits=DATA_7;
				break;
			case 8:
				portSet.DataBits=DATA_8;
				break;
		}
		switch(Parity){
			case 0:
				portSet.Parity=PAR_NONE;
				break;
			case 1:
				portSet.Parity=PAR_ODD;
				break;
			case 2:
				portSet.Parity=PAR_EVEN;
				break;
		}
		switch(Stopbit){
			case 1:
				portSet.StopBits=STOP_1;
				break;
			case 2:
				portSet.StopBits=STOP_2;
				break;
			case 3:
				portSet.StopBits=STOP_1_5;
				break;
		}
		switch(BPS){
			case 110:
				portSet.BaudRate=BAUD110;
				break;
			case 300:
				portSet.BaudRate=BAUD300;
				break;
			case 600:
				portSet.BaudRate=BAUD600;
				break;
			case 1200:
				portSet.BaudRate=BAUD1200;
				break;
			case 2400:
				portSet.BaudRate=BAUD2400;
				break;
			case 4800:
				portSet.BaudRate=BAUD4800;
				break;
			case 9600:
				portSet.BaudRate=BAUD9600;
				break;
			case 14400:
				portSet.BaudRate=BAUD14400;
				break;
			case 19200:
				portSet.BaudRate=BAUD19200;
				break;
			case 38400:
				portSet.BaudRate=BAUD38400;
				break;
			case 56000:
				portSet.BaudRate=BAUD56000;
				break;
			case 57600:
				portSet.BaudRate=BAUD57600;
				break;
			case 115200:
				portSet.BaudRate=BAUD115200;
				break;
		}
		portSet.FlowControl=FLOW_OFF;
		portSet.Timeout_Sec=1;
		portSet.Timeout_Millisec=0;
		sio=new QextSerialPort((const char*)portName,*((PortSettings const *)&portSet));
		sio->setDtr(true);
		sio->setRts(true);

		sio->open(QIODevice::ReadWrite);
	}
	return true;

}
	
bool	DisplacementMeterForm::ClosePort(void)
{
	if(sio!=NULL){
		sio->close();
		delete	sio;
		sio=NULL;
	}
	return true;
}

void DisplacementMeterForm::on_pushButtonZero_clicked()
{
	SendStr(/**/"SW,00,001\x0d\x0a");

	char	buff[200];
	GetStr(buff ,sizeof(buff));
}

void DisplacementMeterForm::on_pushButtonMeasure_clicked()
{
	SendStr(/**/"SR,00,037\x0d\x0a");

	char	buff[200];
	GetStr(buff ,sizeof(buff));
	QString	s=buff;
	QStringList	Ls=s.split(',');
	if(Ls.count()>=4){
		double	L=Ls[3].toDouble();
		ui->labelResult->setText(Ls[3]);
		if(oMeasured!=NULL){
			oMeasured->Set(L*1000);
		}
	}
}


int		DisplacementMeterForm::GetChar(void)
{
		char	buff[1];
	if(sio!=NULL && sio->bytesAvailable()>0){
		sio->read(buff,1);
		return (unsigned char)buff[0];
	}
	else{
		return -1;
	}
}
void	DisplacementMeterForm::SendChar(unsigned char d)
{
	if(sio!=NULL){
		sio->write((char *)&d,sizeof(d));
	}
}

	
bool	DisplacementMeterForm::SendStr(char *s)
{
	while(*s!=0){
		SendChar(*s);
		s++;
	}
	return true;
}

bool	DisplacementMeterForm::GetStr(char buff[] ,int maxlen)
{
	int	L=0;
	for(;;){
		int	c=GetChar();
		if(c>=0){
			buff[L]=c;
			L++;
			if(L>=maxlen){
				return true;
			}
			if(c=='\x0a'){
				if(buff[L-2]=='\x0d')
					buff[L-2]=0;
				else
					buff[L-1]=0;
				return true;
			}
		}
	}
}
