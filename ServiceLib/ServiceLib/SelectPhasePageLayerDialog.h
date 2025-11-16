#ifndef SELECTPHASEPAGELAYERDIALOG_H
#define SELECTPHASEPAGELAYERDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SelectPhasePageLayerDialog;
}

class SelectPhasePageLayerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectPhasePageLayerDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectPhasePageLayerDialog();

	int	SelectPhase;
	int	SelectPage;
	int	SelectLayer;

private slots:
    void on_listWidgetPhase1_doubleClicked(const QModelIndex &index);
    void on_listWidgetPage1_doubleClicked(const QModelIndex &index);
    void on_listWidgetLayer1_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect1_clicked();
    void on_pushButtonCancel1_clicked();

private:
    Ui::SelectPhasePageLayerDialog *ui;
};

#endif // SELECTPHASEPAGELAYERDIALOG_H
