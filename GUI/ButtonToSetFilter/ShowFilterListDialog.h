#ifndef SHOWFILTERLISTDIALOG_H
#define SHOWFILTERLISTDIALOG_H

#include <QDialog>
#include "ButtonToSetFilterForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class ShowFilterListDialog;
}

class ShowFilterListDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
	int						GlobalPage;
	GUIFilterListContainer	FList;

    explicit ShowFilterListDialog(LayersBase *base ,QWidget *parent = 0);
    ~ShowFilterListDialog();

	void	Init(int globalPage ,GUIFilterListContainer &_FList);

private slots:
    void on_pushButtonClose_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowFilterListDialog *ui;
};

#endif // SHOWFILTERLISTDIALOG_H
