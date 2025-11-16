#ifndef MOVEALLFORM_H
#define MOVEALLFORM_H

#include <QDialog>
#include "ui_MoveAllForm.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"

class MoveAllForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	QCheckBox	**CheckedPage;
	int		AllocCheckedPage;
public:
	MoveAllForm(LayersBase *Base,QWidget *parent = 0);
	~MoveAllForm();

	int	MovX;
	int	MovY;
	bool	MoveMasterImage;
	bool	MoveTargetImage;
	IntList	AppliedPages;
	QLabel	FrameCheckBox;
private:
	Ui::MoveAllFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // MOVEALLFORM_H
