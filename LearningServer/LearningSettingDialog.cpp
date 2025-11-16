#include "LearningSettingDialog.h"
#include "XDataInLayer.h"

LearningSettingDialog::LearningSettingDialog(LayersBase *_Base,ParamBase *base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(_Base)
{
	ui.setupUi(this);
	Base=base;

	WTabGeneral=new WEditParameterTab(Base ,-1,ui.frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui.frame->width(),ui.frame->height());

}

LearningSettingDialog::~LearningSettingDialog()
{

}


void LearningSettingDialog::on_ButtonOK_clicked()
{
	WTabGeneral->LoadFromWindow();
	Base->SaveDefault(GetLayersBase()->GetUserPath());
	done(true);
}

void LearningSettingDialog::on_ButtonCancel_clicked()
{
	done(false);
}