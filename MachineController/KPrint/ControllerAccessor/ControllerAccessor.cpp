#include "ControllerAccessor.h"
#include "XGeneralFunc.h"

ControllerAccessor::ControllerAccessor(QWidget *parent)
    : QMainWindow(parent)
	,Socket(this)
{
    ui.setupUi(this);
}

void ControllerAccessor::on_pushButtonSend_clicked()
{

}

void ControllerAccessor::on_pushButtonClose_clicked()
{

}

void ControllerAccessor::on_pushButtonSignal_clicked()
{

}

void	ControllerAccessor::ShowInfo(void)
{
	ui.doubleSpinBoxMMPerPulse->setValue(CInfo.EncoderMMPerPulse);
}
void	ControllerAccessor::GetInfoFromWindow(void)
{
}

bool	ControllerAccessor::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==true)
		return false;
	if(f->write((const char *)&CInfo,sizeof(CInfo))!=sizeof(CInfo))
		return false;
	return true;
}

bool	ControllerAccessor::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==true)
		return false;
	if(f->read((char *)&CInfo,sizeof(CInfo))!=sizeof(CInfo))
		return false;
	return true;
}

