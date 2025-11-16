#include "ListMasterDataAndLoadResource.h"
#include "ListMasterDataAndLoad.h"
#include "ListMasterDataAndLoadPacket.h"
#include "../XGUICmdReviewCommon.h"
#include "XReviewCommonPacket.h"

char	*sRoot=/**/"Review";
char	*sName=/**/"ListMasterDataAndLoad";




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
	return(/**/"Show Data List for Master Data");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListMasterDataAndLoad(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqLoadSlaveMaster(Base, sRoot, sName);
	(*Base)=new GUICmdAckLoadSlaveMaster(Base, sRoot, sName);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);

	Data[0].Type = /**/"bool";
	Data[0].VariableNameWithRoute=/**/"SameWidth";
	Data[0].Pointer	=&((ListMasterDataAndLoad *)Instance)->m_ListMasterForm.SameWidth;
	Data[1].Type = /**/"int32";
	Data[1].VariableNameWithRoute=/**/"WidthID";
	Data[1].Pointer	=&((ListMasterDataAndLoad *)Instance)->m_ListMasterForm.WidthID;
	Data[2].Type = /**/"int32";
	Data[2].VariableNameWithRoute=/**/"WidthName";
	Data[2].Pointer	=&((ListMasterDataAndLoad *)Instance)->m_ListMasterForm.WidthName;
	Data[3].Type = /**/"int32";
	Data[3].VariableNameWithRoute=/**/"WidthLatest";
	Data[3].Pointer	=&((ListMasterDataAndLoad *)Instance)->m_ListMasterForm.WidthLatest;

	return(4);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	RootNameList *item = new RootNameList(/**/"Review", /**/"ReviewStructure");
	List.AppendList(item);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListMasterDataAndLoad.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XXX
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ListMasterDataAndLoad::ListMasterDataAndLoad(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent), m_ListMasterForm(Base, this)
{
	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));
	initProperty();
		
	LangSolver.SetUI(this);
}

ListMasterDataAndLoad::~ListMasterDataAndLoad()
{

}
void	ListMasterDataAndLoad::Prepare(void)
{
	m_ListMasterForm.Prepare();
}

void ListMasterDataAndLoad::ResizeAction()
{
	m_ListMasterForm.resize(this->size());
}

void ListMasterDataAndLoad::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		m_ListMasterForm.updateGUI();
		return;
	}
	
	GUICmdSetEnable *GUICmdSetEnableVar = dynamic_cast<GUICmdSetEnable *>(packet);
	if(GUICmdSetEnableVar!=NULL){
		m_ListMasterForm.setGUIEnable(GUICmdSetEnableVar->enable);
		return;
	}

	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Global);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::ListMasterDataAndLoad);
		return;
	}
}
