#ifndef LIGHTCCSCONTROLGUIFORM_H
#define LIGHTCCSCONTROLGUIFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class LightCCSControlGUIForm;
}

class	LightDLLBaseClass;

class LightCCSControlGUIForm : public GUIFormBase
{
    Q_OBJECT
    LightDLLBaseClass	*LightPointer;

public:
    explicit LightCCSControlGUIForm(LayersBase *base,QWidget *parent = 0);
    ~LightCCSControlGUIForm();
    
	virtual void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;
private slots:
    void on_dialBrightness_valueChanged(int value);
    void on_spinBoxBrightness_editingFinished();
    void on_toolButtonON_clicked();
	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);

private:
    Ui::LightCCSControlGUIForm *ui;

	QString	GetParamFileName(void);
	bool SaveFile(bool OnOff, int value);
	bool LoadFile(bool &OnOff, int &value);
};

#endif // LIGHTCCSCONTROLGUIFORM_H
