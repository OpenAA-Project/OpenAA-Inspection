#ifndef BUTTONSETOFFSETFORM_H
#define BUTTONSETOFFSETFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonSetOffsetForm;
}

class	SignalOperandBit;
class ButtonSetOffsetForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandBit	*iButton;
public:
    explicit ButtonSetOffsetForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSetOffsetForm();
    
	virtual void	Prepare(void)	override;
private slots:
    void on_pushButtonSetOffset_clicked();
	void	ResizeAction();
	void	OperandChanged();
private:
    Ui::ButtonSetOffsetForm *ui;
};

#endif // BUTTONSETOFFSETFORM_H
