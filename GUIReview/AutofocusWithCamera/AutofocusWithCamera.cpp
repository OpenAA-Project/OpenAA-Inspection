#include "AutofocusWithCameraResource.h"
#include "AutofocusWithCamera.h"
#include "AutofocusWithCameraForm.h"



char	*sRoot=/**/"Review";
char	*sName=/**/"AutofocusWithCamera";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Auto-Focus");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdExecuteWindUp		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AutofocusWithCameraForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SetZSysPort";
	Data[0].Pointer				 =&((AutofocusWithCameraForm *)Instance)->SetZSysPort;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"ZPositionSysPort";
	Data[1].Pointer				 =&((AutofocusWithCameraForm *)Instance)->ZPositionSysPort;

	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"MinZValue";
	Data[2].Pointer				 =&((AutofocusWithCameraForm *)Instance)->MinZValue;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"MaxZValue";
	Data[3].Pointer				 =&((AutofocusWithCameraForm *)Instance)->MaxZValue;

	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"CameraDLLRoot";
	Data[4].Pointer				 =&((AutofocusWithCameraForm *)Instance)->CameraDLLRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"CameraDLLName";
	Data[5].Pointer				 =&((AutofocusWithCameraForm *)Instance)->CameraDLLName;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"CameraDLLInst";
	Data[6].Pointer				 =&((AutofocusWithCameraForm *)Instance)->CameraDLLInst;


	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutofocusWithCamera.png")));
}
