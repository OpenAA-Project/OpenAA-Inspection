#include "GeneralTabWizardResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabWizard\GeneralTabWizard.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralTabWizard.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include "XStatusController.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XMacroFunction.h"
#include "XEntryPoint.h"

static	bool	MacroShowPage(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"TabWizard";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General TabWizard");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeTab(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralTabWizard(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"Msgs";
	Data[0].Pointer				 =&((GeneralTabWizard *)Instance)->Msgs;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"Left,Right";
	Data[1].VariableNameWithRoute=/**/"TabPosition";
	Data[1].Pointer				 =&((GeneralTabWizard *)Instance)->TabPosition;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"ButtonFont";
	Data[2].Pointer				 =&((GeneralTabWizard *)Instance)->ButtonFont;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"UncheckedColor";
	Data[3].Pointer				 =&((GeneralTabWizard *)Instance)->UncheckedColor;
	Data[4].Type				 =/**/"QColor";
	Data[4].VariableNameWithRoute=/**/"ActiveColor";
	Data[4].Pointer				 =&((GeneralTabWizard *)Instance)->ActiveColor;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"CheckedColor";
	Data[5].Pointer				 =&((GeneralTabWizard *)Instance)->CheckedColor;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"CommonWidth";
	Data[6].Pointer				 =&((GeneralTabWizard *)Instance)->CommonWidth;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"ButtonStyle";
	Data[7].Pointer				 =&((GeneralTabWizard *)Instance)->ButtonStyle;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"RegNo";
	Data[8].Pointer				 =&((GeneralTabWizard *)Instance)->RegNo;

	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralTabWizard.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShowPage";
		Functions[ret].Explain.append(/**/"Show tab page");
		Functions[ret].ArgName.append(/**/"tab page name");
		Functions[ret].DLL_ExcuteMacro	=MacroShowPage;
		ret++;
	}
	return ret;
}
static	bool	MacroShowPage(GUIFormBase *Instance ,QStringList &Args)
{
	GeneralTabWizard	*V=dynamic_cast<GeneralTabWizard *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	PageName=Args[0];

	V->CommandShowPage(PageName);

	return true;
}
//==================================================================================================

GTWToolButtonColoredForTab::GTWToolButtonColoredForTab(QWidget *parent)
:mtToolButtonColored(false,parent)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	connect(this,SIGNAL(toggled(bool)),this,SLOT(SlotToggled (bool)));
}
void	GTWToolButtonColoredForTab::SlotClicked()
{
	emit	IDClicked(ID);
}
void	GTWToolButtonColoredForTab::SlotToggled ( bool checked )
{
	if(checked==true){
		GeneralTabWizard	*w=dynamic_cast<GeneralTabWizard *>(parent());
		if(w!=NULL){
			w->UncheckAll(this);
			setColor(w->ActiveColor);
			if(w->GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==false
			&& w->GetLayersBase()->GetParamComm()->Mastered==true
			&& w->GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
				for(int page=0;page<w->GetPageNumb();page++){
					GUICmdChangeTab	RCmd(w->GetLayersBase(),sRoot,sName,page);
					RCmd.ID=ID;
					RCmd.TabName=w->GetName();
					RCmd.Send(NULL,page,0);
				}
			}
			//int	Cmd[2];
			QByteArray	IDPacket((char *)&ID,sizeof(ID));
			if(w->FromSync==false){
				w->TxSync(IDPacket);
			}
			w->GetLayersBase()->SetStatusModes(w,QString(/**/"Tab")+QString::number(ID));
		}
	}
	else{
		GeneralTabWizard	*w=dynamic_cast<GeneralTabWizard *>(parent());
		if(w!=NULL){
			if(w->GetCountOfButtonDown()==0){
				setChecked(true);
			}
			else{
				setColor(w->CheckedColor);
			}
		}
	}
}

GTWToolButtonStyledTab::GTWToolButtonStyledTab(QWidget *parent)
:QToolButton(parent)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	connect(this,SIGNAL(toggled(bool)),this,SLOT(SlotToggled (bool)));
}
void	GTWToolButtonStyledTab::SlotClicked()
{
	emit	IDClicked(ID);
}
void	GTWToolButtonStyledTab::SlotToggled ( bool checked )
{
	if(checked==true){
		GeneralTabWizard	*w=dynamic_cast<GeneralTabWizard *>(parent());
		if(w!=NULL){
			w->UncheckAll(this);
			if(w->GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==false
			&& w->GetLayersBase()->GetParamComm()->Mastered==true
			&& w->GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
				for(int page=0;page<w->GetPageNumb();page++){
					GUICmdChangeTab	RCmd(w->GetLayersBase(),sRoot,sName,page);
					RCmd.ID=ID;
					RCmd.TabName=w->GetName();
					RCmd.Send(NULL,page,0);
				}
			}
			int	Cmd[2];
			QByteArray	IDPacket((char *)&ID,sizeof(ID));
			if(w->FromSync==false){
				w->TxSync(IDPacket);
			}
			w->GetLayersBase()->SetStatusModes(w,QString(/**/"Tab")+QString::number(ID));
		}
	}
	else{
		GeneralTabWizard	*w=dynamic_cast<GeneralTabWizard *>(parent());
		if(w!=NULL){
			if(w->GetCountOfButtonDown()==0){
				setChecked(true);
			}
		}
	}
}


GeneralTabWizardPage::GeneralTabWizardPage(LayersBase *Base ,GeneralTabWizard *p ,QWidget *parent)
:GUIFormBase(Base,parent),Parent(p),ID(0)
{
	ShowingOn=none3;
	SetKeyGrab(false);
}
GeneralTabWizardPage::~GeneralTabWizardPage(void)
{
}
void	GeneralTabWizardPage::Prepare(void)
{
}
void	GeneralTabWizardPage::ResizeAction(void)
{
}
bool	GeneralTabWizardPage::IsShown(void)
{
	if(Parent->GetTopTabWizardPage()==this){
		return Parent->IsShown();
	}
	return false;
}

GeneralTabWizardCommon::GeneralTabWizardCommon(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SetKeyGrab(false);
}
GeneralTabWizardCommon::~GeneralTabWizardCommon(void)
{
}
void	GeneralTabWizardCommon::Prepare(void)
{
}
void	GeneralTabWizardCommon::ResizeAction(void)
{
}

GeneralTabWizard::GeneralTabWizard(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Common(this)
{
	FromSync	=false;
	oPageNumber=NULL;
	CommonWidth	=200;
	LastID		=-1;
	TabPosition=/**/"Left";
	Msgs.append(QString(/**/"Default"));
	Msgs.append(QString(/**/"Page1"));
	resize(400,400);
	MainTab.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	Common.addWidget(new GeneralTabWizardCommon(GetLayersBase(),&Common));
	ArrowColor		=Qt::black;
	UncheckedColor	=Qt::green;
	ActiveColor		=Qt::red;
	CheckedColor	=Qt::gray;
	RegNo			=550;
}

GeneralTabWizard::~GeneralTabWizard(void)
{
}

void	GeneralTabWizard::Prepare(void)
{
	if(Msgs.count()>MainTab.count()){
		for(int i=MainTab.count();i<Msgs.count();i++){
			GeneralTabWizardPage	*w=new GeneralTabWizardPage(GetLayersBase(),this,&MainTab);
			MainTab.addWidget(w);
		}
	}
	else if(Msgs.count()<MainTab.count()){
		while(Msgs.count()<MainTab.count()){
			MainTab.removeWidget(MainTab.widget(0));
		}
	}
	if(ButtonStyle.isEmpty()==true){
		if(Msgs.count()>Buttons.count()){
			for(int i=Buttons.count();i<Msgs.count();i++){
				GTWToolButtonColoredForTab	*d=new GTWToolButtonColoredForTab(this);
				Buttons.append(d);
				connect(d,SIGNAL(IDClicked(int)),this,SLOT(SlotIDClicked(int)));
			}
		}
		else if(Msgs.count()<Buttons.count()){
			while(Msgs.count()<Buttons.count()){
				GTWToolButtonColoredForTab	*d=Buttons.value(0);
				Buttons.removeAt(0);
				delete	d;
			}
		}
	}
	else{
		if(Msgs.count()>ButtonsStyle.count()){
			for(int i=ButtonsStyle.count();i<Msgs.count();i++){
				GTWToolButtonStyledTab	*d=new GTWToolButtonStyledTab(this);
				ButtonsStyle.append(d);
				connect(d,SIGNAL(IDClicked(int)),this,SLOT(SlotIDClicked(int)));
			}
		}
		else if(Msgs.count()<ButtonsStyle.count()){
			while(Msgs.count()<ButtonsStyle.count()){
				GTWToolButtonStyledTab	*d=ButtonsStyle.value(0);
				ButtonsStyle.removeAt(0);
				delete	d;
			}
		}
	}

	for(int i=0;i<Msgs.count();i++){
		QString	S=Msgs.value(i);
		QWidget	*w=MainTab.widget(i);
		GeneralTabWizardPage	*wt=dynamic_cast<GeneralTabWizardPage *>(w);
		if(wt!=NULL){
			wt->setWindowTitle(S);
			wt->SetName(S);
			wt->ID=i;
		}
		if(Buttons.count()>i){
			GTWToolButtonColoredForTab	*wb=Buttons.value(i);
			if(wb!=NULL){
				wb->setObjectName(QString(/**/"GTWToolButtonColoredForTab")+QString::number(i));
				wb->setColor(UncheckedColor);
				if(ButtonStyle.isEmpty()==false){
					wb->setStyleSheet(ButtonStyle);
				}
				wb->setFont(ButtonFont);
				wb->setCheckable(true);
				wb->setAutoExclusive(false);
				wb->setText(S);
				wb->ID=i;
			}
		}
		else if(ButtonsStyle.count()>i){
			GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
			if(wb!=NULL){
				wb->setObjectName(QString(/**/"GTWToolButtonStyledTab")+QString::number(i));
				if(ButtonStyle.isEmpty()==false){
					wb->setStyleSheet(ButtonStyle);
				}
				wb->setFont(ButtonFont);
				wb->setCheckable(true);
				wb->setAutoExclusive(false);
				wb->setText(S);
				wb->ID=i;
			}
		}
	}
	if(Buttons.count()>0){
		GTWToolButtonColoredForTab	*wb=Buttons.value(0);
		if(wb!=NULL){
			wb->setChecked(true);
		}
	}
	else if(ButtonsStyle.count()>0){
		GTWToolButtonStyledTab	*wb=ButtonsStyle.value(0);
		if(wb!=NULL){
			wb->setChecked(true);
		}
	}

	ResizeAction();
	update();

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			oPageNumber	=new SignalOperandInt(this,RegNo,/**/"GeneralTabWizard:oPageNumber");
			connect(oPageNumber	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(oPageNumber,&Error)==false){
				oPageNumber->ShowErrorMessage(Error);
			}
		}
	}

}
 GUIFormBase	*GeneralTabWizard::GetTopTabWizardPage(void)
 {
	for(int i=0;i<Msgs.count();i++){
		if(Buttons.count()>i){
			GTWToolButtonColoredForTab	*wb=Buttons.value(i);
			if(wb!=NULL && wb->isChecked()==true){
				QWidget	*w=MainTab.widget(i);
				GeneralTabWizardPage	*wt=dynamic_cast<GeneralTabWizardPage *>(w);
				if(wt!=NULL){
					return wt;
				}
			}
		}
	}
	return NULL;
 }

int	GeneralTabWizard::GetChildCount()
{
	return MainTab.count()+1;
}
GUIFormBase	*GeneralTabWizard::GetChild(int index)	const
{
	if(index<MainTab.count())
		return dynamic_cast<GUIFormBase*>(MainTab.widget(index));
	return dynamic_cast<GUIFormBase*>(Common.widget(0));
}

GUIFormBase	*GeneralTabWizard::GetTopSurfaceWidget(int x ,int y)
{
	if(MainTab.geometry().left()<=x && x<MainTab.geometry().right()
		&& MainTab.geometry().top()<=y && y<MainTab.geometry().bottom()){
		return dynamic_cast<GUIFormBase*>(MainTab.currentWidget());
	}
	if(Common.geometry().left()<=x && x<Common.geometry().right()
		&& Common.geometry().top()<=y && y<Common.geometry().bottom()){
		return dynamic_cast<GUIFormBase*>(Common.widget(0));
	}
	return this;
}

void	GeneralTabWizard::UncheckAll(GTWToolButtonColoredForTab *excludedItem)
{
	for(int i=0;i<Buttons.count();i++){
		GTWToolButtonColoredForTab	*wb=Buttons.value(i);
		if(wb!=excludedItem && wb!=NULL && wb->isChecked()==true){
			wb->setChecked(false);
		}
	}
}

void	GeneralTabWizard::UncheckAll(GTWToolButtonStyledTab *excludedItem)
{
	for(int i=0;i<ButtonsStyle.count();i++){
		GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
		if(wb!=excludedItem && wb!=NULL && wb->isChecked()==true){
			wb->setChecked(false);
		}
	}
}


void	GeneralTabWizard::ResizeAction()
{
	int	LW=CommonWidth;	//200;
	if(width()<LW)
		LW=width();
	if(Buttons.count()>0){
		int	Count=Buttons.count();
		if(Count==0){
			Count=1;
		}
		int	hb=height()/2/Count;
		if(TabPosition==/**/"Left"){
			for(int i=0;i<Buttons.count();i++){
				GTWToolButtonColoredForTab	*wb=Buttons.value(i);
				wb->move(0,hb*i);
				wb->resize(LW,hb/2);
			}
			Common.move(0,height()/2);
			Common.resize(LW,height()/2);
			MainTab.move(LW,0);
			MainTab.resize(width()-LW,height());
		}
		else{
			MainTab.move(0,0);
			MainTab.resize(width()-LW,height());
			for(int i=0;i<Buttons.count();i++){
				GTWToolButtonColoredForTab	*wb=Buttons.value(i);
				wb->move(width()-LW,hb*i);
				wb->resize(LW,hb/2);
			}
			Common.move(width()-LW,height()/2);
			Common.resize(LW,height()/2);
		}
	}
	else{
		int	Count=ButtonsStyle.count();
		if(Count==0){
			Count=1;
		}
		int	hb=height()/2/Count;
		if(TabPosition==/**/"Left"){
			for(int i=0;i<ButtonsStyle.count();i++){
				GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
				wb->move(0,hb*i);
				wb->resize(LW,hb/2);
			}
			Common.move(0,height()/2);
			Common.resize(LW,height()/2);
			MainTab.move(LW,0);
			MainTab.resize(width()-LW,height());
		}
		else{
			MainTab.move(0,0);
			MainTab.resize(width()-LW,height());
			for(int i=0;i<ButtonsStyle.count();i++){
				GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
				wb->move(width()-LW,hb*i);
				wb->resize(LW,hb/2);
			}
			Common.move(width()-LW,height()/2);
			Common.resize(LW,height()/2);
		}
	}
}

void	GeneralTabWizard::SlotIDClicked(int id)
{
	if(LastID>=0){
		GeneralTabWizardPage	*w=(GeneralTabWizardPage *)MainTab.widget(LastID);
		w->BroadcastLeavePage();
	}

	MainTab.setCurrentIndex(id);
	
	for(int i=0;i<MainTab.count();i++){
		GeneralTabWizardPage	*w=(GeneralTabWizardPage *)MainTab.widget(i);
		if(i==id){
			w->BroadcastSetViewingOnChildrenWithMe(true);
			w->BroadcastStartPage();
			w->SetKeyGrab(true);
			w->ShowingOn=true3;
		}
		else{
			if(w->ShowingOn==true3){
				w->BroadcastSetViewingOnChildrenWithMe(false);
				w->BroadcastLeavePage();
				w->SetKeyGrab(false);
			}
			w->ShowingOn=false3;
		}
	}
	GeneralTabWizardPage	*w=(GeneralTabWizardPage *)MainTab.widget(id);
	w->BroadcastStartPage();
	BroadcastTabChanged();
	LastID=id;
	if(oPageNumber!=NULL){
		oPageNumber->Set(id);
	}
}

void	GeneralTabWizard::showEvent(QShowEvent * event )
{
	if(Buttons.count()!=0){
		for(int i=0;i<MainTab.count();i++){
			GeneralTabWizardPage	*w=(GeneralTabWizardPage *)MainTab.widget(i);
			GTWToolButtonColoredForTab *b=Buttons[i];
			if(b->isChecked()==true){
				w->BroadcastSetViewingOnChildrenWithMe(true);
				w->BroadcastStartPage();
				w->SetKeyGrab(true);
				w->ShowingOn=true3;
			}
			else{
				if(w->ShowingOn==true3){
					w->BroadcastSetViewingOnChildrenWithMe(false);
					w->BroadcastLeavePage();
					w->SetKeyGrab(false);
				}
				w->ShowingOn=false3;
			}
		}
	}
	else if(ButtonsStyle.count()!=0){
		for(int i=0;i<MainTab.count();i++){
			GeneralTabWizardPage	*w=(GeneralTabWizardPage *)MainTab.widget(i);
			GTWToolButtonStyledTab *b=ButtonsStyle[i];
			if(b->isChecked()==true){
				w->BroadcastSetViewingOnChildrenWithMe(true);
				w->BroadcastStartPage();
				w->SetKeyGrab(true);
				w->ShowingOn=true3;
			}
			else{
				if(w->ShowingOn==true3){
					w->BroadcastSetViewingOnChildrenWithMe(false);
					w->BroadcastLeavePage();
					w->SetKeyGrab(false);
				}
				w->ShowingOn=false3;
			}
		}
	}

}

void	GeneralTabWizard::CommandShowPage(const QString &PageName)
{
	for(int i=0;i<Msgs.count();i++){
		if(Msgs[i]==PageName){
			SlotIDClicked(i);
			break;
		}
	}
}

void	GeneralTabWizard::DrawDownArrow(QPainter &pnt ,float size ,int PosX, int PosY)
{
	QPointF points[8];

	pnt.setBrush(ArrowColor);
	points[0].setX(1);	points[0].setY(-1);
	points[1].setX(1);	points[1].setY(0);
	points[2].setX(2);	points[2].setY(0);
	points[3].setX(0);	points[3].setY(2);
	points[4].setX(-2);	points[4].setY(0);
	points[5].setX(-1);	points[5].setY(0);
	points[6].setX(-1);	points[6].setY(-1);
	for(int i=0;i<8;i++){
		points[i].setX(points[i].x()*size+PosX);
		points[i].setY(points[i].y()*size+PosY);
	}
	pnt.drawPolygon ( points, 7);
}

void GeneralTabWizard::paintEvent ( QPaintEvent * event )
{
	GUIFormBase::paintEvent(event);
	QPainter	pnt(this);

	if(Buttons.count()>0){
		int	LW=CommonWidth;
		if(width()<LW)
			LW=width();
		int	hb=height()/2/Buttons.count();
		if(TabPosition==/**/"Left"){
			for(int i=0;i<Buttons.count();i++){
				DrawDownArrow(pnt ,hb/10,LW/2, hb*i+hb/2+hb/4);
			}
		}
		else if(TabPosition==/**/"Left"){
			for(int i=0;i<Buttons.count();i++){
				DrawDownArrow(pnt ,hb/10,width()-LW+LW/2, hb*i+hb/2+hb/4);
			}
		}
	}
	if(ButtonsStyle.count()>0){
		int	LW=CommonWidth;
		if(width()<LW)
			LW=width();
		int	hb=height()/2/ButtonsStyle.count();
		if(TabPosition==/**/"Left"){
			for(int i=0;i<ButtonsStyle.count();i++){
				DrawDownArrow(pnt ,hb/10,LW/2, hb*i+hb/2+hb/4);
			}
		}
		else if(TabPosition==/**/"Left"){
			for(int i=0;i<ButtonsStyle.count();i++){
				DrawDownArrow(pnt ,hb/10,width()-LW+LW/2, hb*i+hb/2+hb/4);
			}
		}
	}

}

void	GeneralTabWizard::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdNextForWizard	*CmdNextForWizardPoint=dynamic_cast<CmdNextForWizard *>(packet);
	if(CmdNextForWizardPoint!=NULL){
		if(Buttons.count()>0){
			for(int i=0;i<Buttons.count();i++){
				GTWToolButtonColoredForTab	*wb=Buttons.value(i);
				if(wb->isChecked()==true){
					if(i<Buttons.count()-1){
						GTWToolButtonColoredForTab	*wnext=Buttons.value(i+1);
						wnext->setChecked(true);
						SlotIDClicked(i+1);
						break;
					}
				}
			}
		}
		else{
			for(int i=0;i<ButtonsStyle.count();i++){
				GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
				if(wb->isChecked()==true){
					if(i<ButtonsStyle.count()-1){
						GTWToolButtonStyledTab	*wnext=ButtonsStyle.value(i+1);
						wnext->setChecked(true);
						SlotIDClicked(i+1);
						break;
					}
				}
			}
		}
	}
}

void	GeneralTabWizard::SwapTab(QWidget *TabStack ,int index1 ,int index2)
{
	if(index1<index2)
		swap(index1,index2);
	QWidget *w=MainTab.widget(index1);
	MainTab.removeWidget(w);
	MainTab.insertWidget(index2,w);

	Swap(Msgs,index1,index2);
	for(int i=0;i<Msgs.count();i++){
		QString	S=Msgs.value(i);
		if(Buttons.count()>0){
			GTWToolButtonColoredForTab	*wb=Buttons.value(i);
			if(wb!=NULL){
				wb->setText(S);
			}
		}
		else{
			GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
			if(wb!=NULL){
				wb->setText(S);
			}
		}
	}
}
void	GeneralTabWizard::ClickTab(int id)
{
	if(Buttons.count()>0){
		Buttons[id]->toggle ();
	}
	else{
		ButtonsStyle[id]->toggle ();
	}
	SlotIDClicked(id);
}
QWidgetList	GeneralTabWizard::GetTabChildren(void)
{
	QWidgetList	ret;
	ret.append(&MainTab);
	return ret;
}
void	GeneralTabWizard::RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)
{
	for(int i=0;i<MainTab.count();i++){
		QWidget	*w=MainTab.widget(i);
		if(w==RemovedPage){
			if(Buttons.count()>0){
				GTWToolButtonColoredForTab	*wb=Buttons.value(i);
				Buttons.removeAt(i);
				if(wb!=NULL){
					delete	wb;
				}
			}
			else if(ButtonsStyle.count()>0){
				GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
				ButtonsStyle.removeAt(i);
				if(wb!=NULL){
					delete	wb;
				}
			}
			Msgs.removeAt(i);
		}
	}
	GUIFormBase::RemovedTabSheet(TabRoot ,RemovedPage);
	ResizeAction();
}

int	GeneralTabWizard::GetCountOfButtonDown(void)
{
	int	N=0;
	if(Buttons.count()>0){
		for(int i=0;i<Buttons.count();i++){
			GTWToolButtonColoredForTab	*wb=Buttons.value(i);
			if(wb->isChecked()==true){
				N++;
			}
		}
	}
	else{
		for(int i=0;i<ButtonsStyle.count();i++){
			GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
			if(wb->isChecked()==true){
				N++;
			}
		}
	}
	return N;
}


void	GeneralTabWizard::RxSync(QByteArray &f)
{
	int	*p=(int*)f.data();
	int	PushedID=*p;
	if(Buttons.count()>0){
		for(int i=0;i<Buttons.count();i++){
			GTWToolButtonColoredForTab	*wb=Buttons.value(i);
			if(wb->ID==PushedID){
				FromSync	=true;
				wb->setChecked(true);
				SlotIDClicked(i);
				FromSync	=false;
				break;
			}
		}
	}
	else{
		for(int i=0;i<ButtonsStyle.count();i++){
			GTWToolButtonStyledTab	*wb=ButtonsStyle.value(i);
			if(wb->ID==PushedID){
				FromSync	=true;
				wb->setChecked(true);
				SlotIDClicked(i);
				FromSync	=false;
				break;
			}
		}
	}
}
void	GeneralTabWizard::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	OpenTabPageSpecifiedBroadcaster	*OpenTabPageSpecifiedBroadcasterVar=dynamic_cast<OpenTabPageSpecifiedBroadcaster *>(v);
	if(OpenTabPageSpecifiedBroadcasterVar!=NULL){
		CommandShowPage(OpenTabPageSpecifiedBroadcasterVar->TabPageName);
		return;
	}
}

void	GeneralTabWizard::OperandChanged()
{
	int	Page=oPageNumber->Get();
	ClickTab(Page);
}

GUICmdChangeTab::GUICmdChangeTab(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeTab::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,TabName)==false)
		return false;
	return true;
}
bool	GUICmdChangeTab::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,TabName)==false)
		return false;
	return true;
}
void	GUICmdChangeTab::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,TabName);
	if(f!=NULL){
		GeneralTabWizard	*G=dynamic_cast<GeneralTabWizard *>(f);
		if(G!=NULL){
			G->ClickTab(ID);
		}
	}
}

