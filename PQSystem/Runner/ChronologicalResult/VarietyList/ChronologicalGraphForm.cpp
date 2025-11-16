#include "ChronologicalGraphForm.h"
#include "ui_ChronologicalGraphForm.h"

ChronologicalGraphForm::ChronologicalGraphForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChronologicalGraphForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
}

ChronologicalGraphForm::~ChronologicalGraphForm()
{
    delete ui;
}

void ChronologicalGraphForm::on_comboBoxTimeSpan_currentIndexChanged(int index)
{

}
