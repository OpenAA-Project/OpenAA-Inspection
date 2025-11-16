#ifndef BUTTONSAVERESULTWITHALL_H
#define BUTTONSAVERESULTWITHALL_H

#include "buttonsaveresultwithall_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonSaveResultWithAll : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonSaveResultWithAll(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	SaveRWA(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
#endif // BUTTONSAVERESULTWITHALL_H
