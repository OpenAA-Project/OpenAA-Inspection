#ifndef SELECTCOMPOSITEDEFDIALOG_H
#define SELECTCOMPOSITEDEFDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SelectCompositeDefDialog;
}

class	GeneralLibFolderForm;

class SelectCompositeDefDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	int		LibType;
public:
    explicit SelectCompositeDefDialog(LayersBase *base,QWidget *parent = 0);
    ~SelectCompositeDefDialog();

	int	SelectedCompositeID;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectCompositeDefDialog *ui;

	void ShowCompositeList(void);
};

#endif // SELECTCOMPOSITEDEFDIALOG_H
