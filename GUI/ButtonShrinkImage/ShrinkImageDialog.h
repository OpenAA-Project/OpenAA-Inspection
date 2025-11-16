#ifndef SHRINKIMAGEDIALOG_H
#define SHRINKIMAGEDIALOG_H

#include <QDialog>
#include "ui_ShrinkImageDialog.h"
#include "XServiceForLayers.h"

class ShrinkImageDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ShrinkImageDialog(LayersBase *base, QWidget *parent = 0);
	~ShrinkImageDialog();

	double	Rate;
	bool	ExeMaster;
	bool	ExeTarget;
private:
	Ui::ShrinkImageDialogClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOk_clicked();
};

#endif // SHRINKIMAGEDIALOG_H
