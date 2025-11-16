#include "XTypeDef.h"
#include "EasyPropertyAlignmentForm.h"
#include "XIntegrationSimpleImagePanel.h"
#include "XDataInLayer.h"

//============================================================================
IntegrationCmdReqAlignmentMark::IntegrationCmdReqAlignmentMark(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqAlignmentMark::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(AreaPriority.Load(f)==false)	return false;
	if(AreaIDList.Load(f)==false)	return false;
	return true;

}
bool	IntegrationCmdReqAlignmentMark::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(AreaPriority.Save(f)==false)	return false;
	if(AreaIDList.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdReqAlignmentMark::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckAlignmentMark	*SendBack
		=GetSendBackIntegration(IntegrationCmdAckAlignmentMark,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		if(AreaIDList.GetFirst()==NULL){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(LocalPage);
				if(Ap!=NULL){
					for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
						AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(layer);
						if(AL!=NULL){
							for(XAlignmentLargeArea *a=AL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
								if(AreaPriority.IsInclude(a->Priority)==true){
									for(XAlignmentLargePointer *p=a->GPack.GetFirst();p!=NULL;p=p->GetNext()){
										XAlignmentLarge	*item=p->Point;
										int	cx,cy;
										item->GetCenter(cx,cy);
										int	x1,y1,x2,y2;
										item->GetXY(x1,y1,x2,y2);
										int	xsize=x2-x1;
										int	ysize=y2-y1;
										AlignmentLargePointList *r=NULL;
										for(r=SendBack->Marks.GetFirst();r!=NULL;r=r->GetNext()){
											if(r->Cx==cx && r->Cy==cy
											&& r->XSize==xsize && r->YSize==ysize){
												break;
											}
										}
										if(r==NULL){
											const	AlignmentLargeThreshold	*RThr=item->GetThresholdR();
											r=new AlignmentLargePointList();
											r->ID		=item->GetID();
											r->GroupNumber=item->GroupNumber;
											r->Phase	=Phase;
											r->Layer	=layer;
											r->AreaID	=a->AreaID;
											r->ItemID	=item->GetID();
											r->Page		=LocalPage;
											r->Cx		=cx;
											r->Cy		=cy;
											r->XSize	=xsize;
											r->YSize	=ysize;
											r->AlignmentLargeOnOutline	=false;
											r->MoveDotX		=RThr->MoveDotX;
											r->MoveDotY		=RThr->MoveDotY;
											r->MoveDotX2	=RThr->MoveDotX2;
											r->MoveDotY2	=RThr->MoveDotY2;
											r->SearchAround	=RThr->SearchAround;
											r->UsageGlobal	=RThr->UsageGlobal;
											r->JudgeWithBrDif=RThr->JudgeWithBrDif;
											r->CharacterMode=RThr->CharacterMode;
											SendBack->Marks.AppendList(r);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else{
			for(ListPhasePageLayerItem *t=AreaIDList.GetFirst();t!=NULL;t=t->GetNext()){
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(t->Data.Phase);
				if(Ah!=NULL){
					AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(t->Data.Page);
					if(Ap!=NULL){
						AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(t->Data.Layer);
						if(AL!=NULL){
							CmdFindAlignmentLargeArea	Cmd(GetLayersBase());
							Cmd.AreaID=t->Data.ItemID;
							AL->TransmitDirectly(&Cmd);
							XAlignmentLargeArea	*a=Cmd.Area;
							if(a!=NULL){
								for(XAlignmentLargePointer *p=a->GPack.GetFirst();p!=NULL;p=p->GetNext()){
									XAlignmentLarge	*item=p->Point;
									int	cx,cy;
									item->GetCenter(cx,cy);
									int	x1,y1,x2,y2;
									item->GetXY(x1,y1,x2,y2);
									int	xsize=x2-x1;
									int	ysize=y2-y1;
									AlignmentLargePointList *r=NULL;
									for(r=SendBack->Marks.GetFirst();r!=NULL;r=r->GetNext()){
										if(r->Cx==cx && r->Cy==cy
										&& r->XSize==xsize && r->YSize==ysize){
											break;
										}
									}
									if(r==NULL){
										const	AlignmentLargeThreshold	*RThr=item->GetThresholdR();
										r=new AlignmentLargePointList();
										r->ID		=item->GetID();
										r->GroupNumber=item->GroupNumber;
										r->Phase	=t->Data.Phase;
										r->Layer	=t->Data.Layer;
										r->AreaID	=a->AreaID;
										r->ItemID	=item->GetID();
										r->Page		=LocalPage;
										r->Cx		=cx;
										r->Cy		=cy;
										r->XSize	=xsize;
										r->YSize	=ysize;
										r->AlignmentLargeOnOutline	=false;
										r->MoveDotX		=RThr->MoveDotX;
										r->MoveDotY		=RThr->MoveDotY;
										r->MoveDotX2	=RThr->MoveDotX2;
										r->MoveDotY2	=RThr->MoveDotY2;
										r->SearchAround	=RThr->SearchAround;
										r->UsageGlobal	=RThr->UsageGlobal;
										r->JudgeWithBrDif=RThr->JudgeWithBrDif;
										r->CharacterMode=RThr->CharacterMode;
										SendBack->Marks.AppendList(r);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,slaveNo,LocalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckAlignmentMark::IntegrationCmdAckAlignmentMark(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckAlignmentMark::Load(QIODevice *f)
{
	if(Marks.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckAlignmentMark::Save(QIODevice *f)
{
	if(Marks.Save(f)==false)
		return false;
	return true;
}
//============================================================================
IntegrationCmdSetAlignmentMark::IntegrationCmdSetAlignmentMark(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetAlignmentMark::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(Mark.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdSetAlignmentMark::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(Mark.Save(f)==false)
		return false;
	return true;
}

void	IntegrationCmdSetAlignmentMark::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(Mark.Layer);
				if(AL!=NULL){
					XAlignmentLarge	*item=(XAlignmentLarge *)AL->SearchIDItem(Mark.ItemID);
					if(item!=NULL){
						AlignmentLargeThreshold	*WThr=item->GetThresholdW();
						WThr->MoveDotX		=Mark.MoveDotX;
						WThr->MoveDotY		=Mark.MoveDotY;
						WThr->MoveDotX2		=Mark.MoveDotX2;
						WThr->MoveDotY2		=Mark.MoveDotY2;
						WThr->SearchAround	=Mark.SearchAround;
						WThr->UsageGlobal	=Mark.UsageGlobal;
						WThr->JudgeWithBrDif=Mark.JudgeWithBrDif;
						WThr->CharacterMode	=Mark.CharacterMode;
					}
				}
			}
		}
	}
}

//============================================================================
IntegrationCmdReqAlignmentAreaID::IntegrationCmdReqAlignmentAreaID(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqAlignmentAreaID::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(AreaPriority.Load(f)==false)	return false;
	return true;

}
bool	IntegrationCmdReqAlignmentAreaID::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(AreaPriority.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdReqAlignmentAreaID::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckAlignmentAreaID	*SendBack
		=GetSendBackIntegration(IntegrationCmdAckAlignmentAreaID,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	SendBack->AreaID.RemoveAll();
	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
					AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(layer);
					if(AL!=NULL){
						for(XAlignmentLargeArea *a=AL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
							if(AreaPriority.IsInclude(a->Priority)==true){
								int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
								ListPhasePageLayerItem	*k=new ListPhasePageLayerItem(Phase,GlobalPage,layer,a->AreaID);
								SendBack->AreaID.AppendList(k);
							}
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,slaveNo,LocalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckAlignmentAreaID::IntegrationCmdAckAlignmentAreaID(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckAlignmentAreaID::Load(QIODevice *f)
{
	if(AreaID.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdAckAlignmentAreaID::Save(QIODevice *f)
{
	if(AreaID.Save(f)==false)	return false;
	return true;
}

//============================================================================
IntegrationCmdReqAlignmentLimitedLib::IntegrationCmdReqAlignmentLimitedLib(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqAlignmentLimitedLib::Load(QIODevice *f)
{
	if(AreaID.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdReqAlignmentLimitedLib::Save(QIODevice *f)
{
	if(AreaID.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdReqAlignmentLimitedLib::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckAlignmentLimitedLib	*SendBack
		=GetSendBackIntegration(IntegrationCmdAckAlignmentLimitedLib,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		for(ListPhasePageLayerItem *t=AreaID.GetFirst();t!=NULL;t=t->GetNext()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(t->Data.Phase);
			if(Ah!=NULL){
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(t->Data.Page);
				if(Ap!=NULL){
					AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(t->Data.Layer);
					if(AL!=NULL){
						CmdFindAlignmentLargeArea	Cmd(GetLayersBase());
						Cmd.AreaID=t->Data.ItemID;
						AL->TransmitDirectly(&Cmd);
						XAlignmentLargeArea	*a=Cmd.Area;
						if(a!=NULL){
							SendBack->LimitedLib+=a->LimitedLib;
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,slaveNo,LocalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckAlignmentLimitedLib::IntegrationCmdAckAlignmentLimitedLib(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckAlignmentLimitedLib::Load(QIODevice *f)
{
	if(LimitedLib.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdAckAlignmentLimitedLib::Save(QIODevice *f)
{
	if(LimitedLib.Save(f)==false)	return false;
	return true;
}

//============================================================================
IntegrationCmdAddAlignmentLimitedLib::IntegrationCmdAddAlignmentLimitedLib
									(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAddAlignmentLimitedLib::Load(QIODevice *f)
{
	if(AreaID.Load(f)==false)	return false;
	if(LimitedLib.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdAddAlignmentLimitedLib::Save(QIODevice *f)
{
	if(AreaID.Save(f)==false)	return false;
	if(LimitedLib.Save(f)==false)	return false;
	return true;
}
void	IntegrationCmdAddAlignmentLimitedLib::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		for(ListPhasePageLayerItem *t=AreaID.GetFirst();t!=NULL;t=t->GetNext()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(t->Data.Phase);
			if(Ah!=NULL){
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(t->Data.Page);
				if(Ap!=NULL){
					AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(t->Data.Layer);
					if(AL!=NULL){
						CmdFindAlignmentLargeArea	Cmd(GetLayersBase());
						Cmd.AreaID=t->Data.ItemID;
						AL->TransmitDirectly(&Cmd);
						XAlignmentLargeArea	*a=Cmd.Area;
						if(a!=NULL){
							a->LimitedLib.Merge(LimitedLib);
						}
					}
				}
			}
		}
	}
}

//============================================================================
IntegrationCmdDelAlignmentLimitedLib::IntegrationCmdDelAlignmentLimitedLib
									(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdDelAlignmentLimitedLib::Load(QIODevice *f)
{
	if(AreaID.Load(f)==false)	return false;
	if(LimitedLib.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdDelAlignmentLimitedLib::Save(QIODevice *f)
{
	if(AreaID.Save(f)==false)	return false;
	if(LimitedLib.Save(f)==false)	return false;
	return true;
}
void	IntegrationCmdDelAlignmentLimitedLib::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		for(ListPhasePageLayerItem *t=AreaID.GetFirst();t!=NULL;t=t->GetNext()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(t->Data.Phase);
			if(Ah!=NULL){
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(t->Data.Page);
				if(Ap!=NULL){
					AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(t->Data.Layer);
					if(AL!=NULL){
						CmdFindAlignmentLargeArea	Cmd(GetLayersBase());
						Cmd.AreaID=t->Data.ItemID;
						AL->TransmitDirectly(&Cmd);
						XAlignmentLargeArea	*a=Cmd.Area;
						if(a!=NULL){
							for(AlgorithmLibraryList *c=LimitedLib.GetFirst();c!=NULL;c=c->GetNext()){
								AlgorithmLibraryList	*d=a->LimitedLib.SearchLibrary(*c);
								if(d!=NULL){
									a->LimitedLib.RemoveList(d);
									delete	d;
								}
							}
						}
					}
				}
			}
		}
	}
}


//============================================================================
IntegrationCmdReqMakeAreaFromMask::IntegrationCmdReqMakeAreaFromMask(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqMakeAreaFromMask::Load(QIODevice *f)
{
	if(AreaPriority.Load(f)==false)	return false;
	return true;

}
bool	IntegrationCmdReqMakeAreaFromMask::Save(QIODevice *f)
{
	if(AreaPriority.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdReqMakeAreaFromMask::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				for(int page=0;page<GetPageNumb();page++){
					AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(page);
					if(Ap!=NULL){
						for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
							AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(layer);
							if(AL!=NULL){
								CmdReqMakeAreaFromMask	Cmd(GetLayersBase());
								Cmd.AreaPriority=AreaPriority;
								AL->TransmitDirectly(&Cmd);
							}
						}
					}
				}
			}
		}
	}
}

//============================================================================
IntegrationCmdReqMakeAreaFromCAD::IntegrationCmdReqMakeAreaFromCAD(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqMakeAreaFromCAD::Load(QIODevice *f)
{
	if(AreaPriority.Load(f)==false)	return false;
	return true;

}
bool	IntegrationCmdReqMakeAreaFromCAD::Save(QIODevice *f)
{
	if(AreaPriority.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdReqMakeAreaFromCAD::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				for(int page=0;page<GetPageNumb();page++){
					AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(page);
					if(Ap!=NULL){
						for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
							AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(layer);
							if(AL!=NULL){
								CmdReqMakeAreaFromCAD	Cmd(GetLayersBase());
								Cmd.AreaPriority=AreaPriority;
								AL->TransmitDirectly(&Cmd);
							}
						}
					}
				}
			}
		}
	}
}
