#ifndef FILTERSETTINGDIALOG_H
#define FILTERSETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class FilterSettingDialog;
}

class FilterSettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
public:
	int		Position;
	double	Strength;

    explicit FilterSettingDialog(int position ,double strength ,LayersBase *base,QWidget *parent = 0);
    ~FilterSettingDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::FilterSettingDialog *ui;
};

#endif // FILTERSETTINGDIALOG_H
