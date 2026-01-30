/*
 * Copyright (C) 2023
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

#include "ResultFrameDLL.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XResultDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XDataInLayer.h"


DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str="MEGATRADE";
	return true;
}

DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Result";
	Name=/**/"ResultFrameDLL";
	return true;
}

DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Store ResultFrameDLL in XML";
}
DEFFUNCEX	const	char		*DLL_GetParamName(void)
{
	return "ResultFrameDLL.dat";
}

DEFFUNCEX	ResultDLLBaseRoot	*DLL_Initial(LayersBase *Base)
{
	ResultFrameDLL	*ResultPointer=new ResultFrameDLL(Base);
	return ResultPointer;
}

DEFFUNCEX	bool	DLL_Release(ResultDLLBaseRoot *ResultPort)
{
	ResultFrameDLL	*ResultPointer=((ResultFrameDLL *)ResultPort);
	if(ResultPointer!=NULL){
		ResultPointer->Close();
		delete	ResultPointer;
	}
	return true;
}


DEFFUNCEX	bool		DLL_OutputResultCommon(ResultDLLBaseRoot *ResultPointer
												,ResultInspection *RBase 
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,EntryPointBase &entryPoint)
{
	bool	ret=((ResultFrameDLL *)ResultPointer)->OutputCommon(*RBase,ShadowResStocks);
	if(ret==false)
		return false;
	return true;
}
DEFFUNCEX	bool		DLL_OutputResultSlave (ResultDLLBaseRoot *ResultPointer
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,int32 MachineID ,const XDateTime &InspectedTime
												,ResultInspection *RBase 
												,const QString &LotID
												,int phase
												,int localPage 
												,EntryPointBase &entryPoint)
{
	bool	ret=((ResultFrameDLL *)ResultPointer)->OutputResult(ShadowResStocks
																,MachineID ,InspectedTime
																,RBase 
																,LotID,phase,localPage);
	if(ret==false)
		return false;
	return true;
}

DEFFUNCEX	bool			DLL_RemoveResult(ResultDLLBaseRoot *ResultPointer
												,int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID)
{
	bool	ret=((ResultFrameDLL *)ResultPointer)->RemoveResult(MachineID ,ResultTime ,InspectionID);
	if(ret==false){
		return false;
	}
	return true;
}
DEFFUNCEX	bool			DLL_GetLastInspectionID(ResultDLLBaseRoot *ResultPointer
												,int MasterID ,QString LotID ,int64 &InspectionID)
{

	int64	hInspectionID=0;
	bool	ret=((ResultFrameDLL *)ResultPointer)->GetLastInspectionID(MasterID, LotID ,hInspectionID);
	if(ret==false){
		return false;
	}
	InspectionID=hInspectionID;
	return true;
}
DEFFUNCEX	bool			DLL_SearchLotID(ResultDLLBaseRoot *ResultPointer
												,const QString &iLotID)
{
	bool	ret=((ResultFrameDLL *)ResultPointer)->SearchLotID(iLotID);
	return ret;
}

DEFFUNCEX	bool		DLL_OutputInLotChangedCommon(ResultDLLBaseRoot *ResultPointer
												,EntryPointBase &entryPoint)
{
	((ResultFrameDLL *)ResultPointer)->OutputInLib();
	return true;
}

DEFFUNCEX	bool		DLL_OutputInLotChangedSlave (ResultDLLBaseRoot *ResultPointer
												,EntryPointBase &entryPoint ,int LocalPage)
{
	((ResultFrameDLL *)ResultPointer)->OutputInLotChangedSlave(LocalPage);
	return true;
}

DEFFUNCEX	bool			DLL_CheckConnection(ResultDLLBaseRoot *ResultPointer)
{
	return ((ResultFrameDLL *)ResultPointer)->CheckConnection();
}

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}