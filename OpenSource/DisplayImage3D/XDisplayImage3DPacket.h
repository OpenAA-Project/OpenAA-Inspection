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

class	GUICmdSendBmp3D : public GUICmdPacketBase	//画像表示用ビットマップ送信コマンド
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

