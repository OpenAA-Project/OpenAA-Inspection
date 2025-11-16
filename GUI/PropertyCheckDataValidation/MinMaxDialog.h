#ifndef MINMAXDIALOG_H
#define MINMAXDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XPropertyCheckDataValidationPacket.h"

namespace Ui {
class MinMaxDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationCheckMinMaxThreshold;

class MinMaxDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;
    ThresholdMemberListContainer	LContainer;
public:
    explicit MinMaxDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~MinMaxDialog();

    int SelectedLibType ;
    int SelectedLibID   ;
	int32	ParamID;
	double	MinValue;
	double	MaxValue;

    void    SetCurrentItem(const CheckDataValidationCheckMinMaxThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationCheckMinMaxThreshold *WThr);

private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::MinMaxDialog *ui;
};

#endif // MINMAXDIALOG_H
