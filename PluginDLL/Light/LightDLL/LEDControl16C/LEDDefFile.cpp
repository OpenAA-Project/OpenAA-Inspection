#include "LEDControl16C.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <QMessageBox>


//----------------------------------------------------------------

bool	LEDControl16CPanel::LoadAllocationFile(QFile *f)
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