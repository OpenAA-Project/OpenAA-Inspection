#ifndef BUTTONSAVEMATRIXCELL_H
#define BUTTONSAVEMATRIXCELL_H

#include "buttonsavematrixcell_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonSaveMatrixCell : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonSaveMatrixCell(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	SaveMatrixCell(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqAlgorithmData : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QString	AlgorithmRoot;
	QString	AlgorithmName;


	GUICmdReqAlgorithmData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmData : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QBuffer	Data;

	GUICmdSendAlgorithmData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONSAVEMATRIXCELL_H
