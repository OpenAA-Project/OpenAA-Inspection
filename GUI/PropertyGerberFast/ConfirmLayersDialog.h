#ifndef CONFIRMLAYERSDIALOG_H
#define CONFIRMLAYERSDIALOG_H

#include <QDialog>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGUIGerberPacket.h"
#include "XServiceForLayers.h"

namespace Ui {
class ConfirmLayersDialog;
}

class	PropertyGerberFastForm;
class	GerberLayerListOnScreen;
class	GerberCompositeLayerListOnScreen;

class ConfirmLayersDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	PropertyGerberFastForm	*Parent;
	bool					CompositeMode;
	GerberLayerListOnScreen				*IndexChild[MaxGerberLayer];
	GerberCompositeLayerListOnScreen	*IndexCompChild[MaxGerberLayer];

public:
    explicit ConfirmLayersDialog(PropertyGerberFastForm *p,bool CompositeMode ,QWidget *parent = 0);
    ~ConfirmLayersDialog();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonClearAll_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ConfirmLayersDialog *ui;
};

#endif // CONFIRMLAYERSDIALOG_H
