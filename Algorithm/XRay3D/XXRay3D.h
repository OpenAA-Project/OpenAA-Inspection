/*
 * Copyright (C) 2023
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

#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"

#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithmList.h"
#include "XDataComponent.h"

#define	XRay3DVersion	1

class   XRay3DItem;
class	XRay3DInPage;
class	XRay3DBase;


//----------------------------------------------------------------------
class	XRay3DThreshold : public AlgorithmThreshold
{
public:
	int		SearchDot;

	XRay3DThreshold(XRay3DItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class   XRay3DItem : public AlgorithmItemPITemplate<XRay3DInPage,XRay3DBase>
{
public:

	XRay3DItem(void);
	virtual	~XRay3DItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new XRay3DItem();	}
	const	XRay3DThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const XRay3DThreshold *)GetThresholdBaseReadable(base);	}
	XRay3DThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (XRay3DThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override		{	return new XRay3DThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	XRay3DItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(XRay3DItem &src);
	void	CopyThresholdOnly(XRay3DItem &src);
	void	CopyArea(XRay3DItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

private:

};

class	XRay3DInPage : public AlgorithmInPagePITemplate<XRay3DItem,XRay3DBase>
{
public:
	ImageBufferListContainer	*ImageDim;
	int							CountImageDim;
	double						PointToDraw;		

	XRay3DInPage(AlgorithmBase *parent);
	~XRay3DInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return new XRay3DItem();	}
	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	void	ExeSmooth(ImageBuffer *Img);
	void	ExeEmphasize(ImageBuffer *Img);
	double	ExeMatch(ImageBuffer &Src,ImageBuffer &L,int &X,int &Y);
};

class	XRay3DBase : public AlgorithmBase
{
public:
	QColor		ColorNormal		;
	QColor		ColorSelected	;
	QColor		ColorActive		;
	QColor		Color0;
	QColor		Color1;
	QColor		Color2;
	QColor		Color3;
	QColor		Color4;
	QColor		Color5;
	QColor		Color6;
	QColor		Color7;

	XRay3DBase(LayersBase *Base);

	virtual	XRay3DInPage	*NewChild(AlgorithmBase *parent)override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("XRay3D");			}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigXRay3D.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

private:

};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	XRay3DHistogramListReqCommand			3
#define	XRay3DHistogramListSendCommand			4
#define	XRay3DReqThresholdReqCommand			5
#define	XRay3DReqThresholdSendCommand			6
#define	XRay3DReqTryThresholdCommand			7
#define	XRay3DSendTryThresholdCommand			8
#define	XRay3DReqChangeShiftCommand				9
#define	SetIndependentItemNameDataCommand_All	10
//==================================================================================
class	XRay3DDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			ShowingItemID;

	XRay3DDrawAttr(void):ServiceForLayers(NULL){	ShowingItemID=-1;	}
	XRay3DDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	XRay3DDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, int ptranparentLevel
				, const QColor &blockColor0
				, const QColor &blockColor1
				, const QColor &blockColor2
				, const QColor &blockColor3
				, const QColor &blockColor4
				, const QColor &blockColor5
				, const QColor &blockColor6
				, const QColor &blockColor7);

	void	Initial(void);

	XRay3DDrawAttr	&operator=(XRay3DDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	XRay3DDrawAttr::XRay3DDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base),ShowingItemID(-1)
{
}

inline	XRay3DDrawAttr::XRay3DDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, int ptranparentLevel
				, const QColor &blockColor0
				, const QColor &blockColor1
				, const QColor &blockColor2
				, const QColor &blockColor3
				, const QColor &blockColor4
				, const QColor &blockColor5
				, const QColor &blockColor6
				, const QColor &blockColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel,scol,stranparentLevel,acol,atranparentLevel)
,ServiceForLayers(Base)
,BlockColor0(blockColor0)
,BlockColor1(blockColor1)
,BlockColor2(blockColor2)
,BlockColor3(blockColor3)
,BlockColor4(blockColor4)
,BlockColor5(blockColor5)
,BlockColor6(blockColor6)
,BlockColor7(blockColor7)
,ShowingItemID(-1)
{
	BlockColor0.setAlpha(ptranparentLevel);
	BlockColor1.setAlpha(ptranparentLevel);
	BlockColor2.setAlpha(ptranparentLevel);
	BlockColor3.setAlpha(ptranparentLevel);
	BlockColor4.setAlpha(ptranparentLevel);
	BlockColor5.setAlpha(ptranparentLevel);
	BlockColor6.setAlpha(ptranparentLevel);
	BlockColor7.setAlpha(ptranparentLevel);
}
inline	XRay3DDrawAttr	&XRay3DDrawAttr::operator=(XRay3DDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	ShowingItemID	=src.ShowingItemID;
	return *this;
}
inline	bool	XRay3DDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,BlockColor0)==false)	return false;
	if(::Save(f,BlockColor1)==false)	return false;
	if(::Save(f,BlockColor2)==false)	return false;
	if(::Save(f,BlockColor3)==false)	return false;
	if(::Save(f,BlockColor4)==false)	return false;
	if(::Save(f,BlockColor5)==false)	return false;
	if(::Save(f,BlockColor6)==false)	return false;
	if(::Save(f,BlockColor7)==false)	return false;
	if(::Save(f,ShowingItemID)==false)	return false;
	return true;
}
inline	bool	XRay3DDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,BlockColor0)==false)	return false;
	if(::Load(f,BlockColor1)==false)	return false;
	if(::Load(f,BlockColor2)==false)	return false;
	if(::Load(f,BlockColor3)==false)	return false;
	if(::Load(f,BlockColor4)==false)	return false;
	if(::Load(f,BlockColor5)==false)	return false;
	if(::Load(f,BlockColor6)==false)	return false;
	if(::Load(f,BlockColor7)==false)	return false;
	if(::Load(f,ShowingItemID)==false)	return false;
	return true;
}

//==================================================================================
//==================================================================================

class	XRay3DThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	XRay3DThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	XRay3DThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	XRay3DThresholdSend(void);

	void	ConstructList(XRay3DThresholdReq *reqPacket,XRay3DBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdCreateTempXRay3DItemPacket : public GUIDirectMessage
{
public:
	XRay3DItem	*Point;
	CmdCreateTempXRay3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempXRay3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromXRay3DItemPacket : public GUIDirectMessage
{
public:
	XRay3DItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromXRay3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromXRay3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddXRay3DItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdAddXRay3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddXRay3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdModifyXRay3DItemPacket : public GUIDirectMessage
{
public:
	int		ItemID			;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdModifyXRay3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdModifyXRay3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadXRay3DItemPacketFromByteArray : public GUIDirectMessage
{
public:
	XRay3DItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadXRay3DItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadXRay3DItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateWholeXRay3D : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdCreateWholeXRay3D(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateWholeXRay3D(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqWholeXRay3D : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdReqWholeXRay3D(LayersBase *base):GUIDirectMessage(base){}
	CmdReqWholeXRay3D(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	CmdLoadImages: public GUIDirectMessage
{
public:
	QStringList	ImageFileNames;

	CmdLoadImages(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdSetPointY: public GUIDirectMessage
{
public:
	double	PointToDraw;

	CmdSetPointY(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqSmooth: public GUIDirectMessage
{
public:

	CmdReqSmooth(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdReqEmphasize: public GUIDirectMessage
{
public:

	CmdReqEmphasize(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdMatchFile: public GUIDirectMessage
{
public:
	QString	FileName;
	int		RetFileNo;
	int		RetX,RetY;

	CmdMatchFile(LayersBase *base):GUIDirectMessage(base){}
};