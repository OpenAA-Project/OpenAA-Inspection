#include "SettingBarcodeFormDialog.h"
#include "ui_SettingBarcodeFormDialog.h"
#include "swap.h"
#include "XCrossObj.h"
#include "XColorSpace.h"
#include "ButtonSettingBarcodeForm.h"
#include "XGeneralFunc.h"


extern	char *sRoot;
extern	char *sName;


SettingBarcodeFormDialog::SettingBarcodeFormDialog(LayersBase *base, ButtonSettingBarcodeForm *p, QWidget *parent) :
    QDialog(parent),ServiceForLayers(base), Parent(p),
    ui(new Ui::SettingBarcodeFormDialog)
{
    ui->setupUi(this);
}

SettingBarcodeFormDialog::~SettingBarcodeFormDialog()
{
    delete ui;
}

void SettingBarcodeFormDialog::on_tableWidgetItemList_clicked(const QModelIndex &index)
{

}

void SettingBarcodeFormDialog::on_pushButtonAdd_clicked()
{

}

void SettingBarcodeFormDialog::on_pushButtonSub_clicked()
{

}

void SettingBarcodeFormDialog::on_ButtonRelrectOnlyBlock_clicked()
{

}

void SettingBarcodeFormDialog::on_ButtonReflectAllBlocks_clicked()
{

}

void SettingBarcodeFormDialog::on_ButtonClose_clicked()
{

}
