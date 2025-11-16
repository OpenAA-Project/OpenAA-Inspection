#include "LiveCameraDFK31AF03Resource.h"
#include "LiveCameraDFK31AF03.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "LiveCameraCommonPacket.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"LiveCameraDFK31AF03";


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
	return(/**/"Camera DFK31AF03 viewer.");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	LiveCameraDFK31AF03 *form = new LiveCameraDFK31AF03(Base,parent);
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
	return(new QIcon(QPixmap(/**/":LiveCameraDFK31AF03.PNG")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ButtonToShowTotalNGMap
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LiveCameraDFK31AF03::LiveCameraDFK31AF03(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent)
{
	ui.setupUi(this);

	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));

	ui.AreaCameraView->setEditMode(GetEditMode());

	if(GetEditMode()==false){
		ui.AreaCameraView->init();
		if(ui.AreaCameraView->Open()==false || ui.AreaCameraView->StartLive()==false){
			QMessageBox::critical(this, LangSolver.GetString(LiveCameraDFK31AF03_LS,LID_17)/*"Camera Error"*/, LangSolver.GetString(LiveCameraDFK31AF03_LS,LID_18)/*"Camera can't start."*/);
		}
	}
}

LiveCameraDFK31AF03::~LiveCameraDFK31AF03()
{
	//m_areaCamera.StopLive();
	//m_areaCamera.Close();
	ui.AreaCameraView->Close();
}

void LiveCameraDFK31AF03::TransmitDirectly(GUIDirectMessage *packet){
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}

	GUICmdSetCameraWindow *GUICmdSetCameraWindowVar = dynamic_cast<GUICmdSetCameraWindow *>(packet);
	if(GUICmdSetCameraWindowVar!=NULL){
		ui.AreaCameraView->changePaintLabel(GUICmdSetCameraWindowVar->label);
		GUICmdSetCameraWindowVar->ret = true;
		return;
	}

	GUICmdResetCameraWindow *GUICmdResetCameraWindowVar = dynamic_cast<GUICmdResetCameraWindow *>(packet);
	if(GUICmdResetCameraWindowVar!=NULL){
		ui.AreaCameraView->changePaintLabel(NULL);
		GUICmdResetCameraWindowVar->ret = true;
		return;
	}
}

void LiveCameraDFK31AF03::mousePressEvent(QMouseEvent *event)
{
	GUIFormBase::mousePressEvent(event);
	
	if(GetEditMode()==true){
		return;
	}

	if((event->buttons() & Qt::MouseButton::RightButton)!=0){
		if(GetEditMode()==false){
			ui.AreaCameraView->setVisible(false);
			ui.AreaCameraView->update();
			ui.AreaCameraView->show();
		}
		return;
	}

	if((event->buttons() & Qt::MouseButton::LeftButton)==0){
		return;
	}
	
	AlgorithmBase *RBase = GetReviewAlgorithmBase();
	if(RBase==NULL){
		return;
	}

	qreal x,y;

	if(ui.AreaCameraView->pixmap()==NULL || ui.AreaCameraView->pixmap()->isNull()){

		qreal x_rate = event->pos().x() / (qreal)width();
		qreal y_rate = event->pos().y() / (qreal)height();

		x = 2*x_rate - 1;
		y = 2*y_rate - 1;

	}else{
		QSize pixSize = ui.AreaCameraView->pixmap()->size();

		qreal x_rate = event->pos().x() / (qreal)pixSize.width();
		qreal y_rate = event->pos().y() / (qreal)pixSize.height();

		x = 2*x_rate - 1;
		y = 2*y_rate - 1;
	}
	CmdMoveVRSOnCameraView moveVRS(GetLayersBase());

	moveVRS.x = x;
	moveVRS.y = y;

	RBase->TransmitDirectly( &moveVRS );
}

void LiveCameraDFK31AF03::updateGUI()
{
	GUIFormBase::update();
	ui.AreaCameraView->StopLive();
	ui.AreaCameraView->StartLive();
}

void LiveCameraDFK31AF03::ResizeAction()
{
	if(GetEditMode()==false){
		ui.AreaCameraView->Resize();
	}
}
