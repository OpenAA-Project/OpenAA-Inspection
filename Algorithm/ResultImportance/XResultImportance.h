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


#if	!defined(XResultImportance_H)
#define	XResultImportance_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
//#include "XResultImportanceCommon.h"

class	ResultImportanceItem;
class	ResultImportanceInPage;
class	ResultImportanceBase;

#define	ResultImportanceVersion		1
#define	DefLibTypeResultImportance			28

class	ResultImportanceLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	ResultImportanceLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override{	return true;	}
	virtual	bool	LoadBlob(QIODevice *f)	override{	return true;	}
};

class	ResultImportanceLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ResultImportanceLibraryContainer(LayersBase *base)
		:AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeResultImportance;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ResultImportance Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ResultImportanceLibrary(GetLibType(),GetLayersBase());	}
};

//-------------------------------------------------------------------------

class	ResultImportanceThreshold : public AlgorithmThreshold
{
public:

	ResultImportanceThreshold(ResultImportanceItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	ResultImportanceItem : public AlgorithmItemPITemplate<ResultImportanceInPage,ResultImportanceBase>
{
	ResultPosList **RetDim;
	int MaxCount;
public:
	int		ImportanceLevel;	//0 is the most important

	ResultImportanceItem(void);
	~ResultImportanceItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ResultImportanceItem();	}
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	const	ResultImportanceThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ResultImportanceThreshold *)GetThresholdBaseReadable(base);	}
	ResultImportanceThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ResultImportanceThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ResultImportanceThreshold(this);	}
};


class   ResultImportanceInPage : public AlgorithmInPagePITemplate<ResultImportanceItem,AlgorithmBase>
{
public:
	ResultImportanceInPage(AlgorithmBase *parent);
	~ResultImportanceInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			ResultImportanceItem	*a=new ResultImportanceItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	ResultImportanceBase : public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorSelected;
	QColor		ColorActive;
	int32		TransparentLevel;
	QColor		NegColorArea;
	QColor		NegColorSelected;

	QColor		AreaColor0;
	QColor		AreaColor1;
	QColor		AreaColor2;
	QColor		AreaColor3;
	QColor		AreaColor4;
	QColor		AreaColor5;
	QColor		AreaColor6;
	QColor		AreaColor7;

	ResultImportanceBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new ResultImportanceInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("ResultImportance");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigResultImportance.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

//==================================================================================

class	CmdAddResultImportanceItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		ImportanceLevel;

	CmdAddResultImportanceItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

//==================================================================================

class	ResultImportanceList : public NPList<ResultImportanceList>
{
public:
	int		Page;
	int		x1,y1,x2,y2;
	int		ImportanceLevel;
	int		ItemID;

	ResultImportanceList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	ResultImportanceListForPacketPack: public NPListPack<ResultImportanceList>
{
public:
	ResultImportanceListForPacketPack(void){}

	ResultImportanceListForPacketPack	&operator+=(ResultImportanceListForPacketPack &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	CmdMakeResultImportanceList : public GUIDirectMessage
{
public:
	ResultImportanceListForPacketPack	*ResultImportanceInfo;

	CmdMakeResultImportanceList(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSelectResultImportance : public GUIDirectMessage
{
public:
	IntList	*ImportanceLevels;

	CmdSelectResultImportance(LayersBase *base):GUIDirectMessage(base){}
};

#endif