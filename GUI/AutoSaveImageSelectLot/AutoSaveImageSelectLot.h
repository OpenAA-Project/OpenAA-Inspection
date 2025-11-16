#ifndef AUTOSAVEIMAGESELECTLOT_H
#define AUTOSAVEIMAGESELECTLOT_H

#include "autosaveimageselectlot_global.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	AutoSaveImageSelectLot : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	AutoSaveImageSelectLot(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // AUTOSAVEIMAGESELECTLOT_H
