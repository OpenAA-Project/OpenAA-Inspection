#ifndef ADDSOURCEITEMDIALOG_H
#define ADDSOURCEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class AddSourceItemDialog;
}

class AddSourceItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int GlobalPage;
	int	Layer;
	AlgorithmBasePointerContainer AlgoBases;
public:
    explicit AddSourceItemDialog(LayersBase *Base,int GlobalPage ,int _Layer,QWidget *parent = 0);
    ~AddSourceItemDialog();

	QString	AlgoRoot;
	QString	AlgoName;
	int		ItemID;

private slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddSourceItemDialog *ui;
};

#endif // ADDSOURCEITEMDIALOG_H
