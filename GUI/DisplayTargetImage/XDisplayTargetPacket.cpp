#include "DisplayTargetImage.h"
#include "XAlgorithmBase.h"
#include "TargetImageControlTools.h"
#include "XGUI.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "SelectItemIndependent.h"
#include "DisplayTargetImageResource.h"
#include "XDisplayImagePacket.h"
#include "XPassword.h"
#include "XCriticalFunc.h"
#include "DisplayTargetImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdReqTargetItemsBmp::GUICmdReqTargetItemsBmp(LayersBase *Base ,DisplayTargetImage *form  
									,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Form=form;
}
GUICmdReqTargetItemsBmp::~GUICmdReqTargetItemsBmp(void)
{
}

bool	GUICmdReqTargetItemsBmp::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false)
		return false;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	if(LayerList.Load(f)==false)
		return false;
	QString	DLLRoot;
	QString	DLLName;

	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	SelectedAlgorithm=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);

	return(true);
}
bool	GUICmdReqTargetItemsBmp::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false)
		return false;
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(LayerList.Save(f)==false)
		return false;

	QString	DLLRoot;
	QString	DLLName;
	if(SelectedAlgorithm!=NULL){
		SelectedAlgorithm->GetDLLName(DLLRoot,DLLName);
	}
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	return(true);
}

void	GUICmdReqTargetItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL)
		return;
	DisplayTargetImage	*A=dynamic_cast<DisplayTargetImage *>(q);
	if(A==NULL)
		return;
	GUICmdSendTargetItemsBmp	*SendBack=(GUICmdSendTargetItemsBmp *)((GetSendBackPacket()==NULL)?new GUICmdSendTargetItemsBmp(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	if(Data.ShowNGItemButton==true){
		SendBack->MakeImage(LayerList
							,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
							,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
							,Data.MovX,Data.MovY,Data.ZoomRate
							,localPage
							,Data.MoveGlobalDx ,Data.MoveGlobalDy
							,A ,SelectedAlgorithm
							,*GetLayersBase());
	}
	else if(Data.ShowAllItemsButton==true){
		SendBack->MakeImageAll(LayerList
							,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
							,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
							,Data.MovX,Data.MovY,Data.ZoomRate
							,localPage
							,Data.MoveGlobalDx ,Data.MoveGlobalDy
							,A ,SelectedAlgorithm
							,*GetLayersBase());
	}
	else{
		if(SendBack->IData!=NULL){
			SendBack->IData->fill(0);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendTargetItemsBmp::GUICmdSendTargetItemsBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData=NULL;
	PntFromIData=NULL;
}

GUICmdSendTargetItemsBmp::~GUICmdSendTargetItemsBmp(void)
{
	if(PntFromIData!=NULL)
		delete	PntFromIData;
	PntFromIData=NULL;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

bool	GUICmdSendTargetItemsBmp::Load(QIODevice *f)
{
	if(IData==NULL)
		IData=new QImage();
	IData->load(f,/**/"PNG");
	return(true);
}
bool	GUICmdSendTargetItemsBmp::Save(QIODevice *f)
{
	if(IData == NULL)
		IData = new QImage();
	IData->save(f,/**/"PNG");
	return(true);
}

void	GUICmdSendTargetItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendTargetItemsBmp::MakeImage(
								  IntList &LayerList
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,int MoveGlobalDx ,int MoveGlobalDy
								 ,DisplayTargetImage	*A
								 ,AlgorithmBase	*L
								 ,LayersBase &LocalLBase)
{
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;

	if(L==NULL)
		return;
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		delete	IData;
		IData=NULL;
		PntFromIData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_ARGB32);
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromIData==NULL)
		PntFromIData=new QPainter(IData);
	IData->fill(0);
	ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(L);
		if(Res!=NULL){
			IntList PhaseCodes;
			GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
			for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
				int	phase=v->GetValue();
				L->GetPageDataPhase(phase)->GetPageData(localPage)->DrawResultItem(Res->GetPageDataPhase(phase)->GetPageData(localPage),LayerList,*IData ,*PntFromIData,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate,true);
			}
		}
	}
}
void	GUICmdSendTargetItemsBmp::MakeImageAll(
								  IntList &LayerList
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,int MoveGlobalDx ,int MoveGlobalDy
								 ,DisplayTargetImage	*A
								 ,AlgorithmBase	*L
								 ,LayersBase &LocalLBase)
{
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;

	if(L==NULL)
		return;
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		delete	IData;
		IData=NULL;
		PntFromIData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_ARGB32);
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromIData==NULL)
		PntFromIData=new QPainter(IData);
	IData->fill(0);
	ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(L);
		if(Res!=NULL){
			IntList PhaseCodes;
			GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
			for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
				int	phase=v->GetValue();
				L->GetPageDataPhase(phase)->GetPageData(localPage)->DrawResultItem(Res->GetPageDataPhase(phase)->GetPageData(localPage),LayerList,*IData ,*PntFromIData,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate,false);
			}
		}
	}
}
//=======================================================================


GUICmdReqItemsZone::GUICmdReqItemsZone( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqItemsZone::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqItemsZone::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqItemsZone::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemsZone	*SendBack=GetSendBack(GUICmdSendItemsZone,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->X1=99999999;
	SendBack->Y1=99999999;
	SendBack->X2=-99999999;
	SendBack->Y2=-99999999;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*A=L->GetInstance();
		if(A!=NULL){
			AlgorithmInPageRoot		*PData=A->GetPageData(localPage);
			if(PData!=NULL){
				int	x1,y1,x2,y2;
				if(PData->GetOccupiedItemXY(x1,y1,x2,y2)==true){
					if(x1<SendBack->X1)
						SendBack->X1=x1;
					if(y1<SendBack->Y1)
						SendBack->Y1=y1;
					if(x2>SendBack->X2)
						SendBack->X2=x2;
					if(y2>SendBack->Y2)
						SendBack->Y2=y2;
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendItemsZone::GUICmdSendItemsZone( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendItemsZone::Load(QIODevice *f)
{
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}
bool	GUICmdSendItemsZone::Save(QIODevice *f)
{
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}

//=================================================================

GUICmdReqMultiItemsByArea::GUICmdReqMultiItemsByArea( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMultiItemsByArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqMultiItemsByArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

class SelectByItemsAlgorithm
{
public:
	FlexArea	Area;
	int			Layer;
	ResultInPageRoot	*Rp;

	SelectByItemsAlgorithm(){	Layer=0;	}
	~SelectByItemsAlgorithm(){}
};

bool SelectByItemsAlgorithmFunc(void *caller,AlgorithmItemRoot *item)
{
	SelectByItemsAlgorithm	*p=(SelectByItemsAlgorithm *)caller;
	if(item->GetLayer()!=p->Layer)
		return false;
	int	dx=0;
	int	dy=0;
	if(p->Rp!=NULL){
		ResultInItemRoot	*R=item->GetResult(p->Rp);
		if(R!=NULL){
			dx=R->GetTotalShiftedX();
			dy=R->GetTotalShiftedY();
		}
	}
	if(item->GetArea().CheckOverlap(&p->Area,-dx,-dy)==true){
		return true;
	}
	return false;
}

void	GUICmdReqMultiItemsByArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendMultiItemsByArea	*SendBack=GetSendBack(GUICmdSendMultiItemsByArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SelectByItemsAlgorithm	Selector;
	Selector.Area=Area;
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*A=L->GetInstance();
		if(A!=NULL
		&& A->GetLibType()>0
		&& A->GetLogicDLL()!=NULL
		&& A->GetLogicDLL()->IsProcessAlgorithm()==true){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(A);
				ResultInPageRoot	*Rp=NULL;
				if(Res!=NULL){
					Rp=Res->GetPageDataPhase(phase)->GetPageData(localPage);
				}
				AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(phase);
				AlgorithmInPageRoot		*PData=Ph->GetPageData(localPage);
				if(PData!=NULL){
					for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
						Selector.Layer=Layer;
						Selector.Rp=Rp;
						AlgorithmItemPointerListContainer Items;
						PData->EnumItems(&Selector,Items , SelectByItemsAlgorithmFunc);

						if(Items.GetCount()!=0){
							IntList	LibID;
							for(AlgorithmItemPointerList *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
								LibID.Merge(p->GetItem()->GetLibID());
							}
							for(IntClass *Lib=LibID.GetFirst();Lib!=NULL;Lib=Lib->GetNext()){
								ItemsByAlgorithm	*r=new ItemsByAlgorithm();
								r->LibType	=A->GetLibType();
								r->LibID	=Lib->GetValue();
								for(AlgorithmItemPointerList *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
									if(p->GetItem()->GetLibID()==Lib->GetValue()){
										r->ItemID.Add(phase,GlobalPage,p->GetItem()->GetID());
									}
								}
								SendBack->Container.AppendList(r);
							}
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendMultiItemsByArea::GUICmdSendMultiItemsByArea( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendMultiItemsByArea::Load(QIODevice *f)
{
	if(Container.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendMultiItemsByArea::Save(QIODevice *f)
{
	if(Container.Save(f)==false)
		return false;
	return true;
}


