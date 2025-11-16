#include "ProgressOnIdleResource.h"
#include "ProgressOnIdleForm.h"

ProgressOnIdleForm::ProgressOnIdleForm(LayersBase *Base,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ProgressOnIdleForm::~ProgressOnIdleForm()
{

}
void	ProgressOnIdleForm::ResizeAction()
{
	ui.progressBar->resize(width(),height());
}

bool ProgressOnIdleForm::OnIdle(void)
{
	if(ui.progressBar->value()>=ui.progressBar->maximum()){
		ui.progressBar->setValue(0);
	}
	else{
		ui.progressBar->setValue(ui.progressBar->value()+1);
	}
	return true;
}
