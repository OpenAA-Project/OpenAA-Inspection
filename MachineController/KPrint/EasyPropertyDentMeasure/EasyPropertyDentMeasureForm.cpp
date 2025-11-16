#include "EasyPropertyDentMeasureResource.h"
#include "EasyPropertyDentMeasureForm.h"
#include "ui_EasyPropertyDentMeasureForm.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "XPropertyDentPacket.h"
#include "XMeasureLineMove.h"
#include "EasyDentMeasureImagePanel.h"
#include "InputPanelDialog.h"
#include <QComboBox>
#include "XPropertyAlignmentLargeCommon.h"
#include "XAlignmentLarge.h"
#include "XDotColorMatching.h"
#include "SettingFilmPositionDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


DentMeasurePointButton::DentMeasurePointButton(void)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	setCheckable(true);
	setStyleSheet(/**/"QPushButton {\n	border-style: outset;\n	border-width: 1px;\n	"
				/**/"border-radius: 20px;\n	border-color: gray;\n	"
				/**/"background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1,stop:0 rgba(160, 160, 160, 255), stop:1 rgba(120, 120, 120, 255));\n"
				/**/"}\n"
				/**/"QPushButton:checked { 	\n	"
				/**/"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(180, 0, 0, 255));\n}");

}
void	DentMeasurePointButton::SlotClicked()
{
	emit	SignalClicked(EndNo , MeasureNo);
}

//===============================================================

EasyPropertyDentMeasureForm::EasyPropertyDentMeasureForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyPropertyDentMeasureForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo	=0;
	BladeUpsideDown=false;
	GenerateFilmInLoadingMaster			=false;
	GenerateFilmInLoadingMasterSlaveNo	=1;
	GenerateFilmBlock					=true;

	ui->tableWidgetBladePos->setColumnWidth(0,172);
	ui->tableWidgetBladePos->setColumnWidth(1,68);
	ui->tableWidgetBladePos->setColumnWidth(2,68);
	ui->tableWidgetBladePos->setColumnWidth(3,68);
	ui->tableWidgetBladePos->setColumnWidth(4,68);
	ui->tableWidgetBladePos->setColumnWidth(5,68);
	ui->tableWidgetBladePos->setColumnWidth(6,68);
	ui->tableWidgetBladePos->setColumnWidth(7,70);
	ui->tableWidgetBladePos->setColumnWidth(8,48);
	ui->tableWidgetBladePos->setColumnWidth(9,48);

	ui->tableWidgetFilmPos->setColumnWidth(0,172);
	ui->tableWidgetFilmPos->setColumnWidth(1,68);
	ui->tableWidgetFilmPos->setColumnWidth(2,68);
	ui->tableWidgetFilmPos->setColumnWidth(3,68);
	ui->tableWidgetFilmPos->setColumnWidth(4,68);
	ui->tableWidgetFilmPos->setColumnWidth(5,68);
	ui->tableWidgetFilmPos->setColumnWidth(6,68);
	ui->tableWidgetFilmPos->setColumnWidth(7,70);
	ui->tableWidgetFilmPos->setColumnWidth(8,48);
	ui->tableWidgetFilmPos->setColumnWidth(9,48);


	for(int i=0;i<sizeof(Row2GUITable)/sizeof(Row2GUITable[0]);i++){
		Row2GUITable[i]=i;
	}

	InspectionIDNoFilmUpper		=28;
	InspectionIDNeedFilmUpper	=29;
	InspectionIDNoFilmLower		=28;
	InspectionIDNeedFilmLower	=29;
	FilmNeededOffsetY		=60;
	FilmNoNeedOffsetY		=120;
	GetParamGUI()->SetParam(&BladeUpsideDown, /**/"EasyPropertyDentMeasure",/**/"BladeUpsideDown"	
												,"Blade UpsideDown"		);
	GetParamGUI()->SetParam(&InspectionIDNoFilmUpper, /**/"EasyPropertyDentMeasure",/**/"InspectionIDNoFilmUpper"	
												,"InspectionID for NoFilm Upper"		);
	GetParamGUI()->SetParam(&InspectionIDNeedFilmUpper, /**/"EasyPropertyDentMeasure",/**/"InspectionIDNeedFilmUpper"	
												,"InspectionID for needed Film Upper"		);
	GetParamGUI()->SetParam(&InspectionIDNoFilmLower, /**/"EasyPropertyDentMeasure",/**/"InspectionIDNoFilmLower"	
												,"InspectionID for NoFilm Lower"		);
	GetParamGUI()->SetParam(&InspectionIDNeedFilmLower, /**/"EasyPropertyDentMeasure",/**/"InspectionIDNeedFilmLower"	
												,"InspectionID for needed Film Lower"		);
	GetParamGUI()->SetParam(&FilmNeededOffsetY, /**/"EasyPropertyDentMeasure",/**/"FilmNeededOffsetY"	
												,"Offset Y for Film-Needed"		);
	GetParamGUI()->SetParam(&FilmNoNeedOffsetY, /**/"EasyPropertyDentMeasure",/**/"FilmNoNeedOffsetY"	
												,"Offset Y for Film-NoNeed"		);

	GetParamGUI()->SetParam(&GenerateFilmBlock, /**/"EasyPropertyDentMeasure",/**/"GenerateFilmBlock"	
												,"Generate Film block"		);
	GetParamGUI()->SetParam(&GenerateFilmInLoadingMaster, /**/"EasyPropertyDentMeasure",/**/"GenerateFilmInLoadingMaster"	
												,"Generate Film in loading master data"		);
	GetParamGUI()->SetParam(&GenerateFilmInLoadingMasterSlaveNo, /**/"EasyPropertyDentMeasure",/**/"GenerateFilmInLoadingMasterSlaveNo"	
												,"Slave Nnumber to generate Film in loading master data"		);

	ui->toolButtonBlade->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);


	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

EasyPropertyDentMeasureForm::~EasyPropertyDentMeasureForm()
{
    delete ui;
}

void	EasyPropertyDentMeasureForm::ResizeAction()
{
}
	
static	QString	DefautFileName=/**/"DefaultDentMeasure.Blade";

void	EasyPropertyDentMeasureForm::Prepare(void)
{
	if(BladeUpsideDown==false){
		Row2GUITable[0]=0;
		Row2GUITable[1]=1;
		Row2GUITable[2]=2;
		Row2GUITable[3]=3;
		Row2GUITable[4]=4;
		Row2GUITable[5]=5;
		Row2GUITable[6]=6;
		Row2GUITable[7]=7;
		Row2GUITable[8]=8;
		Row2GUITable[9]=9;
		Row2GUITable[10]=10;
	}
	else{
		Row2GUITable[0]=1;
		Row2GUITable[1]=0;
		Row2GUITable[2]=2;
		Row2GUITable[3]=4;
		Row2GUITable[4]=3;
		Row2GUITable[5]=6;
		Row2GUITable[6]=5;
		Row2GUITable[7]=7;
		Row2GUITable[8]=8;
		Row2GUITable[9]=9;
		Row2GUITable[10]=10;
	}
	for(int i=0;i<sizeof(GUI2RowTable)/sizeof(GUI2RowTable[0]);i++){
		for(int j=0;j<sizeof(Row2GUITable)/sizeof(Row2GUITable[0]);j++){
			if(i==Row2GUITable[j]){
				GUI2RowTable[i]=j;
				break;
			}
		}
	}
	QString	FileName=GetLayersBase()->GetUserPath()+::GetSeparator()+DefautFileName;
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		BladeMeasureData.Load(&File);
		FilmMeasureData.Load(&File);
	}
	ShowList();
	ShowFilmList();
}

void	EasyPropertyDentMeasureForm::WriteDefault(void)
{
	QString	FileName=GetLayersBase()->GetUserPath()+::GetSeparator()+DefautFileName;
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		if(SlaveNo==0 && GProp->Param.GenerateBradeTop==true){
			FileName=GProp->Param.BradeDefFileNameTop;
		}
		else
		if(SlaveNo==1 && GProp->Param.GenerateBradeBottom==true){
			FileName=GProp->Param.BradeDefFileNameBottom;
		}
	}
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			BladeMeasureData.Save(&File);
			FilmMeasureData.Save(&File);
		}
	}
}

void	EasyPropertyDentMeasureForm::ReadyParam(void)
{
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		QString	FileName;
		if(SlaveNo==0 && GProp->Param.GenerateBradeTop==true){
			FileName=GProp->Param.BradeDefFileNameTop;
		}
		else
		if(SlaveNo==1 && GProp->Param.GenerateBradeBottom==true){
			FileName=GProp->Param.BradeDefFileNameBottom;
		}
		if(FileName.isEmpty()==false){
			QFile	File(FileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(BladeMeasureData.Load(&File)==true){
					ShowList();
				}
				if(FilmMeasureData.Load(&File)==true){
					ShowFilmList();
				}
			}
		}
	}
}
void	EasyPropertyDentMeasureForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqDentMeasureData	*CmdReqDentMeasureDataVar=dynamic_cast<CmdReqDentMeasureData *>(packet);
	if(CmdReqDentMeasureDataVar!=NULL){
		CmdReqDentMeasureDataVar->ManualCreateBlade=ui->PushButtonManualCreateArea->isChecked();
		return;
	}
	CmdIsEndPointMode	*CmdIsEndPointModeVar=dynamic_cast<CmdIsEndPointMode *>(packet);
	if(CmdIsEndPointModeVar!=NULL){
		CmdIsEndPointModeVar->ModeON=false;
		if(ui->toolButtonGenFilmLower->isChecked()==true){
			IntegrationCmdFilm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.GenerateMode	=GenerateFilmBlock;
			RCmd.UpperMode		=false;
			RCmd.UniversalDx	=CmdIsEndPointModeVar->UniversalDx;
			RCmd.UniversalDy	=CmdIsEndPointModeVar->UniversalDy;
			RCmd.Send(NULL,SlaveNo,0);
			ui->toolButtonGenFilmLower->setChecked(false);
		}
		else
		if(ui->toolButtonGenFilmUpper->isChecked()==true){
			IntegrationCmdFilm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.GenerateMode	=GenerateFilmBlock;
			RCmd.UpperMode		=true;
			RCmd.UniversalDx	=CmdIsEndPointModeVar->UniversalDx;
			RCmd.UniversalDy	=CmdIsEndPointModeVar->UniversalDy;
			RCmd.Send(NULL,SlaveNo,0);
			ui->toolButtonGenFilmUpper->setChecked(false);
		}
		else{
			if(ui->toolButtonBlade->isChecked()==true){
				for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
					for(int Col=8;Col<=9;Col++){
						QWidget *AnotherButton=ui->tableWidgetBladePos->cellWidget(row,Col);
						if(AnotherButton!=NULL){
							DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
							if(MAnotherButton!=NULL){
								if(MAnotherButton->isChecked()==true){
									CmdIsEndPointModeVar->EndNo=Col-8;
									CmdIsEndPointModeVar->MeasureNo	=row;
									CmdIsEndPointModeVar->ModeON=true;
									return;
								}
							}
						}
					}
				}
			}
			else
			if(ui->toolButtonFilm->isChecked()==true){
				for(int row=0;row<FilmMeasureData.CountGenDatas;row++){
					for(int Col=8;Col<=9;Col++){
						QWidget *AnotherButton=ui->tableWidgetFilmPos->cellWidget(row,Col);
						if(AnotherButton!=NULL){
							DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
							if(MAnotherButton!=NULL){
								if(MAnotherButton->isChecked()==true){
									CmdIsEndPointModeVar->EndNo=Col-8;
									CmdIsEndPointModeVar->MeasureNo	=100+row;
									CmdIsEndPointModeVar->ModeON=true;
									return;
								}
							}
						}
					}
				}
			}
		}
		CmdIsEndPointModeVar->ModeON=false;
		return;
	}
	CmdSetEndPoint	*CmdSetEndPointVar=dynamic_cast<CmdSetEndPoint *>(packet);
	if(CmdSetEndPointVar!=NULL){
		IntegrationCmdSetMeasureEndPoint	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.EndNo		=CmdSetEndPointVar->EndNo;
		RCmd.MeasureNo	=CmdSetEndPointVar->MeasureNo;
		RCmd.GlobalX	=CmdSetEndPointVar->GlobalX;
		RCmd.GlobalY	=CmdSetEndPointVar->GlobalY;
		RCmd.Send(NULL,SlaveNo,0);
		return;
	}
	CmdClearPushMode	*CmdClearPushModeVar=dynamic_cast<CmdClearPushMode *>(packet);
	if(CmdClearPushModeVar!=NULL){
		if(ui->toolButtonBlade->isChecked()==true){
			for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
				for(int Col=8;Col<=9;Col++){
					QWidget *AnotherButton=ui->tableWidgetBladePos->cellWidget(row,Col);
					if(AnotherButton!=NULL){
						DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
						if(MAnotherButton!=NULL){
							MAnotherButton->setChecked(false);
						}
					}
				}
			}
		}
		else
		if(ui->toolButtonFilm->isChecked()==true){
			for(int row=0;row<FilmMeasureData.CountGenDatas;row++){
				for(int Col=8;Col<=9;Col++){
					QWidget *AnotherButton=ui->tableWidgetFilmPos->cellWidget(row,Col);
					if(AnotherButton!=NULL){
						DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
						if(MAnotherButton!=NULL){
							MAnotherButton->setChecked(false);
						}
					}
				}
			}
		}
		return;
	}
	IntegrationGenerateAutomatically	*IntegrationGenerateAutomaticallyVar=dynamic_cast<IntegrationGenerateAutomatically *>(packet);
	if(IntegrationGenerateAutomaticallyVar!=NULL){
		GenerateAutomatically();
		return;
	}
	IntegrationCmdUpdateBladeList	*IntegrationCmdUpdateBladeListVar=dynamic_cast<IntegrationCmdUpdateBladeList *>(packet);
	if(IntegrationCmdUpdateBladeListVar!=NULL){
		ShowList();
		ShowFilmList();
		SetOnlyBladeThreshold();
		WriteDefault();
		return;
	}
	IntegrationReqBladeList	*IntegrationReqBladeListVar=dynamic_cast<IntegrationReqBladeList *>(packet);
	if(IntegrationReqBladeListVar!=NULL){
		IntegrationCmdReqCorrectValues	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationCmdAckCorrectValues	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.BladeMeasureData	=BladeMeasureData;
		RCmd.Mastered			=true;

		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			BladeMeasureData=ACmd.BladeMeasureData;
		}
		return;
	}
}

void	EasyPropertyDentMeasureForm::SetColumn0(QStringList	&List ,struct MeasureHVInfo	&p ,int grow,int ComboIndex)
{
	if(ui->toolButtonSetName->isChecked()==true){
		QLineEdit	*b=new QLineEdit();
		b->setText(QString::fromLocal8Bit(p.MeasureName));
		ui->tableWidgetBladePos->setCellWidget(grow,0,b);
	}
	else{
		::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,grow ,List ,ComboIndex);
	}
}

void	EasyPropertyDentMeasureForm::SetFilmColumn0(QStringList	&List ,struct MeasureHVInfo	&p ,int grow,int ComboIndex)
{
	if(ui->toolButtonSetName->isChecked()==true){
		QLineEdit	*b=new QLineEdit();
		b->setText(QString::fromLocal8Bit(p.MeasureName));
		ui->tableWidgetFilmPos->setCellWidget(grow,0,b);
	}
	else{
		::SetDataToTableComboBox(ui->tableWidgetFilmPos ,0 ,grow ,List ,ComboIndex);
	}
}
void	EasyPropertyDentMeasureForm::ShowList(void)
{
	QStringList	List;
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_1)/*"左から水平計測/上からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_2)/*"左から水平計測/下からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_3)/*"右から水平計測/上からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_4)/*"右から水平計測/下からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_5)/*"上から垂直計測/左からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_6)/*"上から垂直計測/右からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_7)/*"下から垂直計測/左からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_8)/*"下から垂直計測/右からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_9)/*"横幅/上からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_10)/*"横幅/下からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_11)/*"縦幅/左からの位置"*/);
	List.append(LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_12)/*"縦幅/右からの位置"*/);

	ui->tableWidgetBladePos->setRowCount(BladeMeasureData.CountGenDatas);
	for(int grow=0;grow<BladeMeasureData.CountGenDatas;grow++){
		int	row=GUI2RowTable[grow];
		struct	MeasureHVInfo	&p=BladeMeasureData.GenDatas[row];

		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==true && p.bPartnerFrom0==true){
			SetColumn0(List ,p ,grow,0);
			ShwListInner(grow,0);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==true && p.bPartnerFrom0==false){
			SetColumn0(List ,p ,grow,1);
			ShwListInner(grow,1);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==false && p.bPartnerFrom0==true){
			SetColumn0(List ,p ,grow,2);
			ShwListInner(grow,2);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==false && p.bPartnerFrom0==false){
			SetColumn0(List ,p ,grow,3);
			ShwListInner(grow,3);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==true && p.bPartnerFrom0==true){
			SetColumn0(List ,p ,grow,4);
			ShwListInner(grow,4);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==true && p.bPartnerFrom0==false){
			SetColumn0(List ,p ,grow,5);
			ShwListInner(grow,5);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==true){
			SetColumn0(List ,p ,grow,6);
			ShwListInner(grow,6);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==false){
			SetColumn0(List ,p ,grow,7);
			ShwListInner(grow,7);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==true && p.bPartnerFrom0==true){
			SetColumn0(List ,p ,grow,8);
			ShwListInner(grow,8);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==true && p.bPartnerFrom0==false){
			SetColumn0(List ,p ,grow,9);
			ShwListInner(grow,9);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==false && p.bPartnerFrom0==true){
			SetColumn0(List ,p ,grow,10);
			ShwListInner(grow,10);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==false && p.bPartnerFrom0==false){
			SetColumn0(List ,p ,grow,11);
			ShwListInner(grow,11);
		}
		else{
			SetColumn0(List ,p ,grow,0);
			ShwListInner(grow,0);
		}

		QWidget *w=ui->tableWidgetBladePos->cellWidget(grow,0);
		if(w!=NULL){
			QComboBox	*b=dynamic_cast<QComboBox *>(w);
			if(b!=NULL){
				connect(b,SIGNAL(currentIndexChanged (int)),this ,SLOT(SlotBladeListIndexChanged (int)));
			}
		}
		

		double	LenMin=p.CorrectLength-p.OKWidth/2.0;
		double	LenMax=p.CorrectLength+p.OKWidth/2.0;

		::SetDataToTable(ui->tableWidgetBladePos ,5 ,grow ,QString::number(LenMin,'f',2),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,6 ,grow ,QString::number(LenMax,'f',2),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,7 ,grow ,QString::number(p.RegLineLength),Qt::ItemIsEditable);

		QWidget *b1=ui->tableWidgetBladePos->cellWidget(grow,8);
		if(b1==NULL){
			DentMeasurePointButton	*b=new DentMeasurePointButton();
			b->EndNo=0;
			b->MeasureNo=row;
			ui->tableWidgetBladePos->setCellWidget(grow,8,b);
			connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotEndPointClicked(int,int)));
		}
		QWidget *b2=ui->tableWidgetBladePos->cellWidget(grow,9);
		if(b2==NULL){
			DentMeasurePointButton	*b=new DentMeasurePointButton();
			b->EndNo=1;
			b->MeasureNo=row;
			ui->tableWidgetBladePos->setCellWidget(grow,9,b);
			connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotEndPointClicked(int,int)));
		}
	}
}

void	EasyPropertyDentMeasureForm::ShowFilmList(void)
{
	QStringList	List;
	List.append("上側フィルムから刃上端");
	List.append("下側フィルムから刃下端");
	List.append("上側フィルムから紙上端");
	List.append("下側フィルムから紙下端");


	ui->tableWidgetFilmPos->setRowCount(FilmMeasureData.CountGenDatas);
	for(int grow=0;grow<FilmMeasureData.CountGenDatas;grow++){
		int	row=GUI2RowTable[grow];
		struct	MeasureHVInfo	&p=FilmMeasureData.GenDatas[row];

		if(p.bOnlyInside==true && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==true){
			SetFilmColumn0(List ,p ,grow,0);
			ShwFilmListInner(grow,0);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==false){
			SetFilmColumn0(List ,p ,grow,1);
			ShwFilmListInner(grow,1);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==true){
			SetFilmColumn0(List ,p ,grow,2);
			ShwFilmListInner(grow,2);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==false){
			SetFilmColumn0(List ,p ,grow,3);
			ShwFilmListInner(grow,3);
		}

		else{
			SetFilmColumn0(List ,p ,grow,0);
			ShwFilmListInner(grow,0);
		}

		QWidget *w=ui->tableWidgetFilmPos->cellWidget(grow,0);
		if(w!=NULL){
			QComboBox	*b=dynamic_cast<QComboBox *>(w);
			if(b!=NULL){
				connect(b,SIGNAL(currentIndexChanged (int)),this ,SLOT(SlotFilmListIndexChanged (int)));
			}
		}
		

		double	LenMin=p.CorrectLength-p.OKWidth/2.0;
		double	LenMax=p.CorrectLength+p.OKWidth/2.0;

		::SetDataToTable(ui->tableWidgetFilmPos ,5 ,grow ,QString::number(LenMin,'f',2),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetFilmPos ,6 ,grow ,QString::number(LenMax,'f',2),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetFilmPos ,7 ,grow ,QString::number(p.RegLineLength),Qt::ItemIsEditable);

		QWidget *b1=ui->tableWidgetFilmPos->cellWidget(grow,8);
		if(b1==NULL){
			DentMeasurePointButton	*b=new DentMeasurePointButton();
			b->EndNo=0;
			b->MeasureNo=row;
			ui->tableWidgetFilmPos->setCellWidget(grow,8,b);
			connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotFilmEndPointClicked(int,int)));
		}
		QWidget *b2=ui->tableWidgetFilmPos->cellWidget(grow,9);
		if(b2==NULL){
			DentMeasurePointButton	*b=new DentMeasurePointButton();
			b->EndNo=1;
			b->MeasureNo=row;
			ui->tableWidgetFilmPos->setCellWidget(grow,9,b);
			connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotFilmEndPointClicked(int,int)));
		}
	}
}
void	EasyPropertyDentMeasureForm::SlotBladeListIndexChanged ( int index )
{
	int	grow=ui->tableWidgetBladePos->currentRow();
	int	Index=::GetDataToTableComboBoxIndex(ui->tableWidgetBladePos ,0 ,grow);
	ShwListInner(grow, Index );
}
void	EasyPropertyDentMeasureForm::SlotFilmListIndexChanged ( int index )
{
	int	grow=ui->tableWidgetFilmPos->currentRow();
	int	Index=::GetDataToTableComboBoxIndex(ui->tableWidgetFilmPos ,0 ,grow);
	ShwFilmListInner(grow, Index );
}

const	QColor	InpColor(200,255,200);

void	EasyPropertyDentMeasureForm::ShwListInner(int grow, int Index )
{
	int	row=GUI2RowTable[grow];
	struct	MeasureHVInfo	&p=BladeMeasureData.GenDatas[row];
	if(Index==0){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,2,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==1){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,4,grow ,InpColor);
	}
	else
	if(Index==2){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,2,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==3){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,4,grow ,InpColor);
	}
	else
	if(Index==4){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,1,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==5){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,3,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==6){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,1,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==7){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,3,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==8){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,2,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==9){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,4,grow ,InpColor);
	}
	else
	if(Index==10){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,1,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else
	if(Index==11){
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,3,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
	else{
		::SetDataToTable(ui->tableWidgetBladePos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor(ui->tableWidgetBladePos  ,2,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetBladePos ,3,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,grow ,/**/"");
	}
}


void	EasyPropertyDentMeasureForm::ShwFilmListInner(int grow, int Index )
{
	int	row=GUI2RowTable[grow];
	struct	MeasureHVInfo	&p=FilmMeasureData.GenDatas[row];
	//if(Index==0){
		::SetDataToTable(ui->tableWidgetFilmPos ,1,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetFilmPos ,2,grow ,/**/"");
		::SetDataToTable(ui->tableWidgetFilmPos ,3,grow ,QString::number(p.PartnerPos,'f',2),Qt::ItemIsEditable);
		::SetTableColor (ui->tableWidgetFilmPos ,3,grow ,InpColor);
		::SetDataToTable(ui->tableWidgetFilmPos ,4,grow ,/**/"");
	//}
}
void	EasyPropertyDentMeasureForm::GetDataFromList(void)
{
	for(int grow=0;grow<BladeMeasureData.CountGenDatas;grow++){
		int	row=GUI2RowTable[grow];
		struct	MeasureHVInfo	&p=BladeMeasureData.GenDatas[row];
		QWidget *w=ui->tableWidgetBladePos->cellWidget(grow,0);
		QLineEdit	*b=dynamic_cast<QLineEdit *>(w);
		if(b!=NULL){
			QString	s=b->text();
			::QString2Char(s ,p.MeasureName ,sizeof(p.MeasureName));

			if(p.bOnlyInside	==false
			&& p.bHorizontal	==true
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==true
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==true
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==true
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==false
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==false
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==false
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==false
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==true
			&& p.bHorizontal	==true
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==true
			&& p.bHorizontal	==true
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==true
			&& p.bHorizontal	==false
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==true
			&& p.bHorizontal	==false
			&& p.bFrom0			==true
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else{
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.PartnerPos=s.toDouble();
			}
		}
		else{
			int	Index=::GetDataToTableComboBoxIndex(ui->tableWidgetBladePos ,0 ,grow);
			if(Index==0){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=true;
				p.bFrom0		=true;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==1){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=true;
				p.bFrom0		=true;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==2){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=true;
				p.bFrom0		=false;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==3){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=true;
				p.bFrom0		=false;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==4){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=false;
				p.bFrom0		=true;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==5){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=false;
				p.bFrom0		=true;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==6){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=false;
				p.bFrom0		=false;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==7){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=false;
				p.bFrom0		=false;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==8){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.bOnlyInside	=true;
				p.bHorizontal	=true;
				p.bFrom0		=true;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==9){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,grow);
				p.bOnlyInside	=true;
				p.bHorizontal	=true;
				p.bFrom0		=true;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==10){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,grow);
				p.bOnlyInside	=true;
				p.bHorizontal	=false;
				p.bFrom0		=true;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==11){
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,grow);
				p.bOnlyInside	=true;
				p.bHorizontal	=false;
				p.bFrom0		=true;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else{
				QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=true;
				p.bFrom0			=true;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
		}
		QString	RangeMinStr=GetDataToTable(ui->tableWidgetBladePos ,5 ,grow);
		QString	RangeMaxStr=GetDataToTable(ui->tableWidgetBladePos ,6 ,grow);
		double	RangeMin=RangeMinStr.toDouble();
		double	RangeMax=RangeMaxStr.toDouble();
		p.OKWidth		=fabs(RangeMax-RangeMin);
		p.CorrectLength	=(RangeMax+RangeMin)/2.0;
		QString	sL=GetDataToTable(ui->tableWidgetBladePos ,7 ,grow);
		p.RegLineLength=sL.toInt();
	}

	for(int grow=0;grow<FilmMeasureData.CountGenDatas;grow++){
		int	row=GUI2RowTable[grow];
		struct	MeasureHVInfo	&p=FilmMeasureData.GenDatas[row];
		QWidget *w=ui->tableWidgetFilmPos->cellWidget(grow,0);
		QLineEdit	*b=dynamic_cast<QLineEdit *>(w);
		if(b!=NULL){
			QString	s=b->text();
			::QString2Char(s ,p.MeasureName ,sizeof(p.MeasureName));

			if(p.bOnlyInside	==true
			&& p.bHorizontal	==false
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==true
			&& p.bHorizontal	==false
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==false
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==true){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else
			if(p.bOnlyInside	==false
			&& p.bHorizontal	==false
			&& p.bFrom0			==false
			&& p.bPartnerFrom0	==false){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
			else{
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.PartnerPos=s.toDouble();
			}
		}
		else{
			int	Index=::GetDataToTableComboBoxIndex(ui->tableWidgetFilmPos ,0 ,grow);
			if(Index==0){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.bOnlyInside	=true;
				p.bHorizontal	=false;
				p.bFrom0		=false;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==1){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.bOnlyInside	=true;
				p.bHorizontal	=false;
				p.bFrom0		=false;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==2){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=false;
				p.bFrom0		=false;
				p.bPartnerFrom0	=true;
				p.PartnerPos=s.toDouble();
			}
			else
			if(Index==3){
				QString	s=GetDataToTable(ui->tableWidgetFilmPos ,3 ,grow);
				p.bOnlyInside	=false;
				p.bHorizontal	=false;
				p.bFrom0		=false;
				p.bPartnerFrom0	=false;
				p.PartnerPos=s.toDouble();
			}
		}
		QString	RangeMinStr=GetDataToTable(ui->tableWidgetFilmPos ,5 ,grow);
		QString	RangeMaxStr=GetDataToTable(ui->tableWidgetFilmPos ,6 ,grow);
		double	RangeMin=RangeMinStr.toDouble();
		double	RangeMax=RangeMaxStr.toDouble();
		p.OKWidth		=fabs(RangeMax-RangeMin);
		p.CorrectLength	=(RangeMax+RangeMin)/2.0;
		QString	sL=GetDataToTable(ui->tableWidgetFilmPos ,7 ,grow);
		p.RegLineLength=sL.toInt();
	}
}
void EasyPropertyDentMeasureForm::on_toolButtonAutoGenerate_clicked()
{
	emit	SignalBusy();

	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		//if((SlaveNo==0 && GProp->Param.GenerateBradeTop==true)
		//|| (SlaveNo==1 && GProp->Param.GenerateBradeBottom==true)){
			GenerateAutomaticallyPure();
			GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
			BroadcastRepaintAll();
		//}
	}

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();
}

void	EasyPropertyDentMeasureForm::GenerateAutomatically(void)
{
	GetDataFromList();
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		if((SlaveNo==0 && GProp->Param.GenerateBradeTop==true)
		|| (SlaveNo==1 && GProp->Param.GenerateBradeBottom==true)){
			GenerateAutomaticallyPure();
		}
	}
}

void	EasyPropertyDentMeasureForm::GenerateAutomaticallyPure(bool OnlyGenerateFilmLen)
{
	GetDataFromList();
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		IntegrationCmdGenerateDentAndMeasure	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(SlaveNo==0){
			RCmd.BladePickupRL=GProp->Param.BladeTopPickupRL;
			RCmd.BladePickupRH=GProp->Param.BladeTopPickupRH;
			RCmd.BladePickupGL=GProp->Param.BladeTopPickupGL;
			RCmd.BladePickupGH=GProp->Param.BladeTopPickupGH;
			RCmd.BladePickupBL=GProp->Param.BladeTopPickupBL;
			RCmd.BladePickupBH=GProp->Param.BladeTopPickupBH;
			RCmd.BladeLeft		=GProp->Param.BladeTopLeft ;
			RCmd.BladeRight		=GProp->Param.BladeTopRight;

		}
		else{
			RCmd.BladePickupRL=GProp->Param.BladeBottomPickupRL;
			RCmd.BladePickupRH=GProp->Param.BladeBottomPickupRH;
			RCmd.BladePickupGL=GProp->Param.BladeBottomPickupGL;
			RCmd.BladePickupGH=GProp->Param.BladeBottomPickupGH;
			RCmd.BladePickupBL=GProp->Param.BladeBottomPickupBL;
			RCmd.BladePickupBH=GProp->Param.BladeBottomPickupBH;
			RCmd.BladeLeft		=GProp->Param.BladeBottomLeft ;
			RCmd.BladeRight		=GProp->Param.BladeBottomRight;
		}
		RCmd.LineLib		=GProp->Param.BladeLineLib;
		RCmd.RxLineLib		=GProp->Param.BladeRxLineLib;
		RCmd.DistanceLib	=GProp->Param.BladeDistanceLib;
		RCmd.BladeHoleMinArea	=GProp->Param.BladeHoleMinArea		;
		RCmd.BladeHoleErosionDot=GProp->Param.BladeHoleErosionDot	;
		RCmd.BladeMeasureData=BladeMeasureData;
		RCmd.FilmMeasureData =FilmMeasureData;
		RCmd.OnlyGenerateFilmLen=OnlyGenerateFilmLen;

		if(GProp->Param.DentLib1>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib1);
		if(GProp->Param.DentLib2>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib2);
		if(GProp->Param.DentLib3>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib3);
		if(GProp->Param.DentLib4>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib4);
		if(GProp->Param.DentLib5>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib5);
		if(GProp->Param.DentLib6>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib6);
		if(GProp->Param.DentLib7>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib7);
		if(GProp->Param.DentLib8>0)
			RCmd.ItemLibIDs.Add(GProp->Param.DentLib8);
		RCmd.MaskLib	=GProp->Param.MaskLibIDForBlade;

		RCmd.Send(NULL,SlaveNo,0);
	}
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyDentMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return;
	EasyDentMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyDentMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyDentMeasureImagePanel *)GUIFormRet[i]);
			break;
		}
	}

	if(AccessPanel!=NULL && BladeMeasureData.UpperFilmIndex>=0 && BladeMeasureData.UpperFilmPointNo>=0){
		int	drow=GUI2RowTable[BladeMeasureData.UpperFilmIndex];
		IntegrationReqMeasurePosition	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckMeasurePosition	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Page			=0;
		RCmd.Phase			=ThisM->GetCurrentPhase();
		RCmd.DistanceItemID	=drow;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			int	X,Y;
			if(BladeMeasureData.UpperFilmPointNo==0){
				X=ACmd.Point1X;
				Y=ACmd.Point1Y;
			}
			else{
				X=ACmd.Point2X;
				Y=ACmd.Point2Y;
			}
			IntegrationCmdFilm	CCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			CCmd.GenerateMode	=GenerateFilmBlock;
			CCmd.UpperMode		=true;
			CCmd.UniversalDx	=X;
			CCmd.UniversalDy	=Y;
			CCmd.Send(NULL,SlaveNo,0);
		}
	}
	if(AccessPanel!=NULL && BladeMeasureData.LowerFilmIndex>=0 && BladeMeasureData.LowerFilmPointNo>=0){
		int	drow=GUI2RowTable[BladeMeasureData.LowerFilmIndex];
		IntegrationReqMeasurePosition	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckMeasurePosition	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Page			=0;
		RCmd.Phase			=ThisM->GetCurrentPhase();
		RCmd.DistanceItemID	=drow;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			int	X,Y;
			if(BladeMeasureData.LowerFilmPointNo==0){
				X=ACmd.Point1X;
				Y=ACmd.Point1Y;
			}
			else{
				X=ACmd.Point2X;
				Y=ACmd.Point2Y;
			}
			IntegrationCmdFilm	CCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			CCmd.GenerateMode	=GenerateFilmBlock;
			CCmd.UpperMode		=false;
			CCmd.UniversalDx	=X;
			CCmd.UniversalDy	=Y;
			CCmd.Send(NULL,SlaveNo,0);
		}
	}
}

void	EasyPropertyDentMeasureForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		IntegrationBase *Base=GetLayersBase()->GetIntegrationBasePointer();
		if(Base->IsMastered()==true){
			QVariant	data;
			QString	FieldName=QString(/**/"DentMeasureBlade")+QString::number(SlaveNo);
			if(GetLayersBase()->LoadRelationFieldData(Base->GetMasterRelationCode()
													,FieldName, data)==true){
				QByteArray	BData=data.toByteArray();
				QBuffer	File(&BData);
				if(File.open(QIODevice::ReadOnly)==true){
					BladeMeasureData.Load(&File);
					FilmMeasureData.Load(&File);
				}
			}
		}
		ShowList();
		ShowFilmList();
		SetOnlyBladeThreshold();

		if(GenerateFilmInLoadingMaster==true
		&& GenerateFilmInLoadingMasterSlaveNo==SlaveNo){
			on_PushButtonGenerateFilmPos_clicked();
		}
		return;
	}
	CreateUpdateMasterSpecifiedBroadcaster	*CreateUpdateMasterSpecifiedBroadcasterVar=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	if(CreateUpdateMasterSpecifiedBroadcasterVar!=NULL){
		IntegrationBase *Base=GetLayersBase()->GetIntegrationBasePointer();
		if(Base->IsMastered()==true){
			QBuffer	File;
			if(File.open(QIODevice::WriteOnly)==true){
				BladeMeasureData.Save(&File);
				FilmMeasureData.Save(&File);
			}
			QByteArray	ArrayData=File.buffer();
			QVariant	VData(ArrayData);
			QString	FieldName=QString("DentMeasureBlade")+QString::number(SlaveNo);
			GetLayersBase()->AddRelationFieldData	(Base->GetMasterRelationCode()
													,FieldName, VData);
		}
		return;
	}
}

void EasyPropertyDentMeasureForm::on_PushButtonAddLine_clicked()
{
	GetDataFromList();
	if(ui->toolButtonBlade->isChecked()==true){
		if(BladeMeasureData.CountGenDatas<sizeof(BladeMeasureData.GenDatas)/sizeof(BladeMeasureData.GenDatas[0])){
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].bOnlyInside	=false;
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].bHorizontal	=false;
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].bFrom0		=true;
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].bPartnerFrom0	=true;
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].OKWidth		=100;
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].PartnerPos	=500;
			BladeMeasureData.GenDatas[BladeMeasureData.CountGenDatas].RegLineLength	=100;
			BladeMeasureData.CountGenDatas++;
		}
		ShowList();
	}
	else{
		if(FilmMeasureData.CountGenDatas<sizeof(FilmMeasureData.GenDatas)/sizeof(FilmMeasureData.GenDatas[0])){
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].bOnlyInside	=false;
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].bHorizontal	=false;
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].bFrom0		=true;
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].bPartnerFrom0	=true;
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].OKWidth		=100;
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].PartnerPos	=500;
			FilmMeasureData.GenDatas[FilmMeasureData.CountGenDatas].RegLineLength	=100;
			FilmMeasureData.CountGenDatas++;
		}
		ShowFilmList();
	}
}

void EasyPropertyDentMeasureForm::on_PushButtonRemoveLine_clicked()
{
	if(ui->toolButtonBlade->isChecked()==true){
		if(BladeMeasureData.CountGenDatas>0){
			int	CurrentRow=ui->tableWidgetBladePos->currentRow();
			if(CurrentRow<0)
				CurrentRow=BladeMeasureData.CountGenDatas-1;
			GetDataFromList();
			
			for(int i=CurrentRow;i<BladeMeasureData.CountGenDatas-1;i++){
				memcpy(&BladeMeasureData.GenDatas[i],&BladeMeasureData.GenDatas[i+1],sizeof(BladeMeasureData.GenDatas[0]));
			}
			BladeMeasureData.CountGenDatas--;
			ShowList();
		}
	}
	else{
		if(FilmMeasureData.CountGenDatas>0){
			int	CurrentRow=ui->tableWidgetFilmPos->currentRow();
			if(CurrentRow<0)
				CurrentRow=FilmMeasureData.CountGenDatas-1;
			GetDataFromList();
			
			for(int i=CurrentRow;i<FilmMeasureData.CountGenDatas-1;i++){
				memcpy(&FilmMeasureData.GenDatas[i],&FilmMeasureData.GenDatas[i+1],sizeof(FilmMeasureData.GenDatas[0]));
			}
			FilmMeasureData.CountGenDatas--;
			ShowFilmList();
		}
	}
}

void EasyPropertyDentMeasureForm::on_PushButtonSaveBladePos_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL,LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_13)/*"刃の計測位置設定をファイルに保存"
*/													, QString()
													,/**/"Blade(*.blade);;All files(*.*)");
	if(FileName.isEmpty()==false){
		GetDataFromList();
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			BladeMeasureData.Save(&File);
			FilmMeasureData.Save(&File);
		}
	}
}

void EasyPropertyDentMeasureForm::on_PushButtonLoadBladePos_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL,LangSolver.GetString(EasyPropertyDentMeasureForm_LS,LID_14)/*"刃の計測位置設定をファイルから読み込み"*/
													, QString()
													,/**/"Blade(*.blade);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(BladeMeasureData.Load(&File)==true){
				ShowList();
			}
			if(FilmMeasureData.Load(&File)==true){
				ShowFilmList();
			}
		}
	}
}
void EasyPropertyDentMeasureForm::on_toolButtonGetCorrentValues_clicked()
{
	GetDataFromList();

	IntegrationCmdReqCorrectValues	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationCmdAckCorrectValues	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.BladeMeasureData	=BladeMeasureData;
	RCmd.Mastered			=true;

	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
			struct	MeasureHVInfo	&p=ACmd.BladeMeasureData.GenDatas[row];
			int	grow=Row2GUITable[row];
			::SetDataToTable(ui->tableWidgetBladePos ,10 ,grow ,QString::number(p.CorrectLength,'f',2));
		}
	}
}
void EasyPropertyDentMeasureForm::on_toolButtonGetCorrentValuesTarget_clicked()
{
	GetDataFromList();

	IntegrationCmdReqCorrectValues	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationCmdAckCorrectValues	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.BladeMeasureData	=BladeMeasureData;
	RCmd.Mastered			=false;

	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
			struct	MeasureHVInfo	&p=ACmd.BladeMeasureData.GenDatas[row];
			int	grow=Row2GUITable[row];
			::SetDataToTable(ui->tableWidgetBladePos ,10 ,grow ,QString::number(p.CorrectLength,'f',2));
		}
	}
}

void EasyPropertyDentMeasureForm::on_toolButtonSetCorrentValues_clicked()
{
 	GetDataFromList();
	
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		IntegrationCmdSetCorrectValues	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.BladeMeasureData	=BladeMeasureData;
		RCmd.LineLib			=GProp->Param.BladeLineLib;
		RCmd.RxLineLib			=GProp->Param.BladeRxLineLib;
		RCmd.DistanceLib		=GProp->Param.BladeDistanceLib;

		if(SlaveNo==0){
			RCmd.BladePickupRL=GProp->Param.BladeTopPickupRL;
			RCmd.BladePickupRH=GProp->Param.BladeTopPickupRH;
			RCmd.BladePickupGL=GProp->Param.BladeTopPickupGL;
			RCmd.BladePickupGH=GProp->Param.BladeTopPickupGH;
			RCmd.BladePickupBL=GProp->Param.BladeTopPickupBL;
			RCmd.BladePickupBH=GProp->Param.BladeTopPickupBH;
		}
		else{
			RCmd.BladePickupRL=GProp->Param.BladeBottomPickupRL;
			RCmd.BladePickupRH=GProp->Param.BladeBottomPickupRH;
			RCmd.BladePickupGL=GProp->Param.BladeBottomPickupGL;
			RCmd.BladePickupGH=GProp->Param.BladeBottomPickupGH;
			RCmd.BladePickupBL=GProp->Param.BladeBottomPickupBL;
			RCmd.BladePickupBH=GProp->Param.BladeBottomPickupBH;
		}
		RCmd.MaskLib	=GProp->Param.MaskLibIDForBlade;

		RCmd.Send(NULL,SlaveNo,0);
	}
	BroadcastRepaintAll();
}

void	EasyPropertyDentMeasureForm::SetOnlyBladeThreshold(void)
{
 	GetDataFromList();
	
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		IntegrationCmdSetOnlyBladeThreshold	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.BladeMeasureData	=BladeMeasureData;
		RCmd.FilmMeasureData	=FilmMeasureData;
		RCmd.Send(NULL,SlaveNo,0);
	}

}

void	EasyPropertyDentMeasureForm::SlotEndPointClicked(int EndNo,int MeasureNo)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyDentMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return;
	EasyDentMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyDentMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyDentMeasureImagePanel *)GUIFormRet[i]);
			break;
		}
	}
	int RCount=ui->tableWidgetBladePos->rowCount();
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidgetBladePos->cellWidget(i,8));
		if(tb!=NULL && (tb->EndNo!=EndNo || tb->MeasureNo!=MeasureNo)){
			tb->setChecked(false);
		}
	}
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidgetBladePos->cellWidget(i,9));
		if(tb!=NULL && (tb->EndNo!=EndNo || tb->MeasureNo!=MeasureNo)){
			tb->setChecked(false);
		}
	}

	if(AccessPanel!=NULL){
		if(0<=MeasureNo && MeasureNo<BladeMeasureData.CountGenDatas){
			int	drow=GUI2RowTable[MeasureNo];
			AccessPanel->ShowingItemID=drow;
			CmdWatchItem	WCmd(GetLayersBase());
			AccessPanel->TransmitDirectly(&WCmd);
			AccessPanel->Repaint();
		}

		bool	Pushed=false;
		for(int grow=0;grow<BladeMeasureData.CountGenDatas;grow++){
			int	row=GUI2RowTable[grow];
			if(row==MeasureNo){
				QWidget *ThisButton=ui->tableWidgetBladePos->cellWidget(grow,(EndNo==0)?8:9);
				if(ThisButton!=NULL){
					DentMeasurePointButton	*MThisButton=dynamic_cast<DentMeasurePointButton *>(ThisButton);
					if(MThisButton!=NULL){
						if(MThisButton->isChecked()==true){
							AccessPanel->SetMode(IntegrationSimpleImagePanel::Mode_AddItem);
							AccessPanel->SetMode(mtFrameDraw::fdNone);
							Pushed=true;
						}
						else{
							AccessPanel->SetMode();
						}
					}
				}
			}
		}
		if(Pushed==true){
			for(int grow=0;grow<BladeMeasureData.CountGenDatas;grow++){
				int	row=GUI2RowTable[grow];
				for(int Col=8;Col<=9;Col++){
					if(row==MeasureNo && Col==(EndNo+8))
						continue;
					QWidget *AnotherButton=ui->tableWidgetBladePos->cellWidget(grow,Col);
					if(AnotherButton!=NULL){
						DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
						if(MAnotherButton!=NULL){
							MAnotherButton->setChecked(false);
						}
					}
				}
			}
		}
	}
}

void	EasyPropertyDentMeasureForm::SlotFilmEndPointClicked(int EndNo,int MeasureNo)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyDentMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return;
	EasyDentMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyDentMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyDentMeasureImagePanel *)GUIFormRet[i]);
			break;
		}
	}
	int RCount=ui->tableWidgetFilmPos->rowCount();
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidgetFilmPos->cellWidget(i,8));
		if(tb!=NULL && (tb->EndNo!=EndNo || tb->MeasureNo!=MeasureNo)){
			tb->setChecked(false);
		}
	}
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidgetFilmPos->cellWidget(i,9));
		if(tb!=NULL && (tb->EndNo!=EndNo || tb->MeasureNo!=MeasureNo)){
			tb->setChecked(false);
		}
	}

	if(AccessPanel!=NULL){
		if(0<=MeasureNo && MeasureNo<FilmMeasureData.CountGenDatas){
			int	drow=GUI2RowTable[MeasureNo];
			AccessPanel->ShowingItemID=200+drow;
			CmdWatchItem	WCmd(GetLayersBase());
			AccessPanel->TransmitDirectly(&WCmd);
			AccessPanel->Repaint();
		}

		bool	Pushed=false;
		for(int grow=0;grow<FilmMeasureData.CountGenDatas;grow++){
			int	row=GUI2RowTable[grow];
			if(row==MeasureNo){
				QWidget *ThisButton=ui->tableWidgetFilmPos->cellWidget(grow,(EndNo==0)?8:9);
				if(ThisButton!=NULL){
					DentMeasurePointButton	*MThisButton=dynamic_cast<DentMeasurePointButton *>(ThisButton);
					if(MThisButton!=NULL){
						if(MThisButton->isChecked()==true){
							AccessPanel->SetMode(IntegrationSimpleImagePanel::Mode_AddItem);
							AccessPanel->SetMode(mtFrameDraw::fdNone);
							Pushed=true;
						}
						else{
							AccessPanel->SetMode();
						}
					}
				}
			}
		}
		if(Pushed==true){
			for(int grow=0;grow<FilmMeasureData.CountGenDatas;grow++){
				int	row=GUI2RowTable[grow];
				for(int Col=8;Col<=9;Col++){
					if(row==MeasureNo && Col==(EndNo+8))
						continue;
					QWidget *AnotherButton=ui->tableWidgetFilmPos->cellWidget(grow,Col);
					if(AnotherButton!=NULL){
						DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
						if(MAnotherButton!=NULL){
							MAnotherButton->setChecked(false);
						}
					}
				}
			}
		}
	}
}
void EasyPropertyDentMeasureForm::on_PushButtonManualCreateArea_clicked()
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyDentMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return;
	EasyDentMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyDentMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyDentMeasureImagePanel *)GUIFormRet[i]);
			break;
		}
	}
	if(AccessPanel!=NULL){
		AccessPanel->SetMode();
	}
	for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
		for(int Col=8;Col<=9;Col++){
			QWidget *AnotherButton=ui->tableWidgetBladePos->cellWidget(row,Col);
			if(AnotherButton!=NULL){
				DentMeasurePointButton	*MAnotherButton=dynamic_cast<DentMeasurePointButton *>(AnotherButton);
				if(MAnotherButton!=NULL){
					MAnotherButton->setChecked(false);
				}
			}
		}
	}
}
void EasyPropertyDentMeasureForm::on_tableWidgetBladePos_clicked(const QModelIndex &index)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyDentMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return;
	EasyDentMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyDentMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyDentMeasureImagePanel *)GUIFormRet[i]);
			break;
		}
	}
	if(AccessPanel!=NULL){
		int	grow=ui->tableWidgetBladePos->currentRow();
		if(0<=grow && grow<BladeMeasureData.CountGenDatas){
			int	row=GUI2RowTable[grow];
			AccessPanel->ShowingItemID=row;
			CmdWatchItem	WCmd(GetLayersBase());
			AccessPanel->TransmitDirectly(&WCmd);
			AccessPanel->Repaint();
		}
	}
}

void EasyPropertyDentMeasureForm::on_tableWidgetBladePos_doubleClicked(const QModelIndex &index)
{
	if((index.flags() & Qt::ItemIsEditable)!=0){
		QString	Str=::GetDataToTable(ui->tableWidgetBladePos ,index.column() ,index.row());
		InputPanelDialog	D(IPD_Number ,Str);
		if(D.exec()==(bool)true){
			::SetDataToTable(ui->tableWidgetBladePos ,index.column() ,index.row() 
							,D.GetResult(),Qt::ItemIsEditable);
		}
	}
}

void EasyPropertyDentMeasureForm::on_toolButtonSetName_clicked()
{
	GetDataFromList();
	ShowList();
	ShowFilmList();
}

void EasyPropertyDentMeasureForm::on_toolButtonGenFilmLower_clicked()
{
	//if(ui->toolButtonGenFilmLower->isChecked()==false){
	//	IntegrationCmdFilm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	//	RCmd.GenerateMode	=false;
	//	RCmd.UpperMode		=false;
	//
	//	RCmd.Send(NULL,SlaveNo,0);
	//}
	if(ui->toolButtonGenFilmLower->isChecked()==true){
		ui->toolButtonGenFilmUpper->setChecked(false);
	}
}

void EasyPropertyDentMeasureForm::on_toolButtonGenFilmUpper_clicked()
{
	//if(ui->toolButtonGenFilmUpper->isChecked()==false){
	//	IntegrationCmdFilm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	//	RCmd.GenerateMode	=false;
	//	RCmd.UpperMode		=true;
	//
	//	RCmd.Send(NULL,SlaveNo,0);
	//}
	if(ui->toolButtonGenFilmUpper->isChecked()==true){
		ui->toolButtonGenFilmLower->setChecked(false);
	}
}


void EasyPropertyDentMeasureForm::on_pushButtonSetUpper_clicked()
{
	SettingFilmPositionDialog	D(this,BladeMeasureData.UpperFilmIndex,BladeMeasureData.UpperFilmPointNo);
	if(D.exec()==true){
		BladeMeasureData.UpperFilmIndex		=D.FilmIndex;
		BladeMeasureData.UpperFilmPointNo	=D.FilmPointNo;
	}
}


void EasyPropertyDentMeasureForm::on_pushButtonSetLower_clicked()
{
	SettingFilmPositionDialog	D(this,BladeMeasureData.LowerFilmIndex,BladeMeasureData.LowerFilmPointNo);
	if(D.exec()==true){
		BladeMeasureData.LowerFilmIndex		=D.FilmIndex;
		BladeMeasureData.LowerFilmPointNo	=D.FilmPointNo;
	}
}

void EasyPropertyDentMeasureForm::on_toolButtonBlade_clicked()
{
	if(ui->toolButtonBlade->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
}


void EasyPropertyDentMeasureForm::on_toolButtonFilm_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void EasyPropertyDentMeasureForm::on_PushButtonGenerateFilmPos_clicked()
{
	emit	SignalBusy();

	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		//if((SlaveNo==0 && GProp->Param.GenerateBradeTop==true)
		//|| (SlaveNo==1 && GProp->Param.GenerateBradeBottom==true)){
			GenerateAutomaticallyPure(true);
			GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
			BroadcastRepaintAll();
		//}
	}

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();

}



//============================================================================
IntegrationCmdGenerateDentAndMeasure::IntegrationCmdGenerateDentAndMeasure(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	OnlyGenerateFilmLen=false;
}
bool	IntegrationCmdGenerateDentAndMeasure::Load(QIODevice *f)
{
	if(::Load(f,BladePickupRL)==false)	return false;
	if(::Load(f,BladePickupRH)==false)	return false;
	if(::Load(f,BladePickupGL)==false)	return false;
	if(::Load(f,BladePickupGH)==false)	return false;
	if(::Load(f,BladePickupBL)==false)	return false;
	if(::Load(f,BladePickupBH)==false)	return false;
	if(::Load(f,BladeLeft	)==false)	return false;
	if(::Load(f,BladeRight	)==false)	return false;
	if(::Load(f,LineLib		)==false)	return false;
	if(::Load(f,RxLineLib	)==false)	return false;
	if(::Load(f,DistanceLib	)==false)	return false;
	if(::Load(f,MaskLib		)==false)	return false;
	if(::Load(f,BladeHoleMinArea	)==false)	return false;
	if(::Load(f,BladeHoleErosionDot	)==false)	return false;
	if(BladeMeasureData.Load(f)==false)	return false;
	if(ItemLibIDs.Load(f)==false)		return false;
	FilmMeasureData.Load(f);
	if(::Load(f,OnlyGenerateFilmLen)==false)	return false;
	return true;
}
bool	IntegrationCmdGenerateDentAndMeasure::Save(QIODevice *f)
{
	if(::Save(f,BladePickupRL)==false)	return false;
	if(::Save(f,BladePickupRH)==false)	return false;
	if(::Save(f,BladePickupGL)==false)	return false;
	if(::Save(f,BladePickupGH)==false)	return false;
	if(::Save(f,BladePickupBL)==false)	return false;
	if(::Save(f,BladePickupBH)==false)	return false;
	if(::Save(f,BladeLeft	)==false)	return false;
	if(::Save(f,BladeRight	)==false)	return false;
	if(::Save(f,LineLib		)==false)	return false;
	if(::Save(f,RxLineLib	)==false)	return false;
	if(::Save(f,DistanceLib	)==false)	return false;
	if(::Save(f,MaskLib		)==false)	return false;
	if(::Save(f,BladeHoleMinArea	)==false)	return false;
	if(::Save(f,BladeHoleErosionDot	)==false)	return false;
	if(BladeMeasureData.Save(f)==false)	return false;
	if(ItemLibIDs.Save(f)==false)		return false;
	FilmMeasureData.Save(f);
	if(::Save(f,OnlyGenerateFilmLen)==false)	return false;
	return true;
}

void	IntegrationCmdGenerateDentAndMeasure::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fd=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyDent",/**/"");
	if(fd!=NULL){
		{
			CmdDentGenerate	RCmd(GetLayersBase());

			//RCmd.BladePickupRL	=BladePickupRL;
			//RCmd.BladePickupRH	=BladePickupRH;
			//RCmd.BladePickupGL	=BladePickupGL;
			//RCmd.BladePickupGH	=BladePickupGH;
			//RCmd.BladePickupBL	=BladePickupBL;
			//RCmd.BladePickupBH	=BladePickupBH;
			RCmd.ItemLibIDs		=ItemLibIDs;

			fd->TransmitDirectly(&RCmd);
		}
	}
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdGenerateMeasure	RCmd(GetLayersBase());

			RCmd.BladePickupRL	=BladePickupRL;
			RCmd.BladePickupRH	=BladePickupRH;
			RCmd.BladePickupGL	=BladePickupGL;
			RCmd.BladePickupGH	=BladePickupGH;
			RCmd.BladePickupBL	=BladePickupBL;
			RCmd.BladePickupBH	=BladePickupBH;
			RCmd.BladeLeft		=BladeLeft	;
			RCmd.BladeRight		=BladeRight	;
			RCmd.LineLib		=LineLib;
			RCmd.RxLineLib		=RxLineLib;
			RCmd.DistanceLib	=DistanceLib;
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.FilmMeasureData	=FilmMeasureData;
			RCmd.MaskLib			=MaskLib;
			RCmd.BladeHoleMinArea	=BladeHoleMinArea	;
			RCmd.BladeHoleErosionDot=BladeHoleErosionDot;
			RCmd.OnlyGenerateFilmLen=OnlyGenerateFilmLen;

			fm->TransmitDirectly(&RCmd);
		}
	}
}

//============================================================================
IntegrationCmdReqCorrectValues::IntegrationCmdReqCorrectValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqCorrectValues::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)	==false)	return false;
	if(::Load(f,Mastered)		==false)	return false;
	return true;
}
bool	IntegrationCmdReqCorrectValues::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)	==false)	return false;
	if(::Save(f,Mastered)		==false)	return false;
	return true;
}

void	IntegrationCmdReqCorrectValues::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckCorrectValues	*SendBack=GetSendBackIntegration(IntegrationCmdAckCorrectValues,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdReqCorrentValues	RCmd(GetLayersBase());
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.Mastered			=Mastered;
			fm->TransmitDirectly(&RCmd);
			SendBack->BladeMeasureData=RCmd.BladeMeasureData;
		}
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckCorrectValues::IntegrationCmdAckCorrectValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckCorrectValues::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdAckCorrectValues::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)	return false;
	return true;
}

//============================================================================
IntegrationCmdSetCorrectValues::IntegrationCmdSetCorrectValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetCorrectValues::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)	return false;
	if(::Load(f,LineLib)==false)
		return false;
	if(::Load(f,RxLineLib)==false)
		return false;
	if(::Load(f,DistanceLib)==false)
		return false;
	if(::Load(f,BladePickupRL)==false)	return false;
	if(::Load(f,BladePickupRH)==false)	return false;
	if(::Load(f,BladePickupGL)==false)	return false;
	if(::Load(f,BladePickupGH)==false)	return false;
	if(::Load(f,BladePickupBL)==false)	return false;
	if(::Load(f,BladePickupBH)==false)	return false;
	if(::Load(f,MaskLib		)==false)	return false;
	return true;
}
bool	IntegrationCmdSetCorrectValues::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)	return false;
	if(::Save(f,LineLib)==false)
		return false;
	if(::Save(f,RxLineLib)==false)
		return false;
	if(::Save(f,DistanceLib)==false)
		return false;
	if(::Save(f,BladePickupRL)==false)	return false;
	if(::Save(f,BladePickupRH)==false)	return false;
	if(::Save(f,BladePickupGL)==false)	return false;
	if(::Save(f,BladePickupGH)==false)	return false;
	if(::Save(f,BladePickupBL)==false)	return false;
	if(::Save(f,BladePickupBH)==false)	return false;
	if(::Save(f,MaskLib		)==false)	return false;
	return true;
}

void	IntegrationCmdSetCorrectValues::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetCorrectValues	RCmd(GetLayersBase());
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.LineLib			=LineLib;
			RCmd.RxLineLib			=RxLineLib;
			RCmd.DistanceLib		=DistanceLib;
			RCmd.BladePickupRL		=BladePickupRL;
			RCmd.BladePickupRH		=BladePickupRH;
			RCmd.BladePickupGL		=BladePickupGL;
			RCmd.BladePickupGH		=BladePickupGH;
			RCmd.BladePickupBL		=BladePickupBL;
			RCmd.BladePickupBH		=BladePickupBH;
			RCmd.MaskLib			=MaskLib;
			fm->TransmitDirectly(&RCmd);
		}
	}
}

//============================================================================
IntegrationCmdSetOnlyBladeThreshold::IntegrationCmdSetOnlyBladeThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetOnlyBladeThreshold::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)	return false;
	if(FilmMeasureData.Load(f)==false)	return false;

	return true;
}
bool	IntegrationCmdSetOnlyBladeThreshold::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)	return false;
	if(FilmMeasureData.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdSetOnlyBladeThreshold::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetOnlyBladeThreshold	RCmd(GetLayersBase());
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.FilmMeasureData	=FilmMeasureData;
			fm->TransmitDirectly(&RCmd);
		}
	}
}
//============================================================================
IntegrationCmdSetMeasureEndPoint::IntegrationCmdSetMeasureEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetMeasureEndPoint::Load(QIODevice *f)
{
	if(::Load(f,EndNo)==false)	return false;
	if(::Load(f,MeasureNo)==false)	return false;
	if(::Load(f,GlobalX)==false)	return false;
	if(::Load(f,GlobalY)==false)	return false;
	return true;
}
bool	IntegrationCmdSetMeasureEndPoint::Save(QIODevice *f)
{
	if(::Save(f,EndNo)==false)	return false;
	if(::Save(f,MeasureNo)==false)	return false;
	if(::Save(f,GlobalX)==false)	return false;
	if(::Save(f,GlobalY)==false)	return false;
	return true;
}

void	IntegrationCmdSetMeasureEndPoint::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetMeasureEndPoint	RCmd(GetLayersBase());
			RCmd.EndNo		=EndNo;
			RCmd.MeasureNo	=MeasureNo;
			RCmd.X			=GlobalX;
			RCmd.Y			=GlobalY;
			fm->TransmitDirectly(&RCmd);
		}
	}
}
//============================================================================

IntegrationCmdFilm::IntegrationCmdFilm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdFilm::Load(QIODevice *f)
{
	if(::Load(f,GenerateMode)==false)	return false;
	if(::Load(f,UpperMode	)==false)	return false;
	if(::Load(f,UniversalDx	)==false)	return false;
	if(::Load(f,UniversalDy	)==false)	return false;
	return true;
}
bool	IntegrationCmdFilm::Save(QIODevice *f)
{
	if(::Save(f,GenerateMode)==false)	return false;
	if(::Save(f,UpperMode	)==false)	return false;
	if(::Save(f,UniversalDx	)==false)	return false;
	if(::Save(f,UniversalDy	)==false)	return false;
	return true;
}

void	IntegrationCmdFilm::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	InspectionIDNoFilmUpper	=0;
	int	InspectionIDNeedFilmUpper=0;
	int	InspectionIDNoFilmLower	=0;
	int	InspectionIDNeedFilmLower=0;
	int	FilmNeededOffsetY=0;
	int	FilmNoNeedOffsetY=0;
	EasyPropertyDentMeasureForm	*pm=(EasyPropertyDentMeasureForm *)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",/**/"");
	if(pm!=NULL){
		InspectionIDNoFilmUpper		=pm->InspectionIDNoFilmUpper	;
		InspectionIDNeedFilmUpper	=pm->InspectionIDNeedFilmUpper	;
		InspectionIDNoFilmLower		=pm->InspectionIDNoFilmLower	;
		InspectionIDNeedFilmLower	=pm->InspectionIDNeedFilmLower	;
		FilmNeededOffsetY	=pm->FilmNeededOffsetY;
		FilmNoNeedOffsetY	=pm->FilmNoNeedOffsetY;
	}
		
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
	GUIFormBase	*gm=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyDotColorMatching",/**/"");
	if(fm!=NULL && gm!=NULL){
		{
			CmdReqDelAlignmentAreaByName	RCmd(GetLayersBase());
			if(UpperMode==true)
				RCmd.AreaName	="Upper";
			else
				RCmd.AreaName	="Lower";
			fm->TransmitDirectly(&RCmd);
		}

		CmdDeleteDotColorMatchingByName	Del1(GetLayersBase());
		if(UpperMode==true)
			Del1.ItemName=/**/"FilmUpper1";
		else
			Del1.ItemName=/**/"FilmLower1";
		gm->TransmitDirectly(&Del1);

		if(GenerateMode==true){
			{
				CmdReqAddAlignmentArea	RCmd(GetLayersBase());
				RCmd.Area.SetRectangle(  UniversalDx-100,UniversalDy-500
										,UniversalDx+100,UniversalDy+500);
				if(UpperMode==true){
					RCmd.AreaName	="Upper";
					AlgorithmLibraryList	*L11=new AlgorithmLibraryList(GetLayersBase(),DefLibTypeAlignmentLarge,InspectionIDNoFilmUpper	);
					AlgorithmLibraryList	*L12=new AlgorithmLibraryList(GetLayersBase(),DefLibTypeAlignmentLarge,InspectionIDNeedFilmUpper	);
					RCmd.LimitedLib.AppendList(L11);
					RCmd.LimitedLib.AppendList(L12);
				}
				else{
					RCmd.AreaName	="Lower";
					AlgorithmLibraryList	*L21=new AlgorithmLibraryList(GetLayersBase(),DefLibTypeAlignmentLarge,InspectionIDNoFilmLower	);
					AlgorithmLibraryList	*L22=new AlgorithmLibraryList(GetLayersBase(),DefLibTypeAlignmentLarge,InspectionIDNeedFilmLower	);
					RCmd.LimitedLib.AppendList(L21);
					RCmd.LimitedLib.AppendList(L22);
				}
				RCmd.Priority=XAlignmentLargeArea::_PriorityMiddle;

				fm->TransmitDirectly(&RCmd);

				CmdReqAddAlignmentPoint	PCmd(GetLayersBase());
				PCmd.AreaID=RCmd.GeneratedAreaID;
				PCmd.Area.SetRectangle(  UniversalDx-20,UniversalDy-20
										,UniversalDx+20,UniversalDy+20);
				PCmd.MoveDotX	=20;
				PCmd.MoveDotY	=50;
				fm->TransmitDirectly(&PCmd);
			}

			CmdAddDotColorMatching	D1(GetLayersBase());
			if(UpperMode==true){
				D1.LibID	=InspectionIDNoFilmUpper;
				D1.Area.SetRectangle(UniversalDx-20,UniversalDy-FilmNoNeedOffsetY-20
									,UniversalDx+20,UniversalDy-FilmNoNeedOffsetY+20);
			}
			else{
				D1.LibID	=InspectionIDNoFilmLower;
				D1.Area.SetRectangle(UniversalDx-20,UniversalDy+FilmNoNeedOffsetY-20
									,UniversalDx+20,UniversalDy+FilmNoNeedOffsetY+20);
			}
			D1.ItemName=Del1.ItemName;
			gm->TransmitDirectly(&D1);


			CmdDeleteDotColorMatchingByName	Del2(GetLayersBase());
			if(UpperMode==true)
				Del2.ItemName=/**/"FilmUpper2";
			else
				Del2.ItemName=/**/"FilmLower2";
			gm->TransmitDirectly(&Del2);

			CmdAddDotColorMatching	D2(GetLayersBase());
			
			if(UpperMode==true){
				D2.LibID	=InspectionIDNeedFilmUpper;
				D2.Area.SetRectangle(UniversalDx-20,UniversalDy-FilmNeededOffsetY-20
									,UniversalDx+20,UniversalDy-FilmNeededOffsetY+20);
			}
			else{
				D2.LibID	=InspectionIDNeedFilmLower;
				D2.Area.SetRectangle(UniversalDx-20,UniversalDy+FilmNeededOffsetY-20
									,UniversalDx+20,UniversalDy+FilmNeededOffsetY+20);
			}
			D2.ItemName=Del2.ItemName;
			gm->TransmitDirectly(&D2);
		}
		//else{
		//	CmdReqDelAlignmentAreaByName	RCmd(GetLayersBase());
		//	if(UpperMode==true)
		//		RCmd.AreaName	="Upper";
		//	else
		//		RCmd.AreaName	="Lower";
		//	fm->TransmitDirectly(&RCmd);
		//}
	}
}

IntegrationReqMeasurePosition::IntegrationReqMeasurePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqMeasurePosition::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Page)==false)	return false;
	if(::Load(f,DistanceItemID)==false)	return false;
	return true;
}
bool	IntegrationReqMeasurePosition::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Page)==false)	return false;
	if(::Save(f,DistanceItemID)==false)	return false;
	return true;
}

void	IntegrationReqMeasurePosition::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckMeasurePosition	*SendBack=GetSendBackIntegration(IntegrationAckMeasurePosition,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		CmdReqMeasureLinePosition	RCmd(GetLayersBase());
		RCmd.Page				=Page;
		RCmd.Phase				=Phase;
		RCmd.DistanceItemID		=DistanceItemID;
		fm->TransmitDirectly(&RCmd);
		SendBack->Point1X=RCmd.RetPos1X;
		SendBack->Point1Y=RCmd.RetPos1Y;
		SendBack->Point2X=RCmd.RetPos2X;
		SendBack->Point2Y=RCmd.RetPos2Y;
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckMeasurePosition::IntegrationAckMeasurePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckMeasurePosition::Load(QIODevice *f)
{
	if(::Load(f,Point1X)==false)	return false;
	if(::Load(f,Point1Y)==false)	return false;
	if(::Load(f,Point2X)==false)	return false;
	if(::Load(f,Point2Y)==false)	return false;
	return true;
}
bool	IntegrationAckMeasurePosition::Save(QIODevice *f)
{
	if(::Save(f,Point1X)==false)	return false;
	if(::Save(f,Point1Y)==false)	return false;
	if(::Save(f,Point2X)==false)	return false;
	if(::Save(f,Point2Y)==false)	return false;
	return true;
}
