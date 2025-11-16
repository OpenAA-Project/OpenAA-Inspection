#include "EditRemainTimeFormResource.h"
#include "EditRemainTimeForm.h"

EditRemainTimeForm::EditRemainTimeForm(LayersBase *base, QWidget *parent)
	:QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	fromMiliSecond(0);

	InstallOperationLog(this);
}

void EditRemainTimeForm::setHour(quint64 val)
{
	ui.sbHour->setValue(val);
}

void EditRemainTimeForm::setMinuite(quint32 val)
{
	ui.sbMinuite->setValue(val);
}

void EditRemainTimeForm::setSecond(quint32 val)
{
	ui.sbSecond->setValue(val);
}

void EditRemainTimeForm::setMiliSecond(quint32 val)
{
	ui.sbMiliSecond->setValue(val);
}

void EditRemainTimeForm::fromMiliSecond(quint64 mili)
{
	LongTime time = LongTime::fromMiliSecond(mili);

	setHour(time.hour());
	setMinuite(time.minuite());
	setSecond(time.second());
	setMiliSecond(time.miliSecond());
}

LongTime EditRemainTimeForm::time() const
{
	LongTime time;

	time.setHour(ui.sbHour->value());
	time.setMinuite(ui.sbMinuite->value());
	time.setSecond(ui.sbSecond->value());
	time.setMiliSecond(ui.sbMiliSecond->value());

	return time;
}
