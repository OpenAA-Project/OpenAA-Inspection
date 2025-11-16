#ifndef BUTTONOUTLINEOFFSETWINDOW_H
#define BUTTONOUTLINEOFFSETWINDOW_H

#include "buttonoutlineoffsetwindow_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	OutlineOffsetForm;

class	ButtonOutlineOffsetWindow: public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	OutlineOffsetForm	*Window;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonOutlineOffsetWindow(LayersBase *Base ,QWidget *parent);
	~ButtonOutlineOffsetWindow(void);
	
	virtual void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

#endif // BUTTONOUTLINEOFFSETWINDOW_H
