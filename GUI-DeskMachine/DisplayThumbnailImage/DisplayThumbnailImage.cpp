#include "DisplayThumbnailImageResource.h"
#include "DisplayThumbnailImage.h"
#include "XGeneralFunc.h"
#include "DisplayThumbnailImagePacket.h"



char	*sRoot=/**/"Inspection";
char	*sName=/**/"DisplayThumbnailImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for starting capture");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
///	(*Base)=new GUICmdPushedStartCapture		(Base,sRoot,sName);
///	(*Base)=new GUICmdRepliedPushStartCapture	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayThumbnailImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0){
		return(-1);
	}
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"Mastered";
	Data[0].Pointer				 =&((DisplayThumbnailImage *)Instance)->Mastered;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"ColumnCount";
	Data[1].Pointer				 =&((DisplayThumbnailImage *)Instance)->ColumnCount;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"RowCount";
	Data[2].Pointer				 =&((DisplayThumbnailImage *)Instance)->RowCount;

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayThumbnailImage.png")));
}

//==================================================================================================

DisplayThumbnailImage::DisplayThumbnailImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent) ,DisplayImageHooked(this) ,LBase(Base)
{
	ThumForm		=NULL;
	MasterImage		=NULL;
	TargetImage		=NULL;

	Mastered		=true;
	ColumnCount		=3;
	wColumnCount	=0;
	RowCount		=3;
	wRowCount		=0;
	ZoomInRate		=4;
	EnableThumbnail	=true;
	EnableThumbnailMaster=true;
	NGTopToBottom	=true;
	BlinkOn			=true;
	ShowNG			=true;
	BlinkNG			=false;
	ShowFixedPhase	=-1;

	ErrorGroupTableCount=0;
	ErrorGroupTable		=NULL;
/*
	TM.setInterval(500);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
*/
	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);

	GetParamGUI()->SetParam(&RowCount,/**/"DisplayThumbnailImage",/**/"RowCount",LangSolver.GetString(DisplayThumbnailImage_LS,LID_6)/*"Row Count of Thumbnail"*/);
	GetParamGUI()->SetParam(&ColumnCount,/**/"DisplayThumbnailImage",/**/"ColumnCount",LangSolver.GetString(DisplayThumbnailImage_LS,LID_7)/*"Column Count of Thumbnail"*/);
	GetParamGUI()->SetParam(&ZoomInRate,/**/"DisplayThumbnailImage",/**/"ZoomInRate",LangSolver.GetString(DisplayThumbnailImage_LS,LID_8)/*"ZoomIn Rate of Dialog"*/);
	GetParamGUI()->SetParam(&EnableThumbnail,/**/"DisplayThumbnailImage",/**/"EnableThumbnail",LangSolver.GetString(DisplayThumbnailImage_LS,LID_9)/*"True if Thumbnail is enable"*/);
	GetParamGUI()->SetParam(&EnableThumbnailMaster,/**/"DisplayThumbnailImage",/**/"EnableThumbnailMaster",LangSolver.GetString(DisplayThumbnailImage_LS,LID_10)/*"True if Master image of Thumbnail is necessary"*/);
	GetParamGUI()->SetParam(&NGTopToBottom,/**/"DisplayThumbnailImage",/**/"NGTopToBottom",LangSolver.GetString(DisplayThumbnailImage_LS,LID_11)/*"True if NG Top to Bottom"*/);
}

DisplayThumbnailImage::~DisplayThumbnailImage(void)
{
	if(ThumForm!=NULL){
		for(int Row=0;Row<wRowCount;Row++){
			delete []ThumForm[Row];
		}
		delete []ThumForm;
		ThumForm=NULL;
	}
	delete	[]ErrorGroupTable;
}

//////////////////////////
//デバッグ
int	DebugWWWW;
int	DebugHHHH;
//////////////////////////
void	DisplayThumbnailImage::Prepare(void)
{
	if(EnableThumbnail==false){
		return;
	}

	if(ThumForm!=NULL){
		for(int Row=0;Row<wRowCount;Row++){
			for(int Column=0;Column<wColumnCount;Column++){
				gridLayout->removeWidget(ThumForm[Row][Column]);
				delete ThumForm[Row][Column];
			}
			delete []ThumForm[Row];
		}
		delete []ThumForm;
		ThumForm=NULL;
	}

	ThumForm=new ThumbnailForm**[RowCount];
	for(int Row=0;Row<RowCount;Row++){
		ThumForm[Row]=new ThumbnailForm*[ColumnCount];
		for(int Column=0;Column<ColumnCount;Column++){
			ThumForm[Row][Column]=new ThumbnailForm(LBase,this);
			ThumForm[Row][Column]->MasterCanvas.setVisible(EnableThumbnailMaster);
///			connect(&(ThumForm[Row][Column]->MasterCanvas),SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnMasterPaint(QPainter&)));
			connect(&(ThumForm[Row][Column]->MasterCanvas),SIGNAL(SignalOnPaint(QPainter &)),ThumForm[Row][Column],SLOT(SlotOnMasterPaint(QPainter&)));
			connect(&(ThumForm[Row][Column]->TargetCanvas),SIGNAL(SignalOnPaint(QPainter &)),ThumForm[Row][Column],SLOT(SlotOnTargetPaint(QPainter&)));
			gridLayout->addWidget(ThumForm[Row][Column],Row,Column,1,1);
		}
	}

	wColumnCount=ColumnCount;
	wRowCount	=RowCount;

	//DisplayNGListButtonへデータの受け渡し
	GUIFormBase	*DNGListButtonForm=GetLayersBase()->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");
	if(DNGListButtonForm!=NULL){
		CmdSetThumbnailInformation	CmdSetThumbnailInfo(GetLayersBase());
		CmdSetThumbnailInfo.ThumbnailCount=RowCount*ColumnCount;
		DNGListButtonForm->TransmitDirectly(&CmdSetThumbnailInfo);
	}
}

/////////////////////////////////////
//デバッグ確認
//static int DebugX[4]={460	,6515	,4982	,5226};
//static int DebugY[4]={6225	,6266	,6418	,6625};
//static int DebugX;
//static int DebugY;
/////////////////////////////////////

void	DisplayThumbnailImage::ShowInPlayer(int64 shownInspectionID)
{
	if(EnableThumbnail==false){
		return;
	}

	if(wColumnCount!=ColumnCount || wRowCount!=RowCount){
		Prepare();
	}
}

void	DisplayThumbnailImage::TransmitDirectly(GUIDirectMessage *packet)
{
	if(EnableThumbnail==false){
		return;
	}

	CmdSetNGInformation	*CmdSetNGInformationVer=dynamic_cast<CmdSetNGInformation *>(packet);
	if(CmdSetNGInformationVer!=NULL){
		ErrorGroupTableCount=CmdSetNGInformationVer->ErrorGroupTableCount;
/*
		double	ZoomRate;
		if(ErrorGroupTableCount>0){
			//拡大率
			DebugWWWW=ThumForm[0][0]->TargetCanvas.width();
			DebugHHHH=ThumForm[0][0]->TargetCanvas.height();
			double	zx=((double)ThumForm[0][0]->TargetCanvas.width())/((double)CmdSetNGInformationVer->NGWidth);
			double	zy=((double)ThumForm[0][0]->TargetCanvas.height())/((double)CmdSetNGInformationVer->NGHeight);
			ZoomRate=(zx>zy)?zy:zx;
		}
*/
		//ErrorGroupTableのデータを保持する
		if(ErrorGroupTable!=NULL){
			delete []ErrorGroupTable;
		}
		ErrorGroupTable=new ErrorGroup*[ErrorGroupTableCount];
		for(int i=0;i<ErrorGroupTableCount;i++){
			ErrorGroupTable[i]=CmdSetNGInformationVer->ErrorGroupTable[i];
		}
		if(wColumnCount!=ColumnCount || wRowCount!=RowCount){
			Prepare();
		}
		//ThumFormにNG中心座標と拡大率をセット
///		SetThumFormData(0,ZoomRate);
		SetThumFormData(0);
		return;
	}
	CmdSetCurrentRow	*CmdSetCurrentRowVer=dynamic_cast<CmdSetCurrentRow *>(packet);
	if(CmdSetCurrentRowVer!=NULL){
		int CurrentRow=CmdSetCurrentRowVer->CurrentRow;
		if(wColumnCount!=ColumnCount || wRowCount!=RowCount){
			Prepare();
		}
		//ThumFormにNG中心座標をセット
		SetThumFormData(CurrentRow-(CurrentRow%(RowCount*ColumnCount)),CurrentRow);
		return;
	}
	CmdShowThumbnailDialog	*CmdShowThumbnailDialogVer=dynamic_cast<CmdShowThumbnailDialog*>(packet);
	if(CmdShowThumbnailDialogVer!=NULL){
		int CurrentRow=CmdShowThumbnailDialogVer->CurrentRow;
		//ThumFormに渡す
		if(NGTopToBottom==false){
			ThumForm[(CurrentRow%(RowCount*ColumnCount))/ColumnCount][(CurrentRow%(RowCount*ColumnCount))%ColumnCount]->ExecMousePressEvent();
		}
		else{
			ThumForm[(CurrentRow%(RowCount*ColumnCount))%RowCount][(CurrentRow%(RowCount*ColumnCount))/RowCount]->ExecMousePressEvent();
		}
		return;
	}
}

void	DisplayThumbnailImage::keyPressEvent(QKeyEvent *event)
{
	GUIFormBase	*DisplayNGList=LBase->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");
	if(DisplayNGList==NULL){
		return;
	}
	QCoreApplication::sendEvent(DisplayNGList,event);
}

void	DisplayThumbnailImage::wheelEvent(QWheelEvent *event)
{
	//サムネイルをページ移動する
	GUIFormBase	*DNGListButtonForm=LBase->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");
	if(DNGListButtonForm!=NULL){
		QCoreApplication::sendEvent(DNGListButtonForm,event);
	}
}

///void	DisplayThumbnailImage::SetThumFormData(int FirstIndex,double ZoomR)
void	DisplayThumbnailImage::SetThumFormData(int FirstIndex,int CurrentRow)
{
	if(NGTopToBottom==false){
		for(int Row=0;Row<RowCount;Row++){
			for(int Column=0;Column<ColumnCount;Column++){
				if((Row*ColumnCount+Column)<ErrorGroupTableCount-FirstIndex){
					//NG座標
					ErrorGroup *e=ErrorGroupTable[FirstIndex+Row*ColumnCount+Column];
					int	ex1,ey1,ex2,ey2;
					e->GetXY(ex1,ey1,ex2,ey2);
					ThumForm[Row][Column]->SetCenterXY((ex1+ex2)>>1,(ey1+ey2)>>1);
/*
					//拡大率
					if((int)ZoomR!=0){
						ThumForm[Row][Column]->SetZoomRate(ZoomR);
					}
*/
				}
				else{
					//表示なし（データなし）
					ThumForm[Row][Column]->SetCenterXY(-1,-1);
				}
				//CurrentRow
				ThumForm[Row][Column]->SetCurrentRow(FirstIndex+Row*ColumnCount+Column);

				//表示枠対応
				if((Row*ColumnCount+Column)==(CurrentRow%(RowCount*ColumnCount))){
					ThumForm[Row][Column]->SetFrameColor(true);
				}
				else{
					ThumForm[Row][Column]->SetFrameColor(false);
				}
			}
		}
	}
	else{
		for(int Column=0;Column<ColumnCount;Column++){
			for(int Row=0;Row<RowCount;Row++){
				if((Column*RowCount+Row)<ErrorGroupTableCount-FirstIndex){
					//NG座標
					ErrorGroup *e=ErrorGroupTable[FirstIndex+Column*RowCount+Row];
					int	ex1,ey1,ex2,ey2;
					e->GetXY(ex1,ey1,ex2,ey2);
					ThumForm[Row][Column]->SetCenterXY((ex1+ex2)>>1,(ey1+ey2)>>1);
/*
					//拡大率
					if((int)ZoomR!=0){
						ThumForm[Row][Column]->SetZoomRate(ZoomR);
					}
*/
				}
				else{
					//表示なし（データなし）
					ThumForm[Row][Column]->SetCenterXY(-1,-1);
				}
				//CurrentRow
				ThumForm[Row][Column]->SetCurrentRow(FirstIndex+Column*RowCount+Row);

				//表示枠対応
				if((Column*RowCount+Row)==(CurrentRow%(RowCount*ColumnCount))){
					ThumForm[Row][Column]->SetFrameColor(true);
				}
				else{
					ThumForm[Row][Column]->SetFrameColor(false);
				}
			}
		}
	}
}

double	DisplayThumbnailImage::GetZoomRate(void)
{
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

	double	zx=((double)ThumForm[0][0]->TargetCanvas.width())/((double)globalX2);
	double	zy=((double)ThumForm[0][0]->TargetCanvas.height())/((double)globalY2);
	double	ZoomRate=(zx>zy)?zy:zx;
	return ZoomRate;
}
