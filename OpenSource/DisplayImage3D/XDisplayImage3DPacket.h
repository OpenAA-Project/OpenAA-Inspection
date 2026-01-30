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

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtFrameDraw.h"
#include "XAlgorithmLibrary.h"
#include "XAlgorithmCommon.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "X3DCommon.h"

class	AlgorithmLibraryListContainer;
class	DisplayImage3DAlgo;

class	GUICmdReqBmp3D : public GUICmdPacketBase
{
public:
	Canvas3D	ReqData3D;
	struct{
		bool		RedCircleMode;
		int32		ShowFixedPhase;	//-1: Any phase (current phase)
	}Data;
	DisplayImage3DAlgo	*Form;
	QString		AlgoRoot;
	QString		AlgoName;
	QString		InstName;
	QByteArray	DAttrArray;

	GUICmdReqBmp3D(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendBmp3D : public GUICmdPacketBase	//�摜�\���p�r�b�g�}�b�v���M�R�}���h
{
public:
	QImage		*IData;
	QImage		*NGData;
	QPainter	*PntFromIData;
	QPainter	*PntFromNGData;

	GUICmdSendBmp3D(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdSendBmp3D(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	

	bool	MakeImage(AlgorithmDrawAttr *ModePoint
					 ,const QString &AlgoRoot,const QString &AlgoName
					 ,const Canvas3D &CInfo
					 ,int localPage
					 ,LayersBase &LocalLBase
					 ,bool RedCircleMode
					 ,int32 ShowFixedPhase);
};
