#include "MoveAllFormResource.h"
#include "MoveAllForm.h"

MoveAllForm::MoveAllForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.scrollArea->setWidget(&FrameCheckBox);
	FrameCheckBox.resize(60,500);

	AllocCheckedPage=GetPageNumb();
	CheckedPage=new QCheckBox*[AllocCheckedPage];
	int	Y=0;
	for(int page=0;page<AllocCheckedPage;page++){
		CheckedPage[page]=new QCheckBox(&FrameCheckBox);
		CheckedPage[page]->move(0,Y);
		Y+=20;
		CheckedPage[page]->setText(LangSolver.GetString(MoveAllForm_LS,LID_2)/*"Page "*/+QString::number(page));
		CheckedPage[page]->setCheckable(true);
		CheckedPage[page]->setChecked(true);
	}
	InstallOperationLog(this);
}

MoveAllForm::~MoveAllForm()
{
	if(CheckedPage!=NULL){
		for(int page=0;page<AllocCheckedPage;page++){
			CheckedPage[page]->deleteLater();
		}
		delete	[]CheckedPage;
	}
	CheckedPage=NULL;
}


void MoveAllForm::on_pushButtonOK_clicked()
{
	MovX=ui.spinBoxMoveX->value();
	MovY=ui.spinBoxMoveY->value();
	MoveMasterImage=ui.checkBoxMoveMasterImage->isChecked();
	MoveTargetImage=ui.checkBoxMoveTargetImage->isChecked();

	AppliedPages.RemoveAll();
	for(int page=0;page<AllocCheckedPage;page++){
		if(CheckedPage[page]->isChecked()==true){
			AppliedPages.Add(page);
		}
	}
	done(true);
}

void MoveAllForm::on_pushButtonCancel_clicked()
{
	done(false);
}