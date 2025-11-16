#include "OnFlowForm.h"
#include "ui_OnFlowForm.h"
#include "XGeneralFunc.h"

OnFlowForm::OnFlowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnFlowForm)
{
    ui->setupUi(this);
	::SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
}

OnFlowForm::~OnFlowForm()
{
    delete ui;
}
