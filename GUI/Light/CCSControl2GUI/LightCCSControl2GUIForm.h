#ifndef LIGHTCCSCONTROL2GUIFORM_H
#define LIGHTCCSCONTROL2GUIFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class LightCCSControl2GUIForm;
}
class	LightDLLBaseClass;

class LightCCSControl2GUIForm : public GUIFormBase
{
    Q_OBJECT
    LightDLLBaseClass	*LightPointer;

public:
    explicit LightCCSControl2GUIForm(LayersBase *base,QWidget *parent = 0);
    ~LightCCSControl2GUIForm();
    
	virtual void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;
private slots:
    void on_dialBrightness1_valueChanged(int value);
    void on_spinBoxBrightness1_editingFinished();
    void on_toolButtonON1_clicked();
    void on_dialBrightness2_valueChanged(int value);
    void on_spinBoxBrightness2_editingFinished();
    void on_toolButtonON2_clicked();
	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);

private:
    Ui::LightCCSControl2GUIForm *ui;

	QString	GetParamFileName(void);
	bool SaveFile(bool OnOff1, int value1
				 ,bool OnOff2, int value2);
	bool LoadFile(bool &OnOff1, int &value1
				 ,bool &OnOff2, int &value2);
};

#endif // LIGHTCCSCONTROL2GUIFORM_H
