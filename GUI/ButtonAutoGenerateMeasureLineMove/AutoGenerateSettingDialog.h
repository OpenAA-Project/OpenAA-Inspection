#ifndef AUTOGENERATESETTINGDIALOG_H
#define AUTOGENERATESETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QPushButton>
#include "XMeasureLineMove.h"

namespace Ui {
class AutoGenerateSettingDialog;
}

class AutoGenerateSettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	BladeMeasure &BladeMeasureData;
public:
    explicit AutoGenerateSettingDialog(LayersBase *Base ,BladeMeasure &BladeMeasureData ,QWidget *parent = 0);
    ~AutoGenerateSettingDialog();
    
private slots:
    void on_PushButtonSaveBladePos_clicked();
    void on_PushButtonLoadBladePos_clicked();
    void on_PushButtonClose_clicked();
	void	SlotBladeListIndexChanged ( int index );
private:
    Ui::AutoGenerateSettingDialog *ui;

	void	ShowList(void);
	void	ShwListInner(int row, int Index );
	void	GetDataFromList(void);
};

#endif // AUTOGENERATESETTINGDIALOG_H
