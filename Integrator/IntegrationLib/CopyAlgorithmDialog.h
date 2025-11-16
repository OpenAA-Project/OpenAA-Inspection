#ifndef COPYALGORITHMDIALOG_H
#define COPYALGORITHMDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "XServiceForLayers.h"

namespace Ui {
class CopyAlgorithmDialog;
}

class IntegrationAlgoSimpleImagePanel;

class SlaveButton : public QPushButton
{
    Q_OBJECT

    int SlaveNo;
public:
	SlaveButton(int _SlaveNo);
	~SlaveButton(void);

signals:
    void    SignalClicked(int slaveNo);
private slots:
    void    SlotClicked(bool);
};


class CopyAlgorithmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    IntegrationAlgoSimpleImagePanel *Parent;
    SlaveButton     *RxSlaveButton[100];
    QPushButton     *TxButtonDim[4];

public:
    explicit CopyAlgorithmDialog(LayersBase *base
                                ,IntegrationAlgoSimpleImagePanel *P
                                ,QWidget *parent = nullptr);
    ~CopyAlgorithmDialog();

private slots:
    void on_toolButtonRx_clicked();
    void on_toolButtonTx_clicked();
    void on_pushButtonExeTx_clicked();
    void    SlotRxClicked(int slaveNo);

private:
    Ui::CopyAlgorithmDialog *ui;
};

#endif // COPYALGORITHMDIALOG_H
