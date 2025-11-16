#ifndef INTEGRATIONCLEARNGTHUMBNAIL_H
#define INTEGRATIONCLEARNGTHUMBNAIL_H

#include "integrationclearngthumbnail_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"

class	IntegrationClearNGThumbnail: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;

	IntegrationClearNGThumbnail(LayersBase *Base ,QWidget *parent);

	virtual	void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

#endif // INTEGRATIONCLEARNGTHUMBNAIL_H
