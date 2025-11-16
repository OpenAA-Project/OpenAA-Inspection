#include "ListboxUncoveredAreaResource.h"
#include "ListboxUncoveredAreaForm.h"
#include "XImageProcess.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool	UncoveredAreaList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	if(::Save(f,DotCounts)==false)
		return false;
	return true;
}
bool	UncoveredAreaList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	if(::Load(f,DotCounts)==false)
		return false;
	return true;
}


void	UncoveredAreaList::GetCenter(int &Cx, int &Cy)
{
	Cx=(X1+X2)/2;
	Cy=(Y1+Y2)/2;
}

UncoveredAreaList	&UncoveredAreaList::operator=(UncoveredAreaList &src)
{
	GlobalPage	=src.GlobalPage;
	X1			=src.X1;
	Y1			=src.Y1;
	X2			=src.X2;
	Y2			=src.Y2;
	DotCounts	=src.DotCounts;
	return *this;
}

bool	UncoveredAreaContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(UncoveredAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	UncoveredAreaContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		UncoveredAreaList	*a=new UncoveredAreaList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

UncoveredAreaContainer	&UncoveredAreaContainer::operator=(UncoveredAreaContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

UncoveredAreaContainer	&UncoveredAreaContainer::operator+=(UncoveredAreaContainer &src)
{
	for(UncoveredAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		UncoveredAreaList *b=new UncoveredAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
//===================================================================================

ListboxUncoveredAreaForm::ListboxUncoveredAreaForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	MaxRowCount=100;
}

ListboxUncoveredAreaForm::~ListboxUncoveredAreaForm()
{

}

int	SortAreaListFunc(const void *a , const void *b)
{
	if((*((UncoveredAreaList **)a))->DotCounts <(*((UncoveredAreaList **)b))->DotCounts){
		return -1;
	}
	if((*((UncoveredAreaList **)a))->DotCounts >(*((UncoveredAreaList **)b))->DotCounts){
		return 1;
	}
	return 0;
}

void ListboxUncoveredAreaForm::ShowGrid(void)
{
	AreaList.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqUncoveredAreaList	RCmd(GetLayersBase(),sRoot,sName,page);
		GUICmdSendUncoveredAreaList	SCmd(GetLayersBase(),sRoot,sName,page);
		if(RCmd.Send(page,0,SCmd)==true){
			AreaList+=SCmd.AreaList;
		}
	}
	UncoveredAreaList	**LPoint=new UncoveredAreaList*[AreaList.GetCount()];
	int	n=0;
	for(UncoveredAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
		LPoint[n]=a;
		n++;
	}
	QSort(LPoint,n,sizeof(LPoint[0]),SortAreaListFunc);
	int	LCount=min(n,MaxRowCount);
	ui.tableWidget->setRowCount(LCount);
	for(int i=0;i<n && i<MaxRowCount;i++){
		SetDataToTable(ui.tableWidget,0,i ,QString::number(LPoint[i]->GlobalPage));
		QString	A=QString(/**/"(")  +QString::number(LPoint[i]->X1)+QString(/**/",")+QString::number(LPoint[i]->Y1)
				 +QString(/**/")-(")+QString::number(LPoint[i]->X2)+QString(/**/",")+QString::number(LPoint[i]->Y2)
				 +QString(/**/")");
		SetDataToTable(ui.tableWidget,1,i ,A);
		SetDataToTable(ui.tableWidget,2,i ,QString::number(LPoint[i]->DotCounts));
	}
	delete	[]LPoint;
}

void ListboxUncoveredAreaForm::on_tableWidget_clicked(const QModelIndex &)
{
	int row	=ui.tableWidget->currentRow();
	UncoveredAreaList	*e=AreaList.GetItem(row);
	if(e!=NULL){
		GUIFormBase	*F=GetLayersBase()->FindByName(ImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL){
				int	cx,cy;
				e->GetCenter(cx,cy);
				DataInPage *pdata=GetLayersBase()->GetPageData(e->GlobalPage);
				if(pdata!=NULL){
					d->ShowCenter(cx +pdata->GetOutlineOffset()->x
								 ,cy +pdata->GetOutlineOffset()->y);
				}
			}
		}
	}
}

void	ListboxUncoveredAreaForm::ResizeAction()
{
	ui.tableWidget->resize(width(),height()-ui.pushButtonUpdate->height());
	ui.pushButtonUpdate->move(0,ui.tableWidget->height());
	ui.pushButtonUpdate->resize(width(),ui.pushButtonUpdate->height());
}

void ListboxUncoveredAreaForm::on_pushButtonUpdate_clicked()
{
	ShowGrid();
}

//============================================================================
GUICmdReqUncoveredAreaList::GUICmdReqUncoveredAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


void	GUICmdReqUncoveredAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendUncoveredAreaList	*SendBack=GetSendBack(GUICmdSendUncoveredAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	int XByte ,YLen;
	const BYTE	**BMap=P->GetUncoveredMap(XByte ,YLen);
	PureFlexAreaListContainer FPack;
	::PickupFlexArea(BMap,XByte ,XByte*8,YLen ,FPack);

	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		UncoveredAreaList	*k=new UncoveredAreaList();
		k->GlobalPage		=localPage;
		a->GetXY(k->X1,k->Y1,k->X2,k->Y2);
		k->DotCounts	=a->GetPatternByte();
		SendBack->AreaList.AppendList(k);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendUncoveredAreaList::GUICmdSendUncoveredAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendUncoveredAreaList::Load(QIODevice *f)
{
	if(AreaList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendUncoveredAreaList::Save(QIODevice *f)
{
	if(AreaList.Save(f)==false)
		return false;
	return true;
}




