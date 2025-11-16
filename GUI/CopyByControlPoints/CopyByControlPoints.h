#pragma once

#include "copybycontrolpoints_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>
#include "XFromToInfo.h"

class	CopyByControlPoints : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	Mastered;
	QByteArray	FromToArray;
	QByteArray	AlgorithmRootName;
	FromToClass	FromToInfo;

	CopyByControlPoints(LayersBase *Base ,QWidget *parent = 0);
	~CopyByControlPoints();

	virtual void	Prepare(void)	override;

	void	CopyTopShadowLevel(void);
	void	CopyShadowLevelFromTop(void);

private:
	virtual	bool	ShowQByteArrayDialog(const QString &VariableName)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};



//==================================================================

class	GUICmdReqAlgoDataWithControlPoints: public GUICmdPacketBase
{
public:
	int	Phase;
	int	ShadowLevel;
	int	ShadowNumber;
	RootNameListContainer	AlgorithmList;

	GUICmdReqAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlgoDataWithControlPoints: public GUICmdPacketBase
{
public:
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	GUICmdAckAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdSetAlgoDataWithControlPoints: public GUICmdPacketBase
{
public:
	int	Phase;
	int	ShadowLevel;
	int	ShadowNumber;
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	GUICmdSetAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};