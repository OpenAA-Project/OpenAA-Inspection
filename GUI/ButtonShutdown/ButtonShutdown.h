#ifndef BUTTONSHUTDOWN_H
#define BUTTONSHUTDOWN_H

#include "buttonshutdown_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonShutdown : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString		Msg;
	bool		RebootMode;

	ButtonShutdown(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdShutDown: public GUICmdPacketBase
{
public:
	bool		RebootMode;

	GUICmdShutDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONSHUTDOWN_H
