#ifndef BUTTONLOADPWAFILE_H
#define BUTTONLOADPWAFILE_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonLoadPWAFile : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonLoadPWAFile(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	LoadPWA(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONLOADPWAFILE_H
