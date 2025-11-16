#ifndef BUTTONSHOWSNAPIMAGEFILENAME_H
#define BUTTONSHOWSNAPIMAGEFILENAME_H

#include "buttonshowsnapimagefilename_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"
#include <QLineEdit>
#include <QColor>
#include <QFont>

class	ButtonShowSnapImageFileName : public GUIFormBase
{
	Q_OBJECT

	QLineEdit	Label;
public:
	QColor	CharColor;
	QFont	CFont;

	ButtonShowSnapImageFileName(LayersBase *Base ,QWidget *parent);
	~ButtonShowSnapImageFileName(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)override;

private slots:

	void	ResizeAction();
};


class	CmdShowSnapImageFileName : public GUIDirectMessage
{
public:
	QString	FileName;

	CmdShowSnapImageFileName(LayersBase *base):GUIDirectMessage(base){}
	CmdShowSnapImageFileName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif // BUTTONSHOWSNAPIMAGEFILENAME_H
