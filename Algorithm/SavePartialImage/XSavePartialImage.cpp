/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\SavePartialImage\XSavePartialImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XSavePartialImageResource.h"
#include <QByteArray>
#include "SelectLibraryInMaskForm.h"
#include "XSavePartialImage.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "omp.h"

SavePartialImageThreshold::SavePartialImageThreshold(SavePartialImageItem *parent)
:AlgorithmThreshold(parent)
{
}

bool	SavePartialImageThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const SavePartialImageThreshold	*s=dynamic_cast<const SavePartialImageThreshold *>(&src);
	return true;
}
void	SavePartialImageThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	SavePartialImageThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	return(true);
}
bool	SavePartialImageThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	return(true);
}

AlgorithmItemPI	&SavePartialImageItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    SavePartialImageItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	if(::Save(f,AreaName)==false)
		return false;
	if(MasterImages.Save(f)==false)
		return false;

	return true;
}
bool    SavePartialImageItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	if(::Load(f,AreaName)==false)
		return false;
	if(MasterImages.Load(f)==false)
		return false;

	return true;
}


void	SavePartialImageItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SavePartialImageDrawAttr	*a=dynamic_cast<SavePartialImageDrawAttr	*>(Attr);
	if(a!=NULL){
		if(a->DrawMode==SavePartialImageDrawAttr::_SPI_Image){
			int	W=GetArea().GetWidth();
			int	H=GetArea().GetHeight();
			int	Px=GetArea().GetMinX();
			int	Py=GetArea().GetMinY();
			int	LW=pnt.width();
			int	LH=pnt.height();
			if(MasterImages.GetCount()==1){
				if(ZoomRate<=1.0){
					int	tW=W*ZoomRate;
					int	tH=H*ZoomRate;
					for(int y=0;y<tH;y++){
						int	my=y+(movy+Py)*ZoomRate;
						if(my<0 || LH<=my)
							continue;
						BYTE	*d0=pnt.scanLine(my);
						BYTE	*s0=MasterImages[0]->GetY(y/ZoomRate);
						for(int x=0;x<tW;x++){
							int	mx=x+(movx+Px)*ZoomRate;
							if(mx<0 || LW<=mx)
								continue;
							d0[mx]=s0[x];
						}
					}
				}
				else{
					int	tW=W*ZoomRate;
					int	tH=H*ZoomRate;
				}
			}
			else if(MasterImages.GetCount()==2){
			}
			else if(MasterImages.GetCount()>=3){
			}		
		}
		else if(a->DrawMode==SavePartialImageDrawAttr::_SPI_Area){
			AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		else{
			AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

//===========================================


void	SavePartialImageInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManual	*AddMArea=dynamic_cast<CmdAddAreaManual *>(packet);
	if(AddMArea!=NULL){
		SavePartialImageItem	*MData=(SavePartialImageItem	*)CreateItem(0);
		MData->SetArea(AddMArea->Area);
		MData->SetManualCreated(true);
		AppendItem(MData);
		return;
	}
}

//===========================================
SavePartialImageBase::SavePartialImageBase(LayersBase *Base)
:AlgorithmBase(Base)
{
}

AlgorithmDrawAttr	*SavePartialImageBase::CreateDrawAttr(void)
{
	return new SavePartialImageDrawAttr();
}

bool	SavePartialImageBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,GetLayersBase()->GetMainWidget());
	//DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	SavePartialImageItem	Item;
	//Item.GetThresholdW()->Effective=DForm->Effective;
	//Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	return true;
}

void	SavePartialImageBase::TransmitDirectly(GUIDirectMessage *packet)
{
}

