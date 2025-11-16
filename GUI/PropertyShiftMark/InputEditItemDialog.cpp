#include "PropertyShiftMarkResource.h"
#include "InputEditItemDialog.h"
#include "ui_InputEditItemDialog.h"
#include "XShiftMark.h"
#include "XPropertyShiftMarkPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

InputEditItemDialog::InputEditItemDialog(LayersBase *base 
                                ,int _Page ,int _ItemID 
                                ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::InputEditItemDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    Phase       =GetLayersBase()->GetCurrentPhase();
    GlobalPage  =_Page;
    ItemID      =_ItemID;

    GUICmdReqItemThreshold  RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    GUICmdAckItemThreshold  ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
    RCmd.Phase  =Phase;
    RCmd.ItemID =ItemID;

    if(RCmd.Send(GlobalPage,0,ACmd)==true){
        ui->lineEditItemName        ->setText(ACmd.ItemName);
        ui->EditSearchDotEdge       ->setValue(ACmd.SearchDotEdge);
        ui->EditSearchDotMarkMin    ->setValue(ACmd.SearchDotMarkMin);
        ui->EditSearchDotMarkMax    ->setValue(ACmd.SearchDotMarkMax);
        ui->checkBoxNGByLosingMark  ->setChecked(ACmd.NGByLosingMark);
        ui->EditThresholdLost   ->setValue(ACmd.ThresholdLost);
    }
}

InputEditItemDialog::~InputEditItemDialog()
{
    delete ui;
}

void InputEditItemDialog::on_pushButtonChangeVert_clicked()
{
    GUICmdChangeDirection  SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    SCmd.Phase  =Phase;
    SCmd.ItemID =ItemID;
    SCmd.Send(NULL,GlobalPage,0);
			
    GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShiftMarkImagePanel" ,/**/"");
	if(GProp!=NULL){
        GProp->Repaint();
    }
}


void InputEditItemDialog::on_pushButtonOK_clicked()
{
    GUICmdSetItemThreshold  SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    SCmd.Phase  =Phase;
    SCmd.ItemID =ItemID;
    SCmd.ItemName           =ui->lineEditItemName       ->text();
    SCmd.SearchDotEdge      =ui->EditSearchDotEdge      ->value();
    SCmd.SearchDotMarkMin   =ui->EditSearchDotMarkMin   ->value();
    SCmd.SearchDotMarkMax   =ui->EditSearchDotMarkMax   ->value();
    SCmd.NGByLosingMark     =ui->checkBoxNGByLosingMark ->isChecked();
    SCmd.ThresholdLost      =ui->EditThresholdLost      ->value();
    SCmd.Send(NULL,GlobalPage,0);
    done(true);
}


void InputEditItemDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

