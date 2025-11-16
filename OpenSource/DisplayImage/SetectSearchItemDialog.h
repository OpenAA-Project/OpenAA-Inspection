#ifndef SETECTSEARCHITEMDIALOG_H
#define SETECTSEARCHITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SetectSearchItemDialog;
}
class	AlgorithmBase;

class SetectSearchItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	AlgorithmBase *Algo;
	int GlobalPage;
	ListPageLayerIDLibNamePack	ItemIDList;
public:
    explicit SetectSearchItemDialog(AlgorithmBase *Algo ,ListPageLayerIDLibNamePack &itemIDList ,QWidget *parent);
    ~SetectSearchItemDialog();

	ListPageLayerIDPack	SelectedItems;
private slots:
    void on_pushButtonSortByID_clicked();
    void on_pushButtonSortByLibID_clicked();
    void on_pushButtonSortByName_clicked();
    void on_ButtonSelectAndView_clicked();
    void on_ButtonOnlyView_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonSortByItemID_clicked();

private:
    Ui::SetectSearchItemDialog *ui;

	void	ShowList(void);
	void	SelectOnes(void);
};

#endif // SETECTSEARCHITEMDIALOG_H
