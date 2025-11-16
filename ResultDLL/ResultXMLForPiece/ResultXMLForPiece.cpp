#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XResultDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultXMLForPiece.h"
#include "XDataInLayer.h"


DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str="MEGATRADE";
	return true;
}

DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"";
	Name="ResultXMLForPiece";
	return true;
}


DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Store result for piece in XML";
}
DEFFUNCEX	const	char		*DLL_GetParamName(void)
{
	return "ResultXMLForPiece.dat";
}

DEFFUNCEX	ResultDLLBaseRoot	*DLL_Initial(LayersBase *Base)
{
	ResultXMLForPiece	*ResultPointer=new ResultXMLForPiece(Base);
	return ResultPointer;
}

DEFFUNCEX	bool	DLL_Release(ResultDLLBaseRoot *ResultPort)
{
	ResultXMLForPiece	*ResultPointer	=((ResultXMLForPiece *)ResultPort);
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
	bool	ret=((ResultXMLForPiece *)ResultPointer)->OutputCommon(*RBase,ShadowResStocks);
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
	bool	ret=((ResultXMLForPiece *)ResultPointer)->OutputResult(ShadowResStocks
																	,MachineID ,InspectedTime
																	,RBase 
																	,LotID,phase,localPage);
	if(ret==false)
		return false;
	return true;
}
DEFFUNCEX	bool			DLL_SearchLotID(ResultDLLBaseRoot *ResultPointer
												,const QString &iLotID)
{
	bool	ret=((ResultXMLForPiece *)ResultPointer)->SearchLotID(iLotID);
	return ret;
}
DEFFUNCEX	bool			DLL_RemoveResult(ResultDLLBaseRoot *ResultPointer
												,int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID)
{
	bool	ret=((ResultXMLForPiece *)ResultPointer)->RemoveResult(MachineID ,ResultTime ,InspectionID);
	if(ret==false){
		return false;
	}
	return true;
}
DEFFUNCEX	bool			DLL_GetLastInspectionID(ResultDLLBaseRoot *ResultPointer
												,int MasterID ,QString LotID ,int64 &InspectionID)
{

	int64	hInspectionID=0;
	bool	ret=((ResultXMLForPiece *)ResultPointer)->GetLastInspectionID(MasterID, LotID ,hInspectionID);
	if(ret==false){
		return false;
	}
	InspectionID=hInspectionID;
	return true;
}

DEFFUNCEX	bool		DLL_OutputInLotChangedCommon(ResultDLLBaseRoot *ResultPointer
												,EntryPointBase &entryPoint)
{
	((ResultXMLForPiece *)ResultPointer)->OutputInLib();
	return true;
}

DEFFUNCEX	bool		DLL_OutputInLotChangedSlave (ResultDLLBaseRoot *ResultPointer
												,EntryPointBase &entryPoint ,int LocalPage)
{
	((ResultXMLForPiece *)ResultPointer)->OutputInLotChangedSlave(LocalPage);
	return true;
}

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}