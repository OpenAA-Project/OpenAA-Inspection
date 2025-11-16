#include "IntegrationModifyMasterResource.h"
#include "PopupMenuForm.h"
#include "ui_PopupMenuForm.h"
#include "ChangeImageSizeDialog.h"
#include "MoveAllDialog.h"


PopupMenuForm::PopupMenuForm(LayersBase *Base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),
    ui(new Ui::PopupMenuForm)
{
    ui->setupUi(this);
}

PopupMenuForm::~PopupMenuForm()
{
    delete ui;
}

void PopupMenuForm::on_PushButtonMoveAll_clicked()
{
    MoveAllDialog   D(GetLayersBase());
    D.exec();

    close();
}


void PopupMenuForm::on_PushButtonChangeSize_clicked()
{
    ChangeImageSizeDialog   D(GetLayersBase());
    D.exec();

    close();
}


void PopupMenuForm::on_PushButtonClose_clicked()
{
    close();
}

