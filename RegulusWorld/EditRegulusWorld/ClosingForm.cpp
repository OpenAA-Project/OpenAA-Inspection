#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "ClosingForm.h"
#include "ui_ClosingForm.h"

ClosingForm::ClosingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClosingForm)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	int	LanguageCode=FRegistry.LoadRegInt(/**/"Language",0);
	switch(LanguageCode){
		case 1:
			ui->label->setText(/**/"On closing...");
			break;
	}
}

ClosingForm::~ClosingForm()
{
    delete ui;
}
