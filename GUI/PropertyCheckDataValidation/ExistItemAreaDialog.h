#ifndef EXISTITEMAREADIALOG_H
#define EXISTITEMAREADIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ExistItemAreaDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationExistItemAreaThreshold;

class ExistItemAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;
public:
    explicit ExistItemAreaDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ExistItemAreaDialog();

	int32	SelectedLibType;
	int32	SelectedLibID;
	double	FilledPercentageInMask;
	bool	CheckExistence;

    void    SetCurrentItem(const CheckDataValidationExistItemAreaThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationExistItemAreaThreshold *WThr);

private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
private:
    Ui::ExistItemAreaDialog *ui;
};

#endif // EXISTITEMAREADIALOG_H
