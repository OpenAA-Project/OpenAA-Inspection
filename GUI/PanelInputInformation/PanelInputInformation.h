#ifndef PANELINPUTINFORMATION_H
#define PANELINPUTINFORMATION_H

#include "panelinputinformation_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QColor>
#include <QFont>

class PanelInputInformation: public GUIFormBase
{
	Q_OBJECT

	struct	InformationItem
	{
		QLabel		ItemLabel;
		QLineEdit	Edit;
	};
	struct	InformationItem	*ItemControls;
	int		CountOfItemControls;
public:
	QFont	InputFont;
	QFont	TitleFont;
	QColor	TitleColor;
	QColor	InputColor;
	int		ItemHeight;
	int		TitleWidth;
	QStringList	ItemTitles;

	PanelInputInformation(LayersBase *Base ,QWidget *parent);
	~PanelInputInformation(void);

	virtual void	Prepare(void)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	void		ReflectToWindow(QStringList &Str);
	QStringList	GetListFromWindow(void);

private slots:
	void	ResizeAction();
};

class CmdReqInputInformationPacket : public GUIDirectMessage
{
public:
	QStringList	Titles;
	QStringList	Datas;

	CmdReqInputInformationPacket(LayersBase *base):GUIDirectMessage(base){}
};
#endif // PANELINPUTINFORMATION_H
