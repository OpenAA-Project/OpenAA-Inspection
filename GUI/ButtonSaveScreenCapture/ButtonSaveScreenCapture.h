#pragma once

#include "buttonsavescreencapture_global.h"
#include <QPushButton>
//#include "XGUIDLL.h"
#include "XGUIFormBase.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class ButtonSaveScreenCapture: public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIcon;

    ButtonSaveScreenCapture(LayersBase *Base ,QWidget *parent);
	~ButtonSaveScreenCapture(void);

	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;

	bool	SaveScreen(const QString &FileName);
public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};
