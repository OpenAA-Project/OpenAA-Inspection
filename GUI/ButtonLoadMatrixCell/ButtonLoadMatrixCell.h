#ifndef BUTTONLOADMATRIXCELL_H
#define BUTTONLOADMATRIXCELL_H

#include "buttonloadmatrixcell_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonLoadMatrixCell : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonLoadMatrixCell(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	LoadMatrixCell(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdWriteMatrixData : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QBuffer	Data;

	GUICmdWriteMatrixData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	ExecuteLoadMatrix : public GUIDirectMessage
{
public:
	QString	FileName;

	ExecuteLoadMatrix(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONLOADMATRIXCELL_H
