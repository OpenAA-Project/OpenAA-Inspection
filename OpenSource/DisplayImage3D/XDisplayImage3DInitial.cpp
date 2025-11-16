#include "XDisplayImage3D.h"
#include "XGUIDLL.h"
#include "XDisplayImage3DPacket.h"



int	DisplayImage3DAlgo::SetPropertyInDLL(struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<56){
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
	Data[3].VariableNameWithRoute=/**/"Option.PickColorButton";
	Data[3].Pointer				 =&Option.PickColorButton;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"Option.DrawColorMessage";
	Data[4].Pointer				 =&Option.DrawColorMessage;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"Option.ToolManuButton";
	Data[5].Pointer				 =&Option.ToolManuButton;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"Option.MeasureButton";
	Data[6].Pointer				=&Option.MeasureButton;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"Option.DrawCrossLineButton";
	Data[7].Pointer				=&Option.DrawCrossLineButton;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"Option.UndoButton";
	Data[8].Pointer				=&Option.UndoButton;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"Option.RedoButton";
	Data[9].Pointer				=&Option.RedoButton;
	Data[10].Type				 =/**/"_ScalePositionNoShow,_ScalePositionLeftTop,_ScalePositionRightTop,_ScalePositionLeftBottom,_ScalePositionRightBottom";
	Data[10].VariableNameWithRoute=/**/"StrModeShowScale";
	Data[10].Pointer				=&StrModeShowScale;
	Data[11].Type					=/**/"TunableList";
	Data[11].VariableNameWithRoute=/**/"ImageTunableList";
	Data[11].Pointer				=&ImageTunableList;
	Data[12].Type					=/**/"int32";
	Data[12].VariableNameWithRoute=/**/"IconSize";
	Data[12].Pointer				=&IconSize;
	Data[13].Type					=/**/"int32";
	Data[13].VariableNameWithRoute=/**/"BtnW";
	Data[13].Pointer				=&BtnW;
	Data[14].Type					=/**/"int32";
	Data[14].VariableNameWithRoute=/**/"BtnH";
	Data[14].Pointer				=&BtnH;

	Data[15].Type				 =/**/"QImage";
	Data[15].VariableNameWithRoute=/**/"IconImages.NoneIcon";
	Data[15].Pointer				 =&IconImages.NoneIcon;
	Data[16].Type				 =/**/"QImage";
	Data[16].VariableNameWithRoute=/**/"IconImages.ZoomInIcon";
	Data[16].Pointer				 =&IconImages.ZoomInIcon;
	Data[17].Type				 =/**/"QImage";
	Data[17].VariableNameWithRoute=/**/"IconImages.ZoomRectIcon";
	Data[17].Pointer				 =&IconImages.ZoomRectIcon;
	Data[18].Type				 =/**/"QImage";
	Data[18].VariableNameWithRoute=/**/"IconImages.ZoomWholeIcon";
	Data[18].Pointer				 =&IconImages.ZoomWholeIcon;
	Data[19].Type				 =/**/"QImage";
	Data[19].VariableNameWithRoute=/**/"IconImages.PickColorIcon";
	Data[19].Pointer				 =&IconImages.PickColorIcon;
	Data[20].Type				 =/**/"QImage";
	Data[20].VariableNameWithRoute=/**/"IconImages.ToolManuIcon";
	Data[20].Pointer				 =&IconImages.ToolManuIcon;
	Data[21].Type				 =/**/"QImage";
	Data[21].VariableNameWithRoute=/**/"IconImages.MeasureIcon";
	Data[21].Pointer				=&IconImages.MeasureIcon;
	Data[22].Type				 =/**/"QImage";
	Data[22].VariableNameWithRoute=/**/"IconImages.DrawCrossLineIcon";
	Data[22].Pointer				=&IconImages.DrawCrossLineIcon;
	Data[23].Type				 =/**/"QImage";
	Data[23].VariableNameWithRoute=/**/"IconImages.UndoIcon";
	Data[23].Pointer				=&IconImages.UndoIcon;
	Data[24].Type				 =/**/"bool";
	Data[24].VariableNameWithRoute=/**/"ViewWindowStyle.EnableMeasure";
	Data[24].Pointer				=&ViewWindowStyle.EnableMeasure;
	Data[25].Type				 =/**/"bool";
	Data[25].VariableNameWithRoute=/**/"ViewWindowStyle.EnableToolArea";
	Data[25].Pointer				=&ViewWindowStyle.EnableToolArea;
	Data[26].Type				 =/**/"bool";
	Data[26].VariableNameWithRoute=/**/"ViewWindowStyle.EnableVScroller";
	Data[26].Pointer				=&ViewWindowStyle.EnableVScroller;
	Data[27].Type				 =/**/"bool";
	Data[27].VariableNameWithRoute=/**/"ViewWindowStyle.EnableHScroller";
	Data[27].Pointer				=&ViewWindowStyle.EnableHScroller;
	Data[28].Type				 =/**/"bool";
	Data[28].VariableNameWithRoute=/**/"ViewWindowStyle.EnableZoom";
	Data[28].Pointer				=&ViewWindowStyle.EnableZoom;
	Data[29].Type				 =/**/"bool";
	Data[29].VariableNameWithRoute=/**/"ViewWindowStyle.EnableMove";
	Data[29].Pointer				=&ViewWindowStyle.EnableMove;

	Data[30].Type					=/**/"bool";
	Data[30].VariableNameWithRoute=/**/"AlgoOptions.DrawBtn";
	Data[30].Pointer				 =&AlgoOptions.DrawBtn;
	Data[31].Type					=/**/"bool";
	Data[31].VariableNameWithRoute=/**/"AlgoOptions.SelectBtn";
	Data[31].Pointer				 =&AlgoOptions.SelectBtn;
	Data[32].Type					=/**/"bool";
	Data[32].VariableNameWithRoute=/**/"AlgoOptions.SelectMenuBtn";
	Data[32].Pointer				 =&AlgoOptions.SelectMenuBtn;
	Data[33].Type					=/**/"bool";
	Data[33].VariableNameWithRoute=/**/"AlgoOptions.MoveItemBtn";
	Data[33].Pointer				 =&AlgoOptions.MoveItemBtn;
	Data[34].Type					=/**/"bool";
	Data[34].VariableNameWithRoute=/**/"AlgoOptions.DeleteBtn";
	Data[34].Pointer				 =&AlgoOptions.DeleteBtn;
	Data[35].Type					=/**/"bool";
	Data[35].VariableNameWithRoute=/**/"AlgoOptions.LockBtn";
	Data[35].Pointer				 =&AlgoOptions.LockBtn;
	Data[36].Type					=/**/"bool";
	Data[36].VariableNameWithRoute=/**/"AlgoOptions.GroupBtn";
	Data[36].Pointer				 =&AlgoOptions.GroupBtn;
	Data[37].Type					=/**/"bool";
	Data[37].VariableNameWithRoute=/**/"AlgoOptions.CopyBtn";
	Data[37].Pointer				 =&AlgoOptions.CopyBtn;
	Data[38].Type					=/**/"bool";
	Data[38].VariableNameWithRoute=/**/"AlgoOptions.PasteBtn";
	Data[38].Pointer				 =&AlgoOptions.PasteBtn;
	Data[39].Type					=/**/"bool";
	Data[39].VariableNameWithRoute=/**/"AlgoOptions.VisibleMenuBtn";
	Data[39].Pointer			 =&AlgoOptions.VisibleMenuBtn;
	Data[40].Type					=/**/"bool";
	Data[40].VariableNameWithRoute=/**/"AlgoOptions.RotateBtn";
	Data[40].Pointer			 =&AlgoOptions.RotateBtn;
	Data[41].Type					=/**/"bool";
	Data[41].VariableNameWithRoute=/**/"AlgoOptions.MirrorBtn";
	Data[41].Pointer			 =&AlgoOptions.MirrorBtn;
	Data[42].Type				 =/**/"TunableList";
	Data[42].VariableNameWithRoute=/**/"ItemTunableList";
	Data[42].Pointer			 =&ItemTunableList;

	Data[43].Type					=/**/"QImage";
	Data[43].VariableNameWithRoute	=/**/"IconItemImages.NoneIcon";
	Data[43].Pointer				=&IconItemImages.NoneItemIcon;
	Data[44].Type					=/**/"QImage";
	Data[44].VariableNameWithRoute	=/**/"IconItemImages.DrawItemIcon";
	Data[44].Pointer				=&IconItemImages.DrawItemIcon;
	Data[45].Type					=/**/"QImage";
	Data[45].VariableNameWithRoute	=/**/"IconItemImages.SelectItemIcon";
	Data[45].Pointer				=&IconItemImages.SelectItemIcon;
	Data[46].Type					=/**/"QImage";
	Data[46].VariableNameWithRoute	=/**/"IconItemImages.SelectMenuItemIcon";
	Data[46].Pointer				=&IconItemImages.SelectMenuItemIcon;
	Data[47].Type					=/**/"QImage";
	Data[47].VariableNameWithRoute	=/**/"IconItemImages.MoveItemIcon";
	Data[47].Pointer				=&IconItemImages.MoveItemIcon;
	Data[48].Type					=/**/"QImage";
	Data[48].VariableNameWithRoute	=/**/"IconItemImages.DeleteItemIcon";
	Data[48].Pointer				=&IconItemImages.DeleteItemIcon;
	Data[49].Type					=/**/"QImage";
	Data[49].VariableNameWithRoute	=/**/"IconItemImages.LockItemIcon";
	Data[49].Pointer				=&IconItemImages.LockItemIcon;
	Data[50].Type					=/**/"QImage";
	Data[50].VariableNameWithRoute	=/**/"IconItemImages.GroupItemIcon";
	Data[50].Pointer				=&IconItemImages.GroupItemIcon;
	Data[51].Type					=/**/"QImage";
	Data[51].VariableNameWithRoute	=/**/"IconItemImages.CopyItemIcon";
	Data[51].Pointer				=&IconItemImages.CopyItemIcon;
	Data[52].Type					=/**/"QImage";
	Data[52].VariableNameWithRoute	=/**/"IconItemImages.PasteItemIcon";
	Data[52].Pointer				=&IconItemImages.PasteItemIcon;
	Data[53].Type					=/**/"QImage";
	Data[53].VariableNameWithRoute	=/**/"IconItemImages.VisibleMenuItemIcon";
	Data[53].Pointer				=&IconItemImages.VisibleMenuItemIcon;
	Data[54].Type					=/**/"QImage";
	Data[54].VariableNameWithRoute	=/**/"IconItemImages.RotateItemIcon";
	Data[54].Pointer				=&IconItemImages.RotateItemIcon;
	Data[55].Type					=/**/"QImage";
	Data[55].VariableNameWithRoute	=/**/"IconItemImages.MirrorItemIcon";
	Data[55].Pointer				=&IconItemImages.MirrorItemIcon;

	return(56);
}


void	DisplayImage3DAlgo::InitialDisplayImageInDLL(GUICmdPacketBasePointerListContainer &GUICmdContainer
											   ,LayersBase *Base 
											   ,const QString &sRoot ,const QString &sName)
{
	GUICmdContainer=new GUICmdReqBmp3D				(Base,sRoot,sName);
	GUICmdContainer=new GUICmdSendBmp3D				(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdSendPixelColor		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdReqPixelColor			(Base,sRoot,sName,DType);
	//GUICmdContainer=new GUICmdDrawColor				(Base,sRoot,sName,DType);
	//GUICmdContainer=new GUICmdDrawDot				(Base,sRoot,sName,DType);
	//GUICmdContainer=new GUICmdMoveImage				(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdRotateImage			(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdMirrorXYImage			(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdCopyImageInPhases		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdSwapImage				(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdNegPosImage			(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdCopyImageToTarget		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdCopyImageToMaster		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdCopyImageToMasterBuffN(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdTranspositionTarget	(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdReqSavingImage		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdAckSavingImage		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdRegulateBrightness	(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdGetAvrVar				(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdAckAvrVar				(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdReqClippedImage		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdSendClippedImage		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdCopyRectPacket		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdSendCopyRectPacket	(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdExecutePaste			(Base,GUICmdExecutePaste::_PurePaste,sRoot,sName);
	//GUICmdContainer=new GUICmdSwapRawToTarget		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdCopyRawToTarget		(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdReqPasteRectPacket	(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdClearImage			(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdMirrorImage			(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdPourImage				(Base,sRoot,sName);
	//GUICmdContainer=new GUICmdReplaceColorImage		(Base,sRoot,sName);
	//
	//GUICmdContainer=new GUICmdReqCopiedList			(Base,sRoot,sName,-1);	//QString("ANY"),QString("ANY"),sRoot,sName,-1);
	//GUICmdContainer=new GUICmdSendCopiedList		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	//GUICmdContainer=new GUICmdReqCopiedForSave		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	//GUICmdContainer=new GUICmdAckCopiedForSave		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	//GUICmdContainer=new GUICmdReqCopiedForDelete	(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);
	//GUICmdContainer=new GUICmdSendCopiedForLoad		(Base,sRoot,sName,-1);//QString("ANY"),QString("ANY"),-1);

}