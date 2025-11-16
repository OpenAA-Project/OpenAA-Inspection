#include "XGerberAperture.h"
#include "GerberFast.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XGeneralFunc.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XGerberFastLibrary.h"
#include "XImageProcess.h"

void	GerberFastInPage::MakeImage(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
									,QColor LayerColor[MaxGerberLayer] ,QColor CompColor[MaxGerberLayer])
{
	int	XLen=min(4000,GetDotPerLine());
	int	YLen=min(4000,GetMaxLines());
	int	Overlap=200;
	int	XDir=XLen-2*Overlap;
	int	YDir=YLen-2*Overlap;
	int	XNumb=(GetDotPerLine()+XDir-1)/XDir;
	int	YNumb=(GetMaxLines()+YDir-1)/YDir;
	GerberFastDrawAttr	Attr;
	int	N=0;
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		if(b->GetValue()==true && FileLayerList[N]!=NULL){
			Attr.ShownFileID.Add(FileLayerList[N]->FileLayerID);
			Attr.LayerColor[N]=LayerColor[N];
		}
	}
	
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		Attr.ShownCompositeID.Add(CompositeID);
		Attr.CompColor[CompositeID]=CompColor[CompositeID];
	}
	int	DotPerLine=GetDotPerLine();
	QImage	TmpImage(XLen,YLen,QImage::Format_ARGB32);
	for(int yn=0;yn<YNumb;yn++){
		for(int xn=0;xn<XNumb;xn++){
			TmpImage.fill(0);

			N=0;
			for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
				GerberFileLayer	*F=FileLayerList[N];
				if(b->GetValue()==true && F!=NULL){
					for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
						GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
						if(Item!=NULL){
							if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
								a->Draw(TmpImage,-xn*XDir+Overlap,-yn*YDir+Overlap,1.0,&Attr);
							}
						}
					}
				}
			}
			for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				int	CompositeID=b->GetValue();
				GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
				if(CL!=NULL){
					//GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
					for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
						GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
						if(Item!=NULL){
							if(Item->GetCompositeID()==CompositeID){
								a->Draw(TmpImage,-xn*XDir+Overlap,-yn*YDir+Overlap,1.0,&Attr);
							}
						}
					}
				}
			}

			DataInPage	*Dp=GetDataInPage();
			ImagePointerContainer Images;
			if(GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
				Dp->GetMasterImages(Images);
			else if(GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
				Dp->GetTargetImages(Images);

			if(GetLayerNumb()>1){
				for(int layer=0;layer<GetLayerNumb();layer++){
					ImageBuffer	*IBuff=Images[layer];
					//#pragma omp parallel
					//{
					//	#pragma omp for
						for(int y=Overlap;y<YLen-Overlap;y++){
							int	Y=y-Overlap+yn*YDir;
							if(Y<GetMaxLines()){
								int	X=xn*XDir;
								QRgb	*s=(QRgb *)TmpImage.scanLine(y);
								BYTE	*d=IBuff->GetY(Y);
								int	NN=min(XLen-Overlap-Overlap,DotPerLine-X);
								int	x=Overlap;
								d=&d[X];
								s=&s[x];
								if(layer==0){
									//for(int x=Overlap;x<XLen-Overlap && X<DotPerLine;x++,X++){
									for(int h=0;h<NN;h++,d++,s++){
										*d=qRed(*s);
									}
								}
								else if(layer==1){
									//for(int x=Overlap;x<XLen-Overlap && X<DotPerLine;x++,X++){
									for(int h=0;h<NN;h++,d++,s++){
										*d=qGreen(*s);
									}
								}
								else if(layer==2){
									//for(int x=Overlap;x<XLen-Overlap && X<DotPerLine;x++,X++){
									for(int h=0;h<NN;h++,d++,s++){
										*d=qBlue(*s);
									}
								}
							}
						}
				}
				//}
			}
			else if(GetLayerNumb()==1){
				ImageBuffer	*IBuff=Images[0];
				//#pragma omp parallel
				//{
				//	#pragma omp for
					for(int y=Overlap;y<YLen-Overlap;y++){
						int	Y=y-Overlap+yn*YDir;
						if(Y<GetMaxLines()){
							int	X=xn*XDir;
							QRgb	*s=(QRgb *)TmpImage.scanLine(y);
							BYTE	*d=IBuff->GetY(Y);
							int	NN=min(XLen-Overlap-Overlap,DotPerLine-X);
							int	x=Overlap;
							d=&d[X];
							s=&s[x];
							//for(int x=Overlap;x<XLen-Overlap && X<DotPerLine;x++,X++){
							for(int h=0;h<NN;h++,d++,s++){
								*d=qGray(*s);
							}
						}
					}
				
				//}
			}
		}
	}
}
	
void	GerberFastInPage::MakeBitImage(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
									  ,QColor LayerColor[MaxGerberLayer] ,QColor CompColor[MaxGerberLayer])
{
	int	XLen=min(4000,GetDotPerLine());
	int	YLen=min(4000,GetMaxLines());
	int	Overlap=200;
	int	XDir=XLen-2*Overlap;
	int	YDir=YLen-2*Overlap;
	int	XNumb=(GetDotPerLine()+XDir-1)/XDir;
	int	YNumb=(GetMaxLines()+YDir-1)/YDir;
	GerberFastDrawAttr	Attr;
	int	N=0;
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		if(b->GetValue()==true && FileLayerList[N]!=NULL){
			Attr.ShownFileID.Add(FileLayerList[N]->FileLayerID);
			Attr.LayerColor[N]=LayerColor[N];
		}
	}
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		Attr.ShownCompositeID.Add(CompositeID);
		Attr.CompColor[CompositeID]=CompColor[CompositeID];
	}
	DataInPage	*Dp=GetDataInPage();
	ImagePointerContainer Images;
	Dp->GetBitImages(Images);
	QImage	TmpImage(XLen,YLen,QImage::Format_ARGB32);
	for(int layer=0;layer<GetLayerNumb();layer++){
		ImageBuffer	*IBuff=Images[layer];
		IBuff->Memset(0);
	}
	int	DotPerLine=GetDotPerLine();
	for(int yn=0;yn<YNumb;yn++){
		for(int xn=0;xn<XNumb;xn++){
			TmpImage.fill(0);

			N=0;
			for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
				GerberFileLayer	*F=FileLayerList[N];
				if(b->GetValue()==true && F!=NULL){
					for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
						GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
						if(Item!=NULL){
							if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
								a->Draw(TmpImage,-xn*XDir+Overlap,-yn*YDir+Overlap,1.0,&Attr);
							}
						}
					}
				}
			}
			for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				int	CompositeID=b->GetValue();
				GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
				if(CL!=NULL){
					//GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
					for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
						GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
						if(Item!=NULL){
							if(Item->GetCompositeID()==CompositeID){
								a->Draw(TmpImage,-xn*XDir+Overlap,-yn*YDir+Overlap,1.0,&Attr);
							}
						}
					}
				}
			}

			for(int layer=0;layer<GetLayerNumb();layer++){
				ImageBuffer	*IBuff=Images[layer];
				//#pragma omp parallel
				//{
				//	#pragma omp for
					for(int y=Overlap;y<YLen-Overlap;y++){
						int	Y=y-Overlap+yn*YDir;
						if(Y<GetMaxLines()){
							int	X=xn*XDir;
							QRgb	*s=(QRgb *)TmpImage.scanLine(y);
							BYTE	*d=IBuff->GetY(Y);

							int	NN=min(XLen-Overlap-Overlap,DotPerLine-X);
							int	x=Overlap;
							s=&s[x];
							//for(int x=Overlap;x<XLen-Overlap && X<GetDotPerLine();x++,X++){
							for(int h=0;h<NN;h++,X++,s++){
								if(qRed(*s)>=128 || qGreen(*s)>=128 || qBlue(*s)>=128)
									SetBmpBitOnY1(d,X);
							}
						}
					}
				//}
					IBuff->SetChanged(true);
			}
		}
	}
}

void	GerberFastInPage::MakeLayerImage		(int LayerLibID	,GerberGenerationFileContainer &GFileContainer,BYTE **CurrentBmp,int XByte,int YLen)
{
	MatrixBuffClear	(CurrentBmp ,0,XByte ,YLen);

	bool	PosiMode=true;
	int		Shift	=0;
	for(GerberGenerationFileList *k=GFileContainer.GetFirst();k!=NULL;k=k->GetNext()){
		if(k->LayerLibID==LayerLibID){
			PosiMode=!k->Inverted;
			Shift	=k->Shift;
		}
	}

	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			if(Item->GetFileLayer()!=NULL && Item->GetFileLayer()->GetFileLayerID()==LayerLibID){
				Item->MakeImage(CurrentBmp,0,0,XByte,YLen);
			}
		}
	}
	if(Shift!=0){
		BYTE **TmpBuff=MakeMatrixBuff(XByte,YLen);
		if(Shift<0){
			GetLayersBase()->FatAreaN(CurrentBmp
				,TmpBuff
				,XByte,YLen
				,-Shift);
		}
		else{
			GetLayersBase()->ThinAreaN(CurrentBmp
				,TmpBuff
				,XByte,YLen
				,Shift);
		}
		DeleteMatrixBuff(TmpBuff,YLen);
	}
	if(PosiMode==false){
		MatrixBuffNot	(CurrentBmp,XByte,YLen);
	}
}

void	GerberFastInPage::MakeCompositeImage	(int CompositeID,GerberGenerationFileContainer &GFileContainer,BYTE **CurrentBmp,int XByte,int YLen)
{
	MatrixBuffClear	(CurrentBmp ,0,XByte ,YLen);

	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	GerberCompositeDefLayer	*GLayer=ABase->CompositeDef.Search(CompositeID);
	GerberFileLayerContainer		TmpFileLayerList(this);
	TmpFileLayerList=FileLayerList;

	GerberCompositeDefLayer	TmpGLayer;
	TmpGLayer=*GLayer;

	for(GerberGenerationFileList *f=GFileContainer.GetFirst();f!=NULL;f=f->GetNext()){
		for(GerberFileLayer *g=FileLayerList.GetFirst();g!=NULL;g=g->GetNext()){
			if(g->FileName==f->FileName){
				//g->LibID=f->LayerLibID;
				for(GerberCompositeDefLayerItem	*c=GLayer->Combination.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->LayerTypeLibID==f->LayerLibID){
						if(f->Inverted==true){
							c->NegMode=!c->NegMode;
						}
					}
				}
				break;
			}
		}
	}

	GerberFastItemComposite	*Item=new GerberFastItemComposite();
	Item->CompositeLayer=GLayer;
	Item->SetCompositeID(CompositeID);
	
	AppendItem(Item);
	Item->MakeImage(CurrentBmp,0,0,XByte,YLen);

	RemoveItem(Item);
	FileLayerList=TmpFileLayerList;
	*GLayer=TmpGLayer;

	bool	Error;
	BuildPointer(Error);
	//for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
	//	if(Item!=NULL){
	//		if(Item->GetCompositeID()==CompositeID){
	//			Item->MakeImage(CurrentBmp,0,0,XByte,YLen);
	//		}
	//	}
	//}
}

void	GerberFastInPage::MakeCompositeImageShrink	(int CompositeID,GerberGenerationFileContainer &GFileContainer,BYTE **CurrentBmp,int XByte,int YLen)
{
	MatrixBuffClear	(CurrentBmp ,0,XByte ,YLen);

	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	GerberCompositeDefLayer	*GLayer=ABase->CompositeDef.Search(CompositeID);
	GerberFileLayerContainer		TmpFileLayerList(this);
	TmpFileLayerList=FileLayerList;

	GerberCompositeDefLayer	TmpGLayer;
	TmpGLayer=*GLayer;

	for(GerberGenerationFileList *f=GFileContainer.GetFirst();f!=NULL;f=f->GetNext()){
		for(GerberFileLayer *g=FileLayerList.GetFirst();g!=NULL;g=g->GetNext()){
			if(g->FileName==f->FileName){
				g->LibID=f->LayerLibID;
				for(GerberCompositeDefLayerItem	*c=GLayer->Combination.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->LayerTypeLibID==f->LayerLibID){
						if(f->Inverted==true){
							c->NegMode=!c->NegMode;
						}
					}
				}
			}
		}
	}


	BYTE	**SrcImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,YLen);
	//int	XLen=XByte<<3;

	bool	FirstCreated=false;
	for(GerberCompositeDefLayerItem	*g=GLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		MatrixBuffClear	(SrcImage ,0,XByte ,YLen);
		GerberGenerationFileList	*Current=NULL;
		AlgorithmItemPI	*a;
		bool	ExistItem=false;
		for(a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					item->MakeImage(SrcImage ,0 ,0 ,XByte ,YLen);
					ExistItem=true;
					Current=GFileContainer.SearchByFileName(item->GetFileLayer()->FileName);
				}
			}
		}
		if(ExistItem==true && Current!=NULL){
			if(g->NegMode==true){
				MatrixBuffNot(SrcImage ,XByte ,YLen);
			}
			if(g->DotSpr>0){
				GetLayersBase()->FatAreaN (SrcImage ,TmpMap ,XByte ,YLen ,g->DotSpr);
			}
			else if(g->DotSpr<0){
				GetLayersBase()->ThinAreaN(SrcImage ,TmpMap ,XByte ,YLen ,-g->DotSpr);
			}
			if(g->GetPrev()==NULL){	//First item
				MatrixBuffCopy	(CurrentBmp,XByte ,YLen
								,(const BYTE **)SrcImage,XByte ,YLen);
			}
			else{
				if(g->Operation==GerberCompositeDefLayerItem::_Or){
					GetLayersBase()->FatAreaN(SrcImage ,TmpMap ,XByte ,YLen,Current->Shift);
					MatrixBuffOr (CurrentBmp ,(const BYTE **)SrcImage ,XByte ,YLen);
				}
				else if(g->Operation==GerberCompositeDefLayerItem::_And){
					if(FirstCreated==true){
						GetLayersBase()->FatAreaN(SrcImage ,TmpMap ,XByte ,YLen,Current->Shift);
						MatrixBuffAnd (CurrentBmp ,(const BYTE **)SrcImage ,XByte ,YLen);
					}
					else{
						MatrixBuffCopy	(CurrentBmp,XByte ,YLen
										,(const BYTE **)SrcImage,XByte ,YLen);
					}
				}
				else if(g->Operation==GerberCompositeDefLayerItem::_NotAnd){
					GetLayersBase()->FatAreaN(SrcImage ,TmpMap ,XByte ,YLen,Current->Shift);
					MatrixBuffNotAnd (CurrentBmp ,(const BYTE **)SrcImage ,XByte ,YLen);
				}
				else if(g->Operation==GerberCompositeDefLayerItem::_NotOr){
					GetLayersBase()->FatAreaN(SrcImage ,TmpMap ,XByte ,YLen,Current->Shift);

					#pragma omp parallel
					{
						#pragma omp for
						for(int y=0;y<YLen;y++){
							BYTE	*d=CurrentBmp[y];
							BYTE	*s=SrcImage[y];
							for(int x=0;x<XByte;x++){
								if(s[x]!=0){
									d[x] |=~s[x];
								}
							}
						}
					}
				}
			}
			FirstCreated=true;
		}
	}

	DeleteMatrixBuff(SrcImage,YLen);
	DeleteMatrixBuff(TmpMap,YLen);

	FileLayerList=TmpFileLayerList;
	*GLayer=TmpGLayer;

	bool	Error;
	BuildPointer(Error);
}

void	GerberFastInPage::MakeImage(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();

	if(LayerMode==true){
		BYTE	**TmpMap	=MakeMatrixBuff(XByte ,YLen);
		BYTE	**TmpImage	=MakeMatrixBuff(XByte ,YLen);

		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
			
			int	KNumb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext(),KNumb++){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
						Item->MakeImage(TmpImage,0,0,XByte,YLen);
					}
				}
			}

			if(F->ShrinkDot>0){
				GetLayersBase()->ThinAreaN(TmpImage,TmpMap,XByte,YLen,F->ShrinkDot);
			}
			else if(F->ShrinkDot<0){
				GetLayersBase()->FatAreaN (TmpImage,TmpMap,XByte,YLen,(-F->ShrinkDot));
			}
			MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
		}
		DeleteMatrixBuff(TmpImage ,YLen);
		DeleteMatrixBuff(TmpMap,YLen);
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			//GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID){
						Item->MakeImage(CurrentBmp,0,0,XByte,YLen);
					}
				}
			}
		}
	}
}

void	GerberFastInPage::MakeImageEnlarge(BYTE **CurrentBmp
											,int LayerCompositeID ,bool LayerMode)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();

	BYTE	**TmpImage	=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2	=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(TmpImage ,0,XByte ,YLen);

	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	//GerberFastLibrary	*Lib=(GerberFastLibrary *)GBase->GetLibraryContainer()->CreateNew();
	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				GetLayersBase()->FatAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->MaxEnlargeDot);
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				GetLayersBase()->FatAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->MaxEnlargeDot);
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	DeleteMatrixBuff(TmpImage ,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
}

void	GerberFastInPage::MakeImageShiftable(BYTE **CurrentBmp
											,int LayerCompositeID ,bool LayerMode)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**TmpImage	=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2	=MakeMatrixBuff(XByte ,YLen);

	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	//GerberFastLibrary	*Lib=(GerberFastLibrary *)GBase->GetLibraryContainer()->CreateNew();
	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				GetLayersBase()->FatAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->MaxShiftDot);
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				GetLayersBase()->FatAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->MaxShiftDot);
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				MatrixBuffNotAnd(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				MatrixBuffNotAnd(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	
	DeleteMatrixBuff(TmpImage,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
}

void	GerberFastInPage::MakeImageShrinked(BYTE **CurrentBmp
											,int LayerCompositeID ,bool LayerMode)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**TmpImage =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2=MakeMatrixBuff(XByte ,YLen);

	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	//GerberFastLibrary	*Lib=(GerberFastLibrary *)GBase->GetLibraryContainer()->CreateNew();
	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				MatrixBuffOr(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				MatrixBuffOr(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}

	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				GetLayersBase()->FatAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->MaxShrinkDot);
				MatrixBuffAnd	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				GetLayersBase()->FatAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->MaxShrinkDot);
				MatrixBuffAnd	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	DeleteMatrixBuff(TmpImage,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
}

void	GerberFastInPage::MakeImageUnstable(BYTE **CurrentBmp
											,int LayerCompositeID ,bool LayerMode)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**TmpImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage3=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(TmpImage3 ,0,XByte ,YLen);

	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	//GerberFastLibrary	*Lib=(GerberFastLibrary *)GBase->GetLibraryContainer()->CreateNew();
	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);

				GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->UnstableZone);
				MatrixBuffOr	(TmpImage3,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);

				GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2,XByte,YLen
											,ALib->UnstableZone);
				MatrixBuffOr	(TmpImage3,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	MatrixBuffNotAnd(CurrentBmp ,(const BYTE **)TmpImage3 ,XByte ,YLen);

	DeleteMatrixBuff(TmpImage ,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
	DeleteMatrixBuff(TmpImage3,YLen);
}

void	GerberFastInPage::MakeImageStable(BYTE **CurrentBmp
											,int LayerCompositeID ,bool LayerMode)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**TmpImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2=MakeMatrixBuff(XByte ,YLen);

	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	//GerberFastLibrary	*Lib=(GerberFastLibrary *)GBase->GetLibraryContainer()->CreateNew();
	if(LayerMode==true){
		GerberFileLayer	*F=FileLayerList[LayerCompositeID];
		if(F!=NULL){
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(Container->GetLibrary(F->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				if(F->ShrinkDot>0){
					GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,F->ShrinkDot);
				}
				else if(F->ShrinkDot<0){
					GetLayersBase()->FatAreaN(TmpImage ,TmpImage2 ,XByte ,YLen,-F->ShrinkDot);
				}
				GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2,XByte,YLen
						,ALib->UnstableZone);
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}
	else{
		int	CompositeID=LayerCompositeID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			AlgorithmLibraryLevelContainer	LLib(Container);
			if(CDef!=NULL && Container->GetLibrary(CDef->LibID,LLib)==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
				MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeImage(TmpImage,0,0,XByte,YLen);
						}
					}
				}
				GetLayersBase()->ThinAreaN(TmpImage ,TmpImage2,XByte,YLen
											,ALib->UnstableZone);
				MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
			}
		}
	}

	DeleteMatrixBuff(TmpImage ,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
}

void	GerberFastInPage::MakeClusterContainer(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList)
{
	//CreateImagingBmpBuff();
	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**CurrentBmp	=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(CurrentBmp ,0,XByte ,YLen);

	GerberFastDrawAttr	Attr;
	int	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		if(b->GetValue()==true && FileLayerList[N]!=NULL){
			Attr.ShownFileID.Add(FileLayerList[N]->FileLayerID);
		}
	}
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		Attr.ShownCompositeID.Add(CompositeID);
	}

	BYTE	**TmpMap	=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage	=MakeMatrixBuff(XByte ,YLen);

	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		GerberFileLayer	*F=FileLayerList[N];
		if(b->GetValue()==true && F!=NULL){
			MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
			
			int	KNumb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext(),KNumb++){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()!=NULL && Item->GetFileLayerID()==F->GetFileLayerID()){
						Item->MakeImage(TmpImage,0,0,XByte,YLen);
					}
				}
			}

			if(F->ShrinkDot>0){
				GetLayersBase()->ThinAreaN(TmpImage,TmpMap,XByte,YLen,F->ShrinkDot);
			}
			else if(F->ShrinkDot<0){
				GetLayersBase()->FatAreaN (TmpImage,TmpMap,XByte,YLen,(-F->ShrinkDot));
			}
			MatrixBuffOr	(CurrentBmp,(const BYTE **)TmpImage,XByte ,YLen);
		}
	}
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(b->GetValue()==true && CL!=NULL){
			//GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID){
						Item->MakeImage(CurrentBmp,0,0,XByte,YLen);
					}
				}
			}
		}
	}
	DeleteMatrixBuff(TmpImage ,YLen);
	DeleteMatrixBuff(TmpMap,YLen);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(CurrentBmp ,XByte ,XByte*8,YLen ,FPack);

	DeleteMatrixBuff(CurrentBmp ,YLen);

	ClusterItemContainer.RemoveAll();
	PureFlexAreaList *f;
	int	ClusterID=0;
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		GerberFastClusterItemList	*a=new GerberFastClusterItemList();
		a->Area=*f;
		delete	f;
		a->ClusterID=ClusterID;
		ClusterID++;
		ClusterItemContainer.AppendList(a);
	}
	const int	XDivNumb=20;
	const int	YDivNumb=20;

	AlgorithmItemPointerListContainer	TmpContainer[XDivNumb][YDivNumb];
	int	XDivLen=(GetDotPerLine()+XDivNumb-1)/XDivNumb;
	int	YDivLen=(GetMaxLines  ()+YDivNumb-1)/YDivNumb;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			double	x1,y1,x2,y2;
			Item->GetXY(x1,y1,x2,y2);
			int	kx1=max((int)floor(x1/XDivLen),0);
			int	ky1=max((int)floor(y1/YDivLen),0);
			int	kx2=min((int)ceil(x2/XDivLen),XDivNumb);
			int	ky2=min((int)ceil(y2/YDivLen),YDivNumb);
			for(int xn=kx1;xn<=kx2 && xn<XDivNumb;xn++){
				for(int yn=ky1;yn<=ky2 && yn<YDivNumb;yn++){
					TmpContainer[xn][yn].Add(a);
				}
			}
		}
	}
	for(GerberFastClusterItemList *a=ClusterItemContainer.GetFirst();a!=NULL;a=a->GetNext()){
		int		x1,y1,x2,y2;
		a->Area.GetXY(x1,y1,x2,y2);
		int	kx1=max((int)floor(((double)x1)/XDivLen),0);
		int	ky1=max((int)floor(((double)y1)/YDivLen),0);
		int	kx2=ceil(((double)x2)/XDivLen);
		int	ky2=ceil(((double)y2)/YDivLen);
		for(int xn=kx1;xn<=kx2 && xn<XDivNumb;xn++){
			for(int yn=ky1;yn<=ky2 && yn<YDivNumb;yn++){
				for(AlgorithmItemPointerList *k=TmpContainer[xn][yn].GetFirst();k!=NULL;k=k->GetNext()){
					GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(k->GetItem());
					if(Item!=NULL){
						if(Item->IsCrossed(&a->Area)==true){
							a->ItemPointer.Add(k->GetItem());
						}
					}
				}
			}
		}
	}
}
