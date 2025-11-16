#ifndef SHOWLOADEDINFOFORM_H
#define SHOWLOADEDINFOFORM_H

#include <QDialog>
#include "ui_ShowLoadedInfoForm.h"
#include "XServiceForLayers.h"
class	LayersBase;

class ShowLoadedInfoForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	ShowLoadedInfoForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowLoadedInfoForm();

private:
	Ui::ShowLoadedInfoFormClass ui;

	void	ShowList(void);
signals:
	void	SignalClose();
private slots:
	void on_pushButtonOK_clicked();
	void on_toolButtonByName_clicked();
	void on_toolButtonByPage_clicked();
};

#endif // SHOWLOADEDINFOFORM_H
