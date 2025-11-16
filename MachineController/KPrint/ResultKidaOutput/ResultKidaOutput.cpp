#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XResultDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultKidaOutput.h"
#include "XDataInLayer.h"


DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str="MEGATRADE";
	return true;
}

DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"";
	Name="ResultKidaOutput";
	return true;
}

DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Store result to PIO in Kida print";
}
DEFFUNCEX	const char		*DLL_GetParamName(void)
{
	return "ResultKidaOutput.dat";
}

DEFFUNCEX	ResultDLLBaseRoot	*DLL_Initial(LayersBase *Base)
{
	ResultKidaOutput	*ResultPointer=new ResultKidaOutput(Base);
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
												,int mode ,ResultInspection *RBase 
												,GUIDirectMessage *packet
												,EntryPointBase &entryPoint)
{
	bool	ret=((ResultKidaOutput *)ResultPointer)->OutputResultDirectly(mode,*RBase,packet);
	if(ret==false)
		return false;
	return true;
}