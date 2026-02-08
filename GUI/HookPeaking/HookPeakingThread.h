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
#include <QThread>
#include <QMutex>
#include <QImage>
#include <QPainter>
#include "XServiceForLayers.h"


class HookPeakingForm;
class GpuSharpnessContext;
class ImageBuffer;
class ImageBufferListContainer;
class GpuSharpnessContextBase;

const	int	CountOfAverage = 8;

class FlatPeakingImageBuff
{
public:
	BYTE	*InData;
	BYTE	*OutData;
	int		Width;	
	int		Height;
	int		Page;

	FlatPeakingImageBuff();
	~FlatPeakingImageBuff();

	void	Allocate(int width,int height,int page);
};


class	ThreadPeaking : public QThread,public ServiceForLayers
{
    Q_OBJECT
	friend	class HookPeakingForm;

	ImageBufferListContainer	*AverageBuff;
	int		PageCount;
	int		APointR;
	int		APointW;

	FlatPeakingImageBuff *FlatBuff;
	QMutex				PeakMutex;
	int					AllocatedCount;
	HookPeakingForm		*Parent;
	int					Isolation;
	bool				StartMode;
	float				SensitivityVal;
	int					Radius;			
	bool				isGLES;
	GpuSharpnessContextBase		*GpuContext;
public:
	volatile	bool	Terminated;

	ThreadPeaking(LayersBase *base ,int Isolation ,HookPeakingForm *parent);
	~ThreadPeaking(void);

	virtual	void	run();

	void	SetPeakingParam(float sensitivityVal,int radius);
	void	SetStartMode(bool b)	{ StartMode = b; }
	void	SetTmage(int localPage);
	void	Realloc(void);

signals:
	void	SignalShowPeaking();
private:
	void	MakePeakData(int localPage);
	int		GetPage(void);
	void	SetAverage(ImageBuffer *Dst,ImagePointerContainer &Src);

	int		calculateSharpness(ImageBuffer &Image, int X ,int Y ,int width, int height, double sensitivity = 500.0);

};
