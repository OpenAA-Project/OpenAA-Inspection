/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabSheet\GeneralTabSheet.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralTabSheetResource.h"
#include "GeneralTabSheet.h"
#include "PasswordForm.h"
#include "swap.h"
#include "GeneralTabSheetPacket.h"




DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"TabSheet";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General TabSheet");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralTabSheet(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9){
		return(-1);
	}
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"Msgs";
	Data[0].Pointer				 =&((GeneralTabSheet *)Instance)->Msgs;
	Data[1].Type				 =/**/"North,West,East,South";
	Data[1].VariableNameWithRoute=LangSolver.GetString(GeneralTabSheet_LS,LID_0)/*"TabPosition"*/;
	Data[1].Pointer				 =&((GeneralTabSheet *)Instance)->TabPosition;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((GeneralTabSheet *)Instance)->CharColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"BackColor";
	Data[3].Pointer				 =&((GeneralTabSheet *)Instance)->BackColor;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"TransparentBackColor";
	Data[4].Pointer				 =&((GeneralTabSheet *)Instance)->TransparentBackColor;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"UnSelectTabColor";
	Data[5].Pointer				 =&((GeneralTabSheet *)Instance)->UnSelectTabColor;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"TransparentUnSelectTabColor";
	Data[6].Pointer				 =&((GeneralTabSheet *)Instance)->TransparentUnSelectTabColor;
	Data[7].Type				 =/**/"QFont";
	Data[7].VariableNameWithRoute=/**/"CFont";
	Data[7].Pointer				 =&((GeneralTabSheet *)Instance)->CFont;
	Data[8].Type				 =/**/"QStringList";
	Data[8].VariableNameWithRoute=/**/"Passwords";
	Data[8].Pointer				 =&((GeneralTabSheet *)Instance)->Passwords;

	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralTabSheet.png")));
}


//==================================================================================================


GeneralTabPage::GeneralTabPage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
}
GeneralTabPage::~GeneralTabPage(void)
{
}
void	GeneralTabPage::Prepare(void)
{
}
void	GeneralTabPage::ResizeAction(void)
{
}
/*
void	GeneralTabPage::keyPressEvent ( QKeyEvent * event )
{
	QObjectList Q=children();

	for(int i=0;i<Q.count();i++){
		GUIFormBase *C=dynamic_cast<GUIFormBase *>(Q[i]);
		if(C==NULL)
			continue;
		C->keyPressEvent (event);
	}
}
*/

GeneralTabSheet::GeneralTabSheet(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	TabPosition=/**/"North";
	Msgs.append(QString(/**/"Default"));
	Msgs.append(QString(/**/"Page1"));
	TransparentBackColor=false;
	resize(400,400);
	MainTab.setParent(this);
	MainTab.setFocusPolicy(Qt::NoFocus);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

GeneralTabSheet::~GeneralTabSheet(void)
{
	while(Msgs.count()<MainTab.count()){
		MainTab.removeTab(Msgs.count());
	}
}

void	GeneralTabSheet::Prepare(void)
{
/*	//Color
	QPalette palette;
	palette.setColor(QPalette::WindowText,CharColor);
	palette.setColor(QPalette::Background,BackColor);
	if(TransparentBackColor==true){
		BackColor.setAlpha(0);
	}
//	MainTab.setPalette(palette);
//	MainTab.setAutoFillBackground(true);
*/
	//Background
	QString strBackgroundStyleSheet;
	QString strTabColorStyleSheet=/**/"";
	QString strPaneStyleSheet=/**/"";
	if(TransparentBackColor==true){
		strBackgroundStyleSheet=/**/"background: none;";
	}
	else{
		strBackgroundStyleSheet	= /**/"background-color: "
								+ BackColor.name() + /**/";";
		strTabColorStyleSheet	= /**/"QTabBar::tab:selected {"
								+ strBackgroundStyleSheet + /**/"}";
		strPaneStyleSheet		= /**/"QTabWidget::pane {border-style: none;}";
	}

	for(int i=0;i<Msgs.count();i++){
		if(MainTab.count()>i){
			MainTab.setTabText(i,Msgs.value(i));
		}
		else{
			GeneralTabPage	*p=new GeneralTabPage(GetLayersBase(),NULL);
			p->SetComment(Msgs.value(i));
			MainTab.addTab(p,Msgs.value(i));
			p->setStyleSheet(strBackgroundStyleSheet);
//			p->setPalette(palette);
//			p->setAutoFillBackground(true);
		}
	}
	while(Msgs.count()<MainTab.count()){
		MainTab.removeTab(Msgs.count());
	}
	connect(&MainTab,SIGNAL(currentChanged(int)),this,SLOT(TabCurrentChanged(int)));

	if(TabPosition==/**/"North")
		MainTab.setTabPosition(QTabWidget::North);
	else if(TabPosition==/**/"South")
		MainTab.setTabPosition(QTabWidget::South);
	else if(TabPosition==/**/"East")
		MainTab.setTabPosition(QTabWidget::East);
	else if(TabPosition==/**/"West")
		MainTab.setTabPosition(QTabWidget::West);

	//Font
//	MainTab.setFont (CFont);
	QString strFont=/**/"";
	if(CFont.bold()==true){
		strFont	+=/**/"font-weight: bold;";
	}
	if(CFont.style()==QFont::StyleItalic){
		strFont	+=/**/"font-style: italic;";
	}
	else if(CFont.style()==QFont::StyleOblique){
		strFont	+=/**/"font-style: oblique;";
	}
	QString strFontStyleSheet	= /**/"font-family: "
								+ CFont.family() + /**/";"
								+ /**/"font-size: "
								+ QString::number(CFont.pointSize()) + /**/"pt;"
								+ strFont;

	//StyleSheet
	QString strStyleSheet	= /**/"QTabBar::tab {color: "
							+ CharColor.name() + /**/";"
							+ strFontStyleSheet + /**/"}"
							+ strTabColorStyleSheet
							+ strPaneStyleSheet;
	setStyleSheet(strStyleSheet);

	ResizeAction();
}

int	GeneralTabSheet::GetChildCount()
{
	return MainTab.count();
}
GUIFormBase	*GeneralTabSheet::GetChild(int index)
{
	return dynamic_cast<GUIFormBase*>(MainTab.widget(index));
}

GUIFormBase	*GeneralTabSheet::GetTopSurfaceWidget(int x ,int y)
{
	return dynamic_cast<GUIFormBase*>(MainTab.currentWidget());
}


void	GeneralTabSheet::ResizeAction()
{
	MainTab.resize(width(),height());
}

/*
void	GeneralTabSheet::keyPressEvent ( QKeyEvent * event )
{
	QObjectList Q=children();

	for(int i=0;i<Q.count();i++){
		GUIFormBase *C=dynamic_cast<GUIFormBase *>(Q[i]);
		if(C==NULL)
			continue;
		C->keyPressEvent (event);
	}
}
*/
void	GeneralTabSheet::SwapTab(QWidget *TabStack ,int index1 ,int index2)
{
	if(index1<index2)
		swap(index1,index2);
	QWidget *w=MainTab.widget(index1);
	QString tabstring=MainTab.tabText(index1);
	MainTab.removeTab(index1);
	MainTab.insertTab(index2,w,tabstring);
}

void	GeneralTabSheet::ExecNormalColor()
{
	//Background
	QString strBackgroundStyleSheet;
	if(TransparentBackColor==true){
		strBackgroundStyleSheet=/**/"background: none;";
	}
	else{
		strBackgroundStyleSheet	= /**/"background-color: "
								+ BackColor.name() + /**/";";
	}
	MainTab.widget(0)->setStyleSheet(strBackgroundStyleSheet);
}

void	GeneralTabSheet::ExecNGSizeColor()
{
	//Background
	QString strBackgroundStyleSheet;
	strBackgroundStyleSheet	= /**/"background-color: "
							+ NGSizeColor.name() + /**/";";
	MainTab.widget(0)->setStyleSheet(strBackgroundStyleSheet);
}

void	GeneralTabSheet::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdExecNormalColor	*CmdExecNormalColorVar=dynamic_cast<CmdExecNormalColor *>(packet);
	if(CmdExecNormalColorVar!=NULL){
		ExecNormalColor();
		return;
	}
	CmdExecNGSizeColor	*CmdExecNGSizeColorVar=dynamic_cast<CmdExecNGSizeColor *>(packet);
	if(CmdExecNGSizeColorVar!=NULL){
		ExecNGSizeColor();
		return;
	}
	return;
}

void	GeneralTabSheet::TabCurrentChanged( int index )
{
	if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==false
	&& GetLayersBase()->GetParamComm()->Mastered==true){
		//Password
		if(GetEditMode()==false){
			if(Passwords.count()>index){
				if(Passwords.value(index).trimmed().isEmpty()==false){
					PasswordForm PForm(Passwords.value(index).trimmed());
					if(PForm.exec()==false){
						//‘O‚ÌTag‚É–ß‚é
						MainTab.setCurrentIndex(0);
						return;
					}
				}
			}
			if(GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
				for(int page=0;page<GetPageNumb();page++){
					GUICmdChangeTabSheet	RCmd(GetLayersBase(),/**/"General",/**/"TabSheet",page);
					RCmd.ID=index;
					RCmd.TabName=GetName();
					RCmd.Send(NULL,page,0);
				}
			}
		}
	}

	GeneralTabPage	*p=dynamic_cast<GeneralTabPage	*>(MainTab.widget(index));
	if(p!=NULL){
		p->BroadcastChildrenAndOwnDirectly(GUIFormBase::_BC_StartPage,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
}

GUICmdChangeTabSheet::GUICmdChangeTabSheet(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeTabSheet::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,TabName)==false)
		return false;
	return true;
}
bool	GUICmdChangeTabSheet::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,TabName)==false)
		return false;
	return true;
}
void	GUICmdChangeTabSheet::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==false
	&& GetLayersBase()->GetParamComm()->Mastered==false){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"General",/**/"TabSheet",TabName);
		if(f!=NULL){
			GeneralTabSheet	*G=dynamic_cast<GeneralTabSheet *>(f);
			if(G!=NULL){
				((QTabWidget *)G->parentWidget())->setCurrentIndex(ID);
			}
		}
	}
}
