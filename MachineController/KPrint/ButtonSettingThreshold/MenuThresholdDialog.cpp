#include "ButtonSettingThresholdResource.h"
#include "MenuThresholdDialog.h"
#include "ui_MenuThresholdDialog.h"
#include <QPushButton>
#include "EachThresholdFormFaint.h"
#include "EachThresholdFormMultiSpot.h"
#include "EachThresholdFormOozing.h"
#include "EachThresholdFormRed.h"
#include "EachThresholdFormVariable.h"
#include "XEachThresholdCommon.h"
#include "XParamCustomized.h"
#include "CartonMenuForm.h"
#include "EachThresholdFormBlade.h"
#include "EachThresholdFormCADLine.h"
#include "EachThresholdWholeForm.h"

MenuThresholdDialog::MenuThresholdDialog(LayersBase *base ,ButtonSettingThresholdForm *p,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base),Parent(p)
	,ui(new Ui::MenuThresholdDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	ChildWindow=NULL;
	Phase	=-1;
	Page	=-1;
	GlobalX	=-1;
	GlobalY	=-1;
	FreePosition=true;

	ui->tableWidget->setColumnWidth(0,160);
	ui->tableWidget->setColumnWidth(1,160);
	ui->tableWidget->setColumnWidth(2,160);

	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotMonoFaint()));
		ui->tableWidget->setCellWidget(0,0,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotMonoRed()));
		ui->tableWidget->setCellWidget(1,0,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotMonoOozing()));
		ui->tableWidget->setCellWidget(2,0,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotMonoMultiSpot()));
		ui->tableWidget->setCellWidget(3,0,B);
	}

	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotGradVariable()));
		ui->tableWidget->setCellWidget(0,1,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotGradRed()));
		ui->tableWidget->setCellWidget(1,1,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotGradOozing()));
		ui->tableWidget->setCellWidget(2,1,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotGradMultiSpot()));
		ui->tableWidget->setCellWidget(3,1,B);
	}

	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotCharVariable()));
		ui->tableWidget->setCellWidget(0,2,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotCharRed()));
		ui->tableWidget->setCellWidget(1,2,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotCharOozing()));
		ui->tableWidget->setCellWidget(2,2,B);
	}
	{
		QPushButton	*B=new QPushButton;
		connect(B,SIGNAL(clicked()),this,SLOT(SlotCharMultiSpot()));
		ui->tableWidget->setCellWidget(3,2,B);
	}

	//{
	//	QPushButton	*B=new QPushButton;
	//	connect(B,SIGNAL(clicked()),this,SLOT(SlotMujiFaint()));
	//	ui->tableWidget->setCellWidget(0,3,B);
	//}
	//{
	//	QPushButton	*B=new QPushButton;
	//	connect(B,SIGNAL(clicked()),this,SLOT(SlotMujiRed()));
	//	ui->tableWidget->setCellWidget(1,3,B);
	//}
	//{
	//	QPushButton	*B=new QPushButton;
	//	connect(B,SIGNAL(clicked()),this,SLOT(SlotMujiMultispot()));
	//	ui->tableWidget->setCellWidget(3,3,B);
	//}
	CartonMenuForm	*f=dynamic_cast<CartonMenuForm	*>(GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/""));
	if(f!=NULL){
		ui->PushButtonBlade->setVisible(f->ShowBlade);
	}
	GUIFormBase	*ThresholdLevelPanel=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}

	InstallOperationLog(this);
}

MenuThresholdDialog::~MenuThresholdDialog()
{
    delete ui;
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
}

void MenuThresholdDialog::on_PushButtonClosed_clicked()
{
	done(true);
}

void	MenuThresholdDialog::SetActiveArea(EachThresholdCommon::__AreaType areatype)
{
	if(areatype==EachThresholdCommon::_AreaTypeNothing	){
		for(int column=0;column<3;column++){
			for(int row=0;row<4;row++){
				QPushButton	*B=dynamic_cast<QPushButton *>(ui->tableWidget->cellWidget(row,column));
				if(B!=NULL){
					B->setEnabled(true);
				}
			}
		}
		FreePosition=true;
	}
	if(areatype==EachThresholdCommon::_Mono		){
		for(int column=0;column<3;column++){
			for(int row=0;row<4;row++){
				QPushButton	*B=dynamic_cast<QPushButton *>(ui->tableWidget->cellWidget(row,column));
				if(B!=NULL){
					if(column==0)
						B->setEnabled(true);
					else
						B->setEnabled(false);
				}
			}
		}
		FreePosition=false;
	}
	if(areatype==EachThresholdCommon::_Gradation){
		for(int column=0;column<3;column++){
			for(int row=0;row<4;row++){
				QPushButton	*B=dynamic_cast<QPushButton *>(ui->tableWidget->cellWidget(row,column));
				if(B!=NULL){
					if(column==1)
						B->setEnabled(true);
					else
						B->setEnabled(false);
				}
			}
		}
		FreePosition=false;
	}
	if(areatype==EachThresholdCommon::_Character){
		for(int column=0;column<3;column++){
			for(int row=0;row<4;row++){
				QPushButton	*B=dynamic_cast<QPushButton *>(ui->tableWidget->cellWidget(row,column));
				if(B!=NULL){
					if(column==2)
						B->setEnabled(true);
					else
						B->setEnabled(false);
				}
			}
		}
		FreePosition=false;
	}
	if(areatype==EachThresholdCommon::_NoPrint	){
		for(int column=0;column<3;column++){
			for(int row=0;row<4;row++){
				QPushButton	*B=dynamic_cast<QPushButton *>(ui->tableWidget->cellWidget(row,column));
				if(B!=NULL){
					if(column==3)
						B->setEnabled(true);
					else
						B->setEnabled(false);
				}
			}
		}
		FreePosition=false;
	}
}

void	MenuThresholdDialog::SetActivePosition(int _Phase ,int _Page ,int _GlobalX,int _GlobalY,IntList & _ItemID)
{
	Phase	=_Phase;
	Page	=_Page;
	GlobalX	=_GlobalX;
	GlobalY	=_GlobalY;
	ItemID	=_ItemID;
}

void	MenuThresholdDialog::SlotMonoFaint()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormFaint(GetLayersBase(),Parent
											,EachThresholdCommon::_Mono,EachThresholdCommon::_BrightnessInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotMonoRed()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormRed(GetLayersBase(),Parent
										,EachThresholdCommon::_Mono,EachThresholdCommon::_RedInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotMonoOozing()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormOozing(GetLayersBase(),Parent
											,EachThresholdCommon::_Mono,EachThresholdCommon::_OozingInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotMonoMultiSpot()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormMultiSpot(GetLayersBase(),Parent
												,EachThresholdCommon::_Mono,EachThresholdCommon::_MultiSpotInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}

void	MenuThresholdDialog::SlotGradVariable()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormVariable(GetLayersBase(),Parent
											,EachThresholdCommon::_Gradation,EachThresholdCommon::_BrightnessInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotGradRed()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormRed(GetLayersBase(),Parent
										,EachThresholdCommon::_Gradation,EachThresholdCommon::_RedInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotGradOozing()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormOozing(GetLayersBase(),Parent
											,EachThresholdCommon::_Gradation,EachThresholdCommon::_OozingInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotGradMultiSpot()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormMultiSpot(GetLayersBase(),Parent
											,EachThresholdCommon::_Gradation,EachThresholdCommon::_MultiSpotInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}

void	MenuThresholdDialog::SlotCharVariable()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormVariable(GetLayersBase(),Parent
											,EachThresholdCommon::_Character,EachThresholdCommon::_BrightnessInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotCharRed()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormRed(GetLayersBase(),Parent
										,EachThresholdCommon::_Character,EachThresholdCommon::_RedInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotCharOozing()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormOozing(GetLayersBase(),Parent
											,EachThresholdCommon::_Character,EachThresholdCommon::_OozingInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotCharMultiSpot()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormMultiSpot(GetLayersBase(),Parent
												,EachThresholdCommon::_Character,EachThresholdCommon::_MultiSpotInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}

void	MenuThresholdDialog::SlotMujiFaint()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormFaint(GetLayersBase(),Parent
											,EachThresholdCommon::_NoPrint,EachThresholdCommon::_BrightnessInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotMujiRed()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormRed(GetLayersBase(),Parent
										,EachThresholdCommon::_NoPrint,EachThresholdCommon::_RedInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void	MenuThresholdDialog::SlotMujiMultispot()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormMultiSpot(GetLayersBase(),Parent
												,EachThresholdCommon::_NoPrint,EachThresholdCommon::_MultiSpotInspection);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
void MenuThresholdDialog::on_PushButtonSettingEasy_clicked()
{
	int	Level=ui->horizontalSlider->value();
}

void MenuThresholdDialog::on_horizontalSlider_valueChanged(int value)
{
	CartonMenuForm	*f=dynamic_cast<CartonMenuForm	*>(GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/""));
	if(f!=NULL){
		int	Level=ui->horizontalSlider->value();
		ui->labelLevelName->setText(f->Param.Level[Level].LevelName);
		ui->labelLevelNumber->setText(QString::number(Level));
	}
}

void MenuThresholdDialog::on_PushButtonBlade_clicked()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormBlade(GetLayersBase(),Parent);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}

void MenuThresholdDialog::on_PushButtonCADLine_clicked()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdFormCADLine(GetLayersBase(),Parent);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}

void MenuThresholdDialog::on_PushButtonWhole_clicked()
{
	if(ChildWindow!=NULL){
		delete	ChildWindow;
	}
	ChildWindow=new EachThresholdWholeForm(GetLayersBase(),Parent);
	EachThresholdCommon	*d=dynamic_cast<EachThresholdCommon *>(ChildWindow);
	if(d!=NULL && FreePosition==false){
		d->SetActivePosition(Phase,Page,GlobalX,GlobalY,ItemID);
	}
	ChildWindow->show();
	done(true);
}
