#ifndef GRAPHTRENDCOLORDIFFERENCEFORM_H
#define GRAPHTRENDCOLORDIFFERENCEFORM_H

#include "XGUIFormBase.h"
#include "mtGraph.h"
#include "mtLineGraph.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XServiceForLayers.h"

namespace Ui {
class GraphTrendColorDifferenceForm;
}
class GraphTrendColorDifferenceForm;
class	ColorItem;

#pragma	pack(push,1)
struct	RunningColorHSVE
{
	int		InspectionID;
	struct{
		bool			Ok		:1;
		unsigned int	Second	:6;
		unsigned int	Minute	:6;
		unsigned int	Hour	:5;
		unsigned int	Day		:5;
		unsigned int	Month	:4;
		unsigned int	Year	:5;
	}TmInfo;
	float	HSVE[4];
};
#pragma	pack(pop)


class	TrendGraphList: public mtLineGraph , public ServiceForLayers
{
	friend class GraphTrendKidaForm;

	GraphTrendColorDifferenceForm	*Parent;
	mtGLine			GraphData;
	mtGLine			ThresholdL;
	mtGLine			ThresholdH;
public:
	EachMaster	*Machine;
	int			LibID;
	int			UniqueID;
	int			IndexInMachine;
	int			Index;
	int			StartIndex;
	QColor		ColorData;
	QColor		ColorThreshold;

	TrendGraphList(int index,GraphTrendColorDifferenceForm *p ,QWidget *Bp);
	
	void	DrawGraph(void);
private slots:
private:
};

class	ColorItem : public NPList<ColorItem>
{
	GraphTrendColorDifferenceForm	*Parent;
public:
	struct	RunningColorHSVE	*RunningColorDim;
	int		AllocatedCountOfDim;
	int		CurrentCountDim;

	int		SlaveNo;
	int		Phase;
	int		Page;
	int		ItemID;
	bool	ManualCreated;

	double	ThreHL,ThreHH;
	double	ThreSL,ThreSH;
	double	ThreVL,ThreVH;
	double	ThreE;

	ColorItem(GraphTrendColorDifferenceForm *p);
	~ColorItem(void);
};

class GraphTrendColorDifferenceForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	NPListPack<ColorItem>	ColorItems;

	int32		MaxCount;
	TrendGraphList	*TrendGraphDimH;
	TrendGraphList	*TrendGraphDimS;
	TrendGraphList	*TrendGraphDimV;
	TrendGraphList	*TrendGraphDimE;
	
	explicit GraphTrendColorDifferenceForm(LayersBase *Base ,QWidget *parent = 0);
    ~GraphTrendColorDifferenceForm();

	virtual	void	ReadyParam(void)	override;
	virtual void	BuildForShow(void)	override;

	ColorItem		*GetCurrentItem(void);
	int				GetGraphXSpan(void);

private slots:
    void on_listWidgetItemList_pressed(const QModelIndex &index);
    void on_pushButtonLogOut_clicked();
    void on_comboBoxXScale_currentIndexChanged(int index);
	void	ResizeAction();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
private:
    Ui::GraphTrendColorDifferenceForm *ui;
};


class	IntegrationCmdReqColorItem: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqColorItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
private:

};

class	IntegrationCmdAckColorItem: public IntegrationCmdPacketBase
{
public:
	struct{
		int		Phase;
		int		Page;
		int		ItemID;
		bool	ManualCreated;

		double	ThreHL,ThreHH;
		double	ThreSL,ThreSH;
		double	ThreVL,ThreVH;
		double	ThreE;
	}ItemData[20];
	int	ItemCount;

	IntegrationCmdAckColorItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	
private:

};
#endif // GRAPHTRENDCOLORDIFFERENCEFORM_H
