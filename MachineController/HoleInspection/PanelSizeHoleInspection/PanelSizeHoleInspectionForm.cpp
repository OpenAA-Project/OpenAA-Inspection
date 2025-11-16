#include "PanelSizeHoleInspectionForm.h"
#include "ui_PanelSizeHoleInspectionForm.h"

#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#include "XResult.h"
#include "XResultDLLManager.h"
#include "ButtonAutoMode.h"
#include <QElapsedTimer>
#include <QMessageBox>
#include "XEntryPoint.h"

PanelSizeHoleInspectionForm::PanelSizeHoleInspectionForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PanelSizeHoleInspectionForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);

	LimitMaxX		=800000;
	LimitMaxY		=800000;
	LimitMinX		=100000;
	LimitMinY		=100000;
	XSize			=99999999;
	YSize			=99999999;
	FlagSet			=false;
	iRegXSize		=NULL;
	iRegYSize		=NULL;
	iFlagSet		=NULL;
	iRegScanCount	=NULL;
	XMerginPixels	=300;
	YMerginPixels	=300;
	XMinOverlappedPixels	=300;
	ModeIncrementStrategy	=true;
	ModeXDirection			=/**/"True";
	ModeYDirection			=/**/"FlipFalse";
	DelayInEvenY			=0;
	DelayInOddY				=0;
	ReleaseAutoMode			=true;
	SwitchLabel				=false;
	ReflectOnlyWindow		=true;
	AllocCamera1ToPage		=0;
	AllocCamera2ToPage		=1;
	AllocCamera3ToPage		=2;
	AllocCamera4ToPage		=3;

	OutlineOffsetL0	=0;
	OutlineOffsetL1	=0;
	OutlineOffsetL2	=0;
	OutlineOffsetL3	=0;
	OutlineOffsetL4	=0;
	OutlineOffsetL5	=0;
	OutlineOffsetL6	=0;
	OutlineOffsetL7	=0;

	GetParamGUI()->SetParam(&XSize					, /**/"SizeHoleInspection",/**/"XSize"					,/**/"X Size(width) (um)"	);
	GetParamGUI()->SetParam(&YSize					, /**/"SizeHoleInspection",/**/"YSize"					,/**/"Y Size(length) (um)"	);
	GetParamGUI()->SetParam(&XMerginPixels			, /**/"SizeHoleInspection",/**/"XMerginPixels"			,/**/"X mergin (pixel)"		);
	GetParamGUI()->SetParam(&YMerginPixels			, /**/"SizeHoleInspection",/**/"YMerginPixels"			,/**/"Y mergin (pixel)"		);
	GetParamGUI()->SetParam(&XMinOverlappedPixels	, /**/"SizeHoleInspection",/**/"XMinOverlappedPixels"	,/**/"X overlap pixel"		);
	GetParamGUI()->SetParam(&DelayInEvenY			, /**/"SizeHoleInspection",/**/"DelayInEvenY"			,/**/"Delay Y line in Even scan"	);
	GetParamGUI()->SetParam(&DelayInOddY			, /**/"SizeHoleInspection",/**/"DelayInOddY"			,/**/"Delay Y line in Odd scan"		);
	GetParamGUI()->SetParam(&ReleaseAutoMode		, /**/"SizeHoleInspection",/**/"ReleaseAutoMode"		,/**/"Release AutoMode in changed size"		);
	GetParamGUI()->SetParam(&LimitMaxX				, /**/"SizeHoleInspection",/**/"LimitMaxX"				,/**/"Max X Size(width) (um)"	);
	GetParamGUI()->SetParam(&LimitMaxY				, /**/"SizeHoleInspection",/**/"LimitMaxY"				,/**/"Max Y Size(length) (um)"	);
	GetParamGUI()->SetParam(&LimitMinX				, /**/"SizeHoleInspection",/**/"LimitMinX"				,/**/"Min X Size(width) (um)"	);
	GetParamGUI()->SetParam(&LimitMinY				, /**/"SizeHoleInspection",/**/"LimitMinY"				,/**/"Min Y Size(length) (um)"	);

	GetParamGUI()->SetParam(&AllocCamera1ToPage		, /**/"SizeHoleInspection",/**/"AllocCamera1ToPage"		,/**/"Allocation page number(0-3) for real camera1"	);
	GetParamGUI()->SetParam(&AllocCamera2ToPage		, /**/"SizeHoleInspection",/**/"AllocCamera2ToPage"		,/**/"Allocation page number(0-3) for real camera2"	);
	GetParamGUI()->SetParam(&AllocCamera3ToPage		, /**/"SizeHoleInspection",/**/"AllocCamera3ToPage"		,/**/"Allocation page number(0-3) for real camera3"	);
	GetParamGUI()->SetParam(&AllocCamera4ToPage		, /**/"SizeHoleInspection",/**/"AllocCamera4ToPage"		,/**/"Allocation page number(0-3) for real camera4"	);

	GetParamGUI()->SetParam(&OutlineOffsetL0		, /**/"SizeHoleInspection",/**/"OutlineOffsetL0"		,/**/"OutlineOffset in Scan-0"	);
	GetParamGUI()->SetParam(&OutlineOffsetL1		, /**/"SizeHoleInspection",/**/"OutlineOffsetL1"		,/**/"OutlineOffset in Scan-1"	);
	GetParamGUI()->SetParam(&OutlineOffsetL2		, /**/"SizeHoleInspection",/**/"OutlineOffsetL2"		,/**/"OutlineOffset in Scan-2"	);
	GetParamGUI()->SetParam(&OutlineOffsetL3		, /**/"SizeHoleInspection",/**/"OutlineOffsetL3"		,/**/"OutlineOffset in Scan-3"	);
	GetParamGUI()->SetParam(&OutlineOffsetL4		, /**/"SizeHoleInspection",/**/"OutlineOffsetL4"		,/**/"OutlineOffset in Scan-4"	);
	GetParamGUI()->SetParam(&OutlineOffsetL5		, /**/"SizeHoleInspection",/**/"OutlineOffsetL5"		,/**/"OutlineOffset in Scan-5"	);
	GetParamGUI()->SetParam(&OutlineOffsetL6		, /**/"SizeHoleInspection",/**/"OutlineOffsetL6"		,/**/"OutlineOffset in Scan-6"	);
	GetParamGUI()->SetParam(&OutlineOffsetL7		, /**/"SizeHoleInspection",/**/"OutlineOffsetL7"		,/**/"OutlineOffset in Scan-7"	);
}

PanelSizeHoleInspectionForm::~PanelSizeHoleInspectionForm()
{
    delete ui;

	if(iRegXSize!=NULL){
		delete	iRegXSize;
		iRegXSize=NULL;
	}
	if(iRegYSize!=NULL){
		delete	iRegYSize;
		iRegYSize=NULL;
	}
	if(iFlagSet!=NULL){
		delete	iFlagSet;
		iFlagSet=NULL;
	}
	if(iRegScanCount!=NULL){
		delete	iRegScanCount;
		iRegScanCount=NULL;
	}
}

void	PanelSizeHoleInspectionForm::Prepare(void)
{
	double	m=((double)XSize)/1000.0;
	ui->doubleSpinBoxX->setValue(m);

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegXSize		=new SignalOperandInt(this,450,/**/"PanelSizeHoleInspection:iRegXSize");
			iRegYSize		=new SignalOperandInt(this,451,/**/"PanelSizeHoleInspection:iRegYSize");
			iRegScanCount	=new SignalOperandInt(this,452,/**/"PanelSizeHoleInspection:iRegScanCount");
			iFlagSet		=new SignalOperandBit(this,450,/**/"PanelSizeHoleInspection:iFlagSet");

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iRegXSize		,&Error)==false){
				iRegXSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegYSize		,&Error)==false){
				iRegYSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegScanCount	,&Error)==false){
				iRegScanCount->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iFlagSet		,&Error)==false){
				iFlagSet->ShowErrorMessage(Error);
			}
		}
	}
	ui->label_LineCount	->setText(QString::number(GetMaxLines(0)));
	ui->label_ScanCount	->setText(QString::number(GetPageNumb()));
}

void	PanelSizeHoleInspectionForm::BuildForShow(void)
{
	bool	UpdatedX=false;
	bool	UpdatedY=false;

	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"XSIZE", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true && LimitMinX<=d && d<=LimitMaxX){
			double	m=((double)d)/1000.0;
			if(m>=5){
				ui->doubleSpinBoxX->setValue(m);
				UpdatedX=true;
				if(iRegXSize!=NULL){
					iRegXSize->Set(d);
				}
			}
		}
	}
	else{
		if(LimitMinX<=XSize && XSize<=LimitMaxX){
			double	m=((double)XSize)/1000.0;
			ui->doubleSpinBoxX->setValue(m);
			UpdatedX=true;
			if(iRegXSize!=NULL){
				iRegXSize->Set(XSize);
			}
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"YSIZE", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true && LimitMinY<=d && d<=LimitMaxY){
			double	m=((double)d)/1000.0;
			if(m>=5){
				//ui->doubleSpinBoxY->setValue(m);
				ui->comboBoxLength->setCurrentIndex((int)(m/80.0));
				UpdatedY=true;
				if(iRegYSize!=NULL){
					iRegYSize->Set(d);
				}
			}
		}
	}
	else{
		if(LimitMinY<=YSize && YSize<=LimitMaxY){
			double	m=((double)YSize)/1000.0;
			//ui->doubleSpinBoxY->setValue(m);
			ui->comboBoxLength->setCurrentIndex((int)(m/80.0)-1);
			UpdatedY=true;
			if(iRegYSize!=NULL){
				iRegYSize->Set(YSize);
			}
		}
	}

	if(iFlagSet!=NULL){
		if(UpdatedX==true || UpdatedY==true){
			iFlagSet->Set(true);
		}
	}
	int	iPageNumb=GetPageNumb();
	if((iPageNumb&1)!=0)
		iPageNumb++;

	int	iScanCount=iPageNumb/4;
	if(iRegScanCount!=NULL){
		iRegScanCount->Set(iScanCount);
	}

	ui->label_LineCount	->setText(QString::number(GetMaxLines(0)));
	ui->label_ScanCount	->setText(QString::number(iScanCount));

	if(ModeIncrementStrategy==true){
		GetParamGlobal()->SetMaxScanStrategy(iScanCount);
		for(int s=0;s<GetPageNumb();s++){
			int	scanN=s/4;
			
			for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
				GetParamGlobal()->SetStrategyCode(s ,Layer ,scanN);
			}
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		int	scanN=page/4;
		switch(page%4){
		case 0:
			GetParamGlobal()->SetCameraNo(page,AllocCamera1ToPage);		break;
		case 1:
			GetParamGlobal()->SetCameraNo(page,AllocCamera2ToPage);		break;
		case 2:
			GetParamGlobal()->SetCameraNo(page,AllocCamera3ToPage);		break;
		case 3:
			GetParamGlobal()->SetCameraNo(page,AllocCamera4ToPage);		break;
		}
	}

	for(int strategy=0;strategy<GetPageNumb();strategy++){
		if(ModeXDirection==/**/"True"){
			GetParamGlobal()->SetPageXDir(strategy ,true);
		}
		if(ModeXDirection==/**/"False"){
			GetParamGlobal()->SetPageXDir(strategy ,false);
		}
		if(ModeXDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageXDir(strategy ,(strategy&1)==0?true:false);
		}
		if(ModeXDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageXDir(strategy ,(strategy&1)==0?false:true);
		}
		if(ModeYDirection==/**/"True"){
			GetParamGlobal()->SetPageYDir(strategy ,true);
		}
		if(ModeYDirection==/**/"False"){
			GetParamGlobal()->SetPageYDir(strategy ,false);
		}
		if(ModeYDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageYDir(strategy ,(strategy&1)==0?true:false);
		}
		if(ModeYDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageYDir(strategy ,(strategy&1)==0?false:true);
		}
	}
	SetOutlineOffset();
}

void	PanelSizeHoleInspectionForm::SetOutlineOffset(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	scanN=page/4;
		switch(page%4){
		case 0:
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=2*scanN*(GetDotPerLine(page)-XMinOverlappedPixels);		break;
		case 1:
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=(2*scanN+1)*(GetDotPerLine(page)-XMinOverlappedPixels);	break;
		case 2:
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=2*scanN*(GetDotPerLine(page)-XMinOverlappedPixels)+GetPageNumb()*GetDotPerLine(page)/2;		break;
		case 3:
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=(2*scanN+1)*(GetDotPerLine(page)-XMinOverlappedPixels)+GetPageNumb()*GetDotPerLine(page)/2;	break;
		}
		switch(scanN){
		case 0:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL0;	break;
		case 1:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL1;	break;
		case 2:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL2;	break;
		case 3:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL3;	break;
		case 4:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL4;	break;
		case 5:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL5;	break;
		case 6:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL6;	break;
		case 7:	GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=OutlineOffsetL7;	break;
		}
	}

}
void PanelSizeHoleInspectionForm::on_pushButtonSet_clicked()
{
	bool	UpdateMode=false;
	if(GetLayersBase()->GetMasterCode()>0
	&& QMessageBox::warning(NULL
						,"Choose"
						,"Do you want to update size in Master Data?"
						,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		UpdateMode=true;
	}
	double	Xmm=ui->doubleSpinBoxX->value();
	double	Ymm=(ui->comboBoxLength->currentIndex()+1)*80.0;	//ui->doubleSpinBoxY->value();
	int	d=Xmm*1000.0;
	if(LimitMinX<=d && d<=LimitMaxX){
		if(UpdateMode==true){
			QVariant	dataX(d);
			if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
				QMessageBox::warning ( NULL, "Error"
											, "Can't set XSIZE in MasterData"
											, QMessageBox::Ok);
			}
		}
		if(iRegXSize!=NULL){
			iRegXSize->Set(d);
		}
		XSize=d;
	}
	else{
		QMessageBox::warning ( NULL, "Error"
									, "X size is out of limit"
									, QMessageBox::Ok);
		return;
	}

	d=Ymm*1000.0;
	if(LimitMinY<=d && d<=LimitMaxY){
		if(UpdateMode==true){
			QVariant	dataY(d);
			if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
				QMessageBox::warning ( NULL, "Error"
										, "Can't set YSIZE in MasterData"
										, QMessageBox::Ok);
			}
		}
		if(iRegYSize!=NULL){
			iRegYSize->Set(d);
		}
		if(iFlagSet!=NULL){
			iFlagSet->Set(true);
		}
		YSize=d;
	}
	else{
		QMessageBox::warning ( NULL, "Error"
									, "Y size is out of limit"
									, QMessageBox::Ok);
		return;
	}
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());

	double	XPixels=(Xmm*1000000.0)/GetParamGlobal()->ResolutionXNano;
	double	YPixels=(Ymm*1000000.0)/GetParamGlobal()->ResolutionYNano;

	int	iMaxLines=(((int)(YPixels+YMerginPixels))/1000)*1000;
	//int	iPageNumb=ceil(((double)(XPixels+XMinOverlappedPixels-2*XMerginPixels))/(double)GetDotPerLine());
	int	iPageNumb=ceil(((double)(XPixels)/(double)(GetDotPerLine(0)+XMinOverlappedPixels-2*XMerginPixels)));

	if((iPageNumb&1)!=0)
		iPageNumb++;
	iPageNumb=iPageNumb*2;

	int	iScanCount=iPageNumb/4;
	if(iRegScanCount!=NULL){
		iRegScanCount->Set(iScanCount);
	}

	ui->label_LineCount	->setText(QString::number(iMaxLines));
	ui->label_ScanCount	->setText(QString::number(iScanCount));

	int	OldPageNumb=GetPageNumb();
	if(OldPageNumb!=iPageNumb){
		GetLayersBase()->Reallocate(GetPhaseNumb() , iPageNumb ,GetLayerNumb(0));
		GetLayersBase()->ReallocXYPixels(GetDotPerLine(0) ,iMaxLines);
		GetLayersBase()->WriteAllSettingFiles();
		GetLayersBase()->LoadOutlineOffsetForDatabase();
		GetLayersBase()->SendSettingsToSlave();

		if(ReleaseAutoMode==true){

			GUIFormBase	*AGProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"AutoMode",/**/"");
			if(AGProp!=NULL){
				CmdGetStateOnAutoMode	ReqCmd(GetLayersBase());
				AGProp->TransmitDirectly(&ReqCmd);

				if(ReqCmd.AutoModeOn==true){
					CmdSetStateOnAutoMode	AmCmd(GetLayersBase());
					AmCmd.AutoModeOn=false;
					AGProp->TransmitDirectly(&AmCmd);

					QElapsedTimer	Timer;
					Timer.start();
					while(Timer.hasExpired(3000)==false){
						QApplication::processEvents();
					}

					AmCmd.AutoModeOn=true;
					AGProp->TransmitDirectly(&AmCmd);
				}
			}
		}
	}
	else if(iMaxLines!=GetMaxLines(0)){
		GetLayersBase()->ReallocXYPixels(GetDotPerLine(0) ,iMaxLines);
		GetLayersBase()->WriteAllSettingFiles();
		GetLayersBase()->SendSettingsToSlave();

		if(ReleaseAutoMode==true){

			GUIFormBase	*AGProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"AutoMode",/**/"");
			if(AGProp!=NULL){
				CmdGetStateOnAutoMode	ReqCmd(GetLayersBase());
				AGProp->TransmitDirectly(&ReqCmd);

				if(ReqCmd.AutoModeOn==true){
					CmdSetStateOnAutoMode	AmCmd(GetLayersBase());
					AmCmd.AutoModeOn=false;
					AGProp->TransmitDirectly(&AmCmd);

					QElapsedTimer	Timer;
					Timer.start();
					while(Timer.hasExpired(3000)==false){
						QApplication::processEvents();
					}

					AmCmd.AutoModeOn=true;
					AGProp->TransmitDirectly(&AmCmd);
				}
			}
		}
	}
	if(ModeIncrementStrategy==true){
		GetParamGlobal()->SetMaxScanStrategy(iScanCount);
		for(int s=0;s<GetPageNumb();s++){			
			int	scanN=s/4;
			for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
				GetParamGlobal()->SetStrategyCode(s ,Layer ,scanN);
			}
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		int	scanN=page/4;
		switch(page%4){
		case 0:
			GetParamGlobal()->SetCameraNo(page,AllocCamera1ToPage);		break;
		case 1:
			GetParamGlobal()->SetCameraNo(page,AllocCamera2ToPage);		break;
		case 2:
			GetParamGlobal()->SetCameraNo(page,AllocCamera3ToPage);		break;
		case 3:
			GetParamGlobal()->SetCameraNo(page,AllocCamera4ToPage);		break;
		}
	}
	for(int strategy=0;strategy<GetPageNumb();strategy++){
		if(ModeXDirection==/**/"True"){
			GetParamGlobal()->SetPageXDir(strategy ,true);
		}
		if(ModeXDirection==/**/"False"){
			GetParamGlobal()->SetPageXDir(strategy ,false);
		}
		if(ModeXDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageXDir(strategy ,(strategy&1)==0?true:false);
		}
		if(ModeXDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageXDir(strategy ,(strategy&1)==0?false:true);
		}
		if(ModeYDirection==/**/"True"){
			GetParamGlobal()->SetPageYDir(strategy ,true);
		}
		if(ModeYDirection==/**/"False"){
			GetParamGlobal()->SetPageYDir(strategy ,false);
		}
		if(ModeYDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageYDir(strategy ,(strategy&1)==0?true:false);
		}
		if(ModeYDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageYDir(strategy ,(strategy&1)==0?false:true);
		}
		if((strategy&1)==0)
			GetParamGlobal()->SetPageYDelay(strategy ,DelayInEvenY);
		else
			GetParamGlobal()->SetPageYDelay(strategy ,DelayInOddY);
	}

	SetOutlineOffset();
}
