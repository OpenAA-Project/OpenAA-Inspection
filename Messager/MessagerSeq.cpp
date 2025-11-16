//---------------------------------------------------------------------------

#define	_USE_MATH_DEFINES
#include <math.h>
#include "Messager.h"
#include "MessagerSeq.h"
#include "XParamGlobal.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XLightClass.h"
#include "XFormOperator.h"

//---------------------------------------------------------------------------


SeqMessagerParam *SeqMessagerParamData;

SeqMessagerParam::SeqMessagerParam(LayersBase *Base) 
:SeqLocalParam(Base)
{
	SetSpecialOperand(NULL	,false	,1		,"Hide popup window in true(1)");

	DoneControlGUI=true;

	GetLayersBase()->GetMainWidget()->connect(this,SIGNAL(SignalClosePopup()),this,SLOT(SlotClosePopup()),Qt::QueuedConnection);
}

void	SeqMessagerParam::SetDataSpecialOperand(int ID, int d)
{
}
int		SeqMessagerParam::GetDataSpecialOperand(int ID)	const
{
	return 0;
}
void	SeqMessagerParam::SetDataSpecialBitOperand(int ID, bool d)
{
	if(ID==1){
		emit	SignalClosePopup();
	}
}
bool	SeqMessagerParam::GetDataSpecialBitOperand(int ID)	const
{
	return true;
}
void	SeqMessagerParam::SetDataSpecialStringOperand(int ID, QString d)
{
}
QString SeqMessagerParam::GetDataSpecialStringOperand(int ID)	const
{
	return "";
}
void	SeqMessagerParam::SetDataSpecialFloatOperand(int ID, double d)
{
}
double	SeqMessagerParam::GetDataSpecialFloatOperand(int ID)	const
{
	return 0;
}

void	SeqMessagerParam::SlotButtonClick(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.ButtonPush(formname ,controlname);
	}
	DoneControlGUI=true;
}

void	SeqMessagerParam::SlotTableWidgetSelect(QString formname ,QString controlname,int row ,int col)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.TableSelect(formname ,controlname,row ,col);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotInputEdit(QString formname ,QString controlname,QString data)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.InputEdit(formname ,controlname,data);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotInputValue(QString formname ,QString controlname,int data)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.InputValue(formname ,controlname,data);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotCheckDown(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.CheckboxChecked(formname ,controlname);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotCheckUp(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.CheckboxUnchecked(formname ,controlname);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotCheckToggle(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.CheckboxToggle(formname ,controlname);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotVisilize(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.SetVisible(formname ,controlname);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotInvisilize(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.SetInvisible(formname ,controlname);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotEnable(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.SetEnabled(formname ,controlname);
	}
	DoneControlGUI=true;
}
void	SeqMessagerParam::SlotDisable(QString formname ,QString controlname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		F.SetDisabled(formname ,controlname);
	}
	DoneControlGUI=true;
}

void	SeqMessagerParam::SlotSearchForm(QString formname)
{
	if(GetLayersBase()->GetMainWidget()!=NULL){
		FormOperator	F(GetLayersBase()->GetMainWidget());
		if(F.ExistForm(formname)==true){
			FoundForm=true;
		}
		else{
			FoundForm=false;
		}
	}
}
void	SeqMessagerParam::SlotClosePopup()
{
	Messager	*M=(Messager *)GetLayersBase()->GetMainWidget();
	if(M->PopupW!=NULL){
		M->PopupW->hide();
	}
}


//FifoIntPacket     SeqMessagerParam::SeqWriteID;

void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl)
{
	param->XSeqLocalInit(seqControl);
}

void    _SetDataSpecialOperand(SeqLocalParam *param ,int ID, int d)
{
	param->SetDataSpecialOperand(ID, d);
}

int     _GetDataSpecialOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialOperand(ID));
}

void    _SetDataSpecialBitOperand(SeqLocalParam *param ,int ID,bool d)
{
	param->SetDataSpecialBitOperand(ID, d);
}
bool     _GetDataSpecialBitOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialBitOperand(ID));
}


void _SetDataSpecialStringOperand(SeqLocalParam *param ,int ID, QString d)
{
	param->SetDataSpecialStringOperand(ID, d);
}

QString  _GetDataSpecialStringOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialStringOperand(ID));
}

void    _SetDataSpecialFloatOperand(SeqLocalParam *param ,int ID, double d)
{
}
double  _GetDataSpecialFloatOperand(SeqLocalParam *param ,int ID)
{
	return 0;
}