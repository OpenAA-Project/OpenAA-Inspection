#include "MMCSettingForm.h"
#include <QFileDialog>

extern bool		FlagShowOKMsg;
extern bool		FlagShowNGArea;
extern bool		FlagShowNGArea;
extern int		PickupNGAreaNumbA;
extern int		PickupNGAreaNumbB;
extern int		PickupNGAreaNumbC;
extern bool		FlagNotShowEID;
extern bool		FlagShowPickupForm;
extern QString	LogSaveDirectory;
extern bool		ShowPickupEnable;
extern bool		FlagOKDoubleDone;
extern bool		FlagNGListControl;
extern QString	LogOutputDirectory;

MMCSettingForm::MMCSettingForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.chShowOKMessage		->setChecked(FlagShowOKMsg);
	ui.chShowNGArea			->setChecked(FlagShowNGArea);
	ui.sbPickupNGAreaNumbA	->setValue	(PickupNGAreaNumbA);
	ui.sbPickupNGAreaNumbB	->setValue	(PickupNGAreaNumbB);
	ui.sbPickupNGAreaNumbC	->setValue	(PickupNGAreaNumbC);
	ui.chNotShowEID			->setChecked(FlagNotShowEID);
	ui.gbPickup				->setChecked(FlagShowPickupForm);
	ui.leLogSaveDirectory	->setText	(LogSaveDirectory);
	ui.chOKDoubleDone		->setChecked(FlagOKDoubleDone);
	ui.chNGListControl		->setChecked(FlagNGListControl);
	ui.leLogOutputDirectory	->setText	(LogOutputDirectory);

	connect(ui.pbLogSaveDirectory,	SIGNAL(clicked()),this,SLOT(pbLogSaveDirectoryClicked()));
	connect(ui.pbLogOutputDirectory,SIGNAL(clicked()),this,SLOT(pbLogOutputDirectoryClicked()));
	connect(ui.pbOK,				SIGNAL(clicked()),this,SLOT(pbOKClicked()));
	connect(ui.pbCancel,			SIGNAL(clicked()),this,SLOT(pbCancelClicked()));
}

MMCSettingForm::~MMCSettingForm()
{
}

void MMCSettingForm::pbLogSaveDirectoryClicked()
{
	QString Dir=QFileDialog::getExistingDirectory(this, "Select Log Save Directory",
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(Dir.isEmpty()){
		return;
	}
	ui.leLogSaveDirectory->setText(Dir);
}

void MMCSettingForm::pbLogOutputDirectoryClicked()
{
	QString Dir=QFileDialog::getExistingDirectory(this, "Select Log Output Directory",
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(Dir.isEmpty()){
		return;
	}
	ui.leLogOutputDirectory->setText(Dir);
}

void MMCSettingForm::pbOKClicked()
{
	FlagShowOKMsg		=ui.chShowOKMessage		->isChecked();
	FlagShowNGArea		=ui.chShowNGArea		->isChecked();
	PickupNGAreaNumbA	=ui.sbPickupNGAreaNumbA	->value();
	PickupNGAreaNumbB	=ui.sbPickupNGAreaNumbB	->value();
	PickupNGAreaNumbC	=ui.sbPickupNGAreaNumbC	->value();
	FlagNotShowEID		=ui.chNotShowEID		->isChecked();
	FlagShowPickupForm	=ui.gbPickup			->isChecked();
	LogSaveDirectory	=ui.leLogSaveDirectory	->text();
	FlagOKDoubleDone	=ui.chOKDoubleDone		->isChecked();
	FlagNGListControl	=ui.chNGListControl		->isChecked();
	LogOutputDirectory	=ui.leLogOutputDirectory->text();

	accept();
}

void MMCSettingForm::pbCancelClicked()
{
	reject();
}
