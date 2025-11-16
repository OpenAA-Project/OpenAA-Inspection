/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\CacheTargetImage\XCacheTargetImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XCacheTargetImage_H
#define XCacheTargetImage_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"

#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"



//----------------------------------------------------------------------

class   CacheTargetImageInLayer : public AlgorithmInLayerPLI
{
	ImageBufferListContainer	IBuffer;

  public:
	CacheTargetImageInLayer(AlgorithmInPageRoot *parent);
	~CacheTargetImageInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return(NULL);	}

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInLayerRoot *Res)	override;

	ImageBuffer	*GetPoint(int n);
};

class	CacheTargetImageInPage : public AlgorithmInPagePLI
{
public:

	CacheTargetImageInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}
	~CacheTargetImageInPage(void){}

	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new CacheTargetImageInLayer(parent));	}
	void	TransmitDirectly(GUIDirectMessage *packet)	override;	
private:
};

class	CacheTargetImageBase : public AlgorithmBase
{
public:
	int	BufferCount;

	CacheTargetImageBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new CacheTargetImageInPage((CacheTargetImageBase*)parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("CacheTargetImage");				}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigCacheTargetImage.dat");	}

private:

};
//==================================================================================
class	PacketSetToTarget : public GUIDirectMessage
{
public:
	int			Number;

	PacketSetToTarget(LayersBase *base):GUIDirectMessage(base){}
	PacketSetToTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	PacketGetImageBuffer : public GUIDirectMessage
{
public:
	int			Number;
	ImageBuffer	*Img;

	PacketGetImageBuffer(LayersBase *base):GUIDirectMessage(base){}
	PacketGetImageBuffer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif