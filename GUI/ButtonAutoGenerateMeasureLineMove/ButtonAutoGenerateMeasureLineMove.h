#ifndef BUTTONAUTOGENERATEMEASURELINEMOVE_H
#define BUTTONAUTOGENERATEMEASURELINEMOVE_H

#include "buttonautogeneratemeasurelinemove_global.h"
#include <QPushButton>
#include <QBuffer>
//#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMeasureLineMove.h"

class	ButtonAutoGenerateMeasureLineMove : public GUIFormBase
{
	Q_OBJECT
	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	GUIInst;

	QByteArray		AutoGenInfo;

	int	BladePickupRL;
	int	BladePickupRH;
	int	BladePickupGL;
	int	BladePickupGH;
	int	BladePickupBL;
	int	BladePickupBH;
	int	LineLib;
	int	DistanceLib;
	BladeMeasure	BladeMeasureData;



	ButtonAutoGenerateMeasureLineMove(LayersBase *Base ,QWidget *parent);
	~ButtonAutoGenerateMeasureLineMove();
	virtual void	Prepare(void)	override;
private:

public slots:
	void	SlotClicked (bool checked);
	void	SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
private slots:
	void	ResizeAction();
};

#endif // BUTTONAUTOGENERATEMEASURELINEMOVE_H
