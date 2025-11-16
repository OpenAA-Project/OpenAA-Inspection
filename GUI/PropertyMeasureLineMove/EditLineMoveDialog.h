#ifndef EDITLINEMOVEDIALOG_H
#define EDITLINEMOVEDIALOG_H

#include <QDialog>
#include "XMeasureLineMove.h"
#include "XMeasureLineMovePacket.h"
#include "XServiceForLayers.h"

namespace Ui {
    class EditLineMoveDialog;
}

class EditLineMoveDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	MeasureLineMoveThreshold	*ThreData;
	QString						ItemName;

    explicit EditLineMoveDialog(LayersBase *base, QString &itemName ,MeasureLineMoveThreshold *_ThreData ,QWidget *parent = 0);
    ~EditLineMoveDialog();

private slots:
        void on_ButtonOK_clicked();
        void on_ButtonCancel_clicked();

private:
    Ui::EditLineMoveDialog *ui;
};

#endif // EDITLINEMOVEDIALOG_H
