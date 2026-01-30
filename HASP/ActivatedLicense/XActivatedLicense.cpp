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

#include "XTypeDef.h"

#include "XGeneralFunc.h"
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>
#include "XDataInLayer.h"
#include "XDateTime.h"
#include "XAuthentication.h"
#include <QCryptographicHash> 
#include "XSimpleCrypt.h"
#include "TypeDefinition.h"
#include "ActivationLib.h"
#include "XServiceRegSpector.h"
#include "ActivatedLicense.h"


ActivatedLicense::ActivatedLicense(LayersBase *base)
	:ServiceForLayers(base)
{
}

bool3	ActivatedLicense::PermitByDate(const QString &DLLRoot ,const QString &DLLName
										,qint64 SpanSecFromInstall
										,const QString &_CurrentVersion
										,QString &FailMessage
										,int &ErrorCode)
{
	GUIFormBase *Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"RegSpector" ,/**/"TypeDefinition",Ret ,sizeof(Ret)/sizeof(Ret[0]));
	if(N==0){
		return none3;
	}
	for(int i=0;i<N;i++){
		TypeDefinition	*Form=(TypeDefinition *)Ret[i];
		CmdCheckByDate	RCmd(GetLayersBase());

		RCmd.SpanSecFromInstall=SpanSecFromInstall;
		Form->TransmitDirectly(&RCmd);
		if(RCmd.Result==TypeDefinition::_AR_ExpiredByDate){
			return false3;
		}
		if(RCmd.Result==TypeDefinition::_AR_ActivatedOK){
			return true3;
		}
	}

	return none3;
}
bool3	ActivatedLicense::PermitByProgram(const QString &ProgramCode
											,const QString &_CurrentVersion
											,QString &FailMessage
											,int &ErrorCode)
{
	GUIFormBase *Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"RegSpector" ,/**/"TypeDefinition",Ret ,sizeof(Ret)/sizeof(Ret[0]));
	if(N==0){
		return none3;
	}
	for(int i=0;i<N;i++){
		TypeDefinition	*Form=(TypeDefinition *)Ret[i];
		CmdCheckActivated	RCmd(GetLayersBase());
		Form->TransmitDirectly(&RCmd);
		if(RCmd.Result==TypeDefinition::_AR_ActivatedOK){
			return true3;
		}
		else{
			return false3;
		}
	}
	return false3;
}

void	ActivatedLicense::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool3	ActivatedLicense::PermitByID(const QString &DLLRoot ,const QString &DLLName ,int id
										,const QString &_CurrentVersion
										,QString &FailMessage
										,int &ErrorCode)
{
	return none3;
}