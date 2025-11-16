/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\ListHistoryButton\ListHistoryButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListHistoryButton.h"
#include "ListHistoryButtonForm.h"
#include "ListHistoryButtonPacket.h"
#include "ListHistoryButtonResource.h"
#include "XResult.h"

char	*sRoot=/**/"List";
char	*sName=/**/"HistoryButton";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show list of history button");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUIReqRemoveHistry(Base ,sRoot,sName ,-1);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListHistoryButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7){
		return(-1);
	}
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ListHistoryButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"CFont";
	Data[1].Pointer				 =&((ListHistoryButton *)Instance)->CFont;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"PopupFormX";
	Data[2].Pointer				 =&((ListHistoryButton *)Instance)->PopupFormX;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"PopupFormY";
	Data[3].Pointer				 =&((ListHistoryButton *)Instance)->PopupFormY;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"Popup";
	Data[4].Pointer				 =&((ListHistoryButton *)Instance)->Popup;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"AnytimeShow";
	Data[5].Pointer				 =&((ListHistoryButton *)Instance)->AnytimeShow;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"LocationInForm";
	Data[6].Pointer				 =&((ListHistoryButton *)Instance)->LocationInForm;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListHistoryButton.png")));
}

//=========================================================================================================

ListHistoryButton::ListHistoryButton(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ListHistoryButton");
	Msg=/**/"Show history";
	PopupFormX		=0;
	PopupFormY		=0;
	Popup			=false;
	AnytimeShow		=false;
	LocationInForm	=true;
	resize(60,25);
	connect(&Button	,SIGNAL(clicked(bool))	,this,SLOT(SlotClicked(bool)));
	connect(this	,SIGNAL(SignalResize())	,this,SLOT(ResizeAction()));

	//キー入力受付
	SetKeyGrab(true);

	ListHistoryForm=new ListHistoryButtonForm(Base,this);
}

ListHistoryButton::~ListHistoryButton()
{
}

void	ListHistoryButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont(CFont);

	if(AnytimeShow==true){
		SlotClicked(true);
	}

	ResizeAction();
}

void	ListHistoryButton::ResizeAction()
{
	Button.resize(width(),height());
}

void	ListHistoryButton::ShowInPlayer(int64 shownInspectionID)
{
	int	row=0;
	ListHistoryForm->GetTableWidgetHistory()->setRowCount(GetLayersBase()->GetResultHistryData()->GetNumber());
	for(ResultHistry *a=GetLayersBase()->GetResultHistryData()->GetLast();a!=NULL;a=a->GetPrev(),row++){
		QTableWidgetItem *W;
		W=ListHistoryForm->GetTableWidgetHistory()->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ListHistoryForm->GetTableWidgetHistory()->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->InspectionID));

		W=ListHistoryForm->GetTableWidgetHistory()->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ListHistoryForm->GetTableWidgetHistory()->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->ResultTime.toString(/**/"yy/MM/dd hh:mm:ss"));

		W=ListHistoryForm->GetTableWidgetHistory()->item ( row, 2);
		if(W==NULL){
			W=new QTableWidgetItem();
			ListHistoryForm->GetTableWidgetHistory()->setItem ( row, 2,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		switch(a->Result){
			case 0:	W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_0)/*"Not"*/);
					break;
			case 1:	W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_1)/*"OK"*/);
					break;
			case 2:	if(a->TimeOutBreak==true)
						W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_2)/*"TM-Halt"*/);
					else if(a->MaxErrorBreak==true)
						W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_3)/*"Er-Halt"*/);
					else
						W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_4)/*"NG"*/);
					break;
			default:	
					W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_5)/*"NG Other"*/);
					break;
		}
		W=ListHistoryForm->GetTableWidgetHistory()->item ( row, 3);
		if(W==NULL){
			W=new QTableWidgetItem();
			ListHistoryForm->GetTableWidgetHistory()->setItem ( row, 3,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		if(a->Written==true){
			W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_6)/*"*"*/);
		}
		else{
			W->setText(LangSolver.GetString(ListHistoryButton_LS,LID_7)/*"X"*/);
		}
	}
	ListHistoryForm->GetLabelOK() ->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(1)));
	ListHistoryForm->GetLabelNG() ->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(2)));
	ListHistoryForm->GetLabelSUM()->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetAllCount()));

	//検査後ポップアップ表示対応
	if(Popup==true){
		SlotClicked(true);
	}
}

void ListHistoryButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdListHistoryButtonKeyFunc	*CmdListHistoryButtonKeyFuncVar=dynamic_cast<CmdListHistoryButtonKeyFunc *>(packet);
	if(CmdListHistoryButtonKeyFuncVar!=NULL){
		if(CmdListHistoryButtonKeyFuncVar->KeyDeletePressRepeat==true){
			//履歴Formの表示対応
			if(ListHistoryForm->isHidden()==true){
				SlotClicked(true);
			}
		}
		else if(CmdListHistoryButtonKeyFuncVar->KeyDeleteRelease==true){
			//履歴の削除対応
			if(ListHistoryForm->GetTableWidgetHistory()->rowCount()>0){
				ListHistoryForm->GetTableWidgetHistory()->selectRow(0);
				ListHistoryForm->tableWidgetHistoryDoubleClicked(ListHistoryForm->GetTableWidgetHistory()->currentIndex());
			}
		}
	}
}

void ListHistoryButton::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Delete){
		if(event->isAutoRepeat()==true){
			//履歴Formの表示対応
			if(ListHistoryForm->isHidden()==true){
				SlotClicked(true);
			}
		}
		event->accept();
	}
}

void ListHistoryButton::keyReleaseEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Delete){
		if(event->isAutoRepeat()==false){
			//履歴の削除対応
			if(ListHistoryForm->GetTableWidgetHistory()->rowCount()>0){
				ListHistoryForm->GetTableWidgetHistory()->selectRow(0);
				ListHistoryForm->tableWidgetHistoryDoubleClicked(ListHistoryForm->GetTableWidgetHistory()->currentIndex());
			}
		}
		event->accept();
	}
}

void	ListHistoryButton::SlotClicked (bool checked)
{
	int x=0,y=0;
	if(LocationInForm==true){
		QWidget *f=parentWidget();
		while(f->parentWidget()!=NULL){
			f=f->parentWidget();
		}
		x+=f->x();
		y+=f->y();
	}
	ListHistoryForm->move(PopupFormX+x,PopupFormY+y);
	ListHistoryForm->show();
}
