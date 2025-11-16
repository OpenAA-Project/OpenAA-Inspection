#include "PanelXYCalcResource.h"
#include "PanelXYCalcForm.h"
#include "ui_PanelXYCalcForm.h"

#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XSyncGUI.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "ButtonAutoMode.h"
#include <QElapsedTimer>
#include <QMessageBox>
#include "XEntryPoint.h"

PanelXYCalcForm::PanelXYCalcForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PanelXYCalcForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LimitMaxX	=800000;
	LimitMaxY	=800000;
	LimitMinX	=100000;
	LimitMinY	=100000;
	XSize		=99999999;
	YSize		=99999999;
	FlagSet		=false;
	iRegXSize	=NULL;
	iRegYSize	=NULL;
	iFlagSet	=NULL;
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
	ReflectOnlyWindowX		=true;
	ReflectOnlyWindowY		=true;
	ModeToChangePageCount	=true;
	
	GetParamGUI()->SetParam(&XSize					, /**/"PanelXYCalc",/**/"XSize"					,/**/"X Size(width) (um)"	);
	GetParamGUI()->SetParam(&YSize					, /**/"PanelXYCalc",/**/"YSize"					,/**/"Y Size(length) (um)"	);
	GetParamGUI()->SetParam(&XMerginPixels			, /**/"PanelXYCalc",/**/"XMerginPixels"			,/**/"X mergin (pixel)"		);
	GetParamGUI()->SetParam(&YMerginPixels			, /**/"PanelXYCalc",/**/"YMerginPixels"			,/**/"Y mergin (pixel)"		);
	GetParamGUI()->SetParam(&XMinOverlappedPixels	, /**/"PanelXYCalc",/**/"XMinOverlappedPixels"	,/**/"X overlap pixel"		);
	GetParamGUI()->SetParam(&DelayInEvenY			, /**/"PanelXYCalc",/**/"DelayInEvenY"			,/**/"Delay Y line in Even scan"	);
	GetParamGUI()->SetParam(&DelayInOddY			, /**/"PanelXYCalc",/**/"DelayInOddY"			,/**/"Delay Y line in Odd scan"		);
	GetParamGUI()->SetParam(&ReleaseAutoMode		, /**/"PanelXYCalc",/**/"ReleaseAutoMode"		,/**/"Release AutoMode in changed size"		);
	GetParamGUI()->SetParam(&LimitMaxX				, /**/"PanelXYCalc",/**/"LimitMaxX"				,/**/"Max X Size(width) (um)"	);
	GetParamGUI()->SetParam(&LimitMaxY				, /**/"PanelXYCalc",/**/"LimitMaxY"				,/**/"Max Y Size(length) (um)"	);
	GetParamGUI()->SetParam(&LimitMinX				, /**/"PanelXYCalc",/**/"LimitMinX"				,/**/"Min X Size(width) (um)"	);
	GetParamGUI()->SetParam(&LimitMinY				, /**/"PanelXYCalc",/**/"LimitMinY"				,/**/"Min Y Size(length) (um)"	);
}

PanelXYCalcForm::~PanelXYCalcForm()
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
}

void	PanelXYCalcForm::Prepare(void)
{
	double	m=((double)XSize)/1000.0;
	ui->doubleSpinBoxX->setValue(m);

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegXSize	=new SignalOperandInt(this,450,/**/"PanelXYCalc:iRegXSize");
			iRegYSize	=new SignalOperandInt(this,451,/**/"PanelXYCalc:iRegYSize");
			iFlagSet	=new SignalOperandBit(this,450,/**/"PanelXYCalc:iFlagSet");

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iRegXSize,&Error)==false){
				iRegXSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegYSize,&Error)==false){
				iRegYSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iFlagSet ,&Error)==false){
				iFlagSet->ShowErrorMessage(Error);
			}

			connect(iRegXSize	,SIGNAL(changed())	,this	,SLOT(OperandChangedX())	,Qt::QueuedConnection);
			connect(iRegYSize	,SIGNAL(changed())	,this	,SLOT(OperandChangedY())	,Qt::QueuedConnection);
		}
	}
	ui->label_LineCount	->setText(QString::number(GetMaxLines(0)));
	ui->label_ScanCount	->setText(QString::number(GetPageNumb()));

	if(SwitchLabel==true){
		QString	s1=ui->label->text();
		QString	s2=ui->label_2->text();
		ui->label	->setText(s2);
		ui->label_2	->setText(s1);
	}
}

void	PanelXYCalcForm::BuildForShow(void)
{
	bool	UpdatedX=false;
	bool	UpdatedY=false;

	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"XSIZE", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true && LimitMinX<=d && d<LimitMaxX){
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
		if(LimitMinX<=XSize && XSize<LimitMaxX){
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
		if(ok==true && LimitMinY<=d && d<LimitMaxY){
			double	m=((double)d)/1000.0;
			if(m>=5){
				ui->doubleSpinBoxY->setValue(m);
				UpdatedY=true;
				if(iRegYSize!=NULL){
					iRegYSize->Set(d);
				}
			}
		}
	}
	else{
		if(LimitMinY<=YSize && YSize<LimitMaxY){
			double	m=((double)YSize)/1000.0;
			ui->doubleSpinBoxY->setValue(m);
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
	int	tPage=0;
	ui->label_LineCount	->setText(QString::number(GetMaxLines(0)));
	ui->label_ScanCount	->setText(QString::number(GetPageNumb()));

	if(ModeIncrementStrategy==true){
		GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
		for(int s=0;s<GetPageNumb();s++){
			for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
				GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
			}
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		if(GetParamComm()->GetConnectedPCNumb()==0){
			GetParamGlobal()->SetCameraNo(page,0);
		}

		if(ModeXDirection==/**/"True"){
			GetParamGlobal()->SetPageXDir(page ,true);
		}
		if(ModeXDirection==/**/"False"){
			GetParamGlobal()->SetPageXDir(page ,false);
		}
		if(ModeXDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
		}
		if(ModeXDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
		}
		if(ModeYDirection==/**/"True"){
			GetParamGlobal()->SetPageYDir(page ,true);
		}
		if(ModeYDirection==/**/"False"){
			GetParamGlobal()->SetPageYDir(page ,false);
		}
		if(ModeYDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
		}
		if(ModeYDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
		}
		if((page&1)==0)
			GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
		else
			GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
	}

}
void PanelXYCalcForm::on_pushButtonSet_clicked()
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
	double	Ymm=ui->doubleSpinBoxY->value();
	int	d=Xmm*1000.0;
	if(LimitMinX<=d && d<LimitMaxX){
		if(UpdateMode==true){
			QVariant	dataX(d);
			if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
				QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_0)/*"Error"*/
											, LangSolver.GetString(PanelXYCalcForm_LS,LID_1)/*"Can't set XSIZE in MasterData"*/
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
	if(LimitMinY<=d && d<LimitMaxY){
		if(UpdateMode==true){
			QVariant	dataY(d);
			if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
				QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_2)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_3)/*"Can't set YSIZE in MasterData"*/
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
	int	tPage=0;
	double	XPixels=GetParamGlobal()->TransformUnitToPixelX(tPage,Xmm);
	double	YPixels=GetParamGlobal()->TransformUnitToPixelY(tPage,Ymm);

	int	iMaxLines=YPixels+YMerginPixels;
	//int	iPageNumb=ceil(((double)(XPixels+XMinOverlappedPixels-2*XMerginPixels))/(double)GetDotPerLine());
	int	iPageNumb;
	if(ModeToChangePageCount==true){
		iPageNumb=ceil(((double)(XPixels)/(double)(GetDotPerLine(tPage)+XMinOverlappedPixels-2*XMerginPixels)));
	}
	else{
		iPageNumb=GetPageNumb();
	}

	ui->label_LineCount	->setText(QString::number(iMaxLines));
	ui->label_ScanCount	->setText(QString::number(iPageNumb));

	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		if(QMessageBox::question(NULL
									,"Synchronized"
									,"Synchronize other ?"
									,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int	Cmd=1;
			::Save(&Buff,Cmd);
			::Save(&Buff,Xmm);
			::Save(&Buff,Ymm);

			::Save(&Buff,LimitMaxX);
			::Save(&Buff,LimitMaxY);
			::Save(&Buff,XSize);
			::Save(&Buff,YSize);
			::Save(&Buff,XMerginPixels);
			::Save(&Buff,YMerginPixels);
			::Save(&Buff,XMinOverlappedPixels);
			::Save(&Buff,ModeIncrementStrategy);
			::Save(&Buff,ModeXDirection);
			::Save(&Buff,ModeYDirection);
			::Save(&Buff,DelayInEvenY);
			::Save(&Buff,DelayInOddY);

			TxSync(Buff.buffer());
		}
	}
	int	OldPageNumb=GetPageNumb();
	if(OldPageNumb!=iPageNumb){
		GetParamGlobal()->PageNumb=iPageNumb;
		GetParamGlobal()->MaxLines=iMaxLines;
	}
	if(ModeIncrementStrategy==true){
		GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
		for(int s=0;s<GetPageNumb();s++){
			for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
				GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
			}
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		if(GetParamComm()->GetConnectedPCNumb()==0){
			GetParamGlobal()->SetCameraNo(page,0);
		}

		if(ModeXDirection==/**/"True"){
			GetParamGlobal()->SetPageXDir(page ,true);
		}
		if(ModeXDirection==/**/"False"){
			GetParamGlobal()->SetPageXDir(page ,false);
		}
		if(ModeXDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
		}
		if(ModeXDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
		}
		if(ModeYDirection==/**/"True"){
			GetParamGlobal()->SetPageYDir(page ,true);
		}
		if(ModeYDirection==/**/"False"){
			GetParamGlobal()->SetPageYDir(page ,false);
		}
		if(ModeYDirection==/**/"FlipTrue"){
			GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
		}
		if(ModeYDirection==/**/"FlipFalse"){
			GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
		}
		if((page&1)==0)
			GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
		else
			GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
	}
	if(OldPageNumb!=iPageNumb && ModeToChangePageCount==true){
		GetLayersBase()->WriteAllSettingFiles();
		GetParamGlobal()->PageNumb=OldPageNumb;
		GetLayersBase()->SendSettingsToSlave();
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		GetLayersBase()->Reallocate(GetPhaseNumb(),iPageNumb,LayerNumb);
		GetLayersBase()->LoadOutlineOffsetForDatabase();
		//GetLayersBase()->CloseAll();
		//QCoreApplication::quit();	
		//return;
	}
	if(GetMaxLines(0)!=iMaxLines){
		GetLayersBase()->ReallocXYPixels(GetDotPerLine(0),iMaxLines);
		GetLayersBase()->WriteAllSettingFiles();

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

}

void	PanelXYCalcForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateNewMasterSpecifiedBroadcaster	*C=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(C!=NULL){
		double	Xmm=ui->doubleSpinBoxX->value();
		double	Ymm=ui->doubleSpinBoxY->value();
		int	d=Xmm*1000.0;
		QVariant	dataX(d);
		if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
			QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_0)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_1)/*"Can't set XSIZE in MasterData"*/
										, QMessageBox::Ok);
		}
		if(iRegXSize!=NULL){
			iRegXSize->Set(d);
		}
		XSize=d;

		d=Ymm*1000.0;
		QVariant	dataY(d);
		if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
			QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_2)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_3)/*"Can't set YSIZE in MasterData"*/
										, QMessageBox::Ok);
		}
		if(iRegYSize!=NULL){
			iRegYSize->Set(d);
		}
		if(iFlagSet!=NULL){
			iFlagSet->Set(true);
		}
		YSize=d;
		GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());

		int	tPage=0;
		double	XPixels=GetParamGlobal()->TransformUnitToPixelX(tPage,Xmm);
		double	YPixels=GetParamGlobal()->TransformUnitToPixelY(tPage,Ymm);

		int	iMaxLines=YPixels+YMerginPixels;
		//int	iPageNumb=ceil(((double)(XPixels+XMinOverlappedPixels-2*XMerginPixels))/(double)GetDotPerLine());
		int	iPageNumb;
		if(ModeToChangePageCount==true){
			iPageNumb=ceil(((double)(XPixels)/(double)(GetDotPerLine(tPage)+XMinOverlappedPixels-2*XMerginPixels)));
		}
		else{
			iPageNumb=GetPageNumb();
		}

		ui->label_LineCount	->setText(QString::number(iMaxLines));
		ui->label_ScanCount	->setText(QString::number(iPageNumb));

		if(ModeIncrementStrategy==true){
			GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
			for(int s=0;s<GetPageNumb();s++){
				for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
					GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
				}
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			if(GetParamComm()->GetConnectedPCNumb()==0){
				GetParamGlobal()->SetCameraNo(page,0);
			}

			if(ModeXDirection==/**/"True"){
				GetParamGlobal()->SetPageXDir(page ,true);
			}
			if(ModeXDirection==/**/"False"){
				GetParamGlobal()->SetPageXDir(page ,false);
			}
			if(ModeXDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
			}
			if(ModeXDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
			}
			if(ModeYDirection==/**/"True"){
				GetParamGlobal()->SetPageYDir(page ,true);
			}
			if(ModeYDirection==/**/"False"){
				GetParamGlobal()->SetPageYDir(page ,false);
			}
			if(ModeYDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
			}
			if(ModeYDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
			}
			if((page&1)==0)
				GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
			else
				GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
		}
	}
}

void	PanelXYCalcForm::RxSync(QByteArray &f)
{
	double	Xmm;
	double	Ymm;

	QBuffer	Buff(&f);
			
	Buff.open(QIODevice::ReadWrite);
	int	Cmd;
	if(::Load(&Buff,Cmd)==false)
		return;
	if(::Load(&Buff,Xmm)==false)
		return;
	if(::Load(&Buff,Ymm)==false)
		return;

	if(::Load(&Buff,LimitMaxX)==false)
		return;
	if(::Load(&Buff,LimitMaxY)==false)
		return;
	if(::Load(&Buff,XSize)==false)
		return;
	if(::Load(&Buff,YSize)==false)
		return;
	if(::Load(&Buff,XMerginPixels)==false)
		return;
	if(::Load(&Buff,YMerginPixels)==false)
		return;
	if(::Load(&Buff,XMinOverlappedPixels)==false)
		return;
	if(::Load(&Buff,ModeIncrementStrategy)==false)
		return;
	if(::Load(&Buff,ModeXDirection)==false)
		return;
	if(::Load(&Buff,ModeYDirection)==false)
		return;
	if(::Load(&Buff,DelayInEvenY)==false)
		return;
	if(::Load(&Buff,DelayInOddY)==false)
		return;

	if(Cmd==1){
		ui->doubleSpinBoxX->setValue(Xmm);
		ui->doubleSpinBoxY->setValue(Ymm);

		QVariant	dataX(XSize);
		if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
			QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_0)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_1)/*"Can't set XSIZE in MasterData"*/
										, QMessageBox::Ok);
		}
		if(iRegXSize!=NULL){
			iRegXSize->Set(XSize);
		}

		QVariant	dataY(YSize);
		if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
			QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_2)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_3)/*"Can't set YSIZE in MasterData"*/
										, QMessageBox::Ok);
		}
		if(iRegYSize!=NULL){
			iRegYSize->Set(YSize);
		}
		if(iFlagSet!=NULL){
			iFlagSet->Set(true);
		}
		GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
		int	tPage=0;
		double	XPixels=GetParamGlobal()->TransformUnitToPixelX(tPage,Xmm);
		double	YPixels=GetParamGlobal()->TransformUnitToPixelY(tPage,Ymm);

		int	iMaxLines=YPixels+YMerginPixels;
		//int	iPageNumb=ceil(((double)(XPixels+XMinOverlappedPixels-2*XMerginPixels))/(double)GetDotPerLine());
		int	iPageNumb;
		if(ModeToChangePageCount==true){
			iPageNumb=ceil(((double)(XPixels)/(double)(GetDotPerLine(tPage)+XMinOverlappedPixels-2*XMerginPixels)));
		}
		else{
			iPageNumb=GetPageNumb();
		}

		ui->label_LineCount	->setText(QString::number(iMaxLines));
		ui->label_ScanCount	->setText(QString::number(iPageNumb));

		int	OldPageNumb=GetPageNumb();
		if(OldPageNumb!=iPageNumb){
			GetParamGlobal()->PageNumb=iPageNumb;
			GetParamGlobal()->MaxLines=iMaxLines;
		}
		if(ModeIncrementStrategy==true){
			GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
			for(int s=0;s<GetPageNumb();s++){
				for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
					GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
				}
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			if(GetParamComm()->GetConnectedPCNumb()==0){
				GetParamGlobal()->SetCameraNo(page,0);
			}

			if(ModeXDirection==/**/"True"){
				GetParamGlobal()->SetPageXDir(page ,true);
			}
			if(ModeXDirection==/**/"False"){
				GetParamGlobal()->SetPageXDir(page ,false);
			}
			if(ModeXDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
			}
			if(ModeXDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
			}
			if(ModeYDirection==/**/"True"){
				GetParamGlobal()->SetPageYDir(page ,true);
			}
			if(ModeYDirection==/**/"False"){
				GetParamGlobal()->SetPageYDir(page ,false);
			}
			if(ModeYDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
			}
			if(ModeYDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
			}
			if((page&1)==0)
				GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
			else
				GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
		}
		if(OldPageNumb!=iPageNumb && ModeToChangePageCount==true){
			GetLayersBase()->WriteAllSettingFiles();
			GetParamGlobal()->PageNumb=OldPageNumb;
			GetLayersBase()->SendSettingsToSlave();
					
			GetLayersBase()->CloseAll();
			QCoreApplication::quit();	
			return;
		}
		else if(GetMaxLines(0)!=iMaxLines){
			GetLayersBase()->ReallocXYPixels(GetDotPerLine(0),iMaxLines);
			GetLayersBase()->WriteAllSettingFiles();
		}
	}
	else if(Cmd==2){
		ui->doubleSpinBoxX->setValue(Xmm);

		QVariant	dataX(XSize);
		if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
			QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_0)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_1)/*"Can't set XSIZE in MasterData"*/
										, QMessageBox::Ok);
		}
		if(iRegXSize!=NULL){
			iRegXSize->Set(XSize);
		}

		if(iFlagSet!=NULL){
			iFlagSet->Set(true);
		}
		GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());

		int	tPage=0;
		double	XPixels=GetParamGlobal()->TransformUnitToPixelX(tPage,Xmm);
		int	iPageNumb;
		if(ModeToChangePageCount==true){
			iPageNumb=ceil(((double)(XPixels)/(double)(GetDotPerLine(0)+XMinOverlappedPixels-2*XMerginPixels)));
		}
		else{
			iPageNumb=GetPageNumb();
		}

		ui->label_ScanCount	->setText(QString::number(iPageNumb));

		int	OldPageNumb=GetPageNumb();
		if(OldPageNumb!=iPageNumb){
			GetParamGlobal()->PageNumb=iPageNumb;
		}
		if(ModeIncrementStrategy==true){
			GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
			for(int s=0;s<GetPageNumb();s++){
				for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
					GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
				}
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			if(GetParamComm()->GetConnectedPCNumb()==0){
				GetParamGlobal()->SetCameraNo(page,0);
			}

			if(ModeXDirection==/**/"True"){
				GetParamGlobal()->SetPageXDir(page ,true);
			}
			if(ModeXDirection==/**/"False"){
				GetParamGlobal()->SetPageXDir(page ,false);
			}
			if(ModeXDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
			}
			if(ModeXDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
			}
			if(ModeYDirection==/**/"True"){
				GetParamGlobal()->SetPageYDir(page ,true);
			}
			if(ModeYDirection==/**/"False"){
				GetParamGlobal()->SetPageYDir(page ,false);
			}
			if(ModeYDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
			}
			if(ModeYDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
			}
			if((page&1)==0)
				GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
			else
				GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
		}
		if(OldPageNumb!=iPageNumb && ModeToChangePageCount==true){
			GetLayersBase()->WriteAllSettingFiles();
			GetParamGlobal()->PageNumb=OldPageNumb;
			GetLayersBase()->SendSettingsToSlave();
					
			GetLayersBase()->CloseAll();
			QCoreApplication::quit();	
			return;
		}
	}
	else if(Cmd==3){
		ui->doubleSpinBoxY->setValue(Ymm);

		QVariant	dataY(YSize);
		if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
			QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYCalcForm_LS,LID_2)/*"Error"*/
										, LangSolver.GetString(PanelXYCalcForm_LS,LID_3)/*"Can't set YSIZE in MasterData"*/
										, QMessageBox::Ok);
		}
		if(iRegYSize!=NULL){
			iRegYSize->Set(YSize);
		}
		if(iFlagSet!=NULL){
			iFlagSet->Set(true);
		}
		GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
		int	tPage=0;
		double	YPixels=GetParamGlobal()->TransformUnitToPixelY(tPage,Ymm);

		int	iMaxLines=YPixels+YMerginPixels;

		ui->label_LineCount	->setText(QString::number(iMaxLines));

		if(ModeIncrementStrategy==true){
			GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
			for(int s=0;s<GetPageNumb();s++){
				for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
					GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
				}
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			if(GetParamComm()->GetConnectedPCNumb()==0){
				GetParamGlobal()->SetCameraNo(page,0);
			}

			if(ModeXDirection==/**/"True"){
				GetParamGlobal()->SetPageXDir(page ,true);
			}
			if(ModeXDirection==/**/"False"){
				GetParamGlobal()->SetPageXDir(page ,false);
			}
			if(ModeXDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
			}
			if(ModeXDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
			}
			if(ModeYDirection==/**/"True"){
				GetParamGlobal()->SetPageYDir(page ,true);
			}
			if(ModeYDirection==/**/"False"){
				GetParamGlobal()->SetPageYDir(page ,false);
			}
			if(ModeYDirection==/**/"FlipTrue"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
			}
			if(ModeYDirection==/**/"FlipFalse"){
				GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
			}
			if((page&1)==0)
				GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
			else
				GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
		}
		if(GetMaxLines(0)!=iMaxLines){
			GetLayersBase()->ReallocXYPixels(GetDotPerLine(0),iMaxLines);
			GetLayersBase()->WriteAllSettingFiles();
		}
	}
}

void	PanelXYCalcForm::OperandChangedX()
{
	if(iRegXSize!=NULL){
		int	d=iRegXSize->Get();
		ui->doubleSpinBoxX->setValue(((double)d)/1000.0);

		if(ReflectOnlyWindowX==false){
			XSize=d;

			GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
			double	Xmm=d/1000.0;
			int	tPage=0;
			double	XPixels=GetParamGlobal()->TransformUnitToPixelX(tPage,Xmm);

			int	iPageNumb=ceil(((double)(XPixels)/(double)(GetDotPerLine(tPage)+XMinOverlappedPixels-2*XMerginPixels)));

			ui->label_ScanCount	->setText(QString::number(iPageNumb));

			if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				int	Cmd=2;
				double	YmmDummy=0;
				::Save(&Buff,Cmd);
				::Save(&Buff,Xmm);
				::Save(&Buff,YmmDummy);

				::Save(&Buff,LimitMaxX);
				::Save(&Buff,LimitMaxY);
				::Save(&Buff,XSize);
				::Save(&Buff,YSize);
				::Save(&Buff,XMerginPixels);
				::Save(&Buff,YMerginPixels);
				::Save(&Buff,XMinOverlappedPixels);
				::Save(&Buff,ModeIncrementStrategy);
				::Save(&Buff,ModeXDirection);
				::Save(&Buff,ModeYDirection);
				::Save(&Buff,DelayInEvenY);
				::Save(&Buff,DelayInOddY);

				TxSync(Buff.buffer());
			}
			int	OldPageNumb=GetPageNumb();
			if(OldPageNumb!=iPageNumb && ModeToChangePageCount==true){
				GetParamGlobal()->PageNumb=iPageNumb;
			}
			if(ModeIncrementStrategy==true){
				GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
				for(int s=0;s<GetPageNumb();s++){
					for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
						GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
					}
				}
			}
			for(int page=0;page<GetPageNumb();page++){
				if(GetParamComm()->GetConnectedPCNumb()==0){
					GetParamGlobal()->SetCameraNo(page,0);
				}

				if(ModeXDirection==/**/"True"){
					GetParamGlobal()->SetPageXDir(page ,true);
				}
				if(ModeXDirection==/**/"False"){
					GetParamGlobal()->SetPageXDir(page ,false);
				}
				if(ModeXDirection==/**/"FlipTrue"){
					GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
				}
				if(ModeXDirection==/**/"FlipFalse"){
					GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
				}
				if(ModeYDirection==/**/"True"){
					GetParamGlobal()->SetPageYDir(page ,true);
				}
				if(ModeYDirection==/**/"False"){
					GetParamGlobal()->SetPageYDir(page ,false);
				}
				if(ModeYDirection==/**/"FlipTrue"){
					GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
				}
				if(ModeYDirection==/**/"FlipFalse"){
					GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
				}
				if((page&1)==0)
					GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
				else
					GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
			}
			if(OldPageNumb!=iPageNumb && ModeToChangePageCount==true){
				int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
				GetLayersBase()->Reallocate(GetPhaseNumb() , iPageNumb ,LayerNumb);
				GetLayersBase()->WriteAllSettingFiles();
				GetLayersBase()->LoadOutlineOffsetForDatabase();
				/*
				GetLayersBase()->WriteAllSettingFiles();
				GetParamGlobal()->PageNumb=OldPageNumb;
				GetLayersBase()->SendSettingsToSlave();
						
				GetLayersBase()->CloseAll();
				QCoreApplication::quit();	
				return;
				*/
			}
		}
		else{
			ui->label_ScanCount	->setText(QString::number(GetPageNumb()));
		}
	}
}
void	PanelXYCalcForm::OperandChangedY()
{
	if(iRegYSize!=NULL){
		int	tPage=0;
		int	d=iRegYSize->Get();
		ui->doubleSpinBoxY->setValue(((double)d)/1000.0);

		if(ReflectOnlyWindowY==false){
			YSize=d;
			GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
			double	Ymm=d/1000.0;

			double	YPixels=GetParamGlobal()->TransformUnitToPixelY(tPage,Ymm);

			int	iMaxLines=YPixels+YMerginPixels;
			ui->label_LineCount	->setText(QString::number(iMaxLines));

			if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				int	Cmd=3;
				double	XmmDummy=0;
				::Save(&Buff,Cmd);
				::Save(&Buff,XmmDummy);
				::Save(&Buff,Ymm);

				::Save(&Buff,LimitMaxX);
				::Save(&Buff,LimitMaxY);
				::Save(&Buff,XSize);
				::Save(&Buff,YSize);
				::Save(&Buff,XMerginPixels);
				::Save(&Buff,YMerginPixels);
				::Save(&Buff,XMinOverlappedPixels);
				::Save(&Buff,ModeIncrementStrategy);
				::Save(&Buff,ModeXDirection);
				::Save(&Buff,ModeYDirection);
				::Save(&Buff,DelayInEvenY);
				::Save(&Buff,DelayInOddY);

				TxSync(Buff.buffer());
			}
			int	OldPageNumb=GetPageNumb();
			if(ModeIncrementStrategy==true){
				GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
				for(int s=0;s<GetPageNumb();s++){
					for(int Layer=0;Layer<GetLayerNumb(s);Layer++){
						GetParamGlobal()->SetStrategyCode(s ,Layer ,s);
					}
				}
			}
			for(int page=0;page<GetPageNumb();page++){
				if(GetParamComm()->GetConnectedPCNumb()==0){
					GetParamGlobal()->SetCameraNo(page,0);
				}

				if(ModeXDirection==/**/"True"){
					GetParamGlobal()->SetPageXDir(page ,true);
				}
				if(ModeXDirection==/**/"False"){
					GetParamGlobal()->SetPageXDir(page ,false);
				}
				if(ModeXDirection==/**/"FlipTrue"){
					GetParamGlobal()->SetPageXDir(page ,(page&1)==0?true:false);
				}
				if(ModeXDirection==/**/"FlipFalse"){
					GetParamGlobal()->SetPageXDir(page ,(page&1)==0?false:true);
				}
				if(ModeYDirection==/**/"True"){
					GetParamGlobal()->SetPageYDir(page ,true);
				}
				if(ModeYDirection==/**/"False"){
					GetParamGlobal()->SetPageYDir(page ,false);
				}
				if(ModeYDirection==/**/"FlipTrue"){
					GetParamGlobal()->SetPageYDir(page ,(page&1)==0?true:false);
				}
				if(ModeYDirection==/**/"FlipFalse"){
					GetParamGlobal()->SetPageYDir(page ,(page&1)==0?false:true);
				}
				if((page&1)==0)
					GetParamGlobal()->SetPageYDelay(page ,DelayInEvenY);
				else
					GetParamGlobal()->SetPageYDelay(page ,DelayInOddY);
			}
			if(GetMaxLines(tPage)!=iMaxLines){
				GetLayersBase()->ReallocXYPixels(GetDotPerLine(tPage),iMaxLines);
				GetLayersBase()->WriteAllSettingFiles();

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
		}
		else{
			ui->label_LineCount	->setText(QString::number(GetMaxLines(tPage)));
		}
	}
}