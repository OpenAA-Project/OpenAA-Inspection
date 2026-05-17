#ifndef ZAXISVIEWERGRAPH_H
#define ZAXISVIEWERGRAPH_H

#include "ui_ZAxisViewerGraph.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

class ZAxisViewerGraph : public GUIFormBase
{
	Q_OBJECT

	mtLineGraph			LGraph;
	mtGStick			GraphPower;
	mtGStick			GraphLine;
public:
	int		ID;
	int		Page;
	QColor	PowerColor;
	QColor	LineColor;

	ZAxisViewerGraph(LayersBase *Base ,QWidget *parent = 0);
	~ZAxisViewerGraph();

	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::ZAxisViewerGraphClass ui;
};

//===========================================================================

class	GUICmdReqItemResult: public GUICmdPacketBase
{
public:
	int		AxisID;
	int		Layer;

	GUICmdReqItemResult(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemResult: public GUICmdPacketBase
{
public:
	double	*ResultTable;
	int		ResultCount;

	GUICmdAckItemResult(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdAckItemResult(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // ZAXISVIEWERGRAPH_H
