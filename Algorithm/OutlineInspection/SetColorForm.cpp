#include "OutlineInspectionResource.h"
#include "SetColorForm.h"

SetColorForm::SetColorForm(ColorLogic &data ,LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),RegistPanel(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ColorPanel.setParent(ui.frameColorPanel);
	ColorPanel.Fit(ui.frameColorPanel);
	ColorPanel.Cube=data;

	RegistPanel.setParent(ui.frameRegistPanel);
	RegistPanel.move(0,0);

	connect(&RegistPanel,SIGNAL(SignalSelectCData()),this,SLOT(SlotSelectCData()));
	connect(&RegistPanel,SIGNAL(SignalBeforeSave()) ,this,SLOT(SlotBeforeSave()));

	InstallOperationLog(this);
}

SetColorForm::~SetColorForm()
{

}
void	SetColorForm::SlotSelectCData()
{
	ColorLogic	*c=RegistPanel.CData.GetColorLogic();
	if(c!=NULL){
		ColorPanel.Cube=*c;
		ColorPanel.InitializedDoneCube();
		ColorPanel.Repaint();
	}
}
void	SetColorForm::SlotBeforeSave()
{
	RegistPanel.CData.Set(ColorPanel.Cube);
}

void SetColorForm::on_pushButtonOK_clicked()
{
	Col=ColorPanel.Cube;
	done(true);
}

void SetColorForm::on_pushButtonCancel_clicked()
{
	done(false);
}