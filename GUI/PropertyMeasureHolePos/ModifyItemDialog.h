#ifndef MODIFYITEMDIALOG_H
#define MODIFYITEMDIALOG_H

#include <QDialog>
#include "XMeasureHolePos.h"
#include "XMeasureHolePosPacket.h"
#include "XServiceForLayers.h"

namespace Ui {
    class ModifyItemDialog;
}

class ModifyItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	MeasureHolePosThreshold		*ThreData;
	QString						ItemName;

    explicit ModifyItemDialog(LayersBase *base, QString &itemName ,MeasureHolePosThreshold *_ThreData 
								,QWidget *parent = 0);
    ~ModifyItemDialog();

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ModifyItemDialog *ui;
};

#endif // MODIFYITEMDIALOG_H
