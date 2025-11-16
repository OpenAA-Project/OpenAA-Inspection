#include "EasyPropertyRasterForm.h"
#include "XRasterPacket.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "EasyRasterImagePanel.h"
#include "swap.h"
#include "XGUIRasterPacket.h"
#include "XMaskingLibrary.h"
#include "XMasking.h"
#include "XDatabaseLoader.h"
#include <QMessageBox>
#include "XGeneralFunc.h"

//=================================================================================================

IntegrationCmdLoadRaster::IntegrationCmdLoadRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdLoadRaster::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,RasterData)==false)
		return false;
	return true;
}
bool	IntegrationCmdLoadRaster::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,RasterData)==false)
		return false;
	return true;
}

void	IntegrationCmdLoadRaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*FormP=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(FormP!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)FormP;
		W->SlotSelectAll();
		W->DeleteBtnDown();
	}

	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdLoadRaster	Cmd(GetLayersBase());
		Cmd.FileName	=FileName;
		Cmd.pData		=&RasterData;
		Form->TransmitDirectly(&Cmd);
	}

	GUIFormBase	*Form2=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form2!=NULL){
		DisplayImageWithAlgorithm	*W=dynamic_cast<DisplayImageWithAlgorithm *>(Form2);
		if(W!=NULL){
			W->ExecuteReleaseAllSelection();
		}
	}

	SendAck(slaveNo);
}
//=================================================================================================

IntegrationCmdRotate::IntegrationCmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdRotate::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdRasterRotateInCenter		Cmd(GetLayersBase());
		Cmd.Angle	=90.0;//M_PI/2;
		Form->TransmitDirectly(&Cmd);
	}
	GUIFormBase	*Form2=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form2!=NULL){
		DisplayImageWithAlgorithm	*W=dynamic_cast<DisplayImageWithAlgorithm *>(Form2);
		if(W!=NULL){
			W->ExecuteReleaseAllSelection();
		}
	}

	SendAck(slaveNo);
}
//=================================================================================================
IntegrationCmdExtend::IntegrationCmdExtend(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdExtend::Load(QIODevice *f)
{
	if(::Load(f,ZoomX)==false)
		return false;
	if(::Load(f,ZoomY)==false)
		return false;
	if(::Load(f,YShear)==false)
		return false;
	return true;

}
bool	IntegrationCmdExtend::Save(QIODevice *f)
{
	if(::Save(f,ZoomX)==false)
		return false;
	if(::Save(f,ZoomY)==false)
		return false;
	if(::Save(f,YShear)==false)
		return false;
	return true;

}
void	IntegrationCmdExtend::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdRasterZoomInCenter		Cmd(GetLayersBase());
		Cmd.XZoomDir	=ZoomX;
		Cmd.YZoomDir	=ZoomY;
		Form->TransmitDirectly(&Cmd);

		CmdReqRasterArea	ACmd(GetLayersBase());
		Form->TransmitDirectly(&ACmd);

		CmdRasterShear		SCmd(GetLayersBase());
		SCmd.XMode		=false;
		SCmd.Shear		=YShear;
		SCmd.CenterX	=(ACmd.MinX+ACmd.MaxX)/2;
		SCmd.CenterY	=(ACmd.MinY+ACmd.MaxY)/2;
		Form->TransmitDirectly(&SCmd);
	}
	
	GUIFormBase	*Form2=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form2!=NULL){
		DisplayImageWithAlgorithm	*W=dynamic_cast<DisplayImageWithAlgorithm *>(Form2);
		if(W!=NULL){
			W->ExecuteReleaseAllSelection();
		}
	}

	SendAck(slaveNo);
}
//=================================================================================================
IntegrationCmdAutoGenerate::IntegrationCmdAutoGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAutoGenerate::Load(QIODevice *f)
{
	if(ColorCode.Load(f)==false)
		return false;
	if(::Load(f,Color)==false)
		return false;
	if(::Load(f,GenLibType)==false)
		return false;
	if(::Load(f,GenLibID)==false)
		return false;
	return true;

}
bool	IntegrationCmdAutoGenerate::Save(QIODevice *f)
{
	if(ColorCode.Save(f)==false)
		return false;
	if(::Save(f,Color)==false)
		return false;
	if(::Save(f,GenLibType)==false)
		return false;
	if(::Save(f,GenLibID)==false)
		return false;
	return true;

}
void	IntegrationCmdAutoGenerate::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	//if(Form!=NULL){
	//	CmdMakeAlgoByColor		Cmd(GetLayersBase());
	//	Cmd.ColorCode	=ColorCode;
	//	Cmd.Color		=Color;
	//	Cmd.LibType		=GenLibType;
	//	Cmd.LibID		=GenLibID;
	//	Form->TransmitDirectly(&Cmd);
	//}
	SendAck(slaveNo);
}

//=================================================================================================
IntegrationCmdXMirror::IntegrationCmdXMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdXMirror::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdRasterMirrorInCenter		Cmd(GetLayersBase());
		Cmd.XMode	=true;
		Form->TransmitDirectly(&Cmd);
	}
	GUIFormBase	*Form2=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form2!=NULL){
		DisplayImageWithAlgorithm	*W=dynamic_cast<DisplayImageWithAlgorithm *>(Form2);
		if(W!=NULL){
			W->ExecuteReleaseAllSelection();
		}
	}

	SendAck(slaveNo);
}
//=================================================================================================
IntegrationCmdYMirror::IntegrationCmdYMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdYMirror::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdRasterMirrorInCenter		Cmd(GetLayersBase());
		Cmd.XMode	=false;
		Form->TransmitDirectly(&Cmd);
	}
	GUIFormBase	*Form2=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form2!=NULL){
		DisplayImageWithAlgorithm	*W=dynamic_cast<DisplayImageWithAlgorithm *>(Form2);
		if(W!=NULL){
			W->ExecuteReleaseAllSelection();
		}
	}

	SendAck(slaveNo);
}

//=================================================================================================
IntegrationCmdRasterDeleteAllItem::IntegrationCmdRasterDeleteAllItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
								  
void	IntegrationCmdRasterDeleteAllItem::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)Form;
		W->SlotSelectAll();
		W->DeleteBtnDown();
	}
	SendAck(slaveNo);
}
//=================================================================================================
IntegrationCmdTilt::IntegrationCmdTilt(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdTilt::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;

	return true;

}
bool	IntegrationCmdTilt::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;

	return true;

}
void	IntegrationCmdTilt::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdRasterRotateInCenter		Cmd(GetLayersBase());
		Cmd.Angle	=180.0*Radian/M_PI;
		Form->TransmitDirectly(&Cmd);
	}
	GUIFormBase	*Form2=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form2!=NULL){
		DisplayImageWithAlgorithm	*W=dynamic_cast<DisplayImageWithAlgorithm *>(Form2);
		if(W!=NULL){
			W->ExecuteReleaseAllSelection();
		}
	}

	SendAck(slaveNo);
}

//=================================================================================================

IntegrationCmdMoveXY::IntegrationCmdMoveXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdMoveXY::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	return true;
}
bool	IntegrationCmdMoveXY::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	return true;
}

void	IntegrationCmdMoveXY::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)Form;
		W->ExecuteMove(MovX,MovY);
	}
	SendAck(slaveNo);
}

//=================================================================================================

IntegrationCmdDelMaskByCAD::IntegrationCmdDelMaskByCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdDelMaskByCAD::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdRasterDelMaskByCAD		Cmd(GetLayersBase());
		Form->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}

//=================================================================================================
IntegrationCmdAddRegArea::IntegrationCmdAddRegArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAddRegArea::Load(QIODevice *f)
{
	if(AddedArea.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAddRegArea::Save(QIODevice *f)
{
	if(AddedArea.Save(f)==false)
		return false;
	return true;
}

void	IntegrationCmdAddRegArea::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdAddRegArea		Cmd(GetLayersBase());
		Cmd.AddedArea	=AddedArea;
		Form->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}

IntegrationCmdAddRegColorArea::IntegrationCmdAddRegColorArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAddRegColorArea::Load(QIODevice *f)
{
	if(PickupArea.Load(f)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	IntegrationCmdAddRegColorArea::Save(QIODevice *f)
{
	if(PickupArea.Save(f)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	IntegrationCmdAddRegColorArea::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdAddRegColorArea		Cmd(GetLayersBase());
		Cmd.PickupArea	=PickupArea;
		Cmd.LibID		=LibID;
		Form->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}

//=================================================================================================
IntegrationCmdReqElementInfo::IntegrationCmdReqElementInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdReqElementInfo::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckElementInfo	*SendBack=GetSendBackIntegration(IntegrationCmdAckElementInfo,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdReqElementInfo		Cmd(GetLayersBase());
		Form->TransmitDirectly(&Cmd);
		SendBack->Elements		=Cmd.Elements;
		SendBack->ElementIDList	=Cmd.ElementIDList;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckElementInfo::IntegrationCmdAckElementInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckElementInfo::Save(QIODevice *f)
{
	if(Elements.Save(f)==false)
		return false;
	if(ElementIDList.Save(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckElementInfo::Load(QIODevice *f)
{
	if(Elements.Load(f)==false)
		return false;
	if(ElementIDList.Load(f)==false)
		return false;
	return true;
}


IntegrationCmdSetCurrentElementID::IntegrationCmdSetCurrentElementID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	CurrentElementID=-1;
}
bool	IntegrationCmdSetCurrentElementID::Save(QIODevice *f)
{
	if(::Save(f,CurrentElementID)==false)
		return false;
	return true;
}
bool	IntegrationCmdSetCurrentElementID::Load(QIODevice *f)
{
	if(::Load(f,CurrentElementID)==false)
		return false;
	return true;
}
void	IntegrationCmdSetCurrentElementID::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdSetCurrentElementID		Cmd(GetLayersBase());
		Cmd.CurrentElementID=CurrentElementID;
		Form->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}

//=================================================================================================
IntegrationCmdSetRegColor::IntegrationCmdSetRegColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetRegColor::Save(QIODevice *f)
{
	if(::Save(f,ModeRegArea)==false)
		return false;
	if(::Save(f,ModeRegColor)==false)
		return false;
	return true;
}
bool	IntegrationCmdSetRegColor::Load(QIODevice *f)
{
	if(::Load(f,ModeRegArea)==false)
		return false;
	if(::Load(f,ModeRegColor)==false)
		return false;
	return true;
}
void	IntegrationCmdSetRegColor::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"EasyPropertyRaster",/**/"");
	if(Form!=NULL){
		Form->TransmitDirectly(this);
	}
	SendAck(slaveNo);
}

//=================================================================================================
IntegrationCmdGeneraeRasterAlgorithm::IntegrationCmdGeneraeRasterAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdGeneraeRasterAlgorithm::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdGeneraeRasterAlgorithm		Cmd(GetLayersBase());
		Form->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}

IntegrationCmdDeleteRegColor::IntegrationCmdDeleteRegColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdDeleteRegColor::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ElementID)==false)
		return false;
	return true;
}
bool	IntegrationCmdDeleteRegColor::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ElementID)==false)
		return false;
	return true;
}

void	IntegrationCmdDeleteRegColor::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyRaster",/**/"");
	if(Form!=NULL){
		CmdDeleteRegColor		Cmd(GetLayersBase());
		Cmd.Page=Page;
		Cmd.ElementID=ElementID;
		Form->TransmitDirectly(&Cmd);
	}
	SendAck(slaveNo);
}
