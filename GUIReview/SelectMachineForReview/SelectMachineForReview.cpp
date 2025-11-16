#include "SelectMachineForReviewResource.h"
#include "ButtonSelectMachineForReview.h"

#include "../XGUIReviewGlobal.h"
#include "XReviewCommon.h"
#include "ReviewStructurePacket.h"
#include "..\XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "XReviewCommonPacket.h"


#include "../WholeImageForReview/WholeImageForReviewPacket.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"SelectMachine";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Select machine Form");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSelectMachineForReview(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSelectMachineForReview *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"CFont";
	Data[1].Pointer				 =&((ButtonSelectMachineForReview *)Instance)->CFont;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"DefaultTopMachineID";
	Data[2].Pointer				 =&((ButtonSelectMachineForReview *)Instance)->DefaultTopMachineID;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"DefaultBottomMachineID";
	Data[3].Pointer				 =&((ButtonSelectMachineForReview *)Instance)->DefaultBottomMachineID;

	return(4);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	RootNameList *item = new RootNameList(/**/"Review", /**/"ReviewStructure");
	List.AppendList(item);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SelectMachineForReview.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
