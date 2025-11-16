#include "AutofocusWithCameraResource.h"
#include "AutofocusWithCameraForm.h"
#include "ui_AutofocusWithCameraForm.h"
#include "XReviewCameraCommon.h"

#include "XSequenceRepairLocal.h"
#include "XGeneralFunc.h"
#include "XVRSControlCommand.h"

#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include <QElapsedTimer>
#include "SettingFocusAreaDialog.h"
#include "XDataInLayer.h"
#include "XLightClass.h"

AutofocusWithCameraForm::AutofocusWithCameraForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::AutofocusWithCameraForm)
{
    ui->setupUi(this);

	SetZSysPort		=225;
	ZPositionSysPort=225;
	MinZValue	=0;
	MaxZValue	=10000;

	FocusAreaX1	=0;
	FocusAreaY1	=0;
	FocusAreaX2	=1000;
	FocusAreaY2	=1000;
	WaitMilisecForAutoFocus	=500;

	CameraDLLRoot	=/**/"Review";
	CameraDLLName	=/**/"LiveCameraMightexUSB2";
	CameraDLLInst	=/**/"";

	GetParamGUI()->SetParam(&WaitMilisecForAutoFocus, /**/"AutofocusWithCamera",/**/"WaitMilisecForAutoFocus"
							,LangSolver.GetString(AutofocusWithCameraForm_LS,LID_0)/*"Waiting time milisec) for AutoFocus"*/		);

	iZPosition	=NULL;
	iSetZ		=NULL;
}

AutofocusWithCameraForm::~AutofocusWithCameraForm()
{
    delete ui;
}

void	AutofocusWithCameraForm::Prepare(void)
{
	ui->horizontalSlider->setMinimum(MinZValue);
	ui->horizontalSlider->setMaximum(MaxZValue);

	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				if(ZPositionSysPort>0){
					iZPosition		=new SignalOperandInt(this,ZPositionSysPort,/**/"AutofocusWithCamera:iZPosition");
					Param->SetSpecialOperand(iZPosition);
				}
				if(SetZSysPort>0){
					iSetZ		=new SignalOperandBit(this,SetZSysPort	,/**/"AutofocusWithCamera:iSetZ");
					Param->SetSpecialOperand(iSetZ);
				}
			}
		}
	}

}

void AutofocusWithCameraForm::on_pushButtonStart_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	GUIFormBase	*f=GetLayersBase()->FindByName(CameraDLLRoot ,CameraDLLName ,CameraDLLInst);
	if(f==NULL){
		ReEntrant=false;
		return;
	}
	if(iZPosition==NULL || iSetZ==NULL){
		ReEntrant=false;
		return;
	}
	ui->pushButtonStart->setEnabled(false);

	int	PosC	=iZPosition->Get();
	double MC=0;
	double ML=0;
	double MH=0;
	int LoopCount=0;

	int	DivNumb=10;
	int	DivDistance=(MaxZValue-MinZValue)/DivNumb;
	double	MaxD=0;
	int		MaxPos=0;
	for(int i=0;i<DivNumb;i++){
		double	D;
		int		Pos=MinZValue+DivDistance*i;
		bool ret=MoveCalc(f ,Pos,D);
		if(ret==true){
			if(MaxD<D){
				MaxD=D;
				MaxPos=Pos;
			}
		}
	}
	int	DivDistance2=2*DivDistance/DivNumb;
	for(int i=DivNumb-1;i>=0;i--){
		double	D;
		int		Pos=MaxPos+DivDistance2*(i-DivNumb/2);
		bool ret=MoveCalc(f ,Pos,D);
		if(ret==true){
			if(MaxD<D){
				MaxD=D;
				MaxPos=Pos;
			}
		}
	}
	int	Distance=DivDistance2/3;
	double	D;
	MoveCalc(f ,MaxPos,D);
	LoopCalc(f , MaxPos ,Distance ,ML, MC ,MH ,LoopCount);
	ReEntrant=false;
	ui->pushButtonStart->setEnabled(true);
}

void	AutofocusWithCameraForm::LoopCalc(GUIFormBase *f ,int PosC ,int Distance ,double ML, double MC ,double MH ,int &LoopCount)
{
	if(Distance>(MaxZValue-MinZValue)*0.2)
		Distance=(MaxZValue-MinZValue)*0.2;
	//if(LoopCount>5){
	if(Distance<10){
		MoveZ(PosC);
		return;
	}
	if(MC==0){
		if(MoveCalc(f ,PosC ,MC)==false)
			return;
	}
	int	PosL=PosC-Distance;
	if(PosL<MinZValue)
		PosL=MinZValue;	
	if(ML==0){
		if(MoveCalc(f ,PosL ,ML)==false)
			return;
	}
	int	PosH=PosC+Distance;
	if(PosH>MaxZValue)
		PosH=MaxZValue;
	if(MH==0){
		if(MoveCalc(f ,PosH ,MH)==false)
			return;
	}
	LoopCount++;
	if(ML==MC && MC==MH){
		return;
	}
	else if(ML==MC && MC>MH){
		MC=ML;
		ML=0;
		if(PosL==PosC)
			return;
		LoopCalc(f ,PosL ,Distance ,ML, MC ,MH ,LoopCount);
	}
	else if(ML<MC && MC==MH){
		if(PosH==PosC)
			return;
		MC=MH;
		MH=0;
		LoopCalc(f ,PosH ,Distance ,ML, MC ,MH ,LoopCount);
	}
	else if(ML<MC && MC>MH){
		ML=0;
		MH=0;
		LoopCalc(f ,PosC ,Distance/2 ,ML, MC ,MH ,LoopCount);
	}
	else if(ML>MC && MC>=MH){
		if(PosL==PosC)
			return;
		MC=ML;
		ML=0;
		LoopCalc(f ,PosL ,Distance ,ML, MC ,MH ,LoopCount);
	}
	else if(ML<=MC && MC<MH){
		if(PosH==PosC)
			return;
		MC=MH;
		MH=0;
		LoopCalc(f ,PosH ,Distance ,ML, MC ,MH ,LoopCount);
	}
	else if(ML>MC && MC<MH && ML>=MH){
		if(PosL==PosC)
			return;
		MC=ML;
		ML=0;
		LoopCalc(f ,PosL ,Distance ,ML, MC ,MH ,LoopCount);
	}
	else if(ML>MC && MC<MH && ML<MH){
		if(PosH==PosC)
			return;
		MC=MH;
		MH=0;
		LoopCalc(f ,PosH ,Distance ,ML, MC ,MH ,LoopCount);
	}

}
int Number=0;
double	ResultMax[10000];

bool	AutofocusWithCameraForm::MoveCalc(GUIFormBase *f ,int Pos ,double &RetValue)
{
	if(MoveZ(Pos)==false)
		return false;
	QElapsedTimer	Timer;
	Timer.start();
	while(Timer.hasExpired(WaitMilisecForAutoFocus)==false){
		QCoreApplication::processEvents();
	}

	//GSleep(100);
	CmdReqImageFromReviewCamera	RCmdK(GetLayersBase());
	RCmdK.Result=false;
	for(int k=0;k<3;k++){
		f->TransmitDirectly(&RCmdK);
		if(RCmdK.Result==true){
			break;
		}
	}
	if(RCmdK.Result==false){
		return false;
	}
	//QString ImageFile=QString("TestImg")+QString::number(Number)+QString(".png");
	//RCmdK.Image.save(ImageFile,"PNG");

	RetValue=CalcImage(RCmdK.Image);
	ResultMax[Number]=RetValue;
	Number++;

	return true;
}

bool	AutofocusWithCameraForm::MoveZ(int ZPos)
{
	iZPosition->Set(ZPos);
	iSetZ->Set(true);
	QElapsedTimer	Timer;
	Timer.start();
	while(Timer.hasExpired(30000)==false){
		if(iSetZ->Get()==false){
			break;
		}
		QCoreApplication::processEvents();
	}
	if(Timer.hasExpired(30000)==true)
		return false;
	ui->horizontalSlider->setValue(ZPos);
	return true;
}

double	AutofocusWithCameraForm::CalcImage(QImage &Image)
{
	int	W=FocusAreaX2-FocusAreaX1;
	int	H=FocusAreaY2-FocusAreaY1;

	int	Nx=W/100;
	if(Nx==0)
		Nx=1;
	int	Ny=H/100;
	if(Ny==0)
		Ny=1;
	int	Wx=(FocusAreaX2-FocusAreaX1)/Nx;
	int	Wy=(FocusAreaY2-FocusAreaY1)/Ny;

	double	AddedD=CalcRect(Image,FocusAreaX1,FocusAreaY1,FocusAreaX2,FocusAreaY2);
	/*
	for(int yn=0;yn<Ny;yn++){
		for(int xn=0;xn<Nx;xn++){
			int	x1=FocusAreaX1 + Wx*xn;
			int	y1=FocusAreaY1 + Wy*yn;
			int	x2=x1+Wx;
			int	y2=y1+Wy;
			if(x2>FocusAreaX2)
				x2=FocusAreaX2;
			if(y2>FocusAreaY2)
				y2=FocusAreaY2;
			if(x1>Image.width())
				x1=Image.width();
			if(x2>Image.width())
				x2=Image.width();
			if(y1>Image.height())
				y1=Image.height();
			if(y2>Image.height())
				y2=Image.height();
			double	d=CalcRect(Image,x1,y1,x2,y2);
			AddedD+=d;
		}
	}
	*/
	return AddedD;
}


void AutofocusWithCameraForm::on_pushButtonSettingArea_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(CameraDLLRoot ,CameraDLLName ,CameraDLLInst);
	if(f==NULL)
		return;
	CmdReqImageFromReviewCamera	RCmdK(GetLayersBase());
	RCmdK.Result=false;
	for(int k=0;k<3;k++){
		f->TransmitDirectly(&RCmdK);
		if(RCmdK.Result==true){
			break;
		}
	}
	if(RCmdK.Result==false){
		return;
	}

	SettingFocusAreaDialog	D(this);
	D.Initial(RCmdK.Image,FocusAreaX1,FocusAreaY1,FocusAreaX2,FocusAreaY2);
	int	Ret=D.exec();
	if(Ret==(int)true){
		FocusAreaX1=D.FocusAreaX1;
		FocusAreaY1=D.FocusAreaY1;
		FocusAreaX2=D.FocusAreaX2;
		FocusAreaY2=D.FocusAreaY2;
	}
}

void AutofocusWithCameraForm::on_pushButtonScanNEAR_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	GUIFormBase	*f=GetLayersBase()->FindByName(CameraDLLRoot ,CameraDLLName ,CameraDLLInst);
	if(f==NULL){
		ReEntrant=false;
		return;
	}
	if(iZPosition==NULL || iSetZ==NULL){
		ReEntrant=false;
		return;
	}

	ui->pushButtonScanNEAR->setEnabled(false);

	int	PosC	=iZPosition->Get();
	double MC=0;
	double ML=0;
	double MH=0;
	int LoopCount=5;

	int	DivNumb=10;
	int	DivDistance=(MaxZValue-MinZValue)/DivNumb/16;

	LoopCalc(f , PosC ,DivDistance ,ML, MC ,MH ,LoopCount);
	ReEntrant=false;

	ui->pushButtonScanNEAR->setEnabled(true);
}

QString	AutofocusWithCameraForm::GetFileName(void)
{
	QString	s	=GetLayersBase()->GetUserPath()
				+::GetSeparator()
				+QString(/**/"AutofocusWithCameraDarkLight.dat");
	return s;
}

void	AutofocusWithCameraForm::SaveDarkLightData(void)
{
	QString	FileName=GetFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
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

void	AutofocusWithCameraForm::LoadDarkLightData(void)
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
}
