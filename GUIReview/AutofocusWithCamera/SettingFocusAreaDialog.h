#ifndef SETTINGFOCUSAREADIALOG_H
#define SETTINGFOCUSAREADIALOG_H

#include <QDialog>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "mtGraphicUnit.h"

namespace Ui {
class SettingFocusAreaDialog;
}

class	AutofocusWithCameraForm;

class SettingFocusAreaDialog : public QDialog
{
    Q_OBJECT

	AutofocusWithCameraForm	*Parent;
	mtGraphicUnit	ImagePanel;
	QImage			SampleImage;
public:
    explicit SettingFocusAreaDialog(AutofocusWithCameraForm *p, QWidget *parent = 0);
    ~SettingFocusAreaDialog();

	void	Initial(QImage &Image ,int x1, int y1 ,int x2, int y2);

	int32		FocusAreaX1;
	int32		FocusAreaY1;
	int32		FocusAreaX2;
	int32		FocusAreaY2;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotOnPaint(QPainter &pnt);
	void	SlotDrawEnd(void);
    void on_pushButtonSetDarkLightSetting_clicked();

private:
    Ui::SettingFocusAreaDialog *ui;
};

#endif // SETTINGFOCUSAREADIALOG_H
