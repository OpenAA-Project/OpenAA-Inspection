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