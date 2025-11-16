#ifndef INTEGRATIONRUNNINGTRENDFORM_H
#define INTEGRATIONRUNNINGTRENDFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XServiceForLayers.h"

namespace Ui {
class IntegrationRunningTrendForm;
}
class	IntegrationRunningTrendForm;

#pragma	pack(push,1)
struct	RunningTrendData
{
	unsigned int	Ok		:1;
	unsigned int	Second	:6;
	unsigned int	Minute	:6;
	unsigned int	Hour	:5;
	unsigned int	Day		:5;
	unsigned int	Month	:4;
	unsigned int	Year	:5;
};
#pragma	pack(pop)

class	TrendWidget : public QWidget , public ServiceForLayers
{
	friend	class IntegrationRunningTrendForm;

	IntegrationRunningTrendForm	*Parent;

public:
	TrendWidget(LayersBase *base ,IntegrationRunningTrendForm *p);

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
	int	GetOrder(int n);
};

struct	ScaleYStruct
{
	int		YPos;
	int		Scale;
};

class	ScaleYWidget : public QWidget, public ServiceForLayers
{
	friend	class IntegrationRunningTrendForm;

	IntegrationRunningTrendForm	*Parent;
public:
	ScaleYWidget(LayersBase *base ,IntegrationRunningTrendForm *p);

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};



class IntegrationRunningTrendForm : public GUIFormBase
{
    Q_OBJECT
    friend	class	TrendWidget;
	friend	class	ScaleYWidget;

	struct	RunningTrendData	*RunningData;
	int							AllocRunningDataNumb;
	int							CurrentPoint;
	int							WPoint;
	DWORD						LastWTime;

	struct	ScaleYStruct	ScaleYDim[50];
	int		ScaleYDimCount;

	struct	ResultTrend
	{
		int64	InspectionID;
		bool	OK;
	};
	struct	ResultTrend		Result[10][100];

	TrendWidget		Window;
	ScaleYWidget	ScaleY;
	QColor	NGColor;
	QColor	OKColor;
public:
    explicit IntegrationRunningTrendForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationRunningTrendForm();
    
	virtual void	ReadyParam(void)	override;

	int	GetTimeScale(void);

private slots:
    void on_comboBoxSpan_currentIndexChanged(int index);
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
	void	ResizeAction();
private:
    Ui::IntegrationRunningTrendForm *ui;

	void	Release(void);
	bool	AppendData(void);

};

#endif // INTEGRATIONRUNNINGTRENDFORM_H
