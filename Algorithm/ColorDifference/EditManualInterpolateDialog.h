#ifndef EDITMANUALINTERPOLATEDIALOG_H
#define EDITMANUALINTERPOLATEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XColorDifference.h"
namespace Ui {
class EditManualInterpolateDialog;
}

class EditManualInterpolateDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    AlgorithmItemRoot *Item;
public:
    explicit EditManualInterpolateDialog(AlgorithmItemRoot *item ,LayersBase *Base,QWidget *parent = nullptr);
    ~EditManualInterpolateDialog();

private slots:
    void on_pushButtonDeleteLine_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonAdd_clicked();

private:
    Ui::EditManualInterpolateDialog *ui;

	void	ShowList(void);
};

#endif // EDITMANUALINTERPOLATEDIALOG_H
