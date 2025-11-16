#include "FilterUDColorShift.h"
#include "XCommonFilterUDColorShift.h"
#include "SettingDialog.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="UDColorShift";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make image Upside Down and color shift";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterUDColorShift(base);
}

bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	FilterUDColorShift	*H=dynamic_cast<FilterUDColorShift *>(handle);
	SettingDialog	D(handle->GetLayersBase(),parent);
	D.Initial(H->ShiftR,H->ShiftG,H->ShiftB
			 ,H->CheckTime ,H->TimeRange
			 ,H->ShiftOffset);
	if(D.exec()==(int)true){
		H->ShiftR		=D.ShiftR;
		H->ShiftG		=D.ShiftG;
		H->ShiftB		=D.ShiftB;
		H->CheckTime	=D.CheckTime;
		H->TimeRange	=D.TimeRange;
		H->ShiftOffset	=D.ShiftOffset;
	}
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterUDColorShift::FilterUDColorShift(LayersBase *base)
:FilterClassBase(base)
{
	ShouldExecute=false;
	ShiftR	=0;
	ShiftG	=0;
	ShiftB	=0;
	VShift	=0;
	CheckTime	=true;
	TimeRange	=2000;
	ShiftOffset	=0;
}

bool	FilterUDColorShift::Initial(void)
{
	return true;
}

bool	FilterUDColorShift::Release(void)
{
	return true;
}

	
bool	FilterUDColorShift::Save(QIODevice *f)
{
	if(::Save(f,ShiftR)==false)
		return false;
	if(::Save(f,ShiftG)==false)
		return false;
	if(::Save(f,ShiftB)==false)
		return false;
	if(::Save(f,CheckTime)==false)
		return false;
	if(::Save(f,TimeRange)==false)
		return false;
	if(::Save(f,ShiftOffset)==false)
		return false;
	return true;
}
bool	FilterUDColorShift::Load(QIODevice *f)
{
	if(::Load(f,ShiftR)==false)
		return false;
	if(::Load(f,ShiftG)==false)
		return false;
	if(::Load(f,ShiftB)==false)
		return false;
	if(::Load(f,CheckTime)==false)
		return false;
	if(::Load(f,TimeRange)==false)
		return false;
	::Load(f,ShiftOffset);
	return true;
}
bool	FilterUDColorShift::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(ShouldExecute==false){
		if(BufferDimCounts>=3){
			Buff[0]->TopsideBottom(VShift+ShiftR+ShiftOffset);
			Buff[1]->TopsideBottom(VShift+ShiftG+ShiftOffset);
			Buff[2]->TopsideBottom(VShift+ShiftB+ShiftOffset);
		}
		if(BufferDimCounts==2){
			Buff[0]->TopsideBottom(VShift+ShiftR+ShiftOffset);
			Buff[1]->TopsideBottom(VShift+ShiftG+ShiftOffset);
		}
		if(BufferDimCounts==1){
			Buff[0]->TopsideBottom(VShift+ShiftR+ShiftOffset);
		}
		ShouldExecute=true;
	}
	else{
		ShouldExecute=false;
	}
	return true;
}

void	FilterUDColorShift::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdExecuteFilter	*CmdExecuteFilterVar=dynamic_cast<CmdExecuteFilter *>(packet);
	if(CmdExecuteFilterVar!=NULL){
		VShift	=CmdExecuteFilterVar->VShift;
		ShouldExecute=true;
		return;
	}
	CmdExecuteClearFilter	*CmdExecuteClearFilterVar=dynamic_cast<CmdExecuteClearFilter *>(packet);
	if(CmdExecuteClearFilterVar!=NULL){
		VShift	=CmdExecuteClearFilterVar->VShift;
		ShouldExecute=false;
		return;
	}
	CmdExecuteFilterEveryTime	*CmdExecuteFilterEveryTimeVar=dynamic_cast<CmdExecuteFilterEveryTime *>(packet);
	if(CmdExecuteFilterEveryTimeVar!=NULL){
		int	L=XDateTime::currentDateTime().secsTo(CmdExecuteFilterEveryTimeVar->MasterTime);
		if(CheckTime==false || (L>=0 && L<=TimeRange) || (L<0 && -L<=TimeRange)){
			ShouldExecute=true;
		}
		return;
	}
	CmdExecuteClearFilterEveryTime	*CmdExecuteClearFilterEveryTimeVar=dynamic_cast<CmdExecuteClearFilterEveryTime *>(packet);
	if(CmdExecuteClearFilterEveryTimeVar!=NULL){
		int	L=XDateTime::currentDateTime().secsTo(CmdExecuteClearFilterEveryTimeVar->MasterTime);
		if(CheckTime==false || (L>=0 && L<=TimeRange) || (L<0 && -L<=TimeRange)){
			ShouldExecute=false;
		}
		return;
	}
}