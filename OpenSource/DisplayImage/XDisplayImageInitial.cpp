#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "SelectPasteForm.h"
#include "XGeneralDialog.h"
#include "SelectByLibraryDialog.h"
#include "ExpandedPasteForm.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include "SelectPages.h"
#include "MoveImageForm.h"
#include "SelectByOrigin.h"
#include "SelectMovePastePage.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "SaveImageOnPointDialog.h"
#include "RegulateBrightnessForm.h"
#include "XGeneralStocker.h"
#include "XJpeg2000.h"
#include "XMacroFunction.h"
#include "XDataInLayerToDisplayImage.h"

int	DisplayImage::SetPropertyInDLL(struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<51){
		return(-1);
	}
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"Option.ZoomInButton";
	Data[0].Pointer				 =&Option.ZoomInButton;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"Option.ZoomRectButton";
	Data[1].Pointer				 =&Option.ZoomRectButton;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"Option.ZoomWholeButton";
	Data[2].Pointer				 =&Option.ZoomWholeButton;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"Option.CopyRectButton";
	Data[3].Pointer				 =&Option.CopyRectButton;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"Option.PasteButton";
	Data[4].Pointer				 =&Option.PasteButton;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"Option.PickColorButton";
	Data[5].Pointer				 =&Option.PickColorButton;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"Option.DrawRectButton";
	Data[6].Pointer				 =&Option.DrawRectButton;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"Option.DrawDotButton";
	Data[7].Pointer				 =&Option.DrawDotButton;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"Option.DrawColorMessage";
	Data[8].Pointer				 =&Option.DrawColorMessage;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"Option.ToolManuButton";
	Data[9].Pointer				 =&Option.ToolManuButton;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"Option.MeasureButton";
	Data[10].Pointer				=&Option.MeasureButton;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"Option.ExpandedPasteButton";
	Data[11].Pointer				=&Option.ExpandedPasteButton;
	Data[12].Type				 =/**/"bool";
	Data[12].VariableNameWithRoute=/**/"Option.SaveImageOnRectButton";
	Data[12].Pointer				=&Option.SaveImageOnRectButton;
	Data[13].Type				 =/**/"bool";
	Data[13].VariableNameWithRoute=/**/"Option.SaveImageOnPointButton";
	Data[13].Pointer				=&Option.SaveImageOnPointButton;
	Data[14].Type				 =/**/"bool";
	Data[14].VariableNameWithRoute=/**/"Option.RegulateBrightnessButton";
	Data[14].Pointer				=&Option.RegulateBrightnessButton;
	Data[15].Type				 =/**/"bool";
	Data[15].VariableNameWithRoute=/**/"Option.RegistColorLibButton";
	Data[15].Pointer				=&Option.RegistColorLibButton;
	Data[16].Type				 =/**/"bool";
	Data[16].VariableNameWithRoute=/**/"Option.DrawCrossLineButton";
	Data[16].Pointer				=&Option.DrawCrossLineButton;
	Data[17].Type				 =/**/"bool";
	Data[17].VariableNameWithRoute=/**/"Option.LensButton";
	Data[17].Pointer				=&Option.LensButton;
	Data[18].Type				 =/**/"bool";
	Data[18].VariableNameWithRoute=/**/"Option.UndoButton";
	Data[18].Pointer				=&Option.UndoButton;
	Data[19].Type				 =/**/"bool";
	Data[19].VariableNameWithRoute=/**/"Option.RedoButton";
	Data[19].Pointer				=&Option.RedoButton;
	Data[20].Type				 =/**/"_ScalePositionNoShow,_ScalePositionLeftTop,_ScalePositionRightTop,_ScalePositionLeftBottom,_ScalePositionRightBottom";
	Data[20].VariableNameWithRoute=/**/"StrModeShowScale";
	Data[20].Pointer				=&StrModeShowScale;
	Data[21].Type					=/**/"TunableList";
	Data[21].VariableNameWithRoute=/**/"ImageTunableList";
	Data[21].Pointer				=&ImageTunableList;
	Data[22].Type					=/**/"int32";
	Data[22].VariableNameWithRoute=/**/"IconSize";
	Data[22].Pointer				=&IconSize;
	Data[23].Type					=/**/"int32";
	Data[23].VariableNameWithRoute=/**/"BtnW";
	Data[23].Pointer				=&BtnW;
	Data[24].Type					=/**/"int32";
	Data[24].VariableNameWithRoute=/**/"BtnH";
	Data[24].Pointer				=&BtnH;

	Data[25].Type				 =/**/"QImage";
	Data[25].VariableNameWithRoute=/**/"IconImages.NoneIcon";
	Data[25].Pointer				 =&IconImages.NoneIcon;
	Data[26].Type				 =/**/"QImage";
	Data[26].VariableNameWithRoute=/**/"IconImages.ZoomInIcon";
	Data[26].Pointer				 =&IconImages.ZoomInIcon;
	Data[27].Type				 =/**/"QImage";
	Data[27].VariableNameWithRoute=/**/"IconImages.ZoomRectIcon";
	Data[27].Pointer				 =&IconImages.ZoomRectIcon;
	Data[28].Type				 =/**/"QImage";
	Data[28].VariableNameWithRoute=/**/"IconImages.ZoomWholeIcon";
	Data[28].Pointer				 =&IconImages.ZoomWholeIcon;
	Data[29].Type				 =/**/"QImage";
	Data[29].VariableNameWithRoute=/**/"IconImages.CopyRectIcon";
	Data[29].Pointer				 =&IconImages.CopyRectIcon;
	Data[30].Type				 =/**/"QImage";
	Data[30].VariableNameWithRoute=/**/"IconImages.PasteIcon";
	Data[30].Pointer				 =&IconImages.PasteIcon;
	Data[31].Type				 =/**/"QImage";
	Data[31].VariableNameWithRoute=/**/"IconImages.PickColorIcon";
	Data[31].Pointer				 =&IconImages.PickColorIcon;
	Data[32].Type				 =/**/"QImage";
	Data[32].VariableNameWithRoute=/**/"IconImages.DrawRectIcon";
	Data[32].Pointer				 =&IconImages.DrawRectIcon;
	Data[33].Type				 =/**/"QImage";
	Data[33].VariableNameWithRoute=/**/"IconImages.DrawDotIcon";
	Data[33].Pointer				 =&IconImages.DrawDotIcon;
	Data[34].Type				 =/**/"QImage";
	Data[34].VariableNameWithRoute=/**/"IconImages.ToolManuIcon";
	Data[34].Pointer				 =&IconImages.ToolManuIcon;
	Data[35].Type				 =/**/"QImage";
	Data[35].VariableNameWithRoute=/**/"IconImages.MeasureIcon";
	Data[35].Pointer				=&IconImages.MeasureIcon;
	Data[36].Type				 =/**/"QImage";
	Data[36].VariableNameWithRoute=/**/"IconImages.ExpandedPasteIcon";
	Data[36].Pointer				=&IconImages.ExpandedPasteIcon;
	Data[37].Type				 =/**/"QImage";
	Data[37].VariableNameWithRoute=/**/"IconImages.SaveImageOnRectIcon";
	Data[37].Pointer				=&IconImages.SaveImageOnRectIcon;
	Data[38].Type				 =/**/"QImage";
	Data[38].VariableNameWithRoute=/**/"IconImages.SaveImageOnPointIcon";
	Data[38].Pointer				=&IconImages.SaveImageOnPointIcon;
	Data[39].Type				 =/**/"QImage";
	Data[39].VariableNameWithRoute=/**/"IconImages.RegulateBrightnessIcon";
	Data[39].Pointer				=&IconImages.RegulateBrightnessIcon;
	Data[40].Type				 =/**/"QImage";
	Data[40].VariableNameWithRoute=/**/"IconImages.WheelBarrowIcon";
	Data[40].Pointer				 =&IconImages.WheelBarrowIcon;
	Data[41].Type				 =/**/"QImage";
	Data[41].VariableNameWithRoute=/**/"IconImages.RegistColorLibIcon";
	Data[41].Pointer				=&IconImages.RegistColorLibIcon;
	Data[42].Type				 =/**/"QImage";
	Data[42].VariableNameWithRoute=/**/"IconImages.DrawCrossLineIcon";
	Data[42].Pointer				=&IconImages.DrawCrossLineIcon;
	Data[43].Type				 =/**/"QImage";
	Data[43].VariableNameWithRoute=/**/"IconImages.UndoIcon";
	Data[43].Pointer				=&IconImages.UndoIcon;
	Data[44].Type				 =/**/"bool";
	Data[44].VariableNameWithRoute=/**/"ViewWindowStyle.EnableMeasure";
	Data[44].Pointer				=&ViewWindowStyle.EnableMeasure;
	Data[45].Type				 =/**/"bool";
	Data[45].VariableNameWithRoute=/**/"ViewWindowStyle.EnableToolArea";
	Data[45].Pointer				=&ViewWindowStyle.EnableToolArea;
	Data[46].Type				 =/**/"bool";
	Data[46].VariableNameWithRoute=/**/"ViewWindowStyle.EnableVScroller";
	Data[46].Pointer				=&ViewWindowStyle.EnableVScroller;
	Data[47].Type				 =/**/"bool";
	Data[47].VariableNameWithRoute=/**/"ViewWindowStyle.EnableHScroller";
	Data[47].Pointer				=&ViewWindowStyle.EnableHScroller;
	Data[48].Type				 =/**/"bool";
	Data[48].VariableNameWithRoute=/**/"ViewWindowStyle.EnableZoom";
	Data[48].Pointer				=&ViewWindowStyle.EnableZoom;
	Data[49].Type				 =/**/"bool";
	Data[49].VariableNameWithRoute=/**/"ViewWindowStyle.EnableMove";
	Data[49].Pointer				=&ViewWindowStyle.EnableMove;
	Data[50].Type				 =/**/"bool";
	Data[50].VariableNameWithRoute=/**/"ModeShowOnlyTopTurn";
	Data[50].Pointer				=&ModeShowOnlyTopTurn;
	Data[51].Type				 =/**/"int32";
	Data[51].VariableNameWithRoute=/**/"ShowOnePage";
	Data[51].Pointer				=&ShowOnePage;
	Data[52].Type				 =/**/"int32";
	Data[52].VariableNameWithRoute=/**/"MinInterval";
	Data[52].Pointer				=&MinInterval;
	Data[53].Type				 =/**/"bool";
	Data[53].VariableNameWithRoute=/**/"RepaintContinuously";
	Data[53].Pointer				=&RepaintContinuously;
	Data[54].Type				 =/**/"bool";
	Data[54].VariableNameWithRoute=/**/"FModeRepaintOnMouseMove";
	Data[54].Pointer				=&FModeRepaintOnMouseMove;

	return(55);
}
void	DisplayImage::InitialDisplayImageInDLL(GUICmdPacketBasePointerListContainer &GUICmdContainer
											   ,LayersBase *Base 
											   ,const QString &sRoot ,const QString &sName 
											   ,DisplayImage::DisplayType DType)
{
	GUICmdContainer=new GUICmdReqBmp				(Base,sRoot,sName,DType);
	GUICmdContainer=new GUICmdSendBmp				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendPixelColor		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqPixelColor			(Base,sRoot,sName,DType);
	GUICmdContainer=new GUICmdDrawColor				(Base,sRoot,sName,DType);
	GUICmdContainer=new GUICmdDrawDot				(Base,sRoot,sName,DType);
	GUICmdContainer=new GUICmdMoveImage				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdRotateImage			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdMirrorXYImage			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyImageInPhases		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSwapImage				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdNegPosImage			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyImageToTarget		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyImageToBackGround	(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyImageToMaster		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyImageToMasterBuffN(Base,sRoot,sName);
	GUICmdContainer=new GUICmdTranspositionTarget	(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqSavingImage		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdAckSavingImage		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdRegulateBrightness	(Base,sRoot,sName);
	GUICmdContainer=new GUICmdGetAvrVar				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdAckAvrVar				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqClippedImage		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendClippedImage		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyRectPacket		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendCopyRectPacket	(Base,sRoot,sName);
	GUICmdContainer=new GUICmdExecutePaste			(Base,GUICmdExecutePaste::_PurePaste,sRoot,sName);
	GUICmdContainer=new GUICmdSwapRawToTarget		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdCopyRawToTarget		(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReqPasteRectPacket	(Base,sRoot,sName);
	GUICmdContainer=new GUICmdClearImage			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdMirrorImage			(Base,sRoot,sName);
	GUICmdContainer=new GUICmdPourImage				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdReplaceColorImage		(Base,sRoot,sName);

	GUICmdContainer=new GUICmdReqCopiedList			(Base,sRoot,sName,-1);	//QString("ANY"),QString("ANY"),sRoot,sName,-1);
	GUICmdContainer=new GUICmdSendCopiedList		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqCopiedForSave		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckCopiedForSave		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqCopiedForDelete	(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendCopiedForLoad		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);


}

static	bool	MacroZoomInOut(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	if(QString::compare(Args[2],/**/"In",Qt::CaseInsensitive)==0){
		V->ExeZoomIn(x,y);
		return true;
	}
	else if(QString::compare(Args[2],/**/"Out",Qt::CaseInsensitive)==0){
		V->ExeZoomOut(x,y);
		return true;
	}
	return false;
}
static	bool	MacroZoomRect(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	x1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	x2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ZoomRect(x1 ,y1 ,x2 ,y2);
	return true;
}

static	bool	MacroSetZoomRate(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	QString	ZStr=Args[2];
	char	RBuff[100];
	::QString2Char(ZStr ,RBuff ,sizeof(RBuff));
	double	ZoomRate;
	sscanf(RBuff,/**/"%lf",&ZoomRate);
	//double	ZoomRate=ZStr.toDouble(&ok);	//Buggy
	if(ok==false){
		return false;
	}

	V->ExeSetZoom(x ,y ,ZoomRate);
	return true;
}

static	bool	MacroZoomWhole(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->WholeButtonDown();
	return true;
}

static	bool	MacroCopyRect(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	x1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	x2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(x1,y1,x2,y2);
	V->ExeCopyRect(Area);
	return true;
}
static	bool	MacroPasteImage(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->PasteButtonDown();
	V->ExePasteImage(x-V->ClippedImageGlobalCx,y-V->ClippedImageGlobalCy);

	return true;
}
static	bool	MacroPickupColor(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExePickupColor(x,y);
	return true;
}

static	bool	MacroDrawRect(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	x1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	x2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(x1,y1,x2,y2);
	V->ExeDrawRect(Area);
	return true;
}

static	bool	MacroDrawDot(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExeDrawDot(x,y);
	return true;
}

static	bool	MacroCopyMasterImageToTarget(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotCopyImageToTarget();
	return true;
}

static	bool	MacroCopyTargetImageToMaster(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotCopyImageToMaster();
	return true;
}

static	bool	MacroMoveMasterImage(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	dx=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	dy=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExeMoveImage(dx ,dy ,true,false);
	return true;
}
static	bool	MacroMoveTargetImage(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	dx=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	dy=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExeMoveImage(dx ,dy ,false,true);
	return true;
}

static	bool	MacroUndo(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ExeUndo();
	return true;
}

static	bool	MacroRedo(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ExeRedo();
	return true;
}
static	bool	MacroClearTargetImage(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClearTargetImage();
	return true;
}

static	bool	MacroClearMasterImage(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClearMasterImage();
	return true;
}


static	bool	MacroMirrorX(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotMirrorX();
	return true;
}

static	bool	MacroMirrorY(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayImage	*V=dynamic_cast<DisplayImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotMirrorY();
	return true;
}



int32	DisplayImage::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ZoomInOut";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"In or Out");
		Functions[ret].Explain.append(/**/"ZoomIn/Out at XY");
		Functions[ret].DLL_ExcuteMacro	=MacroZoomInOut;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ZoomRect";
		Functions[ret].ArgName.append(/**/"Left");
		Functions[ret].ArgName.append(/**/"Top");
		Functions[ret].ArgName.append(/**/"Right");
		Functions[ret].ArgName.append(/**/"Bottom");
		Functions[ret].Explain.append(/**/"Zoom in rect");
		Functions[ret].DLL_ExcuteMacro	=MacroZoomRect;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetZoom";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"ZoomRate");
		Functions[ret].Explain.append(/**/"Set ZoomRate at XY");
		Functions[ret].DLL_ExcuteMacro	=MacroSetZoomRate;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ZoomWhole";
		Functions[ret].Explain.append(/**/"Zoom and fit whole image");
		Functions[ret].DLL_ExcuteMacro	=MacroZoomWhole;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CopyRect";
		Functions[ret].ArgName.append(/**/"Left");
		Functions[ret].ArgName.append(/**/"Top");
		Functions[ret].ArgName.append(/**/"Right");
		Functions[ret].ArgName.append(/**/"Bottom");
		Functions[ret].Explain.append(/**/"Copy image in rectangle");
		Functions[ret].DLL_ExcuteMacro	=MacroCopyRect;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"PasteImage";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].Explain.append(/**/"Paste image at XY");
		Functions[ret].DLL_ExcuteMacro	=MacroPasteImage;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"PickupColor";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].Explain.append(/**/"Pickup color at XY");
		Functions[ret].DLL_ExcuteMacro	=MacroPickupColor;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DrawRect";
		Functions[ret].ArgName.append(/**/"Left");
		Functions[ret].ArgName.append(/**/"Top");
		Functions[ret].ArgName.append(/**/"Right");
		Functions[ret].ArgName.append(/**/"Bottom");
		Functions[ret].Explain.append(/**/"Draw in rectangle");
		Functions[ret].DLL_ExcuteMacro	=MacroDrawRect;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DrawDot";
		Functions[ret].ArgName.append(/**/"GlobalX");
		Functions[ret].ArgName.append(/**/"GlobalY");
		Functions[ret].Explain.append(/**/"Draw one pixel");
		Functions[ret].DLL_ExcuteMacro	=MacroDrawDot;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CopyMasterImageToTarget";
		Functions[ret].Explain.append(/**/"Copy master image to target");
		Functions[ret].DLL_ExcuteMacro	=MacroCopyMasterImageToTarget;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CopyTargetImageToMaster";
		Functions[ret].Explain.append(/**/"Copy target image to master");
		Functions[ret].DLL_ExcuteMacro	=MacroCopyTargetImageToMaster;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveMasterImage";
		Functions[ret].ArgName.append(/**/"dX");
		Functions[ret].ArgName.append(/**/"dY");
		Functions[ret].Explain.append(/**/"Move master image to dX,dY");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveMasterImage;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveTargetImage";
		Functions[ret].ArgName.append(/**/"dX");
		Functions[ret].ArgName.append(/**/"dY");
		Functions[ret].Explain.append(/**/"Move target image to dX,dY");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveTargetImage;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Undo";
		Functions[ret].Explain.append(/**/"Undo");
		Functions[ret].DLL_ExcuteMacro	=MacroUndo;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Redo";
		Functions[ret].Explain.append(/**/"Redo");
		Functions[ret].DLL_ExcuteMacro	=MacroRedo;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearTargetImage";
		Functions[ret].Explain.append(/**/"Clear target image");
		Functions[ret].DLL_ExcuteMacro	=MacroClearTargetImage;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearMasterImage";
		Functions[ret].Explain.append(/**/"Clear master image");
		Functions[ret].DLL_ExcuteMacro	=MacroClearMasterImage;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MirrorX";
		Functions[ret].Explain.append(/**/"Mirror image horizontally");
		Functions[ret].DLL_ExcuteMacro	=MacroMirrorX;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MirrorY";
		Functions[ret].Explain.append(/**/"Mirror image vertically");
		Functions[ret].DLL_ExcuteMacro	=MacroMirrorY;
		ret++;
	}
	return ret;
}
