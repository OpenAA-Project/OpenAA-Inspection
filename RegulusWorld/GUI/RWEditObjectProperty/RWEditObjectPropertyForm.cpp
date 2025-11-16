#include "RWEditObjectPropertyForm.h"
#include "ui_RWEditObjectPropertyForm.h"

RWEditObjectPropertyForm::RWEditObjectPropertyForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::RWEditObjectPropertyForm)
{
    ui->setupUi(this);
}

RWEditObjectPropertyForm::~RWEditObjectPropertyForm()
{
    delete ui;
}

void RWEditObjectPropertyForm::on_pushButtonLoadStepFile_clicked()
{

}


void RWEditObjectPropertyForm::on_pushButtonLoadFromServer_clicked()
{

}


void RWEditObjectPropertyForm::on_listWidgetFileList_itemSelectionChanged()
{

}


void RWEditObjectPropertyForm::on_listWidgetFileList_clicked(const QModelIndex &index)
{

}


void RWEditObjectPropertyForm::on_listWidgetFileList_doubleClicked(const QModelIndex &index)
{

}


void RWEditObjectPropertyForm::on_treeWidgetObject_itemSelectionChanged()
{

}


void RWEditObjectPropertyForm::on_treeWidgetObject_clicked(const QModelIndex &index)
{

}


void RWEditObjectPropertyForm::on_treeWidgetObject_doubleClicked(const QModelIndex &index)
{

}


void RWEditObjectPropertyForm::on_pushButtonSave_clicked()
{

}


void RWEditObjectPropertyForm::on_pushButtonLoad_clicked()
{

}


void RWEditObjectPropertyForm::on_pushButtonToServer_clicked()
{

}

