#include "TypeDefinition.h"
#include <QFile>
#include <QBuffer>
#include <QUrl>
#include "ActivationDialog.h"
#include "XGeneralFunc.h"
#include <QDir>
#include <QDateTime>
#include <QSettings>
#include <QCryptographicHash> 
#include "XSimpleCrypt.h"
#include <QByteArray>
#include "ActivationLib.h"
#include "XServiceRegSpector.h"

#define	RegistryPath	"HKEY_CURRENT_USER\\SOFTWARE"
#define	RegKey			/**/"Param"


//==================================================================================================
TypeDefinition::TypeDefinition(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ServerAddress		=/**/"ws://192.168.86.136:8800/ActivationSocket";
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Activate";
	WaitingMilisec=10000;

	CharColor	=Qt::white;
	NormalColor	=Qt::gray;
	PushedColor	=Qt::yellow;

	resize(80,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	connect(&Web, SIGNAL(connected()), this, SLOT(SlotWebConnected()));
}

TypeDefinition::~TypeDefinition(void)
{
}

void	TypeDefinition::Prepare(void)
{
 	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	GetLayersBase()->GetMainWidget()->setWindowTitle(ApplicationName);

    connect(&Web,SIGNAL(binaryMessageReceived(const QByteArray &)),this,SLOT(SlotBinaryMessageReceived(const QByteArray &)));
}

void	TypeDefinition::SlotClicked ()
{
	ActivationDialog	D(this);
	D.exec();
}

void	TypeDefinition::ResizeAction()
{
	Button.resize(width(),height());
}

void	TypeDefinition::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCheckByDate	*CmdCheckByDateVar=dynamic_cast<CmdCheckByDate *>(packet);
	if(CmdCheckByDateVar!=NULL){
		CmdCheckByDateVar->Result=IsActivated(CmdCheckByDateVar->SpanSecFromInstall);
		return;
	}
	CmdCheckActivated	*CmdCheckActivatedVar=dynamic_cast<CmdCheckActivated *>(packet);
	if(CmdCheckByDateVar!=NULL){
		CmdCheckActivatedVar->Result=IsActivated();
		return;
	}
}

void TypeDefinition::SlotBinaryMessageReceived(const QByteArray &message)
{
	QByteArrayList	Packet;
	{
		QBuffer	Buff((QByteArray *)&message);
		Buff.open(QIODevice::ReadOnly);
		::Load(&Buff,Packet);
	}
	if(Packet.count()>=1){
		Ack=Packet[0];
		if(Ack==/**/"NoLic"){
			//データベースに登録されていない
		}
		else
		if(Ack==/**/"OkLic" && Packet.count()>=2){
			QByteArray	LicenseData=Packet[1];
			RegisterActivation(LicenseData);
		}
		else
		if(Ack==/**/"Break"){
			//ライセンスデータ生成中にエラー
		}
		else
		if(Ack==/**/"NoMatch"){
			//以前登録したユーザー情報と異なる
		}
		else{
			Ack=/**/"";
		}
	}
	Received=true;
}
bool	TypeDefinition::RegisterActivation(const QByteArray	&LicenseData)
{
	QByteArray NumberStrHashTag=QCryptographicHash::hash(ApplicationHashTag.toUtf8(), QCryptographicHash::Sha512);
	QString	NumberStr=ConvDat2TxtCode(NumberStrHashTag);

	QSettings	Settings(RegistryPath, QSettings::NativeFormat);
	QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
	Settings.beginGroup(GroupName);
	
	QByteArray	Key=ConvDat2TxtCode(ApplicationHashTag.toUtf8());
	Settings.setValue(Key, LicenseData);

	return true;
}
TypeDefinition::ActivatedResult	TypeDefinition::IsActivated(qint64 SpanSecFromInstall)
{
	QByteArray NumberStrHashTag=QCryptographicHash::hash(ApplicationHashTag.toUtf8(), QCryptographicHash::Sha512);
	QString	NumberStr=ConvDat2TxtCode(NumberStrHashTag);

	QSettings	Settings(RegistryPath, QSettings::NativeFormat);
	QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
	Settings.beginGroup(GroupName);
	
	QByteArray	Key=ConvDat2TxtCode(ApplicationHashTag.toUtf8());
	if(Settings.contains(Key)==true){
		QByteArray EncLicenseData=Settings.value(Key).toByteArray();
		QByteArray	LicenseData=ConvYCode2Dat(EncLicenseData);

		QByteArrayList	RList;
		QBuffer	Buff(&LicenseData);
		Buff.open(QIODevice::ReadOnly);
		if(::Load(&Buff,RList)==true && RList.count()>=5){
			QString	LApplicationHashTag=RList[0];
			int32	StartTm	=*((int32 *)RList[1].data());
			int32	EndTm	=*((int32 *)RList[2].data());

			if(LApplicationHashTag!=ApplicationHashTag){
				return TypeDefinition::_AR_DestroyedRegistry;
			}

			int32	CurrentTm	=QDate::currentDate().toJulianDay();
			if(SpanSecFromInstall<0){
				if(CurrentTm<StartTm || EndTm<CurrentTm){
					return TypeDefinition::_AR_ExpiredByDate;
				}
			}
			else{
				if(CurrentTm<StartTm || EndTm<(StartTm+(SpanSecFromInstall/(24*3600)))){
					return TypeDefinition::_AR_ExpiredByDate;
				}
			}

			QByteArray	LicenseKey	=RList[3];
			QByteArray	UserInfo	=ConvYCode2Dat(RList[4]);

			QBuffer	RBuff(&UserInfo);
			if(RBuff.open(QIODevice::ReadOnly)==false){
				return TypeDefinition::_AR_DestroyedRegistry;
			}
			SerialNumberClass	LicenseInst;
			if(LicenseInst.Load(&RBuff)==false){
				return TypeDefinition::_AR_DestroyedRegistry;
			}

			SerialNumberClass	CurrentAuthenticatedUser;
			if(GetWMicFunc(CurrentAuthenticatedUser)==false){
				return TypeDefinition::_AR_ErrorHardware;
			}
			if(CurrentAuthenticatedUser.isMatch(LicenseInst)==false){
				return TypeDefinition::_AR_NoMatchActivation;
			}

			return TypeDefinition::_AR_ActivatedOK;
		}
	}
	return TypeDefinition::_AR_NoRegistration;
}

void	TypeDefinition::SlotWebConnected()
{
}
bool	TypeDefinition::ActivateByOrderCode(const QString &LicenseKeyStr)
{
	return ActivationByOrderCode(LicenseKeyStr.toUtf8());
}

bool	TypeDefinition::ActivationByOrderCode(const QByteArray &LicenseKey)
{
	Web.open(QUrl(ServerAddress));

	QElapsedTimer	TM;
	TM.start();
	while(TM.hasExpired(WaitingMilisec)==false){
		if(Web.state()==QAbstractSocket::ConnectedState){
			break;
		}
		QCoreApplication::processEvents();
	}

	if(Web.isValid()==true){
		QByteArrayList	DataList;
		DataList.append(QByteArray("1",1));
		DataList.append(LicenseKey);
		DataList.append(ApplicationHashTag.toUtf8());

		SerialNumberClass	AuthenticatedUser;	
		if(GetWMicFunc(AuthenticatedUser)==false){
			return false;
		}

		{
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);
			AuthenticatedUser.Save(&Buff);
			QByteArray	AuthenticatedUserData=ConvDat2YCode(Buff.buffer());
			DataList.append(AuthenticatedUserData);
		}
		QByteArray	Packet;
		{
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);
			::Save(&Buff,DataList);
			Packet=Buff.buffer();
		}
		Received=false;
		Web.sendBinaryMessage(Packet);

		QElapsedTimer	TM;
		TM.start();
		while(TM.hasExpired(WaitingMilisec)==false){
			if(Received==true){
				break;
			}
			QCoreApplication::processEvents();
		}
		if(Ack==/**/"OkLic"){
			return true;
		}
	}
	return false;
}
bool	TypeDefinition::ActivateByLicenseFile(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	QByteArray	LicenseKey=File.readAll();

	return ActivationByOrderCode(LicenseKey);
}
bool	TypeDefinition::ActivateByCode(const QString &ActivationCodeStr)
{
	QByteArray	LicenseData=ConvYCode2Dat(ActivationCodeStr.toUtf8());

	QByteArray NumberStrHashTag=QCryptographicHash::hash(ApplicationHashTag.toUtf8(), QCryptographicHash::Sha512);
	QString	NumberStr=ConvDat2TxtCode(NumberStrHashTag);

	QSettings	Settings(RegistryPath, QSettings::NativeFormat);
	QString		GroupName=QString(/**/"Regulus64_")+NumberStr;
	Settings.beginGroup(GroupName);
	
	QByteArray	Key=ConvDat2TxtCode(ApplicationHashTag.toUtf8());
	//if(Settings.contains(Key)==false){
		Settings.setValue(Key, LicenseData);
		return true;
	//}
}
QString	TypeDefinition::GetPCCode(void)
{
	SerialNumberClass	CurrentAuthenticatedUser;
	if(GetWMicFunc(CurrentAuthenticatedUser)==false){
		return "";
	}
	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	CurrentAuthenticatedUser.Save(&Buff);
	QByteArray	PCInfo=ConvDat2YCode(Buff.buffer());
	return PCInfo;
}

bool	TypeDefinition::SavePCInfo	(const QString &LicenseKey ,const QString &FileName)
{
	QByteArrayList	DataList;
	DataList.append(QByteArray("1",1));
	DataList.append(LicenseKey.toUtf8());
	DataList.append(ApplicationHashTag.toUtf8());

	SerialNumberClass	AuthenticatedUser;	
	if(GetWMicFunc(AuthenticatedUser)==false){
		return false;
	}

	{
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		AuthenticatedUser.Save(&Buff);
		QByteArray	AuthenticatedUserData=Buff.buffer();
		DataList.append(ConvDat2YCode(AuthenticatedUserData));
	}

	QFile	File(FileName);
	File.open(QIODevice::WriteOnly);
	return ::Save(&File,DataList);
}

bool	TypeDefinition::LoadActivation(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	QByteArray	LicenseData=File.readAll();
	
	RegisterActivation(LicenseData);
}