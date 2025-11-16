#ifndef BUTTONSWAPOUTFORM_H
#define BUTTONSWAPOUTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonSwapOutForm;
}

class ButtonSwapOutForm : public GUIFormBase
{
    Q_OBJECT

public:
	QString	Msg;
	QFont	CFont;
	QColor	ButtonColor;
	bool	MasterImage;
	
   	explicit ButtonSwapOutForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSwapOutForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	
	void	CommandSwapOut(void);
private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSwapOutForm *ui;
};

#endif // BUTTONSWAPOUTFORM_H
