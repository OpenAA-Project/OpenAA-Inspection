#include "LEDControl16GTester.h"
#include "XHidCommand.h"
#include "XGeneralFunc.h"
#include <QString>


LEDControl16GTester::LEDControl16GTester(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	Commander=HidCommand::Create((QWidget *)this);

    for(int i=0;i<MaxCountLEDPattern;i++){
		for(int j=0;j<16;j++){
			LEDPattern[i].LEDLine[j].BaseCounter=1000;
			LEDPattern[i].LEDLine[j].HighCounter=200;
		}
    }
    for(int i=0;i<16;i++){
		AnalogData[i]=0;
    }

}

LEDControl16GTester::~LEDControl16GTester()
{

}

bool	LEDControl16GTester::Open(void)
{
	if(Commander->OpenHid(0x1255, 0x0017,0)==false){
		return false;
	}
	return true;
}

void LEDControl16GTester::on_pushButtonReqVersion_clicked()
{
	QString	VersionStr;

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		Commander->SendStr((BYTE *)"V",1);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			VersionStr=((char *)RecData);
		}
		Commander->CloseHid();
		GSleep(10);
	}

	AccessHID.unlock();
	ui.lineEditVersion->setText(VersionStr);
}

void LEDControl16GTester::on_pushButtonReqAttr_clicked()
{
	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		Commander->SendStr((BYTE *)"R",1);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			bool	TestLED		=(RecData[1]==0)?false:true;
			bool	Reset		=(RecData[2]==0)?false:true;
			bool	PLSEnable	=(RecData[3]==0)?false:true;
					DipSW		=RecData[4];
			ui.checkBoxTestLED	->setChecked(TestLED);
			ui.checkBoxReset	->setChecked(Reset);
			ui.checkBoxPLSEnable->setChecked(PLSEnable);
			ui.lineEditDipSW	->setText(QString::number(DipSW));
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonSetAttr_clicked()
{
	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		bool	TestLED		=ui.checkBoxTestLED	->isChecked();
		bool	Reset		=ui.checkBoxReset	->isChecked();
		bool	PLSEnable	=ui.checkBoxPLSEnable->isChecked();

		BYTE	SndData[256];
		SndData[0]	='r';
		SndData[1]	=(TestLED==true)?1:0;
		SndData[2]	=(Reset==true)?1:0;
		SndData[3]	=(PLSEnable==true)?1:0;

		Commander->SendStr(SndData,4);
		GSleep(100);

		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonReqBaseCounter_clicked()
{
	int	PatternNo=ui.spinBoxPatternNo->value();

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='B';
		SndData[1]	=PatternNo;
		Commander->SendStr(SndData,2);

		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			for(int i=0;i<16;i++){
				int	d=RecData[2+i*2+0] + (RecData[2+i*2+1]<<8);
				LEDPattern[PatternNo].LEDLine[i].BaseCounter=d;

				::SetDataToTable(ui.tableWidget ,0,i ,QString::number(d),Qt::ItemIsEditable);
			}
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonSetBaseCounter_clicked()
{
	int	PatternNo=ui.spinBoxPatternNo->value();

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='b';
		SndData[1]	=PatternNo;
		for(int i=0;i<16;i++){
			QString	s=GetDataToTable(ui.tableWidget ,0,i);
			int	d=s.toInt();
			LEDPattern[PatternNo].LEDLine[i].BaseCounter=d;
			SndData[2+i*2+0]=d;
			SndData[2+i*2+1]=d>>8;
		}
		Commander->SendStr(SndData,34);
		GSleep(100);
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonReqHighCounter_clicked()
{
	int	PatternNo=ui.spinBoxPatternNo->value();

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='H';
		SndData[1]	=PatternNo;
		Commander->SendStr(SndData,2);

		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			for(int i=0;i<16;i++){
				int	d=RecData[2+i*2+0] + (RecData[2+i*2+1]<<8);
				LEDPattern[PatternNo].LEDLine[i].HighCounter=d;

				::SetDataToTable(ui.tableWidget ,1,i ,QString::number(d),Qt::ItemIsEditable);
			}
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonSetHighCounter_clicked()
{
	int	PatternNo=ui.spinBoxPatternNo->value();

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='h';
		SndData[1]	=PatternNo;
		for(int i=0;i<16;i++){
			QString	s=GetDataToTable(ui.tableWidget ,1,i);
			int	d=s.toInt();
			LEDPattern[PatternNo].LEDLine[i].HighCounter=d;
			SndData[2+i*2+0]=d;
			SndData[2+i*2+1]=d>>8;
		}
		Commander->SendStr(SndData,34);
		GSleep(100);
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonReqAnalog_clicked()
{
	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='A';
		SndData[1]	=0;
		Commander->SendStr(SndData,1);

		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			for(int i=0;i<16;i++){
				int	d=RecData[2+i*2+0] + (RecData[2+i*2+1]<<8);
				AnalogData[i]=d;
                ::SetDataToTable(ui.tableWidget ,3,i ,QString::number(d));
			}
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonReqBit_clicked()
{
	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='P';
		Commander->SendStr(SndData,1);

		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			int	FIO=RecData[1];
			ui.lineEditI_FIO	->setText(QString::number(FIO,16));

			int	RPInData=RecData[2];
			ui.lineEditI_IN	->setText(QString::number(RPInData,16));
			ui.checkBoxI_iCLK	->setChecked((RecData[3]&0x01)!=0?true:false);
			ui.checkBoxI_iCmdW	->setChecked((RecData[3]&0x02)!=0?true:false);
			ui.checkBoxI_iRESET	->setChecked((RecData[3]&0x04)!=0?true:false);
			ui.checkBoxI_iStrobe->setChecked((RecData[3]&0x08)!=0?true:false);

			int	Key=RecData[4];
			ui.lineEditKey->setText(QString::number(Key));
		}
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonOutRPOut_clicked()
{
    AccessHID.lock();
    if(Commander->IsOpened()==false)
        Open();
    if(Commander->IsOpened()==true){
        BYTE	SndData[256];
        SndData[0]	='o';
        SndData[1]	=1;
		int	d=ui.lineEditO_RPOut->text().toInt(NULL,16);
        SndData[2]	=d;
        Commander->SendStr(SndData,3);

		GSleep(100);
        Commander->CloseHid();
        GSleep(10);
    }
    AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonOutBit_clicked()
{
    AccessHID.lock();
    if(Commander->IsOpened()==false)
        Open();
    if(Commander->IsOpened()==true){
        BYTE	SndData[256];
        SndData[0]	='o';
        SndData[1]	=2;
		int	d=ui.lineEditO_FIO->text().toInt(NULL,16);
        SndData[2]	=d;
        Commander->SendStr(SndData,3);

		GSleep(100);
        Commander->CloseHid();
        GSleep(10);
    }
    AccessHID.unlock();
}

void LEDControl16GTester::on_checkBoxO_InRW_clicked()
{
    AccessHID.lock();
    if(Commander->IsOpened()==false)
        Open();
    if(Commander->IsOpened()==true){
        BYTE	SndData[256];
        SndData[0]	='o';
        SndData[1]	=10;
		bool	d=ui.checkBoxO_InRW->isChecked();
        SndData[2]	=(d==true)?1:0;
        Commander->SendStr(SndData,3);

		GSleep(100);
        Commander->CloseHid();
        GSleep(10);
    }
    AccessHID.unlock();
}

void LEDControl16GTester::on_checkBoxO_InClk_clicked()
{
    AccessHID.lock();
    if(Commander->IsOpened()==false)
        Open();
    if(Commander->IsOpened()==true){
        BYTE	SndData[256];
        SndData[0]	='o';
        SndData[1]	=11;
		bool	d=ui.checkBoxO_InClk->isChecked();
        SndData[2]	=(d==true)?1:0;
        Commander->SendStr(SndData,3);

		GSleep(100);
        Commander->CloseHid();
        GSleep(10);
    }
    AccessHID.unlock();
}

void LEDControl16GTester::on_checkBoxO_InCS_clicked()
{
    AccessHID.lock();
    if(Commander->IsOpened()==false)
        Open();
    if(Commander->IsOpened()==true){
        BYTE	SndData[256];
        SndData[0]	='o';
        SndData[1]	=12;
		bool	d=ui.checkBoxO_InCS->isChecked();
        SndData[2]	=(d==true)?1:0;
        Commander->SendStr(SndData,3);

		GSleep(100);
        Commander->CloseHid();
        GSleep(10);
    }
    AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonReqTargetValue_clicked()
{
    int	PatternNo=ui.spinBoxPatternNo->value();

    AccessHID.lock();
    if(Commander->IsOpened()==false)
        Open();
    if(Commander->IsOpened()==true){
        BYTE	SndData[256];
        SndData[0]	='T';
        SndData[1]	=PatternNo;
        Commander->SendStr(SndData,2);

        BYTE	RecData[256];
        int		ReceivedLen;
        GSleep(100);
        if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
            for(int i=0;i<16;i++){
                int	d=       RecData[2+i*3+0] 
					+ (((int)RecData[2+i*3+1])<<8)
					+ (((int)RecData[2+i*3+2])<<16);
                LEDPattern[PatternNo].LEDLine[i].TargetValue=d;

                ::SetDataToTable(ui.tableWidget ,2,i ,QString::number(d),Qt::ItemIsEditable);
            }
        }
        Commander->CloseHid();
        GSleep(10);
    }
    AccessHID.unlock();
}

void LEDControl16GTester::on_pushButtonSetTargetValue_clicked()
{
	int	PatternNo=ui.spinBoxPatternNo->value();

	AccessHID.lock();
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		BYTE	SndData[256];
		SndData[0]	='t';
		SndData[1]	=PatternNo;
		for(int i=0;i<16;i++){
			QString	s=GetDataToTable(ui.tableWidget ,2,i);
			int	d=s.toInt();
			LEDPattern[PatternNo].LEDLine[i].TargetValue=d;
			SndData[2+i*3+0]=d;
			SndData[2+i*3+1]=d>>8;
			SndData[2+i*3+2]=d>>16;
		}
		Commander->SendStr(SndData,50);
		GSleep(100);
		Commander->CloseHid();
		GSleep(10);
	}
	AccessHID.unlock();
}
