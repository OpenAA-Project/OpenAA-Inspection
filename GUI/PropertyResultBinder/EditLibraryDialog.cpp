#include "PropertyResultBinderFormResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"

EditLibraryDialog::EditLibraryDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}
