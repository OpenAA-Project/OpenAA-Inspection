#ifndef RESETCAMERASEQ_H
#define RESETCAMERASEQ_H

#include "resetcameraseq_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;

class	ResetCameraSeq : public GUIFormBase
{
	Q_OBJECT

public:
	int32	SystemRegisterNo;

	ResetCameraSeq(LayersBase *Base ,QWidget *parent);
	~ResetCameraSeq(void);
	
	virtual void	Prepare(void)	override;

private:
	SignalOperandInt	*ioMode;
private slots:
	void	OperandChanged();
};


//--------------------------------------------------------------------------

class	GUICmdResetCameraSeq : public GUICmdPacketBase
{
public:
	int	Cmd;	

	GUICmdResetCameraSeq(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // RESETCAMERASEQ_H
