#ifndef CREATEDCODEDIALOG_H
#define CREATEDCODEDIALOG_H

#include <QDialog>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateDCodeDialog;
}

class CreateDCodeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	GerberApertureInfoContainer *ApertureList;
public:
    explicit CreateDCodeDialog(LayersBase *base,GerberApertureInfoContainer *_ApertureList,QWidget *parent = 0);
    ~CreateDCodeDialog();

    int     Page;

	void	InitialForEdit(GerberApertureInfo *p);
	GerberDCodeBase		*CreatedAperture;
private slots:
    void on_comboBoxType_currentIndexChanged(int index);
    void on_pushButtonCreate_clicked();
    void on_pushButtonCancel_clicked();
    void on_doubleSpinBoxCircleDiameterPixel_valueChanged(double arg1);
    void on_doubleSpinBoxCircleDiameterMM_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleWidthPixel_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleWidthMM_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleHeightPixel_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleHeightMM_valueChanged(double arg1);
    void on_doubleSpinBoxObroundWidthPixel_valueChanged(double arg1);
    void on_doubleSpinBoxObroundWidthMM_valueChanged(double arg1);
    void on_doubleSpinBoxObroundHeightPixel_valueChanged(double arg1);
    void on_doubleSpinBoxObroundHeightMM_valueChanged(double arg1);
    void on_doubleSpinBoxPolygonDiameterPixel_valueChanged(double arg1);
    void on_doubleSpinBoxPolygonDiameterMM_valueChanged(double arg1);

private:
    Ui::CreateDCodeDialog *ui;
};

#endif // CREATEDCODEDIALOG_H
