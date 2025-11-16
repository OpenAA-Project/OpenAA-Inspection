#ifndef NGTYPEDIALOG_H
#define NGTYPEDIALOG_H

#include <QDialog>
#include "ui_NGTypeDialog.h"
#include "XServiceForLayers.h"

class	BlockLibNGTypeItem;

class NGTypeDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	BlockLibNGTypeItem *Item;

public:
	NGTypeDialog(LayersBase *base, BlockLibNGTypeItem *Item ,QWidget *parent = 0);
	~NGTypeDialog();

private:
	Ui::NGTypeDialogClass ui;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // NGTYPEDIALOG_H
