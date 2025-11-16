#ifndef SELECTMULTIITEMSDIALOG_H
#define SELECTMULTIITEMSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "DisplayTargetImage.h"

namespace Ui {
class SelectMultiItemsDialog;
}

class SelectMultiItemsDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
	ItemsByAlgorithmContainer	ContainersEachPhase;
    ItemsByAlgorithmContainer	ContainersBindedPhase;
	ItemsByAlgorithm			*Selected;

    explicit SelectMultiItemsDialog(LayersBase *Base ,FlexArea &Area,QWidget *parent = 0);
    ~SelectMultiItemsDialog();
    
private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

    void on_tableWidgetBinded_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectMultiItemsDialog *ui;

	virtual	void	resizeEvent(QResizeEvent *event)	override;
};

#endif // SELECTMULTIITEMSDIALOG_H
