#ifndef BUTTONMODEAUTOINCSCANNUMBER_H
#define BUTTONMODEAUTOINCSCANNUMBER_H

#include "buttonmodeautoincscannumber_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>
#include <QIODevice>

class	ButtonModeAutoIncScanNumber : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonModeAutoIncScanNumber(LayersBase *Base ,QWidget *parent);
	~ButtonModeAutoIncScanNumber(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//-------------------------------------------------------
class	GUICmdSetModeAutoIncScanNumber: public GUICmdPacketBase
{
public:
	bool	ModeAutoIncScanNumber;

	GUICmdSetModeAutoIncScanNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};


#endif // BUTTONMODEAUTOINCSCANNUMBER_H
