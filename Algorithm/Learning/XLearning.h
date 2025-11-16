/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Learning\XLearning.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XLearning_H
#define XLearning_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XLearningRule.h"

class	LearningRuleItem;
class	LearningRuleBase;

class	LearningFileList : public NPList<LearningFileList>
{
public:
	QString		FileName;
	int32		GlobalPage;
	int32		LotAutoCount;
	int32		ID;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LearningFileList	&operator=(LearningFileList &src);
};

class	LearningFileListContainer : public NPListPack<LearningFileList>
{
public:
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LearningFileListContainer	&operator=(LearningFileListContainer &src);
	LearningFileListContainer	&operator+=(LearningFileListContainer &src);
	void	SortByName(void);
	void	SortByID(void);
};

class	LearningRuleThreshold : public AlgorithmThreshold
{
public:
	bool		Ok;			//true:ãïïÒîrèú		false:ÇmÇfî≠ïÒ
    int32		NGLevel;	//0:Most important NG 1,2,3...lighter

	LearningRuleThreshold(LearningRuleItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	LearningRuleItem : public AlgorithmItemPI
{
public:

	LearningRuleItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new LearningRuleItem();	}
	const	LearningRuleThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const LearningRuleThreshold *)GetThresholdBaseReadable(base);	}
	LearningRuleThreshold			*GetThresholdW(LayersBase *base=NULL){	return (LearningRuleThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new LearningRuleThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	double	GetCalcFromResult(ResultInspection &Res ,int Page);
};


class   LearningRuleInPage : public AlgorithmInPagePI ,public NPList<LearningRuleInPage>,public LearningPlanBase
{
	double	ResultValueInPage;

public:
	QString		FileName;

	LearningRuleInPage(AlgorithmBase *parent);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			LearningRuleItem	*a=new LearningRuleItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	MakeFileLists(LearningFileListContainer &Dest
							,int MasterCode, int LotAutoCount);
	bool	LoadLearnFile(void);

	virtual	bool    Save(QIODevice *f)	override;
    virtual	bool    Load(QIODevice *f)	override;

	void	TryCalc(void);
	double	CalcResult(void);

protected:
	virtual	double	GetResult(ResultInspection &R)	override;

};

class	LearningRuleInPagePointer : public NPList<LearningRuleInPagePointer>
{
public:
	AlgorithmInPageRoot	*Pointer;
};



class	LeaningSaveThread : public QThread, public ServiceForLayers
{
	LearningRuleBase	*BaseParent;
	QString	FolderName;	//êeÉtÉHÉãÉ_ÇÃâ∫Ç…çÏÇÈÉtÉHÉãÉ_ñº('/'Ç≈ãÊêÿÇÁÇÍÇÈÇ±Ç∆Ç‡Ç†ÇÈ)
	int64	InspectionID;
	int32	MasterCode;
	int32	LotAutoCount;
	int32	LocalPage;
	int32	XLen,YLen;
	int32	GlobalPage;

	ImageBuffer	**SavedImage;
	int			AllocatedLayerNumb;

	bool	NowOnWriting;

public:

	LeaningSaveThread(LearningRuleBase *parent ,int localPage);
	~LeaningSaveThread(void);

	void	Allocate(void);
	void	Release(void);

	void	ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed);

	virtual void run ()	override;

	void	CopyFromTarget(void);
	void	CopyToTarget(void);

	bool	Save(void);
	bool	Load(QString FileName);
private:
	QString	CreateFileName(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

public slots:
	void SlotFinished();
};


class	LearningRuleBase : public AlgorithmBase
{
public:
	QColor	ColorRuleNG;
	QColor	ColorRuleOK;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorRule;
	QColor	NegColorSelected;
	QString	ImageFolder;
	bool	AllocBufferPerDemand;
	bool	SaveMode;
	bool	TryCalcMode;
	bool	LoadBmpMode;
	bool	LoadJpgMode;

	LeaningSaveThread	**ThreadSaver;
	int					ThreadSaverCount;

	int32	AllocatedPageCount;
	NPListPack<LearningRuleInPage>			*LearningRuleInPageStocker;
	LearningRuleInPagePointer				*Saved;

	LearningRuleBase(LayersBase *Base);
	~LearningRuleBase(void);

	virtual	void	Initial(LayersBase *Base)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultBaseForAlgorithmRoot *Res)	override;

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new LearningRuleInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)		override{	return QString("LearningRule");				}
	QString	GetDefaultFileName(void)		override{	return QString("ConfigLearningRule.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;
};
//==================================================================================
//==================================================================================

class	LearningRuleDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	ColorRuleNG;
	QColor	ColorRuleOK;

	LearningRuleDrawAttr(void){}
	LearningRuleDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	LearningRuleDrawAttr(QColor ncolNG ,QColor ncolOK ,int ntranparentLevel
						,QColor scol ,int stranparentLevel
						,QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncolNG,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		ColorRuleOK	=ncolOK;	
		ColorRuleNG	=ncolNG;	
		ColorRuleOK.setAlpha(ntranparentLevel);
		ColorRuleNG.setAlpha(ntranparentLevel);
	}
};

class	LearningAddFilePacket : public GUIDirectMessage
{
public:
	QString		FileName;
	int			Index;

	LearningAddFilePacket(LayersBase *base):GUIDirectMessage(base){}
	LearningAddFilePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LearningDelFilePacket : public GUIDirectMessage
{
public:
	int32		IndexNumber;
	int32		Page;

	LearningDelFilePacket(LayersBase *base):GUIDirectMessage(base){}
	LearningDelFilePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	LearningReqSaveMode : public GUIDirectMessage
{
public:
	bool	Mode;

	LearningReqSaveMode(LayersBase *base):GUIDirectMessage(base){}
	LearningReqSaveMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LearningSetSaveMode : public GUIDirectMessage
{
public:
	bool	Mode;

	LearningSetSaveMode(LayersBase *base):GUIDirectMessage(base){}
	LearningSetSaveMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class LearningReqStoredFileList : public GUIDirectMessage
{
public:	
	int MasterCode;
	int LotAutoCount;
	LearningFileListContainer	*List;

	LearningReqStoredFileList(LayersBase *base):GUIDirectMessage(base){}
	LearningReqStoredFileList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class LearningReqPickedFileList : public GUIDirectMessage
{
public:	
	int	LocalPage;
	LearningFileListContainer	*List;

	LearningReqPickedFileList(LayersBase *base):GUIDirectMessage(base){}
	LearningReqPickedFileList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	LearningChangeSelectedNumber : public GUIDirectMessage
{
public:
	int	SelectedNumber;
	int	Page;

	LearningChangeSelectedNumber(LayersBase *base):GUIDirectMessage(base){}
	LearningChangeSelectedNumber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AddLearningAreaWithAttr : public GUIDirectMessage
{
public:
	bool		Ok;			//true:ãïïÒîrèú		false:ÇmÇfî≠ïÒ
    int32		NGLevel;	//0:Most important NG 1,2,3...lighter
	FlexArea	Area;

	AddLearningAreaWithAttr(LayersBase *base):GUIDirectMessage(base){}
	AddLearningAreaWithAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LearningAreaList : public NPList<LearningAreaList>
{
public:
	int32	GlobalPage;
	int32	ItemID;
	bool	Ok;
	int32	NGLevel;
	int32	X1,Y1,X2,Y2;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LearningAreaList	&operator=(LearningAreaList &src);
};

class	LearningAreaListContainer : public NPListPack<LearningAreaList>
{
public:
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LearningAreaListContainer &operator=(LearningAreaListContainer &src);
	LearningAreaListContainer &operator+=(LearningAreaListContainer &src);
};

class	AlgoLearningAreaListContainer: public GUIDirectMessage
{
public:
	LearningAreaListContainer	*List;

	AlgoLearningAreaListContainer(LayersBase *base):GUIDirectMessage(base){}
	AlgoLearningAreaListContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqStartLearning : public GUIDirectMessage
{
public:
	int MasterCode;
	int LotAutoCount;

	CmdReqStartLearning(LayersBase *base):GUIDirectMessage(base){}
	CmdReqStartLearning(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LearningReqStartOne : public GUIDirectMessage
{
public:
	double	ResultValueInPage;

	LearningReqStartOne(LayersBase *base):GUIDirectMessage(base){}
	LearningReqStartOne(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LearningExeTop: public GUIDirectMessage
{
public:
	LearningExeTop(LayersBase *base):GUIDirectMessage(base){}
	LearningExeTop(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	LearningExeLoopTop: public GUIDirectMessage
{
public:
	LearningExeLoopTop(LayersBase *base):GUIDirectMessage(base){}
	LearningExeLoopTop(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LearningExeLoopNext: public GUIDirectMessage
{
public:
	double	ResultValueInPage;

	LearningExeLoopNext(LayersBase *base):GUIDirectMessage(base){}
	LearningExeLoopNext(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif