#ifndef KOREAST8CHGUIFORM_H
#define KOREAST8CHGUIFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class KoreaST8ChGUIForm;
}
class	LightDLLBaseClass;

class KoreaST8ChGUIForm : public GUIFormBase
{
    Q_OBJECT

	LightDLLBaseClass	*LightPointer;

public:
	int					Number;
	int					StepValue;
	
	explicit KoreaST8ChGUIForm(LayersBase *base,QWidget *parent = 0);
    ~KoreaST8ChGUIForm();

	virtual void	Prepare(void)		override;
    virtual	void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

protected:
	virtual	bool eventFilter(QObject *target, QEvent *event)	override;
	virtual	void	keyPressEvent(QKeyEvent *event)	override;

private slots:
    void on_dialLightValue_valueChanged(int value);
    void on_spinBoxLightValue_valueChanged(int arg1);
    void on_pushButtonSet_clicked();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
    void on_toolButtonON_clicked();

private:
    Ui::KoreaST8ChGUIForm *ui;

	QString	GetParamFileName(void);
	bool SaveFile(bool OnOff, int value);
	bool LoadFile(bool &OnOff, int &value);
};

#endif // KOREAST8CHGUIFORM_H
