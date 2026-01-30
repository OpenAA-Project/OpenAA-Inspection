/*
 * Copyright (C) 2022
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

#ifndef RESULTSAVETARGETIMAGE_H
#define RESULTSAVETARGETIMAGE_H

#include "resultsavetargetimage_global.h"
#include <QThread>
#include <QString>
#include <QMutex>
#include "XResult.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XMainSchemeMemory.h"



class   ImageBuffersListWithFlag : public NPList<ImageBuffersListWithFlag>
{
public:
	bool	ShouldWrite;
	int		Number;
	QString	FileName;
	ImageBufferListContainer	**PageImage;
	int							PhaseNumb;
	int							PageNumb;

	ImageBuffersListWithFlag(int PhaseNumb ,int PageNumb ,int LayerNumb ,int DotPerLine ,int MaxLines);
	~ImageBuffersListWithFlag(void);

	ImageBuffersListWithFlag	&operator=(ImageBuffersListWithFlag &src);

	int	GetDotPerLine(void)	;
	int	GetMaxLines(void)	;
	int	GetLayerNumb(void)	;
	int	GetPageNumb(void)	;
	int	GetPhaseNumb(void)	;

	ImageBuffer	*GetBuffer(int phase,int page,int layer);
	bool	WriteOut(void);
	bool	WriteOut(int UseLayer);
};


class	ResultSaveTargetImage : public QThread ,public ResultDLLBaseRoot
{
	QStringList		PathList;
	int32			AllocatedCount;
	NPListPack<ImageBuffersListWithFlag>	ImageList;

public:
	QString			SavedFolder;
	bool			OnlyNG;
	bool			UseGeneralStockerToGetPath;
	QStringList		SaveFolderList;
	int32			DiskSpaceToCheck;
	bool			Terminated;
	int32			UseLayer;	//-1::Save all layers
	QMutex			MutexImageList;

	ResultSaveTargetImage(LayersBase *Base);
	virtual ~ResultSaveTargetImage(void);	
	
	virtual	QString	GetDataText(void)			override{	return QString("Result Save TargetImage");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ResultSaveTargetImage.dat");	}

	virtual	bool	OutputResultDirectly(int mode,ResultInspection &Res,GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID,ResultInspection *Res) override;
protected:
	virtual	void	run()	override;

	ImageBuffersListWithFlag	*GetEmptyBuffer(void);
};
#endif // RESULTSAVETARGETIMAGE_H