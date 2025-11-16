#ifndef PUSHTOSAVEPIX_H
#define PUSHTOSAVEPIX_H

#include "pushtosavepix_global.h"
#include <QToolButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class PushToSavePix : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	PathToSave;

public:
	PushToSavePix(LayersBase *Base ,QWidget *parent);
	~PushToSavePix();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
#endif // PUSHTOSAVEPIX_H
