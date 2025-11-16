#include "GUIReviewTemplateResource.h"
#include "GUIReviewTemplate.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../XGUIReviewCommonPacket.h"


static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"GUIReviewTemplate";


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
	return(/**/"This is template.");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	GUIReviewTemplate *form = new GUIReviewTemplate(Base,parent);
	return form;
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
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":GUIReviewTemplate.PNG")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ButtonToShowTotalNGMap
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GUIReviewTemplate::GUIReviewTemplate(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent)
{
	ui.setupUi(this);
}

GUIReviewTemplate::~GUIReviewTemplate()
{

}

void GUIReviewTemplate::TransmitDirectly(GUIDirectMessage *packet){
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}
}

void GUIReviewTemplate::updateGUI()
{
	GUIFormBase::update();
}

void GUIReviewTemplate::ResizeAction()
{
}