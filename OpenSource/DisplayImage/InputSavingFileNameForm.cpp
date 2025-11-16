#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "InputSavingFileNameForm.h"
#include "ui_InputSavingFileNameForm.h"
#include "XDisplayImage.h"

InputSavingFileNameForm::InputSavingFileNameForm(LayersBase *Base,const QString &filename,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputSavingFileNameForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Base->InstallOperationLog(this);

    PathFileName=filename;
    ui->lineEditFileName->setText(PathFileName);
}

InputSavingFileNameForm::~InputSavingFileNameForm()
{
    delete ui;
}

void InputSavingFileNameForm::on_pushButtonOK_clicked()
{
    PathFileName=ui->lineEditFileName->text();
    done(true);
}

void InputSavingFileNameForm::on_pushButtonCancel_clicked()
{
    done(false);
}
