#include "ShowBlockListResource.h"
#include "ShowBlockListForm.h"
#include "ui_ShowBlockListForm.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XDataModelPageLayerItem.h"
#include "XBlockInspection.h"
#include "XLibraryType.h"
#include <math.h>

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowBlockListForm::ShowBlockListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowBlockListForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	EasyMode=true;

	ui->tableWidgetLib	->setColumnWidth(0,64);
	ui->tableWidgetLib	->setColumnWidth(1,40);
	ui->tableWidgetLib	->setColumnWidth(2,120);

	ui->tableWidgetValue->setColumnWidth(0,40);
	ui->tableWidgetValue->setColumnWidth(1,40);
	ui->tableWidgetValue->setColumnWidth(2,80);
	ui->tableWidgetValue->setColumnWidth(3,80);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowBlockListForm::~ShowBlockListForm()
{
    delete ui;
}

void	ShowBlockListForm::Prepare(void)
{
	if(EasyMode==true)
		ui->stackedWidgetMode->setCurrentIndex(1);
	else
		ui->stackedWidgetMode->setCurrentIndex(0);

	tableWidgetLibWidth		=ui->tableWidgetLib		->width();
	stackedWidgetModeWidth	=ui->stackedWidgetMode	->width();
	tableWidgetLibHeight	=ui->tableWidgetLib		->height();
	stackedWidgetModeHeight	=ui->stackedWidgetMode	->height();

	if(width()<ui->tableWidgetLib->width()+ui->stackedWidgetMode->width()){
		ui->tableWidgetLib	 ->setGeometry(0,0,width(),height()-ui->stackedWidgetMode->height());
		ui->stackedWidgetMode->setGeometry(0,ui->tableWidgetLib->height(),width(),ui->stackedWidgetMode->height());
	}
}

void	ShowBlockListForm::ResizeAction()
{
	if(width()<tableWidgetLibWidth+stackedWidgetModeWidth){
		ui->tableWidgetLib	 ->setGeometry(0,0,width(),height()-ui->stackedWidgetMode->height());
		ui->stackedWidgetMode->setGeometry(0,ui->tableWidgetLib->height(),width(),ui->stackedWidgetMode->height());
	}
	ui->tableWidgetLib	->setColumnWidth(0,ui->tableWidgetLib->width()*0.20);
	ui->tableWidgetLib	->setColumnWidth(1,ui->tableWidgetLib->width()*0.15);
	ui->tableWidgetLib	->setColumnWidth(2,ui->tableWidgetLib->width()-32-ui->tableWidgetLib->width()*0.35);

	int	d=width()-stackedWidgetModeWidth;
	ui->horizontalSliderBrightnessN	->resize(148+d,22);
	ui->horizontalSizeN				->resize(148+d,22);
	ui->horizontalSliderBrightnessB	->resize(148+d,22);
	ui->horizontalSizeB				->resize(148+d,22);
	ui->horizontalSliderSearch		->resize(148+d,22);

	ui->labelBrightnessN	->move(220+d,ui->labelBrightnessN	->geometry().top());
	ui->labelSIzeN			->move(220+d,ui->labelSIzeN			->geometry().top());
	ui->labelBrightnessB	->move(220+d,ui->labelBrightnessB	->geometry().top());
	ui->labelSIzeB			->move(220+d,ui->labelSIzeB			->geometry().top());
	ui->labelSearch			->move(220+d,ui->labelSearch		->geometry().top());

	ui->label_6	->move(250+d,ui->label_6->geometry().top());
	ui->label_7	->move(250+d,ui->label_7->geometry().top());
	ui->label_8	->move(250+d,ui->label_8->geometry().top());
	ui->label_9	->move(250+d,ui->label_9->geometry().top());

	ui->pushButtonSetEasyOperation->move(250+d,ui->pushButtonSetEasyOperation->geometry().top());
}

void	ShowBlockListForm::BuildForShow(void)
{
	LibIDs.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqUsedLibrary	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUIAckUsedLibrary	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			LibIDs.Merge(ACmd.LibIDs);
		}
	}
	LibIDs.Sort();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(ABase==NULL)
		return;
	ui->tableWidgetLib->setRowCount(LibIDs.GetCount());
	int	n=0;
	for(AlgorithmLibraryList *a=LibIDs.GetFirst();a!=NULL;a=a->GetNext(),n++){
		int	LibType=a->GetLibType();
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LibType);
		if(ABase!=NULL){
			::SetDataToTable(ui->tableWidgetLib ,0 ,n ,ABase->GetNameByCurrentLanguage());
		}
		else{
			QString	TypeName=GetLayersBase()->GetInstalledLibType()->FindLibraryTypeName(LibType);
			::SetDataToTable(ui->tableWidgetLib ,0 ,n ,TypeName);
		}
		::SetDataToTable(ui->tableWidgetLib ,1 ,n ,QString::number(a->GetLibID()));
		QString	LibName=a->GetLibName();
		::SetDataToTable(ui->tableWidgetLib ,2 ,n ,LibName);
	}
	if(LibIDs.GetFirst()!=NULL){
		ui->tableWidgetLib->setCurrentCell(0,0);
		QModelIndex index;
		on_tableWidgetLib_clicked(index);
	}
}

void ShowBlockListForm::on_listWidgetValueType_clicked(const QModelIndex &index)
{
	int	R=ui->listWidgetValueType->currentRow();
	if(0<=R && R<7){
		ui->stackedWidget->setCurrentIndex(R);
	}
}

void ShowBlockListForm::on_listWidgetBroadDark_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetBroadDark->currentRow()){
		case 0:
			ShowValue(BroadDark_BrightnessWidth);
			break;
		case 1:
			ShowValue(BroadDark_NGSize);
			break;
		case 2:
			ShowValue(BroadDark_NGLength);
			break;
		case 3:
			ShowValue(BroadDark_MaxSize);
			break;
		case 4:
			ShowValue(BroadDark_ClusterCount);
			break;
		case 5:
			ShowValue(BroadDark_Connection);
	}
}

void ShowBlockListForm::on_listWidgetBroadLight_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetBroadLight->currentRow()){
		case 0:
			ShowValue(BroadLight_BrightnessWidth);
			break;
		case 1:
			ShowValue(BroadLight_NGSize);
			break;
		case 2:
			ShowValue(BroadLight_NGLength);
			break;
		case 3:
			ShowValue(BroadLight_MaxSize);
			break;
		case 4:
			ShowValue(BroadLight_ClusterCount);
			break;
		case 5:
			ShowValue(BroadLight_Connection);
	}
}

void ShowBlockListForm::on_listWidgetNarrowDark_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetNarrowDark->currentRow()){
		case 0:
			ShowValue(NarrowDark_BrightnessWidth);
			break;
		case 1:
			ShowValue(NarrowDark_NGSize);
			break;
		case 2:
			ShowValue(NarrowDark_NGLength);
			break;
		case 3:
			ShowValue(NarrowDark_MaxSize);
			break;
		case 4:
			ShowValue(NarrowDark_ClusterCount);
			break;
		case 5:
			ShowValue(NarrowDark_Connection);
	}
}

void ShowBlockListForm::on_listWidgetNarrowLight_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetNarrowLight->currentRow()){
		case 0:
			ShowValue(NarrowLight_BrightnessWidth);
			break;
		case 1:
			ShowValue(NarrowLight_NGSize);
			break;
		case 2:
			ShowValue(NarrowLight_NGLength);
			break;
		case 3:
			ShowValue(NarrowLight_MaxSize);
			break;
		case 4:
			ShowValue(NarrowLight_ClusterCount);
			break;
		case 5:
			ShowValue(NarrowLight_Connection);
	}
}

void ShowBlockListForm::on_listWidgetBrightAdjustment_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetBrightAdjustment->currentRow()){
		case 0:
			ShowValue(BrightAdjustment_Enable);
			break;
		case 1:
			ShowValue(BrightAdjustment_DarkSide);
			break;
		case 2:
			ShowValue(BrightAdjustment_LightSide);
			break;
	}
}

void ShowBlockListForm::on_listWidgetAttribute_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetAttribute->currentRow()){
		case 0:
			ShowValue(Attribute_InspectionEffective);
			break;
		case 1:
			ShowValue(Attribute_AbsoluteBrightness);
			break;
		case 2:
			ShowValue(Attribute_Clusterize);
			break;
		case 3:
			ShowValue(Attribute_Differential);
			break;
		case 4:
			ShowValue(Attribute_FollowOutline);
			break;
		case 5:
			ShowValue(Attribute_OnlyMaxNGSize);
			break;
		case 6:
			ShowValue(Attribute_NoOutput);
			break;
		case 7:
			ShowValue(Attribute_WhiteMask);
			break;
		case 8:
			ShowValue(Attribute_BlackMask);
			break;
		case 9:
			ShowValue(Attribute_PickupFromParts);
			break;
		case 10:
			ShowValue(Attribute_ReverseLogic);
			break;
		case 11:
			ShowValue(Attribute_DetailSearch);
			break;
		case 12:
			ShowValue(Attribute_DynamicMask);
			break;
		case 13:
			ShowValue(Attribute_UseMasterImage);
			break;
	}
}

void ShowBlockListForm::on_listWidgetSearch_clicked(const QModelIndex &index)
{
	switch(ui->listWidgetSearch->currentRow()){
		case 0:
			ShowValue(Search_EnableWholeSearch);
			break;
		case 1:
			ShowValue(Search_SelfSearchDot);
			break;
		case 2:
			ShowValue(Search_WholeSearchDot);
			break;
	}
}

void ShowBlockListForm::on_pushButtonSaveCSV_clicked()
{

}

void	ShowBlockListForm::ShowValue(InfoType RType)
{
	int	LibRow=ui->tableWidgetLib->currentRow();
	if(LibRow<0)
		return;
	LayerValueCountContainer	*PData=new LayerValueCountContainer[GetPageNumb()];
	int	N=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqLayerValueCount	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUIAckLayerValueCount	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.LibType=LibIDs[LibRow]->GetLibType();
		RCmd.ReqType=RType;
		RCmd.LibID	=LibIDs[LibRow]->GetLibID();
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			PData[page]=ACmd.ItemCounts;
			N+=ACmd.ItemCounts.GetCount();
		}
	}
	ui->tableWidgetValue->setRowCount(N);
	int	n=0;
	for(int page=0;page<GetPageNumb();page++){
		for(LayerValueCount *a=PData[page].GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui->tableWidgetValue,0,n,QString::number(page));
			::SetDataToTable(ui->tableWidgetValue,1,n,QString::number(a->Layer));
			if(a->ValueType==LayerValueCount::_ValueInt)
				::SetDataToTable(ui->tableWidgetValue,2,n,QString::number(a->ValueInt));
			else if(a->ValueType==LayerValueCount::_ValueDouble)
				::SetDataToTable(ui->tableWidgetValue,2,n,QString::number(a->ValueDouble));
			else if(a->ValueType==LayerValueCount::_ValueBool)
				::SetDataToTable(ui->tableWidgetValue,2,n,a->ValueBool==true?/**/"ON":/**/"OFF");
			::SetDataToTable(ui->tableWidgetValue,3,n,QString::number(a->Count));
			n++;
		}
	}
	delete	[]PData;
}

void	ShowBlockListForm::ShowCurrentPosition(int LibType,int LibID)
{
	BrightWidthBL=0;
	BrightWidthBH=0;
	BrightWidthNL=0;
	BrightWidthNH=0;
	NGSizeBL=0;
	NGSizeBH=0;
	NGSizeNL=0;
	NGSizeNH=0;
	SearchDot=0;
	Count=0;

	for(int i=0;i<256;i++){
		HistTable[i]=0;
	}

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqStatisticByLib	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUIAckStatisticByLib	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.LibType	=LibType;
		RCmd.LibID		=LibID;
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			for(int i=0;i<256;i++){
				HistTable[i]+=ACmd.HistTable[i];
			}
			BrightWidthBL	+=ACmd.BrightWidthBL;
			BrightWidthBH	+=ACmd.BrightWidthBH;
			BrightWidthNL	+=ACmd.BrightWidthNL;
			BrightWidthNH	+=ACmd.BrightWidthNH;
			NGSizeBL		+=ACmd.NGSizeBL;
			NGSizeBH		+=ACmd.NGSizeBH;
			NGSizeNL		+=ACmd.NGSizeNL;
			NGSizeNH		+=ACmd.NGSizeNH;
			SearchDot		+=ACmd.SearchDot;
			Count++;
		}
	}
	if(Count==0)
		return;
	BrightWidthBL	/=Count;
	BrightWidthBH	/=Count;
	BrightWidthNL	/=Count;
	BrightWidthNH	/=Count;
	NGSizeBL/=Count;
	NGSizeBH/=Count;
	NGSizeNL/=Count;
	NGSizeNH/=Count;
	SearchDot/=Count;

	double	Average , Sigma;
	CalcAveSigma(HistTable,Average ,Sigma);

	ui->horizontalSliderBrightnessN	->setValue( (BrightWidthNL+BrightWidthNH)/2/Sigma*10);
	ui->horizontalSliderBrightnessB	->setValue( (BrightWidthBL+BrightWidthBH)/2/Sigma*10);
	ui->horizontalSizeN			->setValue(10.0*log10(0.5*(double)(NGSizeNL+NGSizeNH)));
	ui->horizontalSizeB			->setValue(10.0*log10(0.5*(double)(NGSizeBL+NGSizeBH)));
	ui->horizontalSliderSearch	->setValue(SearchDot);
}

void ShowBlockListForm::on_tableWidgetLib_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetLib->currentRow();
	if(Row<0)
		return;
	int	LibType	=LibIDs[Row]->GetLibType();
	int	LibID	=LibIDs[Row]->GetLibID();
	if(ui->stackedWidgetMode->currentIndex()==1){
		ShowCurrentPosition(LibType,LibID);
	}
}

void ShowBlockListForm::on_horizontalSliderBrightnessN_valueChanged(int value)
{
	double	v=ui->horizontalSliderBrightnessN->value()/10.0;
	ui->labelBrightnessN->setText(QString::number(v,'f',2));
}

void ShowBlockListForm::on_horizontalSizeN_valueChanged(int value)
{
	double	v=ui->horizontalSizeN->value()/10.0;
	double	a=pow(10.0,v);
	NGSizeNL=NGSizeNH=a;
	ui->labelSIzeN->setText(QString::number(NGSizeNH));
}

void ShowBlockListForm::on_horizontalSliderBrightnessB_valueChanged(int value)
{
	double	v=ui->horizontalSliderBrightnessB->value()/10.0;
	ui->labelBrightnessB->setText(QString::number(v,'f',2));
}

void ShowBlockListForm::on_horizontalSizeB_valueChanged(int value)
{
	double	v=ui->horizontalSizeB->value()/10.0;
	double	a=pow(10.0,v);
	NGSizeBL=NGSizeBH=a;
	ui->labelSIzeB->setText(QString::number(NGSizeBL));
}

void ShowBlockListForm::on_horizontalSliderSearch_valueChanged(int value)
{
	SearchDot=ui->horizontalSliderSearch->value();
	ui->labelSearch->setText(QString::number(SearchDot));
}
void ShowBlockListForm::on_pushButtonSetEasyOperation_clicked()
{
 	double	Average , Sigma;
	CalcAveSigma(HistTable,Average ,Sigma);
	double	v1=ui->horizontalSliderBrightnessN->value()/10.0;
	BrightWidthNL=v1*Sigma;
	BrightWidthNH=v1*Sigma;
	double	v2=ui->horizontalSliderBrightnessB->value()/10.0;
	BrightWidthBL=v2*Sigma;
	BrightWidthBH=v2*Sigma;

	double	vN=ui->horizontalSizeN->value()/10.0;
	double	aN=pow(10.0,vN);
	NGSizeNL=NGSizeNH=aN;

	double	vB=ui->horizontalSizeB->value()/10.0;
	double	aB=pow(10.0,vB);
	NGSizeBL=NGSizeBH=aB;
	SearchDot=ui->horizontalSliderSearch->value();

	int	Row=ui->tableWidgetLib->currentRow();
	if(Row<0)
		return;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUISetStatisticByLib	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.LibType		=LibIDs[Row]->GetLibType();
		RCmd.LibID			=LibIDs[Row]->GetLibID();
		RCmd.BrightWidthBL=	BrightWidthBL;
		RCmd.BrightWidthBH=	BrightWidthBH;
		RCmd.BrightWidthNL=	BrightWidthNL;
		RCmd.BrightWidthNH=	BrightWidthNH;
		RCmd.NGSizeBL=		NGSizeBL;
		RCmd.NGSizeBH=		NGSizeBH;
		RCmd.NGSizeNL=		NGSizeNL;
		RCmd.NGSizeNH=		NGSizeNH;
		RCmd.SearchDot=		SearchDot;

		RCmd.Send(NULL,GlobalPage,0);
	}
}

bool	ShowBlockListForm::CalcAveSigma(double HistTable[256],double &Average ,double &Sigma)
{
	double	N=0;
	double	A=0;
	for(int i=0;i<256;i++){
		N+=HistTable[i];
		A+=i*HistTable[i];
	}
	if(N==0.0)
		return false;
	Average=A/N;
	double	B=0;
	for(int i=0;i<256;i++){
		B+=(i-Average)*(i-Average)*HistTable[i];
	}
	Sigma=sqrt(B/N);
	return true;
}

//=======================================================================

LayerValueCount::LayerValueCount(void)
{
	Layer		=-1;
	ValueInt	=0;
	ValueDouble	=0;
	ValueBool	=false;
	ValueType	=_ValueInt;
	Count		=0;
}

bool	LayerValueCount::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ValueInt)==false)
		return false;
	if(::Save(f,ValueDouble)==false)
		return false;
	if(::Save(f,ValueBool)==false)
		return false;
	BYTE	d=(BYTE)ValueType;
	if(::Save(f,d)==false)
		return false;

	if(::Save(f,Count)==false)
		return false;
	return true;
}

bool	LayerValueCount::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ValueInt)==false)
		return false;
	if(::Load(f,ValueDouble)==false)
		return false;
	if(::Load(f,ValueBool)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	ValueType=(EnumValueType)d;
	if(::Load(f,Count)==false)
		return false;
	return true;
}
	
void	LayerValueCountContainer::Add(int Layer ,int d)
{
	for(LayerValueCount *v=GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Layer==Layer && v->ValueType==LayerValueCount::_ValueInt && v->ValueInt==d){
			v->Count++;
			return;
		}
	}
	LayerValueCount	*V=Create();
	V->Layer	=Layer;
	V->ValueType=LayerValueCount::_ValueInt;
	V->ValueInt	=d;
	V->Count	=1;
	AppendList(V);
}

void	LayerValueCountContainer::Add(int Layer ,double d)
{
	for(LayerValueCount *v=GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Layer==Layer && v->ValueType==LayerValueCount::_ValueDouble && v->ValueDouble==d){
			v->Count++;
			return;
		}
	}
	LayerValueCount	*V=Create();
	V->Layer		=Layer;
	V->ValueType	=LayerValueCount::_ValueDouble;
	V->ValueDouble	=d;
	V->Count		=1;
	AppendList(V);
}

void	LayerValueCountContainer::Add(int Layer ,bool d)
{
	for(LayerValueCount *v=GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Layer==Layer && v->ValueType==LayerValueCount::_ValueBool && v->ValueBool==d){
			v->Count++;
			return;
		}
	}
	LayerValueCount	*V=Create();
	V->Layer	=Layer;
	V->ValueType=LayerValueCount::_ValueBool;
	V->ValueBool=d;
	V->Count	=1;
	AppendList(V);
}


//=======================================================================

GUIReqUsedLibrary::GUIReqUsedLibrary(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUIReqUsedLibrary::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckUsedLibrary	*SendBack=GetSendBack(GUIAckUsedLibrary,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		int	LibType=Ab->GetLibType();
		CmdGetUsedLibID	RCmd(GetLayersBase());
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&RCmd);

		for(IntClass *a=RCmd.LibIDs.GetFirst();a!=NULL;a=a->GetNext()){
			int	LibID=a->GetValue();
			QString	LibName;
			if(Ab->GetLibraryContainer()!=NULL){
				LibName=Ab->GetLibraryContainer()->GetLibraryName(LibID);
			}
			SendBack->LibIDs.AppendList(new AlgorithmLibraryList(LibType,LibID,LibName));
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckUsedLibrary::GUIAckUsedLibrary(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUIAckUsedLibrary::Load(QIODevice *f)
{
	if(LibIDs.Load(f)==false)
		return false;
	return true;
}
bool	GUIAckUsedLibrary::Save(QIODevice *f)
{
	if(LibIDs.Save(f)==false)
		return false;
	return true;
}

//=======================================================================

GUIReqLayerValueCount::GUIReqLayerValueCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUIReqLayerValueCount::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	ReqType=(ShowBlockListForm::InfoType)d;
	return true;
}

bool	GUIReqLayerValueCount::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	BYTE	d=(BYTE)ReqType;
	if(::Save(f,d)==false)
		return false;
	return true;
}

void	GUIReqLayerValueCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckLayerValueCount	*SendBack=GetSendBack(GUIAckLayerValueCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		AlgorithmInPagePLI		*Pg=(AlgorithmInPagePLI	*)Ab->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			AlgorithmInLayerPLI *PL=(AlgorithmInLayerPLI *)Pg->GetLayerData(Layer);
			for(AlgorithmItemPLI	*L=PL->GetFirstData();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()!=LibID)
					continue;
				BlockItem	*B=dynamic_cast<BlockItem *>(L);
				if(B!=NULL){
					switch(ReqType){
						case ShowBlockListForm::BroadDark_BrightnessWidth:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BBrightWidthL);
							break;
						case ShowBlockListForm::BroadDark_NGSize:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BOKDotL);
							break;
						case ShowBlockListForm::BroadDark_NGLength:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BOKLengthL);
							break;
						case ShowBlockListForm::BroadDark_MaxSize:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BMaxNGDotL);
							break;
						case ShowBlockListForm::BroadDark_ClusterCount:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BMinNGCountL);
							break;
						case ShowBlockListForm::BroadDark_Connection:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BConnectLen);
							break;

						case ShowBlockListForm::BroadLight_BrightnessWidth:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BBrightWidthH);
							break;
						case ShowBlockListForm::BroadLight_NGSize:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BOKDotH);
							break;
						case ShowBlockListForm::BroadLight_NGLength:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BOKLengthH);
							break;
						case ShowBlockListForm::BroadLight_MaxSize:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BMaxNGDotH);
							break;
						case ShowBlockListForm::BroadLight_ClusterCount:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BMinNGCountH);
							break;
						case ShowBlockListForm::BroadLight_Connection:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.BConnectLen);
							break;

						case ShowBlockListForm::NarrowDark_BrightnessWidth:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NBrightWidthL);
							break;
						case ShowBlockListForm::NarrowDark_NGSize:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NOKDotL);
							break;
						case ShowBlockListForm::NarrowDark_NGLength:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NOKLengthL);
							break;
						case ShowBlockListForm::NarrowDark_MaxSize	:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NMaxNGDotL);
							break;
						case ShowBlockListForm::NarrowDark_ClusterCount:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NMinNGCountL);
							break;
						case ShowBlockListForm::NarrowDark_Connection:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NConnectLen);
							break;

						case ShowBlockListForm::NarrowLight_BrightnessWidth:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NBrightWidthH);
							break;
						case ShowBlockListForm::NarrowLight_NGSize	:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NOKDotH);
							break;
						case ShowBlockListForm::NarrowLight_NGLength:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NOKLengthH);
							break;
						case ShowBlockListForm::NarrowLight_MaxSize:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NMaxNGDotH);
							break;
						case ShowBlockListForm::NarrowLight_ClusterCount:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NMinNGCountH);
							break;
						case ShowBlockListForm::NarrowLight_Connection:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.NConnectLen);
							break;

						case ShowBlockListForm::BrightAdjustment_Enable:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeAdjustable);
							break;
						case ShowBlockListForm::BrightAdjustment_DarkSide:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.AdjustBlack);
							break;
						case ShowBlockListForm::BrightAdjustment_LightSide:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.AdjustWhite);
							break;

						case ShowBlockListForm::Attribute_InspectionEffective:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeEnabled);
							break;
						case ShowBlockListForm::Attribute_AbsoluteBrightness:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeAbsoluteBright);
							break;
						case ShowBlockListForm::Attribute_Clusterize:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeNGCluster);
							break;
						case ShowBlockListForm::Attribute_Differential	:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeDiffer);
							break;
						case ShowBlockListForm::Attribute_FollowOutline:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPosition);
							break;
						case ShowBlockListForm::Attribute_OnlyMaxNGSize:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeAdoptBiggest);
							break;
						case ShowBlockListForm::Attribute_NoOutput:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeOnlyMatching);
							break;
						case ShowBlockListForm::Attribute_WhiteMask:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeWhiteMask);
							break;
						case ShowBlockListForm::Attribute_BlackMask:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeBlackMask);
							break;
						case ShowBlockListForm::Attribute_PickupFromParts:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeCenterBrightFromParts);
							break;
						case ShowBlockListForm::Attribute_ReverseLogic:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeInvertLogic);
							break;
						case ShowBlockListForm::Attribute_DetailSearch:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeSearchDetail);
							break;
						case ShowBlockListForm::Attribute_DynamicMask:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeDynamicMask);
							break;
						case ShowBlockListForm::Attribute_UseMasterImage:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeUseMasterImage);
							break;

						case ShowBlockListForm::Search_EnableWholeSearch:
							SendBack->ItemCounts.Add(Layer,(bool)B->GetThresholdR()->ThreshouldBag.PointMove.ModeCommonMovable);
							break;
						case ShowBlockListForm::Search_SelfSearchDot:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.SelfSearch);
							break;
						case ShowBlockListForm::Search_WholeSearchDot:
							SendBack->ItemCounts.Add(Layer,(int)B->GetThresholdR()->ThreshouldBag.CommonMoveDot);
							break;
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckLayerValueCount::GUIAckLayerValueCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUIAckLayerValueCount::Load(QIODevice *f)
{
	if(ItemCounts.Load(f)==false)
		return false;
	return true;
}

bool	GUIAckLayerValueCount::Save(QIODevice *f)
{
	if(ItemCounts.Save(f)==false)
		return false;
	return true;
}


//=======================================================================

GUIReqStatisticByLib::GUIReqStatisticByLib(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUIReqStatisticByLib::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUIReqStatisticByLib::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUIReqStatisticByLib::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckStatisticByLib	*SendBack=GetSendBack(GUIAckStatisticByLib,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		AlgorithmInPagePLI		*Pg=(AlgorithmInPagePLI	*)Ab->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			AlgorithmInLayerPLI *PL=(AlgorithmInLayerPLI *)Pg->GetLayerData(Layer);
			for(AlgorithmItemPLI	*L=PL->GetFirstData();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()!=LibID)
					continue;
				BlockItem	*B=dynamic_cast<BlockItem *>(L);
				if(B!=NULL){
					int	BTable[256];
					memset(BTable,0,sizeof(BTable));
					B->GetArea().MakeBrightList(BTable ,Pg->GetDotPerLine(), Pg->GetMaxLines() ,B->GetTargetBuff(),B->ShiftX,B->ShiftY);
					for(int i=0;i<256;i++){
						SendBack->HistTable[i]+=BTable[i];
					}
					SendBack->BrightWidthBL	=B->GetThresholdR()->ThreshouldBag.BBrightWidthL;
					SendBack->BrightWidthBH	=B->GetThresholdR()->ThreshouldBag.BBrightWidthH;
					SendBack->BrightWidthNL	=B->GetThresholdR()->ThreshouldBag.NBrightWidthL;
					SendBack->BrightWidthNH	=B->GetThresholdR()->ThreshouldBag.NBrightWidthH;
					SendBack->NGSizeBL		=B->GetThresholdR()->ThreshouldBag.BOKDotL;
					SendBack->NGSizeBH		=B->GetThresholdR()->ThreshouldBag.BOKDotH;
					SendBack->NGSizeNL		=B->GetThresholdR()->ThreshouldBag.NOKDotL;
					SendBack->NGSizeNH		=B->GetThresholdR()->ThreshouldBag.NOKDotH;
					SendBack->SearchDot		=B->GetThresholdR()->ThreshouldBag.SelfSearch;
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckStatisticByLib::GUIAckStatisticByLib(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<256;i++){
		HistTable[i]=0;
	}
}
bool	GUIAckStatisticByLib::Load(QIODevice *f)
{
	if(f->read((char *)HistTable,sizeof(HistTable))!=sizeof(HistTable))
		return false;
	if(::Load(f,BrightWidthBL)==false)
		return false;
	if(::Load(f,BrightWidthBH)==false)
		return false;
	if(::Load(f,BrightWidthNL)==false)
		return false;
	if(::Load(f,BrightWidthNH)==false)
		return false;
	if(::Load(f,NGSizeBL)==false)
		return false;
	if(::Load(f,NGSizeBH)==false)
		return false;
	if(::Load(f,NGSizeNL)==false)
		return false;
	if(::Load(f,NGSizeNH)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}
bool	GUIAckStatisticByLib::Save(QIODevice *f)
{
	if(f->write((const char *)HistTable,sizeof(HistTable))!=sizeof(HistTable))
		return false;
	if(::Save(f,BrightWidthBL)==false)
		return false;
	if(::Save(f,BrightWidthBH)==false)
		return false;
	if(::Save(f,BrightWidthNL)==false)
		return false;
	if(::Save(f,BrightWidthNH)==false)
		return false;
	if(::Save(f,NGSizeBL)==false)
		return false;
	if(::Save(f,NGSizeBH)==false)
		return false;
	if(::Save(f,NGSizeNL)==false)
		return false;
	if(::Save(f,NGSizeNH)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}

GUISetStatisticByLib::GUISetStatisticByLib(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUISetStatisticByLib::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,BrightWidthBL)==false)
		return false;
	if(::Load(f,BrightWidthBH)==false)
		return false;
	if(::Load(f,BrightWidthNL)==false)
		return false;
	if(::Load(f,BrightWidthNH)==false)
		return false;
	if(::Load(f,NGSizeBL)==false)
		return false;
	if(::Load(f,NGSizeBH)==false)
		return false;
	if(::Load(f,NGSizeNL)==false)
		return false;
	if(::Load(f,NGSizeNH)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}
bool	GUISetStatisticByLib::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,BrightWidthBL)==false)
		return false;
	if(::Save(f,BrightWidthBH)==false)
		return false;
	if(::Save(f,BrightWidthNL)==false)
		return false;
	if(::Save(f,BrightWidthNH)==false)
		return false;
	if(::Save(f,NGSizeBL)==false)
		return false;
	if(::Save(f,NGSizeBH)==false)
		return false;
	if(::Save(f,NGSizeNL)==false)
		return false;
	if(::Save(f,NGSizeNH)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}

void	GUISetStatisticByLib::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		AlgorithmInPagePLI		*Pg=(AlgorithmInPagePLI	*)Ab->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			AlgorithmInLayerPLI *PL=(AlgorithmInLayerPLI *)Pg->GetLayerData(Layer);
			for(AlgorithmItemPLI	*L=PL->GetFirstData();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()!=LibID)
					continue;
				BlockItem	*B=dynamic_cast<BlockItem *>(L);
				if(B!=NULL){
					B->GetThresholdW()->ThreshouldBag.BBrightWidthL	=BrightWidthBL	;
					B->GetThresholdW()->ThreshouldBag.BBrightWidthH	=BrightWidthBH	;
					B->GetThresholdW()->ThreshouldBag.NBrightWidthL	=BrightWidthNL	;
					B->GetThresholdW()->ThreshouldBag.NBrightWidthH	=BrightWidthNH	;
					B->GetThresholdW()->ThreshouldBag.BOKDotL		=NGSizeBL		;
					B->GetThresholdW()->ThreshouldBag.BOKDotH		=NGSizeBH		;
					B->GetThresholdW()->ThreshouldBag.NOKDotL		=NGSizeNL		;
					B->GetThresholdW()->ThreshouldBag.NOKDotH		=NGSizeNH		;
					B->GetThresholdW()->ThreshouldBag.SelfSearch	=SearchDot		;
				}
			}
		}
	}

}
