/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingParameters\SettingParamDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SettingParamDialogResource.h"
#include "SettingParamDialog.h"
#include "XDLLOnly.h"
#include "XAlgorithmBase.h"
#include "XResultDLLManager.h"
#include "XGeneralFunc.h"
#include "EditScanPhaseNumber.h"
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "EditEachPageLocalDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


SettingParamDialog::SettingParamDialog(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	int EnableCondition=ParamEnableInTransfer;

	GetParamGlobal()->Push();
	QWidget	*WGeneral	=ui.tabWidgetAllParam->widget(0);
	QTabBar *Bar=ui.tabWidgetAllParam->tabBar();
	int	BarHeight=Bar->height();
	int	WGeneralWidth	=WGeneral->width();
	int	WGeneralHeight	=ui.tabWidgetAllParam->height()-BarHeight;

	WTabGeneral=new WEditParameterTab(GetParamGlobal() ,EnableCondition,WGeneral);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(WGeneralWidth,WGeneralHeight);

	QWidget	*WComm	=ui.tabWidgetAllParam->widget(1);
	WTabFormCommSetting=new FormCommSetting(GetLayersBase(),WComm);
	WTabFormCommSetting->move(0,0);
	WTabFormCommSetting->resize(WGeneralWidth,WGeneralHeight);

	QWidget	*WScanStrategy	=ui.tabWidgetAllParam->widget(2);
	WTabFormScanStrategy=new FormScanStrategy(GetLayersBase(),WScanStrategy);
	WTabFormScanStrategy->move(0,0);
	WTabFormScanStrategy->resize(WGeneralWidth,WGeneralHeight);

	if(GetLayersBase()->GetResultDLLBase()!=NULL){
		int	N=0;
		for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),N++){
			if(ui.tabWidgetResult->count()<=N){
				ui.tabWidgetResult->addTab(new QWidget(),L->GetDLLPoint()->GetDataText());
			}
			QWidget	*w=ui.tabWidgetResult->widget(N);
			QTabBar *ResultBar=ui.tabWidgetResult->tabBar();
			int	ResultBarHeight	=ResultBar->height();
			int	ResultWidth		=WGeneral->width();
			int	ResultHeight	=ui.tabWidgetResult->height()-ResultBarHeight;
			ResultDLLBaseRoot	*P=L->GetDLLPoint();

			WEditParameterTab	*WTabResult=new WEditParameterTab(P ,EnableCondition,w);
			WTabResult->move(0,0);
			WTabResult->resize(ResultWidth,ResultHeight);
		}
	}
	
	if(GetLayersBase()->GetLogicDLLBase()!=NULL){
		int	N=0;
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),N++){
			ParamBaseForAlgorithm	*P=L->GetInstance();
			WEditParameterTab	*WTabAlgorithm=new WEditParameterTab(P ,EnableCondition,NULL);
			//WTabAlgorithm->move(0,0);
			//WTabAlgorithm->resize(w->width(),w->height());

			//if(ui.tabWidgetAlgorithm->count()<=N){
				//ui.tabWidgetAlgorithm->addTab(WTabAlgorithm,L->GetInstance()->GetDataText());
				 ui.tabWidgetAlgorithm->insertTab(N,WTabAlgorithm,L->GetInstance()->GetDataText());
			//}
			//else{
			//	ui.tabWidgetAlgorithm->setTabText(N,L->GetInstance()->GetDataText());
			//}
		}
		//if(ui.tabWidgetAlgorithm->count()>=2){
		//	ui.tabWidgetAlgorithm->setCurrentIndex(0);
		//}
		//ui.tabWidgetAlgorithm->removeTab(N);
	}
	
	WTabFormOutlineOffset=new EditOutlineOffset(GetLayersBase()
												,ui.tabWidgetAllParam->widget(0)->height()-48
												,ui.tabWidgetAllParam->widget(5));
	WTabFormOutlineOffset->move(0,0);
	connect(WTabFormOutlineOffset,SIGNAL(Reflect()),this,SLOT(SlotRefrect()));
	connect(WTabFormOutlineOffset,SIGNAL(ChangedValue()),this,SLOT(SlotRefrect()));

	QWidget	*WGUI	=ui.tabWidgetAllParam->widget(6);
	WTabGUI=new WEditParameterTab(GetParamGUI() ,EnableCondition,WGUI);
	WTabGUI->move(0,0);
	WTabGUI->resize(WGeneralWidth,WGeneralHeight);

	QWidget	*WDirection	=ui.tabWidgetAllParam->widget(7);
	WTabDirection=new FormDirectionOnEachPage(GetLayersBase(),WDirection);
	WDirection->move(0,0);
	WDirection->resize(WGeneralWidth,WGeneralHeight);
    //--------------------------------------------------------------------
    WEditScanPhaseNumber	=new EditScanPhaseNumber(GetLayersBase(),ui.frameScanPhase);
    WEditScanPhaseNumber->show();
	WEditScanPhaseNumber->Show();

	ui.tabWidgetAllParam->setCurrentIndex(0);

	if(GetParamComm()->Mastered==true){
		ui.ButtonOK->setVisible(true);
	}
	else{
		ui.ButtonOK->setVisible(false);
	}
	if(GetLayersBase()->GetBootingLevel()!=0){
		ui.ButtonOutlineOffset->setVisible(false);
	}
	else{
		ui.ButtonOutlineOffset->setVisible(true);
	}
    //--------------------------------------------------------------------

	InstallOperationLog(this);

}

SettingParamDialog::~SettingParamDialog()
{

}

void SettingParamDialog::SlotRefrect()
{
	GetLayersBase()->GetMainWidget()->BroadcastDirectly(GUIFormBase::_BC_ShowInEdit,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void SettingParamDialog::on_ButtonOK_clicked()
{
	WTabFormScanStrategy->LoadFromWindow();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	//GetLayersBase()->SaveDefault();
	WTabGeneral->LoadFromWindow();
	WTabDirection->LoadFromWindow();

	if(GetLayersBase()->GetResultDLLBase()!=NULL){
		int	N=0;
		for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),N++){
			QWidget	*w=ui.tabWidgetResult->widget(N);
			QObject	*W=w->children().first();
			WEditParameterTab	*r=dynamic_cast<WEditParameterTab*>(W);
			if(r!=NULL){
				r->LoadFromWindow();
			}
		}
	}
	if(GetLayersBase()->GetLogicDLLBase()!=NULL){
		int	N=ui.tabWidgetAlgorithm->count();
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),N++){
			ParamBaseForAlgorithm	*P=L->GetInstance();
			for(int i=0;i<N;i++){
				QWidget	*w=ui.tabWidgetAlgorithm->widget(i);
				WEditParameterTab	*WTabAlgorithm=dynamic_cast<WEditParameterTab *>(w);
				if(WTabAlgorithm!=NULL && WTabAlgorithm->GetParamBase()==P){
					WTabAlgorithm->LoadFromWindow();
				}
			}
		}
	}
	WTabGUI->LoadFromWindow();

	QDir::setCurrent(GetLayersBase()->GetUserPath());
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());

	//WTabFormOutlineOffset->move(0,0);
	GetLayersBase()->WriteAllSettingFiles();
	GetLayersBase()->SendSettingsToSlave();
	GetLayersBase()->DeliverOutlineOffset();
	if(GetParamGlobal()->IsChangedCritically(/**/"AllocatedCountMasterBuff")==true){
		GetLayersBase()->ReallocateMasterCount(GetParamGlobal()->AllocatedCountMasterBuff);
	}
	if(GetParamGlobal()->IsChangedCritically(/**/"DotPerLine")==true
	|| GetParamGlobal()->IsChangedCritically(/**/"MaxLines")==true
	|| GetParamGlobal()->IsChangedCritically(/**/"LayerNumb")==true
	|| GetParamGlobal()->IsChangedCritically(/**/"PageNumb")==true){
		QMessageBox::critical ( NULL, LangSolver.GetString(SettingParamDialog_LS,LID_4)/*"Reboot"*/, LangSolver.GetString(SettingParamDialog_LS,LID_5)/*"Reboot software to change critical items"*/, QMessageBox::Ok);
		GetLayersBase()->CloseAll();
		QCoreApplication::quit();	
		//QApplication::closeAllWindows ();
	}
	close();
}

void SettingParamDialog::on_ButtonCancel_clicked()
{
	close();
}

void SettingParamDialog::resizeEvent(QResizeEvent *e)
{
	ui.frameBottom->setGeometry(0,height()-ui.frameBottom->height(),width(),ui.frameBottom->height());
	int	WB=(width()-ui.ButtonOK->width()-ui.ButtonCancel->width()-ui.pushButtonEachPage->width())/4;
	ui.pushButtonEachPage	->move(WB,10);
	ui.ButtonOK				->move(WB+ui.pushButtonEachPage->width()+WB,10);
	ui.ButtonCancel			->move(WB+ui.pushButtonEachPage->width()+WB+ui.ButtonOK->width()+WB,10);
	ui.tabWidgetAllParam->resize(width()-4,height()-4-ui.frameBottom->height());

	WTabGeneral			->resize(ui.tabWidgetAllParam->width()-8,ui.tabWidgetAllParam->height()-30);
	WTabFormCommSetting	->resize(ui.tabWidgetAllParam->width()-8,ui.tabWidgetAllParam->height()-30);
	ui.tabWidgetResult->resize(width()-30,height()-50);
	ui.tabWidgetAlgorithm->resize(width()-30,height()-50);

	WTabGUI->resize(ui.tabWidgetAllParam->width()-8,ui.tabWidgetAllParam->height()-30);

	if(GetLayersBase()->GetResultDLLBase()!=NULL){
		int	N=0;
		for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),N++){
			QWidget	*w=ui.tabWidgetResult->widget(N);
			QObject	*W=w->children().first();
			WEditParameterTab	*r=dynamic_cast<WEditParameterTab*>(W);
			if(r!=NULL){
				r->resize(ui.tabWidgetResult->width()-8,ui.tabWidgetResult->height()-30);
			}
		}
	}
}
void SettingParamDialog::on_tabWidgetAllParam_currentChanged(int)
{

}
void SettingParamDialog::on_ButtonOutlineOffset_clicked()
{
	if(GetLayersBase()->GetBootingLevel()==0){
		if(GetLayersBase()->SaveOutlineOffsetForDatabase()==false){
			QMessageBox::warning( NULL, LangSolver.GetString(SettingParamDialog_LS,LID_6)/*"Error"*/, LangSolver.GetString(SettingParamDialog_LS,LID_7)/*"Machine data has trouble in database"*/, QMessageBox::Ok);
		}
	}
}


void SettingParamDialog::on_pushButtonRowImageTable_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSettingParamImageTable	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.MoveUseStraight		=true;
		Cmd.MoveLoadFromDefault	=false;
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void SettingParamDialog::on_pushButtonLoadImageTable_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSettingParamImageTable	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.MoveUseStraight		=false;
		Cmd.MoveLoadFromDefault	=true;
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void SettingParamDialog::on_pushButtonEachPage_clicked()
{
    WTabGeneral->LoadFromWindow();
    EditEachPageLocalDialog D(GetLayersBase());
    if(D.exec()==true){
        WTabGeneral->ShowToWindow();
    }
}


//==========================================================================================================

GUICmdSettingParamImageTable::GUICmdSettingParamImageTable(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
	
{
	MoveUseStraight		=false;
	MoveLoadFromDefault	=false;
}

bool	GUICmdSettingParamImageTable::Load(QIODevice *f)
{
	if(::Load(f,MoveUseStraight)==false)
		return false;
	if(::Load(f,MoveLoadFromDefault)==false)
		return false;
	return true;
}
bool	GUICmdSettingParamImageTable::Save(QIODevice *f)
{
	if(::Save(f,MoveUseStraight)==false)
		return false;
	if(::Save(f,MoveLoadFromDefault)==false)
		return false;
	return true;
}

void	GUICmdSettingParamImageTable::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(MoveLoadFromDefault==true){
		GetLayersBase()->LoadAttrDefault();
	}
	if(MoveUseStraight==true){
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			for(int i=0;i<256;i++){
				GetLayersBase()->GetCurrentPageDataPhase()->GetPageData(localPage)->GetLayerData(Layer)->CData.RBrightTable[i]=i;
			}
		}
	}
}

