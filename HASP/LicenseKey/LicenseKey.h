#pragma once

#include "licensekey_global.h"
#include "XHaspLib.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"

class LicenseKey : public HaspHandle ,public ServiceForLayers
{
	QString CurrentVersion;
public:
    LicenseKey(LayersBase *base);
	~LicenseKey(void);

	virtual	bool3	PermitByDate(const QString &DLLRoot ,const QString &DLLName
															,qint64 SpanSecFromInstall
															,const QString &_CurrentVersion
															,QString &FailMessage
															,int &ErrorCode)	override;
	virtual	bool3	PermitByProgram(const QString &ProgramCode
															,const QString &_CurrentVersion
															,QString &FailMessage
															,int &ErrorCode)	override;
	virtual	bool3	PermitByID(const QString &DLLRoot ,const QString &DLLName, int id
															,const QString &_CurrentVersion
															,QString &FailMessage
															,int &ErrorCode)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	QString	encryption(const QString &plainData);
	bool	Decrypt(const QString &keyRaw
						,QString &decipheredMailAddress
						,QString &decipheredSoftware
						,QString &decipheredLimit
						,bool &LicenseTimeOK
						,QString &FailMessage
						,int &ErrorCode);
	QString checkDigit(const QString &data);
};

class	CmdReqLicenseKeyInfo: public GUIDirectMessage
{
public:
	QString	LicenseKeyStr;
	QString decipheredMailAddress;
	QString decipheredSoftware;
	QString decipheredLimit;
	bool	LoadedOK;
	bool	PassLicense;
	bool	LicenseTimeOK;
	int		LicensedYear ;
	int		LicensedMonth;
	int		LicensedDay  ;
	QString FailMessage	 ;
	int		ErrorCode;

	CmdReqLicenseKeyInfo(LayersBase *base)
		:GUIDirectMessage(base)
		{	
			LoadedOK		=false;	
			PassLicense		=false;	
			LicenseTimeOK	=false;
			ErrorCode		=0;
		}
};

class	CmdSetLicenseKeyInfo: public GUIDirectMessage
{
public:
	QString	LicenseKeyStr;
	bool	SavedOK;
	bool	PassLicense;
	QString	FailMessage;
	int		ErrorCode;

	CmdSetLicenseKeyInfo(LayersBase *base)
		:GUIDirectMessage(base)
		{	
			SavedOK		=false;
			PassLicense	=false;
			ErrorCode	=0;
		}
};