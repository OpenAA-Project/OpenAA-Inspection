#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class AddItemDialog;
}

class AddItemDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

    explicit AddItemDialog(int globalPage ,LayersBase *base,QWidget *parent
							,int	_AreaNumber
							,QString _AreaName	
							,int	_SysRegNumber);
    explicit AddItemDialog(int globalPage ,LayersBase *base,QWidget *parent = 0);

    ~AddItemDialog();

private slots:
        void on_pushButtonOK_clicked();

        void on_pushButtonCancel_clicked();

        void on_spinBoxSysRegNumber_valueChanged(int arg1);

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
