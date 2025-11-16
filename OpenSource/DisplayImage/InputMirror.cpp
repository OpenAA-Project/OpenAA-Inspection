#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "InputMirror.h"
#include "ui_InputMirror.h"
#include "InputMirror.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

InputMirror::InputMirror(LayersBase *Base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputMirror)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Base->InstallOperationLog(this);
}

InputMirror::~InputMirror()
{
    delete ui;
}

void InputMirror::on_pushButtonCancel_clicked()
{
    done(false);
}

void InputMirror::on_pushButtonYMirror_clicked()
{
    MirrorMode=AlgorithmItemRoot::_YMirror;
    done(true);
}

void InputMirror::on_pushButtonXMirror_clicked()
{
    MirrorMode=AlgorithmItemRoot::_XMirror;
    done(true);
}
