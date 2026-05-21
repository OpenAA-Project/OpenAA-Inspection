#define	ForApplication
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XErrorCode.h"
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include "Regulus64System.h"



MainGUIFormBase::MainGUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent)
	:GUIFormBase(_LayersBasePoint,parent)
{	
	FormPosition	=GUIInstancePack::_Center;
	CloseCompletely=true;
	TopForm=true;
	SetKeyGrab(true);
	//grabKeyboard();
	Execution=NULL;

	ScaleFirst = true;
	BaseSize	=size();
	ScaleX		=1.0;
	ScaleY		=1.0;
	ReEntrant	=false;
}

void MainGUIFormBase::closeEvent ( QCloseEvent * event )
{
	if(GetLayersBase()->GetBootingLevel()!=0){
		if(GUIInstancePackPoint!=NULL){
			GUIInitializerPoint->GUIInstanceRoot.RemoveList(GUIInstancePackPoint);
			GUIInstancePackPoint->deleteLater();
		}
		return;
	}
			
	if(CloseCompletely==false){
		event->ignore();
		emit	QuitFromMenu();
	}
	if(GetLayersBase()->GetInsideLearningEditor()==false){
		OutputPosition();
	}
	else{
		GUIInitializerPoint->GUIInstanceRoot.RemoveList(GUIInstancePackPoint);
		GUIInstancePackPoint->deleteLater();
	}
	for(GUIFormPointer *f=ShouldCloseWindow.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetGUIFormBase()!=NULL){
			f->GetGUIFormBase()->close();
		}
		f->SetGUIFormBase(NULL);
	}

	GetLayersBase()->SetOnTerminating(true);
	BroadcastTerminated();
	emit	SignalCloseEvent();
}

void	MainGUIFormBase::OutputPosition(void)
{
	BroadcastLeavePage();

	int	PosX;
	int	PosY;
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		QWidget	*Win=this;
		while(Win->parentWidget()!=NULL){
			Win=Win->parentWidget();
		}

		int32	Ver=0x7FFF0001;
		if(::Save(&F,Ver)==false){
			return;
		}
		QList<QScreen *> Scr=QGuiApplication::screens();
		QScreen *S=Scr[0];
		int32	ScreenWidth	=S->size().width();
		int32	ScreenHeight=S->size().height();
		if(::Save(&F,ScreenWidth)==false){
			return;
		}
		if(::Save(&F,ScreenHeight)==false){
			return;
		}

		PosX=Win->frameGeometry().left();
		PosY=Win->frameGeometry().top();
		if(::Save(&F,PosX)==false){
			return;
		}
		if(::Save(&F,PosY)==false){
			return;
		}
		int	W=Win->geometry().width();
		int	H=Win->geometry().height();
		if(::Save(&F,W)==false){
			return;
		}
		if(::Save(&F,H)==false){
			return;
		}
	}
}

void	MainGUIFormBase::StartIdentificationServer(const QString &IdentificationName)
{
	connect(&IdentificationServer,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	IdentificationServer.listen(IdentificationName);
}
void	MainGUIFormBase::SlotNewConnection ()
{
	QLocalSocket *s=IdentificationServer.nextPendingConnection ();
	SocketForMainGUI	*sk=new SocketForMainGUI(s,this);
	IdentificationSocket.AppendList(sk);
}

QString	MainGUIFormBase::GetPositionFileName(void)
{
	return GetLayersBase()->GetUserPath()+QString("/MainPosition.dat");
}

void	MainGUIFormBase::ReflectAlignment(void)
{
	bool	SuccessLoadedPos=false;
	QWidget	*Win=this;
	while(Win->parentWidget()!=NULL){
		Win=Win->parentWidget();
	}
	int	PosX,PosY;
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);

	if(F.open(QIODevice::ReadOnly)==true){
		int32	Ver=0x7FFF0001;
		if(::Load(&F,Ver)==false){
			return;
		}
		if((Ver&0xFFFF0000)==0x7FFF0000){
			int32	ScreenWidth;
			int32	ScreenHeight;
			if(::Load(&F,ScreenWidth)==false){
				return;
			}
			if(::Load(&F,ScreenHeight)==false){
				return;
			}
			QList<QScreen *> Scr=QGuiApplication::screens();
			QScreen *S=Scr[0];
			if(ScreenWidth==S->size().width()
			&& ScreenHeight==S->size().height()){

				if(::Load(&F,PosX)==false){
					return;
				}
				if(::Load(&F,PosY)==false){
					return;
				}
				int	W,H;
				if(::Load(&F,W)==false){
					return;
				}
				if(::Load(&F,H)==false){
					return;
				}		//move(PosX,PosY);

				//QDesktopWidget	*s=QApplication::desktop ();
				//QRect R=s->availableGeometry ();
				QScreen	*g=QGuiApplication::screens()[0];

				QStyleOptionTitleBar options;
				options.initFrom(this);
				int tbh = style()->pixelMetric( QStyle::PM_TitleBarHeight, &options, this )+6;
   
				int	MaxW=g->geometry().width();
				int	MaxH=g->geometry().height();
				if(32<=W && W<MaxW && 32<H && H<MaxH
				&& 0<(PosX+W) && PosX<MaxW && 0<(PosY+H) && PosY<MaxH){
					QCoreApplication::processEvents();
					Win->setGeometry(PosX+1,PosY+tbh,W,H);
					SuccessLoadedPos=true;
					//QMessageBox::information(NULL,/**/"Position"
					//	,QString::number(PosX)
					//	+QString(/**/",")
					//	+QString::number(PosY)
					//	+QString(/**/" - ")
					//	+QString::number(W)
					//	+QString(/**/",")
					//	+QString::number(H));
				}
			}
		}
		FormPosition=GUIInstancePack::_None;
	}

	//QMessageBox::critical(NULL,/**/"Test", /**/"BootingH1");


	if(SuccessLoadedPos==false){
		QList<QScreen *> Scr=QGuiApplication::screens();

		if(Scr.count()>0){
			QScreen *S=Scr[0];
			int32	ScreenWidth	=S->size().width();
			int32	ScreenHeight=S->size().height();
						
			QCoreApplication::processEvents();
			//QMessageBox::critical(NULL,/**/"Test"
			//					, /**/"BootingH6");

			if(ScreenWidth!=0 && ScreenHeight!=0){
				//Error occurs
				//Win->setGeometry(ScreenWidth/4,ScreenHeight/4,ScreenWidth/2,ScreenHeight/2);
				//QMessageBox::critical(NULL,/**/"Test", /**/"BootingH7");
			}
		}
	}
	
}
	
void	MainGUIFormBase::moveEvent ( QMoveEvent * event )
{
	GUIFormBase::moveEvent (event );
	int	PosX=geometry().x();
	int	PosY=geometry().y();
	emit	SignalMoveWindow(PosX ,PosY);
}

void	MainGUIFormBase::resizeEvent ( QResizeEvent * event )
{
	if(ReEntrant==true)
		return;

	if(GetLayersBase()!=NULL){
		if(GetLayersBase()->GetEntryPoint()!=NULL){
			if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==true){
				GUIFormBase::resizeEvent ( event );
				return;
			}
		}
	}
	
		if (!BaseSize.isValid() || BaseSize.width() == 0 || BaseSize.height() == 0) {
			ReEntrant=false;
		    return;
		}

		// 3. 現在のサイズと基準サイズの比率（スケール）を計算
		//ScaleX = static_cast<double>(event->size().width()) / BaseSize.width();
		//ScaleY = static_cast<double>(event->size().height()) / BaseSize.height();

		SetClientX2(0);
		SetClientY2(0);
		GUIFormBase::resizeEvent ( event );

		//ResizeByScale(scaleX,scaleY);
	//}

	ReEntrant=false;
}

void	MainGUIFormBase::SetSingleExecution(const QString &IdentifiedName)
{
	if(Execution!=NULL)
		return;
	Execution=new CheckSingleExecution(IdentifiedName,this);
	connect(Execution,SIGNAL(SignalTerminateFromOther()),this,SLOT(SlotTerminateFromOther()));
}
bool	MainGUIFormBase::CheckDoubleBoot(void)
{
	if(Execution!=NULL){
		return Execution->CheckDoubleBoot();
	}
	return false;
}
bool	MainGUIFormBase::RequirePrebootedSoftwareToTerminate(void)
{
	if(Execution!=NULL){
		return Execution->RequireTerminate();
	}
	return false;
}

void	MainGUIFormBase::SlotTerminateFromOther()
{
	emit QuitUnconditionally();
}

void	MainGUIFormBase::GetGUIScale(double &XScale ,double &YScale)
{
	XScale=ScaleX;
	YScale=ScaleY;
}
