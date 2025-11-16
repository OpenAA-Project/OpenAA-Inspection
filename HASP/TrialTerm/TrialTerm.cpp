#include "TrialTerm.h"
#include "XHaspDLL.h"

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XGeneralFunc.h"
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>
#include "XDataInLayer.h"
#include "XAuthentication.h"
#include <QCryptographicHash> 
#include "XSimpleCrypt.h"

TrialTerm::TrialTerm(LayersBase *base)
	:ServiceForLayers(base)
{
}

#define	RegistryPath	"HKEY_CURRENT_USER\\SOFTWARE"
#define	RegKey			/**/"Param"
#define	CryptoKey		41267509334028634LL

TrialTerm::~TrialTerm(void)
{
}

bool3	TrialTerm::PermitByDate(const QString &DLLRoot ,const QString &DLLName
								,qint64 SpanSecFromInstall
								,const QString &_CurrentVersion
								,QString &FailMessage
								,int &ErrorCode)
{
	QString tCurrentVersion=_CurrentVersion;
	if(CurrentVersion.isEmpty()==true && _CurrentVersion.isEmpty()==false){
		CurrentVersion=_CurrentVersion;
	}
	if(CurrentVersion.isEmpty()==false && _CurrentVersion.isEmpty()==true){
		tCurrentVersion=CurrentVersion;
	}

	QString	NumberStr=GetLayersBase()->GetApplicationCode();

	QSettings	Settings(RegistryPath, QSettings::NativeFormat);
	QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
	Settings.beginGroup(GroupName);
	qint64 tm64;
	if(Settings.contains(RegKey)==false){
		SaveAgain:;
		QDateTime	LocalTime=QDateTime::currentDateTime();
		QString		StrLocalTime=LocalTime.toString("yyMMdd-hhmmss");
		//QDateTime	UtcTime = LocalTime.toUTC();
		//QString		StrUtcTime=UtcTime.toString("yyMMdd-hhmmss");
		//tm64=UtcTime.toSecsSinceEpoch();

		tm64=LocalTime.toSecsSinceEpoch();
		QString		StrTm64=QString::number(tm64);
		SimpleCrypt	Crypto(CryptoKey);

		QByteArray	Data((const char *)&tm64,sizeof(tm64));
		int32	Len=tCurrentVersion.length();
		Data.append((const char *)&Len,sizeof(Len));
		Data.append(tCurrentVersion.toUtf8());
		QByteArray HashCode=Crypto.encryptToByteArray(Data) ;

		Settings.setValue(RegKey, HashCode);
	}

	if(Settings.contains(RegKey)==false){
		return false3;
	}
	{
		QByteArray HashCode=Settings.value(RegKey).toByteArray();
		SimpleCrypt	Crypto(CryptoKey);
		QByteArray Data=Crypto.decryptToByteArray(HashCode) ;
		if(Data.length()<sizeof(qint64)+sizeof(int32))
			goto	SaveAgain;
		
		char	*fp	=Data.data();
		tm64		=*((qint64 *)fp);
		fp+=sizeof(tm64);
		int32	Len=*((int32 *)fp);
		fp+=sizeof(Len);
		QByteArray	Mid1=Data.mid(sizeof(tm64)+sizeof(Len));
		QString	Version=Mid1;

		if(Version!=tCurrentVersion && tCurrentVersion.isEmpty()==false){
			if(Version.toInt()<=tCurrentVersion.toInt()){
				goto	SaveAgain;
			}
			//return true3;
		}
		QString		StrTm64=QString::number(tm64);
		QTimeZone tz=QTimeZone::systemTimeZone();
		QDateTime t=QDateTime::fromSecsSinceEpoch(tm64, tz);
		QString		StrLocalTime=t.toString("yyMMdd-hhmmss");

		QDateTime	CurrentTime	  =QDateTime::currentDateTime();
		QString		StrCurrentTime=CurrentTime.toString("yyMMdd-hhmmss");

		qint64 d=t.daysTo(CurrentTime);
		if(d<=SpanSecFromInstall/(60*60*24.0)){
			return true3;
		}
		else{
			ErrorCode=Error_Authentic_InvalidTerm;
		}
	}
	return false3;
}
bool3	TrialTerm::PermitByProgram(const QString &ProgramCode
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)
{
	return none3;
}
bool3	TrialTerm::PermitByID(const QString &DLLRoot ,const QString &DLLName ,int id
							,const QString &_CurrentVersion
							,QString &FailMessage
							,int &ErrorCode)
{
	return none3;
}
void	TrialTerm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqTrialTermInfo	*CmdReqTrialTermInfoVar=dynamic_cast<CmdReqTrialTermInfo *>(packet);
	if(CmdReqTrialTermInfoVar!=NULL){
		QString	NumberStr=GetLayersBase()->GetApplicationCode();

		QSettings	Settings(RegistryPath, QSettings::NativeFormat);
		QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
		Settings.beginGroup(GroupName);
		qint64 tm64;
		if(Settings.contains(RegKey)==false){
			SaveAgain:;
			CmdReqTrialTermInfoVar->PassedDays=-1;
			return;
		}

		{
			QByteArray HashCode=Settings.value(RegKey).toByteArray();
			SimpleCrypt	Crypto(CryptoKey);
			QByteArray Data=Crypto.decryptToByteArray(HashCode) ;
			if(Data.length()<sizeof(qint64)+sizeof(int32))
				goto	SaveAgain;
			
			char	*fp	=Data.data();
			tm64		=*((qint64 *)fp);
			fp+=sizeof(tm64);
			int32	Len=*((int32 *)fp);
			fp+=sizeof(Len);
			QByteArray	Mid1=Data.mid(sizeof(tm64)+sizeof(Len));
			QString	Version=Mid1;

			QString		StrTm64=QString::number(tm64);
			QTimeZone tz=QTimeZone::systemTimeZone();
			QDateTime t=QDateTime::fromSecsSinceEpoch(tm64, tz);
			QString		StrTime=t.toString("yyMMdd-hhmmss");

			QDateTime	CurrentTime=QDateTime::currentDateTime();
			QString		StrCurrentTime=CurrentTime.toString("yyMMdd-hhmmss");

			qint64 d=t.daysTo(CurrentTime);
			CmdReqTrialTermInfoVar->PassedDays=d;
		}
		return;
	}
}

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLHaspMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="TrialTermDLL";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Hasp DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2021.06";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "TrialTerm control DLL";
}

HaspHandleContainer		*_cdecl	DLL_Initial(LayersBase *base,const QString &ParamStr)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	HaspHandleContainer	*H=new HaspHandleContainer();
	TrialTerm	*p=new TrialTerm(base);
	H->AppendList(p);
	return H;
}

bool		_cdecl	DLL_Close(HaspHandleContainer *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	HaspHandleContainer	*H=(HaspHandleContainer *)handle;
	if(H!=NULL){
		delete	H;
	}

	return true;
}
