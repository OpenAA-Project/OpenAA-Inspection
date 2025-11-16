#ifndef PROGRESSONIDLEFORM_H
#define PROGRESSONIDLEFORM_H

#include "ui_ProgressOnIdleForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class ProgressOnIdleForm : public GUIFormBase
{
	Q_OBJECT

public:
	ProgressOnIdleForm(LayersBase *Base,QWidget *parent = 0);
	~ProgressOnIdleForm();

private:
	Ui::ProgressOnIdleFormClass ui;

	bool OnIdle(void);

private slots:
	void	ResizeAction();
};

#endif // PROGRESSONIDLEFORM_H
