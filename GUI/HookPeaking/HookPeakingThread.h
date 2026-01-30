/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
