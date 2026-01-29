#include "DotColorMatchingImagePanelResource.h"
#include "SelectBlockBySpecialDialog.h"
#include "ui_SelectBlockBySpecialDialog.h"
#include "XTypeDef.h"
#include "XDataInLayer.h"
#include "XRememberer.h"
#include "DotColorMatchingImagePanel.h"

SelectBlockBySpecialDialog::SelectBlockBySpecialDialog(DotColorMatchingImagePanel *p,int libType ,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,Parent(p)
    ,Libs(libType ,Base)
    ,ui(new Ui::SelectBlockBySpecialDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    LangSolver.SetUI(this);

    Libs.setParent(ui->frameLibrary);
    Libs.move(0,0);
    Libs.resize(ui->frameLibrary->width(),ui->frameLibrary->height());

    Parent->RestoreForm(this);

    Base->InstallOperationLog(this);
}

SelectBlockBySpecialDialog::~SelectBlockBySpecialDialog()
{
    delete ui;
}

void SelectBlockBySpecialDialog::on_ButtonSelect_clicked()
{
    Parent->SaveForm(this);
    OutlineMode=ui->checkBoxOutline->isChecked();
    done(true);
}


void SelectBlockBySpecialDialog::on_ButtonCancel_clicked()
{
    done(false);
}
