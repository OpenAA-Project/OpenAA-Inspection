#include "ExecuteBatchResource.h"
#include "MessageForm.h"
#include "ui_MessageForm.h"
#include "XGeneralFunc.h"

MessageForm::MessageForm(LayersBase *base, QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::MessageForm)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
	InstallOperationLog(this);
}

MessageForm::~MessageForm()
{
    delete ui;
}

void	MessageForm::SetMessage(const QString &Message)
{
	ui->label->setText(Message);
}
void MessageForm::on_pushButtonClose_clicked()
{
    close();
}
