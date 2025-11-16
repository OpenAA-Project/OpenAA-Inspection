#include "CartonMenuResource.h"
#include "SelectLibraryForGenerateDialog.h"
#include "ui_SelectLibraryForGenerateDialog.h"
#include "CartonMenuForm.h"
#include "SetThresholdLevelForm.h"
#include "swap.h"

SelectLibraryForGenerateDialog::SelectLibraryForGenerateDialog(CartonMenuForm *p,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(p->GetLayersBase())
	,Parent(p),
    ui(new Ui::SelectLibraryForGenerateDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	//if(Parent->ParamInMaster.Slave0Type==0)
	//	ui->PushButtonPrintPatternTop->setChecked(true);
	//else
	//	ui->PushButtonFlatTop->setChecked(true);
	//
	//if(Parent->ParamInMaster.Slave1Type==0)
	//	ui->PushButtonPrintPatternBottom->setChecked(true);
	//else
	//	ui->PushButtonFlatBottom->setChecked(true);
	//
	//if (Parent->ParamInMaster.Slave2Type == 0)
	//	ui->PushButtonPrintPatternMono->setChecked(true);
	//else
	//	ui->PushButtonFlatMono->setChecked(true);

	int	SlaveCount=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if (SlaveCount == 1) {
		resize(540, height());
		ui->groupBoxBottom->setVisible(false);
		ui->groupBoxMono->setVisible(false);
	}
	else if (SlaveCount == 2) {
		resize(630, height());
		ui->groupBoxMono->setVisible(false);
	}
	else if (SlaveCount == 3) {
		resize(930, height());
	}

	ui->PushButtonBladeTop		->setChecked(Parent->Param.GenerateBradeTop);
	ui->PushButtonBladeBottom	->setChecked(Parent->Param.GenerateBradeBottom);

	ui->PushButtonBladeTop		->setVisible(Parent->ShowBlade);
	ui->PushButtonBladeBottom	->setVisible(Parent->ShowBlade);

	if (SlaveCount==1) {
		ui->groupBoxBottom->setVisible(false);
	}
	for(int i=0;i<SlaveCount;i++){
		EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(m!=NULL){
			QString	s=m->GetMachineName();
			if(i==0){
				ui->groupBox		->setTitle(s);
			}
			else if(i==1){
				ui->groupBoxBottom	->setTitle(s);
			}
			else if(i==2){
				ui->groupBoxMono	->setTitle(s);
			}
		}
	}
	int	MaxN=Parent->Param.UsageTopSide.GetCount();
	MaxN=max(MaxN,(int)Parent->Param.UsageBottomSide.GetCount());
	MaxN=max(MaxN,(int)Parent->Param.UsageMonoSide.GetCount());
	int	BladeHeight=(Parent->ShowBlade==true)?80:0;

	if(SlaveCount>=1){
		ui->frameSelect1->setGeometry(30,40+BladeHeight	,ui->frameSelect1->width(),MaxN*80);
	}
	if(SlaveCount>=2){
		ui->frameSelect2->setGeometry(30,40+BladeHeight	,ui->frameSelect2->width(),MaxN*80);
	}
	if(SlaveCount>=3){
		ui->frameSelect3->setGeometry(30,40				,ui->frameSelect3->width(),MaxN*80);
	}

	ui->groupBox		->resize(ui->groupBox		->width(),40+BladeHeight+MaxN*80);
	ui->groupBoxBottom	->resize(ui->groupBoxBottom	->width(),40+BladeHeight+MaxN*80);
	ui->groupBoxMono	->resize(ui->groupBoxMono	->width(),40+BladeHeight+MaxN*80);
	resize(width(),460+BladeHeight-160+MaxN*80);
	ui->frameTail->move(0,height()-ui->frameTail->height());

	for(int i=0;i<GenerationMaxCamDimCount;i++){
		for(int j=0;j<GenerationMaxLibCount;j++){
			SelectionButton[i][j]=NULL;
		}
	}

	if(SlaveCount>=1){
		int	Row=0;
		for(LibraryUsage *a=Parent->Param.UsageTopSide.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			SelectionButton[0][Row]=new QPushButton;
			SelectionButton[0][Row]->setParent(ui->frameSelect1);
			SelectionButton[0][Row]->setGeometry(0,80*Row,240,72);
			SelectionButton[0][Row]->setCheckable(true);
			SelectionButton[0][Row]->setAutoExclusive(true);
			SelectionButton[0][Row]->setStyleSheet(ui->PushButtonPrintPatternTop->styleSheet());
			SelectionButton[0][Row]->setFont(ui->PushButtonPrintPatternTop->font());
			SelectionButton[0][Row]->setText(a->UsageName);
			SelectionButton[0][Row]->setChecked(a->DefaultPushed);
		}
	}
	if(SlaveCount>=2){
		int	Row=0;
		for(LibraryUsage *a=Parent->Param.UsageBottomSide.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			SelectionButton[1][Row]=new QPushButton;
			SelectionButton[1][Row]->setParent(ui->frameSelect2);
			SelectionButton[1][Row]->setGeometry(0,80*Row,240,72);
			SelectionButton[1][Row]->setCheckable(true);
			SelectionButton[1][Row]->setAutoExclusive(true);
			SelectionButton[1][Row]->setStyleSheet(ui->PushButtonPrintPatternTop->styleSheet());
			SelectionButton[1][Row]->setFont(ui->PushButtonPrintPatternTop->font());
			SelectionButton[1][Row]->setText(a->UsageName);
			SelectionButton[1][Row]->setChecked(a->DefaultPushed);
		}
	}
	if(SlaveCount>=3){
		int	Row=0;
		for(LibraryUsage *a=Parent->Param.UsageMonoSide.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			SelectionButton[2][Row]=new QPushButton;
			SelectionButton[2][Row]->setParent(ui->frameSelect3);
			SelectionButton[2][Row]->setGeometry(0,80*Row,240,72);
			SelectionButton[2][Row]->setCheckable(true);
			SelectionButton[2][Row]->setAutoExclusive(true);
			SelectionButton[2][Row]->setStyleSheet(ui->PushButtonPrintPatternTop->styleSheet());
			SelectionButton[2][Row]->setFont(ui->PushButtonPrintPatternTop->font());
			SelectionButton[2][Row]->setText(a->UsageName);
			SelectionButton[2][Row]->setChecked(a->DefaultPushed);
		}
	}
	delete	ui->PushButtonPrintPatternTop;
	delete	ui->PushButtonFlatTop;
	delete	ui->PushButtonPrintPatternBottom;
	delete	ui->PushButtonFlatBottom;
	delete	ui->PushButtonPrintPatternMono;
	delete	ui->PushButtonFlatMono;

	ui->PushButtonPrintPatternTop	=NULL;
	ui->PushButtonFlatTop			=NULL;
	ui->PushButtonPrintPatternBottom=NULL;
	ui->PushButtonFlatBottom		=NULL;
	ui->PushButtonPrintPatternMono	=NULL;
	ui->PushButtonFlatMono			=NULL;

	SForm=new SetThresholdLevelForm(GetLayersBase());
	SForm->setParent(ui->frameThresholdLevel);
	SForm->move(0,0);
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalChangeThresholdLevel(int,int))
			,this,SLOT(SlotChangeThresholdLevel(int,int)));
	connect(SForm,SIGNAL(SignalChangeThresholdLevelID(int))
			,this,SLOT(SlotChangeThresholdLevelID(int)));
	SForm->show();
}

SelectLibraryForGenerateDialog::~SelectLibraryForGenerateDialog()
{
    delete ui;
}

void SelectLibraryForGenerateDialog::on_PushButtonStartGenerate_clicked()
{
	//if(ui->PushButtonPrintPatternTop->isChecked()==true)
	//	Parent->ParamInMaster.Slave0Type=0;
	//else
	//	Parent->ParamInMaster.Slave0Type=1;
	//
	//if(ui->PushButtonPrintPatternBottom->isChecked()==true)
	//	Parent->ParamInMaster.Slave1Type=0;
	//else
	//	Parent->ParamInMaster.Slave1Type=1;
	//
	//if (ui->PushButtonPrintPatternMono->isChecked() == true)
	//	Parent->ParamInMaster.Slave2Type = 0;
	//else
	//	Parent->ParamInMaster.Slave2Type = 1;

	for(int i=0;i<GenerationMaxCamDimCount;i++){
		LibraryUsageContainer	*Container=NULL;
		IntList	*SlaveLibID=NULL;
		if(i==0){
			Container=&Parent->Param.UsageTopSide;
			SlaveLibID=&Parent->ParamInMaster.Slave0LibID;
		}
		else
		if(i==1){
			Container=&Parent->Param.UsageBottomSide;
			SlaveLibID=&Parent->ParamInMaster.Slave1LibID;
		}
		else
		if(i==2){
			Container=&Parent->Param.UsageMonoSide;
			SlaveLibID=&Parent->ParamInMaster.Slave2LibID;
		}
		else{
			break;
		}

		for(int Row=0;Row<GenerationMaxLibCount;Row++){
			if(SelectionButton[i][Row]!=NULL){
				if(SelectionButton[i][Row]->isChecked()==true){
					LibraryUsage *a=Container->GetItem(Row);
					SlaveLibID->RemoveAll();
					for(AlgorithmLibraryList *L=a->LibList.GetFirst();L!=NULL;L=L->GetNext()){
						SlaveLibID->Add(L->GetLibID());
					}
				}
			}
		}
	}

	Parent->Param.GenerateBradeTop		=ui->PushButtonBladeTop		->isChecked();
	Parent->Param.GenerateBradeBottom	=ui->PushButtonBladeBottom	->isChecked();
	done(true);
}

void SelectLibraryForGenerateDialog::on_PushButtonCancel_clicked()
{
	done(false);
}

void    SelectLibraryForGenerateDialog::SlotChangeThresholdLevelID(int ThresholdLevelID)
{
	SForm->SetCurrentThresholdLevelID(ThresholdLevelID);
	GetLayersBase()->GetIntegrationBasePointer()->DeliverThresholdLevel(ThresholdLevelID);
}
