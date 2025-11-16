/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\OperateThroughNet\OperateThroughNet.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "OperateThroughNet.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include <QAbstractButton>
#include <QScreen>

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"OperateThroughNet";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Input integration lot");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	= new IntegrationTransferEvent		(Base	,sRoot	,sName	,-1);
	(*Base)	= new IntegrationReqImageGUIFormBase	(Base	,sRoot	,sName	,-1);
	(*Base)	= new IntegrationAckImageGUIFormBase	(Base	,sRoot	,sName	,-1);


	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new OperateThroughNet(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"TargetGUIRoot";
	Data[0].Pointer				 =&((OperateThroughNet *)Instance)->TargetGUIRoot;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"TargetGUIName";
	Data[1].Pointer				 =&((OperateThroughNet *)Instance)->TargetGUIName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"TargetGUIInst";
	Data[2].Pointer				 =&((OperateThroughNet *)Instance)->TargetGUIInst;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"TargetSlaveNo";
	Data[3].Pointer				 =&((OperateThroughNet *)Instance)->TargetSlaveNo;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/OperateThroughNet.png")));
}

//==============================================================================================================

OperateThroughNet::OperateThroughNet(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Target	=NULL;
	TargetImage	=NULL;
	IntegrationTransferEventPointer			=NULL;
	IntegrationReqImageGUIFormBasePointer	=NULL;
	IntegrationAckImageGUIFormBasePointer	=NULL;
	resize(50,10);
}
OperateThroughNet::~OperateThroughNet()
{
	if(IntegrationTransferEventPointer		!=NULL)
		delete	IntegrationTransferEventPointer;
	if(IntegrationReqImageGUIFormBasePointer!=NULL)
		delete	IntegrationReqImageGUIFormBasePointer;
	if(IntegrationAckImageGUIFormBasePointer!=NULL)
		delete	IntegrationAckImageGUIFormBasePointer;

	Target	=NULL;
	IntegrationTransferEventPointer			=NULL;
	IntegrationReqImageGUIFormBasePointer	=NULL;
	IntegrationAckImageGUIFormBasePointer	=NULL;

	if(TargetImage!=NULL){
		delete	TargetImage;
		TargetImage=NULL;
	}

}

void	OperateThroughNet::ReadyParam(void)
{
	IntegrationTransferEventPointer			=new IntegrationTransferEvent		(GetLayersBase(),sRoot,sName,TargetSlaveNo);
	IntegrationTransferEventPointer->TargetGUIRoot=TargetGUIRoot;
	IntegrationTransferEventPointer->TargetGUIName=TargetGUIName;
	IntegrationTransferEventPointer->TargetGUIInst=TargetGUIInst;

	IntegrationReqImageGUIFormBasePointer	=new IntegrationReqImageGUIFormBase	(GetLayersBase(),sRoot,sName,TargetSlaveNo);
	IntegrationReqImageGUIFormBasePointer->TargetGUIRoot=TargetGUIRoot;
	IntegrationReqImageGUIFormBasePointer->TargetGUIName=TargetGUIName;
	IntegrationReqImageGUIFormBasePointer->TargetGUIInst=TargetGUIInst;

	IntegrationAckImageGUIFormBasePointer	=new IntegrationAckImageGUIFormBase	(GetLayersBase(),sRoot,sName,TargetSlaveNo);

	Target	=GetLayersBase()->FindByName(TargetGUIRoot,TargetGUIName,TargetGUIInst);
	TargetImage	=new QImage(width(),height(),QImage::Format_ARGB32_Premultiplied);
}

void OperateThroughNet::paintEvent ( QPaintEvent * event )
{
	if(GetEditMode()==false
	&& IntegrationReqImageGUIFormBasePointer!=NULL && IntegrationAckImageGUIFormBasePointer!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		if(IntegrationReqImageGUIFormBasePointer->Send(TargetSlaveNo,0,*IntegrationAckImageGUIFormBasePointer)==true){
			if(TargetImage!=NULL && (IntegrationAckImageGUIFormBasePointer->Width!=TargetImage->width() || IntegrationAckImageGUIFormBasePointer->Height!=TargetImage->height())){
				delete	TargetImage;
				TargetImage=NULL;
			}
			if(TargetImage==NULL){
				TargetImage=new QImage(IntegrationAckImageGUIFormBasePointer->Width,IntegrationAckImageGUIFormBasePointer->Height,QImage::Format_ARGB32_Premultiplied);
			}
			memcpy(TargetImage->bits(),IntegrationAckImageGUIFormBasePointer->Data,IntegrationAckImageGUIFormBasePointer->DatByteCount);
			QPainter	Pnt(this);
			Pnt.drawImage(0,0,*TargetImage);
		}
	}
	else{
		GUIFormBase::paintEvent(event);
	}
}
void OperateThroughNet::mouseMoveEvent ( QMouseEvent * event )
{
	if(GetEditMode()==false
	&& IntegrationTransferEventPointer!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		IntegrationTransferEventPointer->EventType	=event->type();
		IntegrationTransferEventPointer->Button		=event->button();
		IntegrationTransferEventPointer->Buttons	=event->buttons();
		IntegrationTransferEventPointer->x			=event->x();
		IntegrationTransferEventPointer->y			=event->y();
		IntegrationTransferEventPointer->KeyModifiers=event->modifiers();
		IntegrationTransferEventPointer->Send(NULL,TargetSlaveNo,0);
		repaint();
	}
	else{
		GUIFormBase::mouseMoveEvent(event);
	}
}
void OperateThroughNet::mousePressEvent ( QMouseEvent * event )
{
	if(GetEditMode()==false
	&& IntegrationTransferEventPointer!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		IntegrationTransferEventPointer->EventType	=event->type();
		IntegrationTransferEventPointer->Button		=event->button();
		IntegrationTransferEventPointer->Buttons	=event->buttons();
		IntegrationTransferEventPointer->x			=event->x();
		IntegrationTransferEventPointer->y			=event->y();
		IntegrationTransferEventPointer->KeyModifiers=event->modifiers();
		IntegrationTransferEventPointer->Send(NULL,TargetSlaveNo,0);
		repaint();
	}
	else{
		GUIFormBase::mousePressEvent(event);
	}
}
void OperateThroughNet::mouseReleaseEvent ( QMouseEvent * event )
{
	if(GetEditMode()==false
	&& IntegrationTransferEventPointer!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		IntegrationTransferEventPointer->EventType	=event->type();
		IntegrationTransferEventPointer->Button		=event->button();
		IntegrationTransferEventPointer->Buttons	=event->buttons();
		IntegrationTransferEventPointer->x			=event->x();
		IntegrationTransferEventPointer->y			=event->y();
		IntegrationTransferEventPointer->KeyModifiers=event->modifiers();
		IntegrationTransferEventPointer->Send(NULL,TargetSlaveNo,0);
		repaint();
	}
	else{
		GUIFormBase::mouseReleaseEvent(event);
	}
}
void OperateThroughNet::keyPressEvent ( QKeyEvent * event )
{
	if(GetEditMode()==false
	&& IntegrationTransferEventPointer!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		IntegrationTransferEventPointer->EventType	=event->type();
		IntegrationTransferEventPointer->Key		=event->key();
		IntegrationTransferEventPointer->KeyText	=event->text();
		IntegrationTransferEventPointer->KeyModifiers=event->modifiers();
		IntegrationTransferEventPointer->Send(NULL,TargetSlaveNo,0);
		repaint();
	}
	else{
		GUIFormBase::keyPressEvent(event);
	}
}
void OperateThroughNet::keyReleaseEvent ( QKeyEvent * event )
{	
	if(GetEditMode()==false
	&& IntegrationTransferEventPointer!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		IntegrationTransferEventPointer->EventType	=event->type();
		IntegrationTransferEventPointer->Key		=event->key();
		IntegrationTransferEventPointer->KeyText	=event->text();
		IntegrationTransferEventPointer->KeyModifiers=event->modifiers();
		IntegrationTransferEventPointer->Send(NULL,TargetSlaveNo,0);
		repaint();
	}
	else{
		GUIFormBase::keyReleaseEvent(event);
	}
}

//===========================================================================================================

IntegrationTransferEvent::IntegrationTransferEvent(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationTransferEvent::Load(QIODevice *f)
{
	if(::Load(f,TargetGUIRoot)==false)
		return false;
	if(::Load(f,TargetGUIName)==false)
		return false;
	if(::Load(f,TargetGUIInst)==false)
		return false;
	int	t;
	if(::Load(f,t)==false)
		return false;
	EventType=(QEvent::Type)t;

	int	d;
	if(::Load(f,d)==false)
		return false;
	Button=(Qt::MouseButton)d;

	if(::Load(f,d)==false)
		return false;
	Buttons=Qt::MouseButtons((Qt::MouseButton)d);

	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	if(::Load(f,Key)==false)
		return false;
	if(::Load(f,KeyText)==false)
		return false;

	if(::Load(f,d)==false)
		return false;
	KeyModifiers=Qt::KeyboardModifiers((Qt::KeyboardModifier)d);

	return true;
}
bool	IntegrationTransferEvent::Save(QIODevice *f)
{
	if(::Save(f,TargetGUIRoot)==false)
		return false;
	if(::Save(f,TargetGUIName)==false)
		return false;
	if(::Save(f,TargetGUIInst)==false)
		return false;

	int	t=(int)EventType;
	if(::Save(f,t)==false)
		return false;

	int	d;

	d=Button;
	if(::Save(f,d)==false)
		return false;

	d=Buttons;
	if(::Save(f,d)==false)
		return false;

	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;
	if(::Save(f,Key)==false)
		return false;
	if(::Save(f,KeyText)==false)
		return false;

	d=KeyModifiers;
	if(::Save(f,d)==false)
		return false;

	return true;
}

void	IntegrationTransferEvent::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QWidget	*f=GetLayersBase()->FindByName(TargetGUIRoot,TargetGUIName,TargetGUIInst);

	if(f!=NULL){
		if(EventType==QEvent::MouseMove || EventType==QEvent::MouseButtonPress || EventType==QEvent::MouseButtonRelease){
			QPoint	P(x,y);
			QPoint	GlobalP=f->mapToGlobal(P);
			while((f=f->childAt(P))!=NULL){
				P=f->mapFromGlobal(GlobalP);
				QAbstractButton	*b=dynamic_cast<QAbstractButton *>(f);
				if(b!=NULL){
					QMouseEvent	*ev=new QMouseEvent(EventType,P,Button,Buttons,KeyModifiers);
					QCoreApplication::postEvent ( b, ev);
				}
			}
		}
		else
		if(EventType==QEvent::KeyPress || EventType==QEvent::KeyRelease){
			QKeyEvent 	*ev=new QKeyEvent(EventType,Key,KeyModifiers,KeyText);
			QCoreApplication::postEvent ( f, ev);
		}
	}
}

//===========================================================================================================

IntegrationReqImageGUIFormBase::IntegrationReqImageGUIFormBase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqImageGUIFormBase::Load(QIODevice *f)
{
	if(::Load(f,TargetGUIRoot)==false)
		return false;
	if(::Load(f,TargetGUIName)==false)
		return false;
	if(::Load(f,TargetGUIInst)==false)
		return false;
	return true;
}
bool	IntegrationReqImageGUIFormBase::Save(QIODevice *f)
{
	if(::Save(f,TargetGUIRoot)==false)
		return false;
	if(::Save(f,TargetGUIName)==false)
		return false;
	if(::Save(f,TargetGUIInst)==false)
		return false;
	return true;
}

void	IntegrationReqImageGUIFormBase::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckImageGUIFormBase	*SendBack=GetSendBackIntegration(IntegrationAckImageGUIFormBase,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*f=GetLayersBase()->FindByName(TargetGUIRoot,TargetGUIName,TargetGUIInst);

	if(f!=NULL){
		QScreen	*Scr=qGuiApp->screens()[0];
		QPixmap P=Scr->grabWindow( f->winId() );
		QImage Img=P.toImage ();
		int	Len=Img.bytesPerLine()*Img.height();
		SendBack->Allocate(Img.width(),Img.height());
		memcpy(SendBack->Data,(const char *)Img.bits(),Len);
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckImageGUIFormBase::IntegrationAckImageGUIFormBase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Data	=NULL;
	DatByteCount=0;
	Width		=0;
	Height		=0;
}

IntegrationAckImageGUIFormBase::~IntegrationAckImageGUIFormBase(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
	DatByteCount=0;
	Width		=0;
	Height		=0;
}

void	IntegrationAckImageGUIFormBase::Allocate(int w ,int h)
{
	if(w!=Width || h!=Height){
		if(Data!=NULL)
			delete	[]Data;
		Width	=w;
		Height	=h;
		DatByteCount=4*Width*Height;
		Data=new BYTE[DatByteCount];
	}
}

bool	IntegrationAckImageGUIFormBase::Load(QIODevice *f)
{
	int	iWidth,iHeight;
	if(::Load(f,iWidth)==false)
		return false;
	if(::Load(f,iHeight)==false)
		return false;
	if(::Load(f,DatByteCount)==false)
		return false;
	Allocate(iWidth,iHeight);
	if(f->read((char *)Data,DatByteCount)!=DatByteCount)
		return false;
	return true;
}
bool	IntegrationAckImageGUIFormBase::Save(QIODevice *f)
{
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	if(::Save(f,DatByteCount)==false)
		return false;
	if(f->write((const char *)Data,DatByteCount)!=DatByteCount)
		return false;
	return true;
}
