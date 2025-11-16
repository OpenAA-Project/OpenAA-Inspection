#include "CheckEverydayResource.h"
#include "ShowResultForm.h"
#include "ui_ShowResultForm.h"

ShowResultForm::ShowResultForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),
	ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
    ,ui(new Ui::ShowResultForm)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

ShowResultForm::~ShowResultForm()
{
    delete ui;
}

void	ShowResultForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
}

void ShowResultForm::on_pushButtonSet_clicked()
{

}

void ShowResultForm::on_pushButtonClose_clicked()
{

}
