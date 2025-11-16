#ifndef BUTTONCLEARMASTERINFO_H
#define BUTTONCLEARMASTERINFO_H

#include "buttonclearmasterinfo_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonClearMasterInfo : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIcon;
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	int32	WaitingMilisec;

	ButtonClearMasterInfo(LayersBase *Base ,QWidget *parent);
	~ButtonClearMasterInfo(void);
	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);
	void SlotClickedPhase (bool checked);
private slots:
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqButtonClearMasterInfo : public GUICmdPacketBase
{
public:
	GUICmdReqButtonClearMasterInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqButtonClearMasterInfoPhase : public GUICmdPacketBase
{
public:
	GUICmdReqButtonClearMasterInfoPhase(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCLEARMASTERINFO_H
