#ifndef BUTTONSETTINGCOLORDIFFERENCEFORM_H
#define BUTTONSETTINGCOLORDIFFERENCEFORM_H

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
class ButtonSettingColorDifferenceForm;
}

class ButtonSettingColorDifferenceForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit ButtonSettingColorDifferenceForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSettingColorDifferenceForm();
    
	virtual	void	Prepare(void) override;
	int		GetSlaveNo(void)	{	return SlaveNo;		}
private slots:
    void on_PushButtonThreshold_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSettingColorDifferenceForm *ui;
};

#endif // BUTTONSETTINGCOLORDIFFERENCEFORM_H
