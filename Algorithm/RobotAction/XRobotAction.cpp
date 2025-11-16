#include "XRobotAction.h"
#include "EditRobotParameterDialog.h"
#include <QBuffer>

extern	const	char	*sRoot;
extern	const	char	*sName;

RobotActionThreshold::RobotActionThreshold(RobotActionItem *parent)
	:AlgorithmThreshold(parent){}


ActionMarkBase::ActionMarkBase(LayersBase *base,RobotActionBase *aBase)
	:ServiceForLayers(base),ABase(aBase)
{
	IconP		=NULL;
	IconM		=NULL;
	Selected	=false;
	Active		=false;
}

ActionMarkBase::~ActionMarkBase(void)
{
	if(IconP!=NULL){
		delete	IconP;
		IconP=NULL;
	}
	if(IconM!=NULL){
		delete	IconM;
		IconM=NULL;
	}
}

void	ActionMarkBase::SetXY(int x ,int y)
{
	MarkPoint.x=x;
	MarkPoint.y=y;
}

void	ActionMarkBase::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	X=(MarkPoint.x+movx)*ZoomRate;
	int	Y=(MarkPoint.y+movy)*ZoomRate;
	QPainter	Pnt(&pnt);
	if(Selected==true){
		if(IconM!=NULL){
			Pnt.drawPixmap(X,Y,*IconM);
		}
	}
	else{
		if(IconP!=NULL){
			Pnt.drawPixmap(X,Y,*IconP);
		}
	}
}


bool	ActionMarkBase::Save(QIODevice *f)
{
	int32	Ver=RobotActionVersion;
	if(::Save(f,Ver)==false)		return false;
	if(MarkPoint.Save(f)==false)	return false;
	return true;
}
bool	ActionMarkBase::Load(QIODevice *f)
{
	LoadedVer=RobotActionVersion;
	if(::Load(f,LoadedVer)==false)	return false;
	if(MarkPoint.Load(f)==false)	return false;
	return true;
}

void	ActionMarkBase::CopyFrom(const ActionMarkBase &src)
{
	MarkPoint	=src.MarkPoint;
}

void	ActionMarkContainer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	for(ActionMarkBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

bool	ActionMarkContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(ActionMarkBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	ID=a->GetClassID();
		if(::Save(f,ID)==false){
			return false;
		}
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ActionMarkContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		int32	ID;
		if(::Load(f,ID)==false){
			return false;
		}
		ActionMarkBase	*a;
		if(ID==1){
			a=new ActionMarkMove(GetLayersBase(),ABase);
		}
		else
		if(ID==2){
			a=new ActionMarkCapture(GetLayersBase(),ABase);
		}
		else{
			return false;
		}

		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

//=======================================================================================

ActionMarkMove::ActionMarkMove(LayersBase *base,RobotActionBase *aBase)
	:ActionMarkBase(base,aBase)
{
	Speed=20;

	IconP=new QPixmap(/**/":Resources/MarkMoveP.png");
	IconM=new QPixmap(/**/":Resources/MarkMoveM.png");
}
QString	ActionMarkMove::GetTypeName(void)
{	
	return "移動";
}
QString	ActionMarkMove::GetAlgoLibName(void)
{
	return "";
}
QString	ActionMarkMove::GetParamStr(void)	
{
	return QString("Speed:")+QString::number(Speed,'f',2);
}

bool	ActionMarkMove::Save(QIODevice *f)
{
	if(ActionMarkBase::Save(f)==false)	return false;
	if(::Save(f,Speed)==false)			return false;
	return true;
}
bool	ActionMarkMove::Load(QIODevice *f)
{
	if(ActionMarkBase::Load(f)==false)	return false;
	if(::Load(f,Speed)==false)			return false;
	return true;
}

void	ActionMarkMove::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ActionMarkBase::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
}

ActionMarkMove &ActionMarkMove::operator=(const ActionMarkMove &src)
{
	CopyFrom(src);
	Speed	=src.Speed;
	return *this;
}

void	ActionMarkMove::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool	ActionMarkMove::ExecuteInitialAfterEdit	(void)
{
	return true;
}
bool	ActionMarkMove::ExecuteProcessing		(void)
{
	return true;
}

//=======================================================================================

ActionMarkCapture::ActionMarkCapture(LayersBase *base,RobotActionBase *aBase)
	:ActionMarkBase(base,aBase)
{
	AlgorithmType	=-1;
	AlgorithmPhase	=-1;
	AlgorithmPage	=-1;
	AlgorithmLayer	=-1;
	AlgorithmItemID	=-1;
	StopMilisec		=100;
	IconP=new QPixmap(/**/":Resources/MarkCaptureP.png");
	IconM=new QPixmap(/**/":Resources/MarkCaptureM.png");

}

QString	ActionMarkCapture::GetTypeName(void)
{	
	return "検査";
}
QString	ActionMarkCapture::GetAlgoLibName(void)
{
	AlgorithmItemRoot	*Item=ActionMarkCapture::GetOperationItem();
	if(Item!=NULL){
		AlgorithmBase	*tBase=Item->GetParentBase();
		if(tBase!=NULL){
			QString	LibName=GetLayersBase()->GetLibraryName(AlgorithmType,Item->GetLibID());
			return tBase->GetNameByCurrentLanguage()
					+QString(/**/":")
					+LibName;
		}
	}
	return /**/"";
}
QString	ActionMarkCapture::GetParamStr(void)	
{
	return QString("Stop:")+QString::number(StopMilisec,'f',2);
}

AlgorithmItemRoot	*ActionMarkCapture::GetOperationItem(void)
{
	AlgorithmBase	*tBase=GetLayersBase()->GetAlgorithmBase(AlgorithmType);
	if(tBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=tBase->GetPageDataPhase(AlgorithmPhase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(AlgorithmPage);
			if(Ap!=NULL){
				AlgorithmItemRoot	*Item=Ap->GetItemData(AlgorithmLayer ,AlgorithmItemID);
				return Item;
			}
		}
	}
	return NULL;
}

bool	ActionMarkCapture::Save(QIODevice *f)
{
	if(ActionMarkBase::Save(f)==false)	return false;
	if(::Save(f,AlgorithmType	)==false)	return false;
	if(::Save(f,AlgorithmPhase	)==false)	return false;
	if(::Save(f,AlgorithmPage	)==false)	return false;
	if(::Save(f,AlgorithmLayer	)==false)	return false;
	if(::Save(f,AlgorithmItemID	)==false)	return false;
	if(::Save(f,StopMilisec		)==false)	return false;
	return true;
}
bool	ActionMarkCapture::Load(QIODevice *f)
{
	if(ActionMarkBase::Load(f)==false)	return false;
	if(::Load(f,AlgorithmType	)==false)	return false;
	if(::Load(f,AlgorithmPhase	)==false)	return false;
	if(::Load(f,AlgorithmPage	)==false)	return false;
	if(::Load(f,AlgorithmLayer	)==false)	return false;
	if(::Load(f,AlgorithmItemID	)==false)	return false;
	if(::Load(f,StopMilisec		)==false)	return false;
	return true;
}

void	ActionMarkCapture::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ActionMarkBase::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
}

ActionMarkCapture &ActionMarkCapture::operator=(const ActionMarkCapture &src)
{
	CopyFrom(src);
	AlgorithmType	=src.AlgorithmType	;
	AlgorithmPhase	=src.AlgorithmPhase	;
	AlgorithmPage	=src.AlgorithmPage	;
	AlgorithmLayer	=src.AlgorithmLayer	;
	AlgorithmItemID	=src.AlgorithmItemID;
	StopMilisec		=src.StopMilisec	;
	return *this;
}

void	ActionMarkCapture::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool	ActionMarkCapture::ExecuteInitialAfterEdit	(void)
{
	return true;
}
bool	ActionMarkCapture::ExecuteProcessing		(void)
{
	return true;
}

//===========================================================================================


RobotActionInPage::RobotActionInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<RobotActionItem,RobotActionBase>(parent)
{
}

AlgorithmItemRoot	*RobotActionInPage::CreateItem(int ItemClassType)
{
	return new RobotActionItem();
}

void	RobotActionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdAddPalletizeItemPacket	*AddBItem=dynamic_cast<CmdAddPalletizeItemPacket *>(packet);
	//if(AddBItem!=NULL){
	//	PalletizeItem	*Item=tCreateItem(0);
	//	Item->SetArea(AddBItem->Area);
	//	Item->SetLibID(AddBItem->LibID);
	//	PalletizeBase	*BBase=tGetParentBase();
	//	AlgorithmLibraryLevelContainer	LLib(BBase);
	//	if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
	//		Item->CopyThresholdFromLibrary(&LLib);
	//		if(AppendItem(Item)==true){
	//			ImageBuffer *TargetImageList[100];
	//			GetTargetBuffList(TargetImageList);
	//			Item->ItemArea.Set(AddBItem->Area,*TargetImageList[0]);
	//			int	Dx=Item->ItemArea.GetMinX();
	//			int	Dy=Item->ItemArea.GetMinY();
	//			Item->ItemArea.MoveToNoClip(-Dx,-Dy);
	//			ExecuteInitialAfterEditInfo EInfo;
	//			Item->ExecuteInitialAfterEdit(0,0,NULL,EInfo);
	//		}
	//		else{
	//			delete	Item;
	//		}
	//	}
	//
	//	return;
	//}
}

void	RobotActionInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	RobotActionDrawAttr	*BAttr=dynamic_cast<RobotActionDrawAttr *>(Attr);
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);

	//QColor Col(255,255,0,196);
}

ExeResult	RobotActionInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePITemplate<RobotActionItem,RobotActionBase>::ExecuteStartByInspection(ExeID ,Res);
}
ExeResult	RobotActionInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	return AlgorithmInPagePITemplate<RobotActionItem,RobotActionBase>::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
ExeResult	RobotActionInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePITemplate<RobotActionItem,RobotActionBase>::ExecuteProcessing(ExeID ,Res);

	return Ret;
}


//===========================================================================================
RobotActionBase::RobotActionBase(LayersBase *Base)
:AlgorithmBase(Base),RContainer(Base,this),RobotPack(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorArea		=Qt::darkGreen;
	ColorSelected	=Qt::green;
	ColorActive		=Qt::red;

	SetParam(&ColorArea			, /**/"Color"		,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"		,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"		,/**/"ColorActive"		,"Color for Active Area");

	SetParam(&RobotParamArray, /**/"RobotActionBase", /**/"RobotParamArray"		
												, "Robot Param"		);
		
}

AlgorithmDrawAttr	*RobotActionBase::CreateDrawAttr(void)
{
	return new RobotActionDrawAttr(GetLayersBase());
}
bool	RobotActionBase::SaveUnique(QIODevice *f)
{
	if(RContainer.Save(f)==false)	return false;
	return true;
}
bool	RobotActionBase::LoadUnique(QIODevice *f)
{
	if(RContainer.Load(f)==false)	return false;
	return true;
}

void	RobotActionBase::InitialAfterParamLoaded(void)
{
	QBuffer	Buff(&RobotParamArray);
	Buff.open(QIODevice::ReadWrite);
	RobotPack.Load(&Buff);
}

void	RobotActionBase::ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	EditRobotParameterDialog	D(GetLayersBase(),this);
	D.exec();

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	RobotPack.Save(&Buff);

	RobotParamArray=Buff.buffer();
	data=RobotParamArray;
}

void	RobotActionBase::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	RContainer.Draw(pnt, movx ,movy ,ZoomRate ,Attr);
}

void	RobotActionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdRobotActionAddMove	*CmdRobotActionAddMoveVar=dynamic_cast<CmdRobotActionAddMove *>(packet);
	if(CmdRobotActionAddMoveVar!=NULL){
		ActionMarkMove	*a=new ActionMarkMove(GetLayersBase(),this);
		a->SetXY(CmdRobotActionAddMoveVar->UniversalDx ,CmdRobotActionAddMoveVar->UniversalDy);
		RContainer.AppendList(a);
		return;
	}
	CmdRobotActionAddCapture	*CmdRobotActionAddCaptureVar=dynamic_cast<CmdRobotActionAddCapture *>(packet);
	if(CmdRobotActionAddCaptureVar!=NULL){
		ActionMarkCapture	*a=new ActionMarkCapture(GetLayersBase(),this);
		a->SetXY(CmdRobotActionAddCaptureVar->UniversalDx ,CmdRobotActionAddCaptureVar->UniversalDy);
		a->AlgorithmType	=CmdRobotActionAddCaptureVar->AlgorithmType	;
		a->AlgorithmPhase	=CmdRobotActionAddCaptureVar->AlgorithmPhase	;
		a->AlgorithmPage	=CmdRobotActionAddCaptureVar->AlgorithmPage	;
		a->AlgorithmLayer	=CmdRobotActionAddCaptureVar->AlgorithmLayer	;
		a->AlgorithmItemID	=CmdRobotActionAddCaptureVar->AlgorithmItemID	;
		a->StopMilisec		=CmdRobotActionAddCaptureVar->StopMilisec;
		RContainer.AppendList(a);
		return;
	}
	CmdRobotActionModifyMove	*CmdRobotActionModifyMoveVar=dynamic_cast<CmdRobotActionModifyMove *>(packet);
	if(CmdRobotActionModifyMoveVar!=NULL){
		ActionMarkMove	*a=dynamic_cast<ActionMarkMove *>(RContainer.GetItem(CmdRobotActionModifyMoveVar->Number));
		if(a!=NULL){
			a->Speed=CmdRobotActionModifyMoveVar->Speed;
		}
		return;
	}
	CmdRobotActionModifyCapture	*CmdRobotActionModifyCaptureVar=dynamic_cast<CmdRobotActionModifyCapture *>(packet);
	if(CmdRobotActionModifyCaptureVar!=NULL){
		ActionMarkCapture	*a=dynamic_cast<ActionMarkCapture *>(RContainer.GetItem(CmdRobotActionModifyMoveVar->Number));
		if(a!=NULL){
			a->AlgorithmType	=CmdRobotActionModifyCaptureVar->AlgorithmType	;
			a->AlgorithmPhase	=CmdRobotActionModifyCaptureVar->AlgorithmPhase	;
			a->AlgorithmPage	=CmdRobotActionModifyCaptureVar->AlgorithmPage	;
			a->AlgorithmLayer	=CmdRobotActionModifyCaptureVar->AlgorithmLayer	;
			a->AlgorithmItemID	=CmdRobotActionModifyCaptureVar->AlgorithmItemID	;
			a->StopMilisec		=CmdRobotActionModifyCaptureVar->StopMilisec;
		}
		return;
	}
	CmdRobotActionClear	*CmdRobotActionClearVar=dynamic_cast<CmdRobotActionClear *>(packet);
	if(CmdRobotActionClearVar!=NULL){
		RContainer.RemoveAll();
		return;
	}
	CmdRobotTeachingMode	*CmdRobotTeachingModeVar=dynamic_cast<CmdRobotTeachingMode *>(packet);
	if(CmdRobotTeachingModeVar!=NULL){
		//RobotPack.
	}
}