/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\XImageProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XImageProcessor.h"
#include "ImageProcessorPanel.h"
#include "XFlexArea.h"
#include "XFlexAreaImage.h"
#include "XDataInLayer.h"
#include "XAnyData.h"

ImageProcessorLibrary::ImageProcessorLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base),FilterList(Base)
{
}
ImageProcessorLibrary::~ImageProcessorLibrary(void)
{
}

bool	ImageProcessorLibrary::SaveBlob(QIODevice *f)
{
	if(FilterList.Save(f)==false)
		return false;
	return true;
}
bool	ImageProcessorLibrary::LoadBlob(QIODevice *f)
{
	if(FilterList.Load(f)==false)
		return false;
	return true;
}

ImageProcessorLibrary	&ImageProcessorLibrary::operator=(const AlgorithmLibrary &src)
{
	const ImageProcessorLibrary	*s=dynamic_cast<const ImageProcessorLibrary *>(&src);
	if(s!=NULL){
		FilterList	=s->FilterList;
	}
	return *this;
}

ImageProcessorLibraryContainer::ImageProcessorLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
ImageProcessorLibraryContainer::~ImageProcessorLibraryContainer(void)
{
}

//==========================================================================

ImageProcessThreshold::ImageProcessThreshold(ImageProcessItem *parent)
:AlgorithmThreshold(parent)
{
}

void	ImageProcessThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	ImageProcessThreshold::Save(QIODevice *f)
{
	return true;
}
bool	ImageProcessThreshold::Load(QIODevice *f)
{
	return true;
}
//==========================================================================

AlgorithmItemPI	&ImageProcessItem::operator=(const AlgorithmItemRoot &src)
{
	return *this;
}
bool    ImageProcessItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    ImageProcessItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	return true;
}
void	ImageProcessItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
}

//==========================================================================
void	ImageProcessInPage::RegistArea(FlexArea &localArea,const IntList &LayerList)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ImageProcessorPanel" ,/**/"");
	ImageProcessorPanel	*GPanel=dynamic_cast<ImageProcessorPanel *>(DProp);
	if(GPanel!=NULL){
		if(GPanel->CurrentItem!=NULL){
			int64	NByte=localArea.GetPatternByte();
			BYTE	*D=new BYTE[NByte];
			int	n=0;
			for(int i=0;i<localArea.GetFLineLen();i++){
		        int y  =localArea.GetFLineAbsY (i);
		        int tx =localArea.GetFLineLeftX(i);
				int tn =localArea.GetFLineNumb(i);
				for(int x=0;x<tn;x++){
					D[n]=GPanel->CurrentItem->GetXY(tx+x,y)->GetR();
					n++;
				}
			}
			FlexAreaImageListCoeff	*F=new FlexAreaImageListCoeff(D,n);
			((FlexArea *)F)->operator=(localArea);
			LearnPattern.AppendList(F);
		}
	}
}
//==========================================================================

ImageProcessBase::ImageProcessBase(LayersBase *Base)
:AlgorithmBase(Base)
,GData(NULL)
{
}
void	ImageProcessBase::Initial(LayersBase *Base)
{
	AlgorithmBase::Initial(Base);
	GData.SetLayersBase(Base);
}

AlgorithmDrawAttr	*ImageProcessBase::CreateDrawAttr(void)
{
	return NULL;
}

bool	ImageProcessBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	if(GData.Save(f)==false)
		return false;
	if(Program.Save(f)==false)
		return false;
	return true;
}
bool	ImageProcessBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	if(GData.Load(f)==false)
		return false;
	if(Program.Load(f)==false)
		return false;
	return true;
}

void	ImageProcessBase::TransmitDirectly(GUIDirectMessage *packet)
{
	ImageProcessorPaint	*ImageProcessorPaintVar=dynamic_cast<ImageProcessorPaint *>(packet);
	if(ImageProcessorPaintVar!=NULL){
		for(FilterBase *a=GData.FilterBaseList.GetFirst();a!=NULL;a=a->GetNext()){
			a->Draw(ImageProcessorPaintVar->Pnt,0,0);
		}
		return;
	}
	ImageProcessorPaintPanel	*ImageProcessorPaintPanelVar=dynamic_cast<ImageProcessorPaintPanel *>(packet);
	if(ImageProcessorPaintPanelVar!=NULL){
		ImageProcessorPaintPanelVar->Item->DrawOnPanel(*ImageProcessorPaintPanelVar->Img,ImageProcessorPaintPanelVar->ZoomRate,ImageProcessorPaintPanelVar->MovX,ImageProcessorPaintPanelVar->MovY);
		return;
	}
	ImageProcessorAddInstance	*ImageProcessorAddInstanceVar=dynamic_cast<ImageProcessorAddInstance *>(packet);
	if(ImageProcessorAddInstanceVar!=NULL){
		FilterBase *b=GData.CreateNew(GetLayersBase(),ImageProcessorAddInstanceVar->ParamTitle);
		if(b!=NULL){
			b->SetPosition(ImageProcessorAddInstanceVar->x ,ImageProcessorAddInstanceVar->y);
			GData.FilterBaseList.AppendList(b);
			return;
		}
		return;
	}
	ImageProcessorAddProgram	*ImageProcessorAddProgramVar=dynamic_cast<ImageProcessorAddProgram *>(packet);
	if(ImageProcessorAddProgramVar!=NULL){
		GroupImages	*g=new GroupImages();
		g->ProgName=ImageProcessorAddProgramVar->ProgName;
		Program.AppendList(g);
		return;
	}
	ImageProcessorEnumProgram	*ImageProcessorEnumProgramVar=dynamic_cast<ImageProcessorEnumProgram *>(packet);
	if(ImageProcessorEnumProgramVar!=NULL){
		for(GroupImages	*g=Program.GetFirst();g!=NULL;g=g->GetNext()){
			ImageProcessorEnumProgramVar->ProgNameList.append(g->ProgName);
		}
		return;
	}
	ImageProcessorEnumImages	*ImageProcessorEnumImagesVar=dynamic_cast<ImageProcessorEnumImages *>(packet);
	if(ImageProcessorEnumImagesVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorEnumImagesVar->Row);
		if(g!=NULL){
			for(GrouperImageItemList *a=g->GImageLoadedList.GetFirst();a!=NULL;a=a->GetNext()){
				ImageProcessorEnumImagesVar->FileNameList.append(a->FileName);
			}
		}
		return;
	}
	ImageProcessorDelProgram	*ImageProcessorDelProgramVar=dynamic_cast<ImageProcessorDelProgram *>(packet);
	if(ImageProcessorDelProgramVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorDelProgramVar->Row);
		if(g!=NULL){
			Program.RemoveList(g);
			delete	g;
		}
		return;
	}
	ImageProcessorAddFiles	*ImageProcessorAddFilesVar=dynamic_cast<ImageProcessorAddFiles *>(packet);
	if(ImageProcessorAddFilesVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorAddFilesVar->ProgRow);
		if(g!=NULL){
			for(int i=0;i<ImageProcessorAddFilesVar->FileNames.count();i++){
				QString	v=ImageProcessorAddFilesVar->FileNames.value(i);
				GrouperImageItemList	*m=new GrouperImageItemList(g->GImageLoadedList.GetNumber());
				m->FileName=v;
				g->GImageLoadedList.AppendList(m);
			}
		}
		return;
	}
	ImageProcessorDelFile	*ImageProcessorDelFileVar=dynamic_cast<ImageProcessorDelFile *>(packet);
	if(ImageProcessorDelFileVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorDelFileVar->ProgRow);
		if(g!=NULL){
			GrouperImageItemList	*m=g->GImageLoadedList.GetItem(ImageProcessorDelFileVar->FileRow);
			if(m!=NULL){
				g->GImageLoadedList.RemoveList(m);
				delete	m;
			}
		}
		return;
	}
	ImageProcessorSelectItem	*ImageProcessorSelectItemVar=dynamic_cast<ImageProcessorSelectItem *>(packet);
	if(ImageProcessorSelectItemVar!=NULL){
		ImageProcessorSelectItemVar->Item=NULL;
		for(FilterBase *a=GData.FilterBaseList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(ImageProcessorSelectItemVar->x,ImageProcessorSelectItemVar->y)==true){
				ImageProcessorSelectItemVar->Item=a;
				return;
			}
		}
	}
	ImageProcessorDeleteItem	*ImageProcessorDeleteItemVar=dynamic_cast<ImageProcessorDeleteItem *>(packet);
	if(ImageProcessorDeleteItemVar!=NULL){
		GData.RemoveFilterBase(ImageProcessorDeleteItemVar->Item);
		delete	ImageProcessorDeleteItemVar->Item;
		return;
	}
	ImageProcessorMoveItem	*ImageProcessorMoveItemVar=dynamic_cast<ImageProcessorMoveItem *>(packet);
	if(ImageProcessorMoveItemVar!=NULL){
		ImageProcessorMoveItemVar->Item->SetPosition(ImageProcessorMoveItemVar->x,ImageProcessorMoveItemVar->y);
		return;
	}
	ImageProcessorDeleteAllTargetInItem *ImageProcessorDeleteAllTargetInItemVar=dynamic_cast<ImageProcessorDeleteAllTargetInItem *>(packet);
	if(ImageProcessorDeleteAllTargetInItemVar!=NULL){
		GData.DeleteAllTarget(ImageProcessorDeleteAllTargetInItemVar->Item);
		return;
	}
	ImageProcessorAddTargetFromSource	*ImageProcessorAddTargetFromSourceVar=dynamic_cast<ImageProcessorAddTargetFromSource *>(packet);
	if(ImageProcessorAddTargetFromSourceVar!=NULL){
		for(FilterBase *a=GData.FilterBaseList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(ImageProcessorAddTargetFromSourceVar->x,ImageProcessorAddTargetFromSourceVar->y)==true){
				a->AppendTarget(ImageProcessorAddTargetFromSourceVar->CurrentItem);
				ImageProcessorAddTargetFromSourceVar->CurrentItem=NULL;
				return;
			}
		}
	}
	ImageProcessorGetParam	*ImageProcessorGetParamVar=dynamic_cast<ImageProcessorGetParam *>(packet);
	if(ImageProcessorGetParamVar!=NULL){
		ImageProcessorGetParamVar->ParamCount=0;
		for(FilterBase *a=GData.FilterBaseList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetID()==ImageProcessorGetParamVar->ItemID){
				for(int k=0;k<a->GetParamNumb();k++){
					ImageProcessorGetParamVar->Param[k]=a->GetParam(k);
					ImageProcessorGetParamVar->ParamName.append(a->GetParamTitle(k));
				}
				ImageProcessorGetParamVar->ParamCount=a->GetParamNumb();
				return;
			}
		}
	}
	ImageProcessorSetParam	*ImageProcessorSetParamVar=dynamic_cast<ImageProcessorSetParam *>(packet);
	if(ImageProcessorSetParamVar!=NULL){
		for(FilterBase *a=GData.FilterBaseList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetID()==ImageProcessorSetParamVar->ItemID){
				for(int k=0;k<a->GetParamNumb();k++){
					a->SetParam(k,ImageProcessorSetParamVar->Param[k]);
				}
			}
		}
		return;
	}
	ImageProcessorUpperFile	*ImageProcessorUpperFileVar=dynamic_cast<ImageProcessorUpperFile *>(packet);
	if(ImageProcessorUpperFileVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorUpperFileVar->ProgRow);
		GrouperImageItemList	*b1=g->GImageLoadedList.GetItem(ImageProcessorUpperFileVar->FileRow);
		if(b1!=NULL){
			int	n=ImageProcessorUpperFileVar->FileRow-1;
			if(n>=0){
				g->GImageLoadedList.RemoveList(b1);
				g->GImageLoadedList.InsertList(n,b1);
			}
		}
		return;
	}
	ImageProcessorLowerFile	*ImageProcessorLowerFileVar=dynamic_cast<ImageProcessorLowerFile *>(packet);
	if(ImageProcessorLowerFileVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorLowerFileVar->ProgRow);
		GrouperImageItemList	*b1=g->GImageLoadedList.GetItem(ImageProcessorLowerFileVar->FileRow);
		if(b1!=NULL){
			int	n=ImageProcessorLowerFileVar->FileRow+1;
			if(n<g->GImageLoadedList.GetNumber()){
				g->GImageLoadedList.RemoveList(b1);
				g->GImageLoadedList.InsertList(n,b1);
			}
		}
		return;
	}
	ImageProcessorExecuteOne	*ImageProcessorExecuteOneVar=dynamic_cast<ImageProcessorExecuteOne *>(packet);
	if(ImageProcessorExecuteOneVar!=NULL){
		GroupImages	*g=Program.GetItem(ImageProcessorExecuteOneVar->ProgRow);
		if(g!=NULL){
			GetLayersBase()->GetAnyData()->Set(/**/"CurrentName",g->ProgName);
			GData.Calculate(*g,NULL);
		}
	}
	ImageProcessorExecuteAll	*ImageProcessorExecuteAllVar=dynamic_cast<ImageProcessorExecuteAll *>(packet);
	if(ImageProcessorExecuteAllVar!=NULL){
		for(GroupImages *g=Program.GetFirst();g!=NULL;g=g->GetNext()){
			GData.Calculate(*g,NULL);
		}
	}
	ImageProcessorGetMinMaxArea	*ImageProcessorGetMinMaxAreaVar=dynamic_cast<ImageProcessorGetMinMaxArea *>(packet);
	if(ImageProcessorGetMinMaxAreaVar!=NULL){
		ImageProcessorGetMinMaxAreaVar->MinX= 99999999;
		ImageProcessorGetMinMaxAreaVar->MinY= 99999999;
		ImageProcessorGetMinMaxAreaVar->MaxX=-99999999;
		ImageProcessorGetMinMaxAreaVar->MaxY=-99999999;
		for(FilterBase *a=GData.FilterBaseList.GetFirst();a!=NULL;a=a->GetNext()){
			int	x,y;
			a->GetPosition(x,y);
			if(ImageProcessorGetMinMaxAreaVar->MinX>x)
				ImageProcessorGetMinMaxAreaVar->MinX=x;
			if(ImageProcessorGetMinMaxAreaVar->MinY>y)
				ImageProcessorGetMinMaxAreaVar->MinY=y;
			if(ImageProcessorGetMinMaxAreaVar->MaxX<x)
				ImageProcessorGetMinMaxAreaVar->MaxX=x;
			if(ImageProcessorGetMinMaxAreaVar->MaxY<y)
				ImageProcessorGetMinMaxAreaVar->MaxY=y;
		}
	}
	ImageProcessorLoadDefFile	*ImageProcessorLoadDefFileVar=dynamic_cast<ImageProcessorLoadDefFile *>(packet);
	if(ImageProcessorLoadDefFileVar!=NULL){
		QFile	MFile(ImageProcessorLoadDefFileVar->DefFileName);
		MFile.open(QIODevice::ReadOnly);
		QTextStream	FStr(&MFile);
		for(;;){
			QString	LineBuff=FStr.readLine();
			if(LineBuff.isEmpty()==true)
				break;
			QTextStream	LStr(&LineBuff);
			int	N;
			QString	ProjName;
			QString	sFileName[100];
			LStr>>N>>ProjName;
			for(int i=0;i<N;i++){
				LStr>>sFileName[i];
			}
			GroupImages	*g=new GroupImages();
			g->ProgName=ProjName;
			Program.AppendList(g);
			for(int i=0;i<N;i++){
				GrouperImageItemList	*m=new GrouperImageItemList(i);
				m->FileName=sFileName[i];
				g->GImageLoadedList.AppendList(m);
			}
		}
		QFileInfo	FInfo(ImageProcessorLoadDefFileVar->DefFileName);
		QString	BaseName=FInfo.baseName();
		GetLayersBase()->GetAnyData()->Set(/**/"BaseName",BaseName);
	}
	ImageProcessorDelAllProgram	*ImageProcessorDelAllProgramVar=dynamic_cast<ImageProcessorDelAllProgram *>(packet);
	if(ImageProcessorDelAllProgramVar!=NULL){
		Program.RemoveAll();
	}
}

