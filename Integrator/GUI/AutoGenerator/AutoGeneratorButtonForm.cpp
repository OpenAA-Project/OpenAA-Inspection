#include "AutoGeneratorButtonForm.h"
#include "ui_AutoGeneratorButtonForm.h"
#include "AutoGeneratorForm.h"
#include "SelectStartDialog.h"
#include "XAutoGenerator.h"
#include "XIntegrationBase.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XPropertyDXFOperationPacket.h"
#include "XGUIRasterPacket.h"
#include "XPropertyAlignmentLargeCommon.h"
#include "XPropertyDotColorMatchingPacket.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

AutoGeneratorButtonForm::AutoGeneratorButtonForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::AutoGeneratorButtonForm)
{
    ui->setupUi(this);
    Window  =NULL;
    DefaultListFileName =/**/"AutoGenerator.AutoGen";
    iEnableRunning  =NULL;
	iAlarm			=NULL;
	FormRun			=NULL;
	RegNumberEnableRunning	=492;
	RegNumberAlarm			=493;
}

AutoGeneratorButtonForm::~AutoGeneratorButtonForm()
{
    delete ui;
}

void	AutoGeneratorButtonForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			SeqErrorInfo	Error;
			iEnableRunning			=new SignalOperandBit(this,RegNumberEnableRunning,/**/"AutoGeneratorButtonForm : iEnableRunning");
			if(Param->SetSpecialOperand(iEnableRunning	,&Error)==false){
				iEnableRunning->ShowErrorMessage(Error);
			}
			iAlarm					=new SignalOperandBit(this,RegNumberAlarm,/**/"AutoGeneratorButtonForm : iAlarm");
			if(Param->SetSpecialOperand(iAlarm	,&Error)==false){
				iAlarm->ShowErrorMessage(Error);
			}
		}
	}
	if(iEnableRunning!=NULL){
		iEnableRunning->Set(1);
	}
	if(iAlarm!=NULL){
		iAlarm->Set(0);
	}
}
void	AutoGeneratorButtonForm::AfterStartSequence(void)
{
	FormRun=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(FormRun!=NULL){
	}
}

void	AutoGeneratorButtonForm::BuildForShow(void)
{
	int	RelationCode=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
	QVariant	data;
	if(GetLayersBase()->LoadRelationFieldData(RelationCode,/**/"AutoGenerator", data)==true){
		QByteArray	Data=data.toByteArray();
		QBuffer	Buff(&Data);
		if(Buff.open(QIODevice::ReadOnly)==true){
			ListContainer.Load(&Buff);
		}
	}
}
void AutoGeneratorButtonForm::SaveListContainer(void)
{
	QFile	File(DefaultListFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		ListContainer.Save(&File);
	}

	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	ListContainer.Save(&Buff);
	QVariant	data(Buff.buffer());
	int	RelationCode=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
	GetLayersBase()->AddRelationFieldData(RelationCode,/**/"AutoGenerator", data);
}
void	AutoGeneratorButtonForm::SetRun(bool StateRun)
{
	ui->PushButtonRun->setChecked(StateRun);
	on_PushButtonRun_clicked();
}
void	AutoGeneratorButtonForm::SetInspectionRunOnly(bool StateRun)
{
	ui->PushButtonRun->setChecked(StateRun);
	FormRun=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(FormRun!=NULL){
		QStringList Args;
		bool ExeReturn;
		if(ui->PushButtonRun->isChecked()==true){
			Args.append("true");
		}
		else{
			Args.append("false");
		}
		FormRun->ExecuteMacro(/**/"SetInspectionRunOnly", Args, ExeReturn);
	}
}

void AutoGeneratorButtonForm::on_PushButtonRun_clicked()
{
	FormRun=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(FormRun!=NULL){
		QStringList Args;
		bool ExeReturn;
		if(ui->PushButtonRun->isChecked()==true){
			Args.append("true");
		}
		else{
			Args.append("false");
		}
		FormRun->ExecuteMacro(/**/"SetRun", Args, ExeReturn);
	}
}


void AutoGeneratorButtonForm::on_PushButtonSetting_clicked()
{
    if(Window==NULL){
        Window=new class AutoGeneratorForm(GetLayersBase(),this);
    }
    Window->show();
}


void AutoGeneratorButtonForm::on_PushButtonSelect_clicked()
{
    SelectStartDialog   D(GetLayersBase(),this);
    D.exec();
    if(D.Selected!=NULL){
		GetLayersBase()->ShowProcessingForm("新規作成中");

        CurrentList=*D.Selected;

		QByteArray	DXFData;
		if(CurrentList.DXFFileName.isEmpty()==false){
			QFile	DXFFile(CurrentList.DXFFileName);
			if(DXFFile.open(QIODevice::ReadOnly)==false){
				if(iAlarm!=NULL){
					iAlarm->Set(1);
				}
				QMessageBox::critical(NULL, "警告"
									, QString("DXFファイルを読み込めない:")+CurrentList.DXFFileName);
				return;
			}
			DXFData=DXFFile.readAll();
		}
		QByteArray	PDFData;
		if(CurrentList.PDFFileName.isEmpty()==false){
			QFile	PDFFile(CurrentList.PDFFileName);
			if(PDFFile.open(QIODevice::ReadOnly)==false){
				if(iAlarm!=NULL){
					iAlarm->Set(1);
				}
				QMessageBox::critical(NULL, "警告"
									, QString("PDFファイルを読み込めない:")+CurrentList.PDFFileName);
				return;
			}
			PDFData=PDFFile.readAll();
		}
		QByteArray	AlignData;
		if(CurrentList.AlignFileName.isEmpty()==false){
			QFile	AlignFile(CurrentList.AlignFileName);
			if(AlignFile.open(QIODevice::ReadOnly)==false){
				if(iAlarm!=NULL){
					iAlarm->Set(1);
				}
				QMessageBox::critical(NULL, "警告"
									, QString("位置合わせファイルを読み込めない:")+CurrentList.AlignFileName);
				return;
			}
			AlignData=AlignFile.readAll();
		}
		QByteArray	SpecialData;
		if(CurrentList.SpecialFileName.isEmpty()==false){
			QFile	SpecialFile(CurrentList.SpecialFileName);
			if(SpecialFile.open(QIODevice::ReadOnly)==false){
				if(iAlarm!=NULL){
					iAlarm->Set(1);
				}
				QMessageBox::critical(NULL, "警告"
									, QString("Specialファイルを読み込めない:")+CurrentList.SpecialFileName);
				return;
			}
			SpecialData=SpecialFile.readAll();
		}

		if(iEnableRunning!=NULL){
			iEnableRunning->Set(0);
		}

        for(int slaveNo=0;slaveNo<GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();slaveNo++){
            IntegrationCmdExecuteAutoGenerator  RCmd(GetLayersBase(),sRoot,sName,slaveNo);
			RCmd.DXFData	=DXFData;
			RCmd.PDFData	=PDFData;
			RCmd.AlignData	=AlignData;
			RCmd.SpecialData=SpecialData;
            RCmd.Send(NULL,slaveNo,0);
        }
		bool	NowOnIdle;
		do{
			NowOnIdle=true;
			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
					NowOnIdle=false;
				}
			}
		}while(NowOnIdle==false);

		for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<5000;){
			QCoreApplication::processEvents();
		}

		if(iEnableRunning!=NULL){
			iEnableRunning->Set(1);
		}
        GetLayersBase()->CloseProcessingForm();
    }
}

void	AutoGeneratorButtonForm::TransmitDirectly(GUIDirectMessage *packet)
{
    IntegrationCmdExecuteAutoGenerator  *IntegrationCmdExecuteAutoGeneratorVar=dynamic_cast<IntegrationCmdExecuteAutoGenerator *>(packet);
    if(IntegrationCmdExecuteAutoGeneratorVar!=NULL){
		GUIFormBase	*F1=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyDXFOperation",/**/"");
		if(F1!=NULL){
			CmdSetDXFWithSelfTransform	Cmd(GetLayersBase());
			Cmd.DXFData=IntegrationCmdExecuteAutoGeneratorVar->DXFData;
			F1->TransmitDirectly(&Cmd);
		}
		GUIFormBase	*F2=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
		if(F2!=NULL){
			CmdSetPDFWithSelfTransform	Cmd(GetLayersBase());
			Cmd.PDFData=IntegrationCmdExecuteAutoGeneratorVar->PDFData;
			F2->TransmitDirectly(&Cmd);
		}
		GUIFormBase	*F3=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
		if(F3!=NULL){
			CmdSetAlignmentData	Cmd(GetLayersBase());
			Cmd.AlignData=IntegrationCmdExecuteAutoGeneratorVar->AlignData;
			F3->TransmitDirectly(&Cmd);
		}
		GUIFormBase	*F4=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyDotColorMatching",/**/"");
		if(F4!=NULL){
			CmdSetSpecialData	Cmd(GetLayersBase());
			Cmd.SpecialData=IntegrationCmdExecuteAutoGeneratorVar->SpecialData;
			F4->TransmitDirectly(&Cmd);
		}
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"CalcFinalization",/**/"");
		if(f!=NULL){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"ExecuteOnlyByImage", Args, ExeReturn);
		}
		return;
	}
}
