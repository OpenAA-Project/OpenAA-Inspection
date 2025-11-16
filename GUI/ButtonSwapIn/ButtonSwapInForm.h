#ifndef BUTTONSWAPINFORM_H
#define BUTTONSWAPINFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonSwapInForm;
}

class ButtonSwapInForm : public GUIFormBase
{
    Q_OBJECT

public:
	QString	Msg;
	QFont	CFont;
	QColor	ButtonColor;
	bool	MasterImage;
	
    explicit ButtonSwapInForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSwapInForm();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	
	void	CommandSwapIn(void);
private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSwapInForm *ui;
};

#endif // BUTTONSWAPINFORM_H
