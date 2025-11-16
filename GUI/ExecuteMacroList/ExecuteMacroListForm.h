#ifndef EXECUTEMACROLISTFORM_H
#define EXECUTEMACROLISTFORM_H

#include "XGUIFormBase.h"
#include "ui_ExecuteMacroListForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMacroExecuter.h"

class ExecuteMacroListForm : public GUIFormBase
{
	Q_OBJECT

	MacroSentenseContainer	SContainer;

public:
	ExecuteMacroListForm(LayersBase *Base ,QWidget *parent = 0);
	~ExecuteMacroListForm();

private:
	Ui::ExecuteMacroListFormClass ui;

	void ShowList(void);
	volatile	bool	CancelMode;

private slots:
	void on_pushButtonStopExecute_clicked();
	void on_pushButtonStartExecute_clicked();
	void on_pushButtonLoadMacro_clicked();
};

#endif // EXECUTEMACROLISTFORM_H
