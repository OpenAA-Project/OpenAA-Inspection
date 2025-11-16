#pragma once

#include "fftw3.h"
#include <QThread>
#include "XServiceForLayers.h"

class RealtimeGraphMeasure1Form;

class	ThreadFocus : public ServiceForLayers
{
	int	AllocXLen;
	int	AllocYLen;
	int	AllocLayerNumb;
	fftw_complex *inx;
	fftw_complex *iny;
	fftw_complex *outx;
	fftw_complex *outy;
	fftw_plan	PlanX;
	fftw_plan	PlanY;

	RealtimeGraphMeasure1Form	*Parent;
	int		CamNo;
	int		Page;

public:
	int	XLen;
	int	YLen;
	int	XPos;
	int	YPos;

	volatile	bool	Terminated;
	volatile	bool	CalcDone;
	double	*Brightness;
	double	*FocusValue;


	ThreadFocus(LayersBase *base ,RealtimeGraphMeasure1Form *parent);
	~ThreadFocus(void);

	void	Calculate(void);


private:
	void	Realloc(void);
	void	CalcWidth(ImagePointerContainer &Images);
	void	CalcHeight(ImagePointerContainer &Images);

};
