#ifndef BUTTONSELECTMASTER_H
#define BUTTONSELECTMASTER_H

#include "buttonselectmaster_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonSelectMaster : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSelectMaster(LayersBase *Base ,QWidget *parent);
	~ButtonSelectMaster(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


#endif // BUTTONSELECTMASTER_H
