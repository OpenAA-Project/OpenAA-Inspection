#ifndef COPYITEMSBETWEENPHASE_H
#define COPYITEMSBETWEENPHASE_H

#include "copyitemsbetweenphase_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QString>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class	CopyItemsBetweenPhase : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	int32	SourcePhase;
	int32	DestinationPhase;
	bool	ModeCopyMasterImage;
	bool	ModeCopyTargetImage;
	bool	ModeCopyAlgorithm;

	CopyItemsBetweenPhase(LayersBase *Base ,QWidget *parent);
	~CopyItemsBetweenPhase(void);
	
	virtual void	Prepare(void)	override;

	bool ExecuteCopy(QIODevice &F);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdCopyData : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	int32	SourcePhase;
	int32	DestinationPhase;
	bool	ModeCopyMasterImage;
	bool	ModeCopyTargetImage;
	bool	ModeCopyAlgorithm;

	GUICmdCopyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // COPYITEMSBETWEENPHASE_H
