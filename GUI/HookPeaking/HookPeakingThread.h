#pragma once

#include "NListComp.h"
#include "fftw3.h"
#include <QThread>
#include <QMutex>
#include <QImage>
#include <QPainter>
#include "XServiceForLayers.h"
#include "XMainSchemeMemory.h"

class HookPeakingForm;

class	ThreadPeaking : public QThread,public ServiceForLayers
{
    Q_OBJECT
	friend	class HookPeakingForm;

	int	DotPerLine	;
	int	MaxLines	;
	int	ynumb;
	int	xnumb;
	fftw_complex *in[5000];
	fftw_complex *out[5000];
	fftw_plan	p[5000];
	ImageBuffer			**PeakBuff;
	QMutex				PeakMutex;
	int					AllocatedCount;
	HookPeakingForm		*Parent;
	int	Isolation;
	int	Turn;
public:
	int					*CRadius;
	volatile	bool	Terminated;

	ThreadPeaking(LayersBase *base ,HookPeakingForm *parent);
	~ThreadPeaking(void);

	virtual	void	run();

signals:
	void	SignalShowPeaking();
private:
	void	Realloc(void);
	void	MakePeakData(int localPage);
	int		GetPage(void);
	
	int		MakePeakData(int SIZEX,int SIZEY,fftw_plan p,fftw_complex *in,fftw_complex *out
						,ImageBuffer &Src, ImageBuffer &Image,int x1,int y1,int x2,int y2);
	void	CopyToParent(int localPage);
};

