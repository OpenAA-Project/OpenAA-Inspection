#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "InputRotate.h"
#include "ui_InputRotate.h"
#include "XDataInLayer.h"
#include "XRememberer.h"


InputRotate::InputRotate(LayersBase *Base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputRotate)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Base->InstallOperationLog(this);

    Angle=0;
}

InputRotate::~InputRotate()
{
    delete ui;
}

void InputRotate::on_pushButtonCancel_clicked()
{
    done(false);
}

void InputRotate::on_pushButtonSetDegree_clicked()
{
    Angle=ui->spinBoxAngle->value();
    done(true);
}

void InputRotate::on_pushButton90Degree_clicked()
{
    Angle=90;
    done(true);
}

void InputRotate::on_pushButton180Degree_clicked()
{
    Angle=180;
    done(true);
}

void InputRotate::on_pushButton270Degree_clicked()
{
    Angle=270;
    done(true);
}
