#ifndef GENERALDISPLAYWHOLEIMAGEFORM_H
#define GENERALDISPLAYWHOLEIMAGEFORM_H

#include <QDialog>
#include "XDataInLayer.h"
#include "ui_GeneralDisplayWholeImageForm.h"

class GeneralDisplayWholeImageForm : public QDialog
{
	Q_OBJECT

	LayersBase *LBase;

public:
	GeneralDisplayWholeImageForm(LayersBase *Base ,QWidget *parent);
	~GeneralDisplayWholeImageForm();

protected:
	virtual	void keyPressEvent(QKeyEvent *event)	override;
	virtual	void closeEvent(QCloseEvent *event)		override;

private:
	Ui::GeneralDisplayWholeImageFormClass ui;
};

#endif // GENERALDISPLAYWHOLEIMAGEFORM_H
