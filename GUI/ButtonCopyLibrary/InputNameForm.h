#ifndef INPUTNAMEFORM_H
#define INPUTNAMEFORM_H

#include <QDialog>
#include "ui_InputNameForm.h"
#include "XServiceForLayers.h"

class InputNameForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	InputNameForm(LayersBase *base, const QString &_DefaultName ,QWidget *parent = 0);
	~InputNameForm();

	QString	LibName;
private:
	Ui::InputNameFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // INPUTNAMEFORM_H
