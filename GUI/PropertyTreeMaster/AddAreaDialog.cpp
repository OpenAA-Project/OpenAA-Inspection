#include "AddAreaDialogResource.h"
#include "AddAreaDialog.h"
#include "ui_AddAreaDialog.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"

AddAreaDialog::AddAreaDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::AddAreaDialog)
{
    ui->setupUi(this);

	GUIFormBase	*GProp;
	GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"TreeMasterImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		PickupColor=Display->GetPickedColor();
		PickupColorFrame.setParent(ui->framePickupColor);
		PickupColorFrame.move(0,0);
		PickupColorFrame.resize(ui->framePickupColor->width(),ui->framePickupColor->height());
		PickupColorFrame.SetColor(PickupColor);
	}

	ColorFrame.setParent(ui->frameColor);
	ColorFrame.move(0,0);
	ColorFrame.resize(ui->frameColor->width(),ui->frameColor->height());
	ColorFrame.SetColor(Color);

	InstallOperationLog(this);
}

AddAreaDialog::AddAreaDialog(QColor Col,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::AddAreaDialog)
{
    ui->setupUi(this);

	GUIFormBase	*GProp;
	GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"TreeMasterImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		PickupColor=Display->GetPickedColor();
		PickupColorFrame.setParent(ui->framePickupColor);
		PickupColorFrame.move(0,0);
		PickupColorFrame.resize(ui->framePickupColor->width(),ui->framePickupColor->height());
		PickupColorFrame.SetColor(PickupColor);
	}
	Color = Col;
	ui->spinBoxR->setValue(Color.red());
	ui->spinBoxB->setValue(Color.blue());
	ui->spinBoxG->setValue(Color.green());

	ColorFrame.setParent(ui->frameColor);
	ColorFrame.move(0,0);
	ColorFrame.resize(ui->frameColor->width(),ui->frameColor->height());
	ColorFrame.SetColor(Color);
}

AddAreaDialog::~AddAreaDialog()
{
    delete ui;
}

void AddAreaDialog::on_spinBoxR_valueChanged(int arg1)
{
	ShowPanel();
}

void AddAreaDialog::on_spinBoxG_valueChanged(int arg1)
{
	ShowPanel();
}

void AddAreaDialog::on_spinBoxB_valueChanged(int arg1)
{
	ShowPanel();
}

void AddAreaDialog::ShowPanel(void)
{
	int	R=ui->spinBoxR->value();
	int	G=ui->spinBoxG->value();
	int	B=ui->spinBoxB->value();
	QColor	col(R,G,B);
	ColorFrame.SetColor(col);
}

void AddAreaDialog::on_pushButtonAddPickupColor_clicked()
{
	ui->spinBoxR->setValue(PickupColor.red());
	ui->spinBoxG->setValue(PickupColor.green());
	ui->spinBoxB->setValue(PickupColor.blue());
}

void AddAreaDialog::on_pushButtonSubPickupColor_clicked()
{

}

void AddAreaDialog::on_pushButtonOk_clicked()
{
	int	R=ui->spinBoxR->value();
	int	G=ui->spinBoxG->value();
	int	B=ui->spinBoxB->value();

	Color.setRed(R);
	Color.setGreen(G);
	Color.setBlue(B);
	done(true);
}

void AddAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
