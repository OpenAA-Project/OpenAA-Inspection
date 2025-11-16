#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include "XCheckBrightness.h"
#include "XServiceForLayers.h"

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit AddItemDialog(LayersBase *base,QWidget *parent = 0);
    ~AddItemDialog();
    
	void	Reflect(void);

	QString		ItemName;
	CheckBrightnessItem::_Condition	Condition;
	int16		ThreshL,ThreshH;
	int16		RegNumber;
	int16		RepeatableCount;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
