#include "ShowRebootForm.h"
#include "ui_ShowRebootForm.h"

ShowRebootForm::ShowRebootForm(int ReasonIndex ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowRebootForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint);

	ui->stackedWidget->setCurrentIndex(ReasonIndex);

	TM.setInterval(5000);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(OnTimerTicked()));
	TM.start();
}

ShowRebootForm::~ShowRebootForm()
{
    delete ui;
}

void ShowRebootForm::OnTimerTicked()
{
	emit  SignalTimeUp();
}
