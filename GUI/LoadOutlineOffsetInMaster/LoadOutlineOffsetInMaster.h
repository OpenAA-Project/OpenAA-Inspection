#ifndef LOADOUTLINEOFFSETINMASTER_H
#define LOADOUTLINEOFFSETINMASTER_H

#include "loadoutlineoffsetinmaster_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class	LoadOutlineOffsetInMaster : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	LoadOutlineOffsetInMaster(LayersBase *Base ,QWidget *parent);
	~LoadOutlineOffsetInMaster(void);

	virtual void	Prepare(void)		override;
	void			BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

#endif // LOADOUTLINEOFFSETINMASTER_H
