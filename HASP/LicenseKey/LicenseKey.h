/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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