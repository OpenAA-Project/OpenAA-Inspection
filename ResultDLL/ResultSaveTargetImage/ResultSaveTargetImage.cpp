#include "ResultSaveTargetImage.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XResultDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultSaveTargetImage.h"
#include "XDataInLayer.h"


DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str="MEGATRADE";
	return true;
}

DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"";
	Name="ResultSaveTargetImage";
	return true;
}

DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Save Target image in background";
}
DEFFUNCEX	const	char		*DLL_GetParamName(void)
{
	return "ResultSaveTargetImage.dat";
}

DEFFUNCEX	ResultDLLBaseRoot	*DLL_Initial(LayersBase *Base)
{
	ResultSaveTargetImage	*ResultPointer=new ResultSaveTargetImage(Base);
	return ResultPointer;
}

DEFFUNCEX	bool	DLL_Release(ResultDLLBaseRoot *ResultPort)
{
	if(ResultPort!=NULL){
		delete	ResultPort;
	}
	return true;
}

DEFFUNCEX	bool		DLL_OutputResultDirectly(ResultDLLBaseRoot *ResultPointer
												,int mode,ResultInspection *RBase 
												,GUIDirectMessage *packet
												,EntryPointBase &entryPoint)
{
	bool	ret=((ResultSaveTargetImage *)ResultPointer)->OutputResultDirectly(mode,*RBase,packet);
	if(ret==false)
		return false;
	return true;
}


DEFFUNCEX	bool		DLL_OutputResultCommon(ResultDLLBaseRoot *ResultPointer
												,ResultInspection *RBase 
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,EntryPointBase &entryPoint)
{
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
	return true;
}
