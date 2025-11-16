#include "ButtonLightShortCutResource.h"
#include "ButtonLightShortCutForm.h"
#include "ui_ButtonLightShortCutForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XLightClass.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"


ButtonLightShortCutForm::ButtonLightShortCutForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonLightShortCutForm)
{
    ui->setupUi(this);

	Msg			=/**/"Light";
	ButtonColor	=Qt::green;
	IDNumber	=1;
	ShortcutKey	=-1;
	LastKeyTime	=0;

	Button.setParent(this);

	Button.setText(/**/"Change server");
	resize(60,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(clicked()), this ,SLOT(on_pushButton_clicked()));
	connect(&Button,SIGNAL(SignalRightClick()), this ,SLOT(SlotRightClick()));
}

ButtonLightShortCutForm::~ButtonLightShortCutForm()
{
    delete ui;
}
	
void	ButtonLightShortCutForm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setColor(ButtonColor,ButtonColor);
	ResizeAction();
	if(ShortcutKey>0){
		SetKeyGrab(true);
	}
}

void	ButtonLightShortCutForm::TransmitDirectly(GUIDirectMessage *packet)
{
}

QString	ButtonLightShortCutForm::GetFileName(void)
{
	QString	s	=GetLayersBase()->GetUserPath()
				+::GetSeparator()
				+QString(/**/"LightShortCut")
				+QString::number(IDNumber)
				+QString(/**/".dat");
	return s;
}

void ButtonLightShortCutForm::on_pushButton_clicked()
{
	QString	FileName=GetFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	N;
		if(::Load(&File,N)==false)
			return;
		for(int i=0;i<N;i++){
			QString	DLLName;
			if(::Load(&File,DLLName)==false)
				return;

			int32	SameNameCounter;
			if(::Load(&File,SameNameCounter)==false)
				return;
			QByteArray	Array;
			if(::Load(&File,Array)==false)
				return;
			int	iSameNameCounter=0;
			for(LightAccessList *L=GetLayersBase()->GetLightBase()->GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetDLLName()==DLLName){
					if(iSameNameCounter==SameNameCounter){
						QBuffer	Buff(&Array);
						Buff.open(QIODevice::ReadOnly);
						L->Load(&Buff);
						break;
					}
					else{
						iSameNameCounter++;
					}
				}
			}
		}
	}
	CmdReqReflectFromLightSpecifiedBroadcaster	V;
	BroadcastSpecifiedDirectly(&V);
}
void	ButtonLightShortCutForm::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonLightShortCutForm::SlotRightClick()
{
	if(QMessageBox::question ( NULL
			, LangSolver.GetString(ButtonLightShortCutForm_LS,LID_0)/*"Save Light condition"*/
			, LangSolver.GetString(ButtonLightShortCutForm_LS,LID_1)/*"Do you save current light condition?"*/
			,QMessageBox::Yes | QMessageBox::No
			, QMessageBox::Yes)==QMessageBox::Yes){
		QString	FileName=GetFileName();
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			int32	N=GetLayersBase()->GetLightBase()->GetCount();
			if(::Save(&File,N)==false)
				return;

			QStringList		LightDLLNames;

			for(LightAccessList *L=GetLayersBase()->GetLightBase()->GetFirst();L!=NULL;L=L->GetNext()){
				if(::Save(&File,L->GetDLLName())==false)
					return;
				int32	SameNameCounter=0;
				for(int i=0;i<LightDLLNames.count();i++){
					if(LightDLLNames[i]==L->GetDLLName()){
						SameNameCounter++;
					}
				}
				if(::Save(&File,SameNameCounter)==false)
					return;

				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				if(L->Save(&Buff)==false)
					return;
				if(::Save(&File,Buff.buffer())==false)
					return;
			}
		}
	}
}
void	ButtonLightShortCutForm::keyPressEvent ( QKeyEvent * event )
{
	int	Key=event->key();
	//GUIFormBase::keyPressEvent (event);
	if(Key==ShortcutKey){
		DWORD	CurrentKeyTime=::GetComputerMiliSec();
		DWORD	t=CurrentKeyTime-LastKeyTime;
		LastKeyTime=CurrentKeyTime;
		if(t<50)
			return;
		on_pushButton_clicked();
	}
}
