#ifndef CONTROLHAYASHITOKEIGUIFORM_H
#define CONTROLHAYASHITOKEIGUIFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ControlHayashiTokeiGUIForm;
}
class	LightDLLBaseClass;

class ControlHayashiTokeiGUIForm : public GUIFormBase
{
    Q_OBJECT
     LightDLLBaseClass	*LightPointer;
public:
	int32		Number;

	explicit ControlHayashiTokeiGUIForm(LayersBase *base,QWidget *parent = 0);
    ~ControlHayashiTokeiGUIForm();

	virtual void	Prepare(void)		override;
    virtual	void	BuildForShow(void)	override;

private slots:
    void on_dialValue_valueChanged(int value);
    void on_spinBoxValue_valueChanged(int arg1);
    void on_toolButtonON_clicked();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);

private:
    Ui::ControlHayashiTokeiGUIForm *ui;

	QString	GetParamFileName(void);
	bool SaveFile(bool OnOff, int value);
	bool LoadFile(bool &OnOff, int &value);
};

#endif // CONTROLHAYASHITOKEIGUIFORM_H
