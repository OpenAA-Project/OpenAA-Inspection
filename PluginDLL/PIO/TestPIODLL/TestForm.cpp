#include "TestForm.h"
#include "ui_TestForm.h"
#include "swap.h"
#include "windows.h"
#include "CDio.h"
#include "XCriticalFunc.h"
QMutex		TestForm::IOAccess;

TestForm::TestForm(short _BoardID ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
	BoardID=_BoardID;

	BitCountIn=0;
	BitCountOut=0;
	LastAccessTime=0;

	short InPortNum;
	short OutPortNum;
	long Ret;

	Ret = DioGetMaxPorts(BoardID, &InPortNum, &OutPortNum);
	if(Ret==DIO_ERR_SUCCESS){
		BitCountIn	=InPortNum*8;
		BitCountOut	=OutPortNum*8;

		SetupForm();
	}
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::SetupForm(void)
{
	int	StepY=15;

	OutputBit[0]=ui->checkBoxOutput0;
	for(int i=1;i<BitCountOut;i++){
		OutputBit[i]=new QCheckBox(ui->frameOutput);
		OutputBit[i]->setObjectName(QString(/**/"checkBoxOutput")+QString::number(i));
		OutputBit[i]->setText(QString("Bit")+QString::number(i));
		OutputBit[i]->move(ui->checkBoxOutput0->geometry().left()
						,  ui->checkBoxOutput0->geometry().top() + i*StepY);

		OutputBit[i]->resize(ui->checkBoxOutput0->width()
							,ui->checkBoxOutput0->height());
	}

	InputBit[0]=ui->checkBoxInputBit0;
	for(int i=1;i<BitCountIn;i++){
		InputBit[i]=new QCheckBox(ui->frameInput);
		InputBit[i]->setObjectName(QString(/**/"checkBoxInputBit")+QString::number(i));
		InputBit[i]->setText(QString("Bit")+QString::number(i));
		InputBit[i]->move(ui->checkBoxInputBit0->geometry().left()
						, ui->checkBoxInputBit0->geometry().top() + i*StepY);

		InputBit[i]->resize( ui->checkBoxInputBit0->width()
							,ui->checkBoxInputBit0->height());

		InputEnabled[i]=new QToolButton(ui->frameInput);
		InputEnabled[i]->setObjectName(QString(/**/"toolButtonInputEnabledBit")+QString::number(i));
		InputEnabled[i]->setText(QString::number(i));
		InputEnabled[i]->setCheckable(true);
		InputEnabled[i]->move(ui->toolButtonInputEnabledBit0->geometry().left()
							, ui->toolButtonInputEnabledBit0->geometry().top() + i*StepY);

		InputEnabled[i]->resize( ui->toolButtonInputEnabledBit0->width()
								,ui->toolButtonInputEnabledBit0->height());
		InputEnabledMode[i]=false;
	}

	for(int i=1;i<BitCountOut;i++){
		connect(InputBit[i]		,SIGNAL(clicked()),this,SLOT(on_checkBoxInput_clicked()));
		connect(InputEnabled[i]	,SIGNAL(clicked()),this,SLOT(on_toolButtonInputEnabled_clicked()));
	}
	int		YLen=max(BitCountOut*StepY+20,BitCountIn*StepY+20);
	ui->frameInput->resize(ui->frameInput->width(),YLen);
	ui->frameOutput->resize(ui->frameOutput->width(),YLen);

	resize(width(),ui->frameInput->geometry().top()+YLen+20);

	TM.setInterval(50);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();

}

void TestForm::on_toolButtonInputEnabled_clicked()
{

}

void TestForm::on_checkBoxInput_clicked()
{

}

BYTE  TestForm::PIOGetBit(BYTE bitIndex)
{
	if(InputEnabled[bitIndex]->isChecked()==false){
		long Ret;
		BYTE InData;

		IOAccess.lock();
		Ret = DioInpBit ( BoardID , bitIndex , &InData );
		IOAccess.unlock();
		return(InData);
	}
	else{
		if(InputBit[bitIndex]->isChecked()==true){
			return 1;
		}
		else
			return 0;
	}
}

BYTE  TestForm::PIOGetByte(BYTE byteIndex)
{
	BYTE ByteResult=0;

	for(int bit=0;bit<8;bit++){
		int	bitIndex=byteIndex*8+bit;
		if(InputEnabled[bitIndex]->isChecked()==false){
			long Ret;
			BYTE InData;
				
			IOAccess.lock();
			Ret = DioInpBit ( BoardID , bitIndex , &InData );
			IOAccess.unlock();
			if(InData!=0){
				ByteResult |= 0x01<<bit;
			}
		}
		else{
			if(InputBit[bitIndex]->isChecked()==true){
				ByteResult |= 0x01<<bit;
			}
		}
	}	
	return(ByteResult);
}

void	TestForm::SlotTimeout ()
{
	for(int i=1;i<BitCountOut;i++){
		BYTE	Data;
		IOAccess.lock();
		DioEchoBackBit(BoardID, i, &Data);
		IOAccess.unlock();
		if(Data==0){
			OutputBit[i]->setChecked(false);
		}
		else{
			OutputBit[i]->setChecked(true);
		}
	}
	for(int i=1;i<BitCountIn;i++){
		if(InputEnabled[i]->isChecked()==false){
			long Ret;
			BYTE InData;
				
			IOAccess.lock();
			Ret = DioInpBit ( BoardID , i , &InData );
			IOAccess.unlock();
			if(InData!=0){
				InputBit[i]->setChecked(true);
				InputedData[i]=1;
			}
			else{
				InputBit[i]->setChecked(false);
				InputedData[i]=0;
			}
			InputEnabledMode[i]=false;
		}
		else{
			if(InputBit[i]->isChecked()==true){
				InputedData[i]=1;
			}
			else{
				InputedData[i]=0;
			}
			InputEnabledMode[i]=true;
		}
	}
	LastAccessTime=::GetComputerMiliSec();
}

BYTE	TestForm::GetBufferedInBit(BYTE bitIndex)
{
	if(InputEnabledMode[bitIndex]==true){
		return InputedData[bitIndex];
	}
	else{
		long Ret;
		BYTE InData;
				
		IOAccess.lock();
		Ret = DioInpBit ( BoardID , bitIndex , &InData );
		IOAccess.unlock();
		return InData;
	}
}

BYTE	TestForm::GetBufferedInByte(BYTE byteIndex)
{
	BYTE	ResultByte=0;

	long Ret;
				
	IOAccess.lock();
	Ret = DioInpByte ( BoardID , byteIndex , &ResultByte);
	IOAccess.unlock();

	for(int bit=0;bit<8;bit++){
		if(InputEnabledMode[byteIndex*8+bit]==true){
			if(InputedData[byteIndex*8+bit]!=0){
				ResultByte |= 0x01<<bit;
			}
			else{
				ResultByte &= ~(0x01<<bit);
			}
		}
	}
	return ResultByte;
}