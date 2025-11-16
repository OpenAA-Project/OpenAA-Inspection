#include "ButtonToShowReviewSettingResource.h"
#include "ButtonToShowReviewSetting.h"
#include "../XGUIReviewGlobal.h"
#include "XGUIReviewCommonPacket.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ButtonToShowReviewSetting";

const QString saveFilename = /**/"ReviewSetting.ini";


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
	return(/**/"Show ReviewSettingForm.");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ButtonToShowReviewSetting *form = new ButtonToShowReviewSetting(Base,parent);
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
	return(new QIcon(QPixmap(/**/":Resources/ButtonToShowReviewSetting.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ButtonToShowTotalNGMap
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonToShowReviewSetting::ButtonToShowReviewSetting(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	connect(ui.pbShowSetting, SIGNAL(clicked()), this, SLOT(clicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonToShowReviewSetting::~ButtonToShowReviewSetting()
{
}

void ButtonToShowReviewSetting::clicked()
{
	ReviewSettingFormBase *Base = new ReviewSettingFormBase(GetLayersBase(), this);
	Base->exec();
	delete Base;
}

void ButtonToShowReviewSetting::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}
}

void ButtonToShowReviewSetting::updateGUI()
{
	GUIFormBase::update();
}

void ButtonToShowReviewSetting::ResizeAction()
{
	QRect rect = ui.pbShowSetting->geometry();

	if(rect.width()==width() && rect.height()==height()){
		return;
	}

	rect.setWidth(width());
	rect.setHeight(height());

	ui.pbShowSetting->setGeometry(rect);
}