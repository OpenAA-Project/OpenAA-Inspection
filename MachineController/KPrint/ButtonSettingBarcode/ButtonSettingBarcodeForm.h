#ifndef BUTTONSETTINGBARCODEFORM_H
#define BUTTONSETTINGBARCODEFORM_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"

namespace Ui {
class ButtonSettingBarcodeForm;
}

class ButtonSettingBarcodeForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit ButtonSettingBarcodeForm(LayersBase *Base, QWidget *parent = 0);
    ~ButtonSettingBarcodeForm();
    
	virtual	void	Prepare(void) override;
private slots:
    void on_PushButtonThreshold_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSettingBarcodeForm *ui;
};

#endif // BUTTONSETTINGBARCODEFORM_H
