#pragma once

#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"
//#include "fftw3.h"

class	DisplayRealtimeGraph;

class	DisplayRealtimeGraphBrightness: public ServiceForLayers
{
	int	AllocLayerNumb;
	int	AllocXLen;
	volatile	int		CamNo;
	volatile	bool	Calclating;
	DisplayRealtimeGraph *Parent;
public:
	double	**LineData;

	mtLineGraph	GraphBase;
	mtGLine		*GraphLine;
	int			Page;

	DisplayRealtimeGraphBrightness(LayersBase *Base ,DisplayRealtimeGraph *p,QWidget *parent=nullptr);
	~DisplayRealtimeGraphBrightness(void);

	void	SetGeometry(int x, int y ,int w ,int h);
	void	Repaint(void);
};

class	DisplayRealtimeGraphFocus: public ServiceForLayers
{
	int	AllocXLen;
	int	AllocLayerNumb;
	volatile	int		CamNo;
	volatile	bool	Calclating;
	DisplayRealtimeGraph *Parent;
public:
	double	**LineData;

	mtLineGraph	GraphBase;
	mtGLine		*GraphLine;

	DisplayRealtimeGraphFocus(LayersBase *Base ,DisplayRealtimeGraph *p,QWidget *parent=nullptr);
	~DisplayRealtimeGraphFocus(void);

	void	SetGeometry(int x, int y ,int w ,int h);
	void	Repaint(void);

private:
	double	MakeFFTValue(double Brightness[] ,int XPos,int XLen);
};

