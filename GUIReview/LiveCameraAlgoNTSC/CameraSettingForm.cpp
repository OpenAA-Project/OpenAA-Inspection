#include "LiveCameraAlgoNTSCResource.h"
#include "CameraSettingForm.h"

CameraSettingForm::CameraSettingForm(int *r, int *g, int *b, QWidget* parent)
	:QDialog(parent)
{
	ui.setupUi(this);

	cur_red = r;
	cur_green = g;
	cur_blue = b;

	old_red = *r;
	old_green = *g;
	old_blue = *b;

	// Red
	ui.hsRed->setValue(old_red);
	ui.sbRed->setValue(old_red);
	// Green
	ui.hsGreen->setValue(old_green);
	ui.sbGreen->setValue(old_green);
	// Blue
	ui.hsBlue->setValue(old_blue);
	ui.sbBlue->setValue(old_blue);

	// horizonalSlider
	connect(ui.hsRed, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
	connect(ui.hsGreen, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
	connect(ui.hsBlue, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));

	// spinBox
	connect(ui.sbRed, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
	connect(ui.sbGreen, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
	connect(ui.sbBlue, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));

	// button
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(ok()));
}

void CameraSettingForm::setRed(int value)
{
	if(ui.hsRed->value()!=value){
		ui.hsRed->setValue(value);
	}
	if(ui.sbRed->value()!=value){
		ui.sbRed->setValue(value);
	}
	if(*cur_red!=value){
		*cur_red = value;
	}
}

void CameraSettingForm::setGreen(int value)
{
	if(ui.hsGreen->value()!=value){
		ui.hsGreen->setValue(value);
	}
	if(ui.sbGreen->value()!=value){
		ui.sbGreen->setValue(value);
	}
	if(*cur_green!=value){
		*cur_green = value;
	}
}

void CameraSettingForm::setBlue(int value)
{
	if(ui.hsBlue->value()!=value){
		ui.hsBlue->setValue(value);
	}
	if(ui.sbBlue->value()!=value){
		ui.sbBlue->setValue(value);
	}
	if(*cur_blue!=value){
		*cur_blue = value;
	}
}

int CameraSettingForm::getRed()
{
	return ui.hsRed->value();
}

int CameraSettingForm::getGreen()
{
	return ui.hsGreen->value();
}

int CameraSettingForm::getBlue()
{
	return ui.hsBlue->value();
}

void CameraSettingForm::cancel()
{
	*cur_red = old_red;
	*cur_green = old_green;
	*cur_blue = old_blue;

	setRed(old_red);
	setGreen(old_green);
	setBlue(old_blue);
}

void CameraSettingForm::ok()
{}

void CameraSettingForm::ResetRGB(int *r, int *g, int *b)
{
	cur_red = r;
	cur_green = g;
	cur_blue = b;

	old_red = *r;
	old_green = *g;
	old_blue = *b;
	
	// Red
	ui.hsRed->setValue(old_red);
	ui.sbRed->setValue(old_red);
	// Green
	ui.hsGreen->setValue(old_green);
	ui.sbGreen->setValue(old_green);
	// Blue
	ui.hsBlue->setValue(old_blue);
	ui.sbBlue->setValue(old_blue);

}
