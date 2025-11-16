#ifndef BUTTONIMAGETRANSFORMER_H
#define BUTTONIMAGETRANSFORMER_H

#include "buttonimagetransformer_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include <QPushButton>

class	ButtonImageTransformer : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;


	ButtonImageTransformer(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

public slots:
	void	SlotClicked ();

private slots:
	void	ResizeAction();
};

class	GUICmdUpsideDown : public GUICmdPacketBase
{
public:
	bool		MasterImage;
	bool		TargetImage;
	GUICmdUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	;
	virtual	bool	Save(QIODevice *f)	;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLeftsideRight : public GUICmdPacketBase
{
public:
	bool		MasterImage;
	bool		TargetImage;
	GUICmdLeftsideRight(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	;
	virtual	bool	Save(QIODevice *f)	;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONIMAGETRANSFORMER_H
