#ifndef FORMSELECTFOLDERS_H
#define FORMSELECTFOLDERS_H

#include <QDialog>
#include "ui_FormSelectFolders.h"
#include "XServiceForLayers.h"

class FormSelectFolders : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	FormSelectFolders(LayersBase *base, QWidget *parent = 0);
	~FormSelectFolders();

	QStringList	PathLists;
private:
	Ui::FormSelectFoldersClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // FORMSELECTFOLDERS_H
