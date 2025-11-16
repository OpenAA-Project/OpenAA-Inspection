#include "TesterLightDLL.h"

#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XLightClass.h"

extern	LightClassPack		*LightPack;
LightAccessList *LightPointer=NULL;

TesterLightDLL::TesterLightDLL(LayersBase *Base ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base)
{
	ui.setupUi(this);

	ui.listWidgetLightDLL->clear();
	for(LightAccessList *G=LightPack->GetFirst();G!=NULL;G=G->GetNext()){
		ui.listWidgetLightDLL->addItem(G->GetFileName());
	}
	ui.lineEditLightParamStr->setText(GetParamGlobal()->LightParamStr);

	IdleTimer.setInterval(100);
	connect(&IdleTimer,SIGNAL(timeout()),this,SLOT(TimeOutForIdle()),Qt::QueuedConnection);
	IdleTimer.start();
}

TesterLightDLL::~TesterLightDLL()
{
}
void	TesterLightDLL::closeEvent(QCloseEvent *event)
{
	if(LightPointer!=NULL){
		LightPack->RemoveList(LightPointer);
		delete	LightPointer;
		LightPointer=NULL;
	}
}
void TesterLightDLL::on_pushButtonLoadDLL_clicked()
{
	int	Index=ui.listWidgetLightDLL->currentRow();
	LightPointer=LightPack->GetItem(Index);
	if(LightPointer!=NULL){
		int32	ErrorCode;
		QString	Str=ui.lineEditLightParamStr->text();
		if(LightPointer->LoadDLLLibrary(ErrorCode,LightPointer->GetFileName(),Str)==true){
			ui.pushButtonLoadDLL->setEnabled(false);
		}
		connect(LightPointer->GetHandle(),SIGNAL(SignalReflectDataInDialog())		,this,SLOT(SlotReflectDataInDialog()));
		connect(LightPointer->GetHandle(),SIGNAL(SignalReflectOnOffInDialog(bool))	,this,SLOT(SlotReflectOnOffInDialog(bool)));
	}
	GetLayersBase()->CloseInformed();
}

void TesterLightDLL::on_toolButtonOnOff_clicked()
{
	if(LightPointer!=NULL){
		if(ui.toolButtonOnOff->isChecked()==true){
			LightPointer->LightOn();
		}
		else{
			LightPointer->LightOff();
		}
	}
}

void TesterLightDLL::on_pushButtonSetting_clicked()
{
	if(LightPointer!=NULL){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		LightPointer->ShowSetting(NULL);
	}
}
void TesterLightDLL::on_pushButtonSaveToDefault_clicked()
{
	if(LightPointer!=NULL){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		QFile	File(GetParamGlobal()->LightSettingFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(LightPack->Save(&File)==true){
				return;
			}
		}
	}
}

void TesterLightDLL::on_pushButtonLoadFromDefault_clicked()
{
	if(LightPointer!=NULL){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		if(QFile::exists(GetParamGlobal()->LightSettingFileName)==true){
			QFile	File(GetParamGlobal()->LightSettingFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(LightPack->Load(&File)==true){
					LightPack->SetPattern(0);
					return;
				}
			}
		}
	}
}

void TesterLightDLL::on_pushButtonSaveAs_clicked()
{
	if(LightPointer!=NULL){
		QString FileName=GetLayersBase()->LGetSaveFileName(0
													, QString("Save light parameter data")
													, QString()
													, QString(/**/"*.dat;;*.*"));
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(LightPack->Save(&File)==true){
				return;
			}
		}
	}
}

void TesterLightDLL::on_pushButtonLoadAs_clicked()
{
	if(LightPointer!=NULL){
		QString FileName=GetLayersBase()->LGetOpenFileName(0
										, QString("Load light parameter data")
										, QString()
										, QString(/**/"*.dat;;*.*"));
		if(QFile::exists(FileName)==true){
			QFile	File(FileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(LightPointer->Load(&File)==true){
					LightPack->SetPattern(0);
					return;
				}
			}
		}
	}
}
void	TesterLightDLL::TimeOutForIdle(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	MutexTimerFunc.lock();

	if(GetLayersBase()!=NULL){
		GetLayersBase()->LoopOnIdle();
	}
	if(LightPack!=NULL){
		LightPack->LoopOnIdle();
	}

	MutexTimerFunc.unlock();
	ReEntrant=false;
}

void	TesterLightDLL::SlotReflectDataInDialog()
{
	if(LightPointer!=NULL){
		LightPointer->GetHandle()->ReflectPhysical();
	}
}
void	TesterLightDLL::SlotReflectOnOffInDialog(bool LightOn)
{
	if(LightPointer!=NULL){
		LightPointer->GetHandle()->ReflectPhysicalTurnOn(LightOn);
	}
}
