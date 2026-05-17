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

#include "SentinelHasp.h"
#include "XHaspDLL.h"

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XGeneralFunc.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "hasplib.h"
#include "swap.h"

bool3	SentinelHasp::PermitByDate(const QString &DLLRoot ,const QString &DLLName
									,qint64 SpanSecFromInstall
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)
{
	return none3;
}

bool3	SentinelHasp::PermitByProgram(const QString &ProgramCode
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)
{
	Hasplib hasplib;
	hasp_status_t status=hasplib.Login(handle);

	if(ErrorCheck(status)==false)
		return false3;
	char *C = "";
	status = hasp_get_sessioninfo(handle,HASP_KEYINFO,&C);
	if(ErrorCheck(status)==false)
		return false3;

	QString str_ID = GetID(C);
	status = hasp_read(handle,HASP_FILEID_MAIN,0,48,C);
	if(ErrorCheck(status)==false)
		return false3;
//////////
	QByteArray ByteData;
	for(int i=0;i<48;i++){
		ByteData.insert(i,C[i]);
	}
//////////
	//unsigned char *Data = (unsigned char*)C;
//////////
	unsigned char UCData[48];
	for(int i=0;i<48;i++){
		UCData[i] = ByteData[i];
	}
	hasp_size_t deDatalen = sizeof(UCData);
	status = hasp_decrypt(handle,UCData,deDatalen);
	if(ErrorCheck(status)==false)
		return false3;

	ByteData.clear();
	for(int i=0;i<48;i++){
		ByteData.insert(i,UCData[i]);
	}
	QByteArray FukugouData;
	Fukugou(str_ID.toInt(),ByteData,FukugouData);
	for(int i=0;i<48;i++){
		UCData[i] = FukugouData[i];
	}
////////////
	//Fukugou(str_ID,Data);

	QStringList DateList;
	setDateList(UCData,DateList);
	QStringList TypeList;
	setTypeList(UCData,TypeList);

	QDate	CurrentDate=QDate::currentDate();
	for(int i=0;i<TypeList.size();i++){
		if(TypeList[i]==ProgramCode){
			QDate	d=QDate::fromString(DateList[i],"yyyy/MM/dd");
			if(CurrentDate<=d){
				return true3;
			}
		}
	}
	/*
	for(int i=0;i<TypeList.size();i++){
		showCode(TypeList[i],DateList[i]);
	}
	*/
	return false3;
}
bool3	SentinelHasp::PermitByID(const QString &DLLRoot ,const QString &DLLName ,int id
								,const QString &_CurrentVersion
								,QString &FailMessage
								,int &ErrorCode)
{
	return none3;
}

bool SentinelHasp::ErrorCheck(const hasp_status_t &status)
{
	if(status == HASP_STATUS_OK)
		return true;

	QString	MessageStr;
	switch (status) {
		case HASP_MEM_RANGE			   : MessageStr=/**/"Invalid memory address"							; break;
		case HASP_INV_PROGNUM_OPT	   : MessageStr=/**/"Unknown prognum option requested"					; break;
		case HASP_FEATURE_NOT_FOUND    : MessageStr=/**/"The requested feature isn't available"				; break;
		case HASP_CONTAINER_NOT_FOUND  : MessageStr=/**/"Hasp not  found"									; break;
		case HASP_FEATURE_TYPE_NOT_IMPL: MessageStr=/**/"The type of feature isn't implemented"				; break;
		case HASP_TMOF				   : MessageStr=/**/"Too many open handles"								; break;
		case HASP_INSUF_MEM			   : MessageStr=/**/"Out of memory"										; break;
		case HASP_INV_VCODE			   : MessageStr=/**/"invalid vendor code"								; break;
		case HASP_NO_DRIVER			   : MessageStr=/**/"Driver not installed"								; break;
		case HASP_OLD_DRIVER		   : MessageStr=/**/"Old driver installed"								; break;
		case HASP_TS_DETECTED		   : MessageStr=/**/"Program runs on a remote screen on Terminal Server"; break;
		case HASP_INV_HND			   : MessageStr=/**/"Invalid session handle"							; break;
		case HASP_INV_FORMAT		   : MessageStr=/**/"Unrecognized format"								; break;
		case HASP_TOO_SHORT			   : MessageStr=/**/"The length of the data to be encrypted is too short"; break;
		case HASP_ENC_NOT_SUPP		   : MessageStr=/**/"Encryption type not supported by the hardware"		; break;
		default						   : MessageStr=/**/"Unknown Error"										; break;
	}
	QMessageBox::warning(NULL,"HASP error",MessageStr);
	return false;
}

QString  SentinelHasp::GetID(char *C)
{
	QString str;
	str.append(C);
	int first  = str.indexOf("<haspid>")+8;
	int Len    = str.indexOf('<',first) - first;
	return str.mid(first,Len);
}

void SentinelHasp::Fukugou(int ID,QByteArray ReData, QByteArray &fukugou)
{
	//?V???A???R?[?h???3?????g?p??????????
	fukugou.clear();
	QStringList List;
	List.clear();
	//QByteArray??QStringList(swap??????g????)
	for (int iA=0; iA<=47; iA++){
		List.append(ReData.mid(iA,1));
	}
	//?I??????????????????????
	int iNum=0;
	for (int iAn=0; iAn<=QByteArray().setNum(ID).mid(6,3).toInt(); iAn++){
		if (iNum==45){iNum=0;}	
		iNum++;
	}
	iNum=iNum+2;
	//?I???????????　???????
	for (int iFu=0; iFu<=QByteArray().setNum(ID).mid(6,3).toInt(); iFu++){
		if (iNum==2){iNum=47;}
		Swap(List,iNum,iNum-3);
		iNum--;
	}
	//QStringList??QByteArray????
	for (int iB=0; iB<=47; iB++){
		QString	s = List.at(iB);
		fukugou.insert(iB,s.toUtf8());
	}
}
///////
void SentinelHasp::setDateList(unsigned char *Data,QStringList &DateList)
{
	QString str;
	for(int i=0;i<48 && Data[i]!=' ';i++){
		str.append(QString().setNum(Data[i]).rightJustified(2,'0'));
		if(str.size()==8){
			DateList.append(str);
			str.clear();
			i+=8;
		}
	}
	for(int i=0;i<DateList.size();i++){
		DateList[i].insert(4,'/');
		DateList[i].insert(7,'/');
	}
}
void SentinelHasp::setTypeList(unsigned char *Data,QStringList &TypeList)
{
	QString str;
	for(int i=4;i<48 && Data[i]!=0 && Data[i]!=' ';i++){
		char	r=(char)Data[i];
		str.append(r);
		if(str.size()==8){
			TypeList.append(str);
			str.clear();
			i+=4;
		}
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
	str="SentinelHasp";
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
	return "Hasp control for Sentinel";
}

HaspHandleContainer		*_cdecl	DLL_Initial(LayersBase *base,const QString &ParamStr)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	HaspHandleContainer	*H=new HaspHandleContainer();
	H->AppendList(new SentinelHasp());
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

//=======================================================================================

