#pragma once

#include "ui_EditRemainTimeForm.h"
#include "ShowSumTimerForm.h"
#include "XServiceForLayers.h"

class EditRemainTimeForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditRemainTimeForm(LayersBase *base, QWidget *parent=NULL);

public:
	void setHour(quint64 val);
	void setMinuite(quint32 val);
	void setSecond(quint32 val);
	void setMiliSecond(quint32 val);
	void fromMiliSecond(quint64 mili);

	LongTime time() const;

private:
	Ui::EditRemainTimeClass ui;
};
