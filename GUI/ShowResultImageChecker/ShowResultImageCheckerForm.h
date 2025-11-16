#ifndef SHOWRESULTIMAGECHECKERFORM_H
#define SHOWRESULTIMAGECHECKERFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowResultImageCheckerForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowResultImageCheckerForm : public GUIFormBase
{
	Q_OBJECT

	bool	ModeSaveCSV;
public:
	ShowResultImageCheckerForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowResultImageCheckerForm();

	virtual void	Prepare(void)	override;
private:
	Ui::ShowResultImageCheckerFormClass ui;

private slots:
	void on_tableWidget_clicked(const QModelIndex &);
	void on_pushButtonUpdate_clicked();
	void	ResizeAction();
};

#endif // SHOWRESULTIMAGECHECKERFORM_H
