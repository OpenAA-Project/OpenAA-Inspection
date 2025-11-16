#ifndef BUTTONLIGHTSHORTCUTFORM_H
#define BUTTONLIGHTSHORTCUTFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtPushButton.h"

namespace Ui {
class ButtonLightShortCutForm;
}

class ButtonLightShortCutForm : public GUIFormBase
{
    Q_OBJECT

	mtPushButton		Button;
	DWORD	LastKeyTime;
public:
	QString	Msg;
	QFont	CFont;
	QColor	ButtonColor;
	int32	IDNumber;
	int32	ShortcutKey;

	
	explicit ButtonLightShortCutForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonLightShortCutForm();
    
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
	void	SlotRightClick();
private:
    Ui::ButtonLightShortCutForm *ui;

	QString	GetFileName(void);
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
};

#endif // BUTTONLIGHTSHORTCUTFORM_H
