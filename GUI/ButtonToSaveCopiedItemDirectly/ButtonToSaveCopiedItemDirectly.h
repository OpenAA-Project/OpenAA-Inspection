#ifndef BUTTONTOSAVECOPIEDITEMDIRECTLY_H
#define BUTTONTOSAVECOPIEDITEMDIRECTLY_H

#include "buttontosavecopieditemdirectly_global.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonToSaveCopiedItemDirectly : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString ImagePanelName;
	QString FileName;

	ButtonToSaveCopiedItemDirectly(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	SaveCopiedItem(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONTOSAVECOPIEDITEMDIRECTLY_H
