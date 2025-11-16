#ifndef DISPLAYSCANPHASENUMBER_H
#define DISPLAYSCANPHASENUMBER_H

#include "displayscanphasenumber_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	DisplayScanPhaseNumber : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	**Buttons;
	int					AllocatedCount;

public:
	QStringList		ScanPhaseNames;
	QFont			CFont;
	QColor			CharColor;
	QColor			ActiveColor;
	QColor			NormalColor;
	QString			OrientationStr;		//Horizontal,Vertical

	DisplayScanPhaseNumber(LayersBase *Base ,QWidget *parent);
	~DisplayScanPhaseNumber(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	bool OnIdle(void)	override;

public slots:
	void	SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

#endif // DISPLAYSCANPHASENUMBER_H
