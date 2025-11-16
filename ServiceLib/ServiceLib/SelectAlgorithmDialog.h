#ifndef SELECTALGORITHMDIALOG_H
#define SELECTALGORITHMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataComponent.h"

namespace Ui {
class SelectAlgorithmDialog;
}

class SelectAlgorithmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectAlgorithmDialog(LayersBase *base 
                                    ,const RootNameListContainer &_Selected
                                    ,QWidget *parent = nullptr);
    ~SelectAlgorithmDialog();

    RootNameListContainer   Selected;

private slots:
    void on_pushButtonAll_clicked();
    void on_pushButtonSelectOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectAlgorithmDialog *ui;

    virtual void resizeEvent(QResizeEvent *event)    override;
};

#endif // SELECTALGORITHMDIALOG_H
