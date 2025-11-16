#include "LEDControl16A.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <QMessageBox>

LEDControl16APanel::LineValue::LineValue(void)
{
	Pointer		=NULL;
	BoardNumber	=-1;
	LineNumber	=-1;
	Value		=0;
}

bool	LEDControl16APanel::LineValue::Save(QIODevice *f)
{
	if(::Save(f,Value)==false)
		return false;
	if(::Save(f,Comment)==false)
		return false;
	return true;
}

bool	LEDControl16APanel::LineValue::Load(QIODevice *f)
{
	if(::Load(f,Value)==false)
		return false;
	if(::Load(f,Comment)==false)
		return false;
	return true;
}

//----------------------------------------------------------------

bool	LEDControl16APanel::LightPattern::Save(QIODevice *f)
{
	int32	N=sizeof(LineValues)/sizeof(LineValues[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(LineValues[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	LEDControl16APanel::LightPattern::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	int	i;
	for(i=0;i<N && i<sizeof(LineValues)/sizeof(LineValues[0]);i++){
		if(LineValues[i].Load(f)==false)
			return false;
	}
	for(;i<N;i++){
		LineValue	DummyData;
		if(DummyData.Load(f)==false)
			return false;
	}
	return true;
}

//----------------------------------------------------------------

LEDControl16APanel::PortData::PortData(void)
{
	UsageLines=8;
}


bool	LEDControl16APanel::PortData::Save(QIODevice *f)
{
	if(::Save(f,UsageLines)==false)
		return false;
	int32	PatternNumb=sizeof(PatternData)/sizeof(PatternData[0]);
	if(::Save(f,PatternNumb)==false)
		return false;
	for(int i=0;i<PatternNumb;i++){
		if(PatternData[i].Save(f)==false)
			return false;
	}
	if(::Save(f,Comment)==false)
		return false;
	return true;
}
bool	LEDControl16APanel::PortData::Load(QIODevice *f)
{
	if(::Load(f,UsageLines)==false)
		return false;
	int32	PatternNumb;
	if(::Load(f,PatternNumb)==false)
		return false;
	int	i;
	for(i=0;i<PatternNumb && i<sizeof(PatternData)/sizeof(PatternData[0]);i++){
		if(PatternData[i].Load(f)==false)
			return false;
	}
	for(;i<PatternNumb;i++){
		LightPattern	DummyData;
		if(DummyData.Load(f)==false)
			return false;
	}
	if(::Load(f,Comment)==false)
		return false;
	return true;
}

//----------------------------------------------------------------

bool	LEDControl16APanel::LoadAllocationFile(QFile *f)
{
	QTextStream	FStr(f);
	while(FStr.atEnd()==false){

		int	BoardNumber;
		int	Address;
		int	Color;
		int	MaxValue;
		QString	L=FStr.readLine();
		QStringList	BList=L.trimmed().split(QRegularExpression("[ \t,=]+"));
		if(BList.count()>=2 && BList[0].toUpper()=="BOARD"){
			bool	ok;
			BoardNumber=BList[1].toInt(&ok);
			if(ok==false){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
										,"Board number error");
				continue;
			}
			QString	A=FStr.readLine();
			QStringList	AList=A.trimmed ().split(QRegularExpression("[ \t,=]+"));
			if(AList.count()<2 || AList[0].toUpper()!="ADDRESS"){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
					,QString("Need address definition : Board-")+QString::number(BoardNumber));
				continue;
			}
			Address=AList[1].toInt(&ok);
			if(ok==false){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
										,QString("Address number error: Board-")+QString::number(BoardNumber) + QString("  Address-")+QString::number(Address));
				continue;
			}

			QString	C=FStr.readLine();
			QStringList	CList=C.trimmed ().split(QRegularExpression("[ \t,=]+"));
			if(CList.count()<2 || CList[0].toUpper()!="COLOR"){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
					,QString("Need Color definition : Board-")+QString::number(BoardNumber) + QString("  Address-")+QString::number(Address));
				continue;
			}
			Color=CList[1].toInt(&ok);
			if(ok==false){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
										,QString("Color number error: Board-")+QString::number(BoardNumber) + QString("  Address-")+QString::number(Address));
				continue;
			}

			QString	V=FStr.readLine();
			QStringList	VList=V.trimmed ().split(QRegularExpression("[ \t,=]+"));
			if(VList.count()<2 || VList[0].toUpper()!="MAXVALUE"){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
					,QString("Need MaxValue definition : Board-")+QString::number(BoardNumber) + QString("  Address-")+QString::number(Address));
				continue;
			}
			MaxValue=VList[1].toInt(&ok);
			if(ok==false){
				QMessageBox::warning(NULL,"Description error in LEDControl16A allocation file"
										,QString("MaxValue number error: Board-")+QString::number(BoardNumber) + QString("  Address-")+QString::number(Address));
				continue;
			}
			BoardData[BoardNumber].EPROMData[0].LineData[Address].ColorType		=Color;
			BoardData[BoardNumber].EPROMData[0].LineData[Address].MaxCurrent	=MaxValue;		
		}
	}
	return true;
}