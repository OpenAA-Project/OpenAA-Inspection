/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShortcutKeyInvisible\ShortcutKeyInvisible.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShortcutKeyInvisible.h"
#include "ThreadSequence.h"
#include "XExecuteInspectBase.h"
#include "XRememberer.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include "DefineShortcutKeyDialog.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"ShortcutKey";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Action for shortcut key");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShortcutKeyInvisible(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"RegSysShortcutKey";
	Data[0].Pointer				 =&((ShortcutKeyInvisible *)Instance)->RegSysShortcutKey;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShortcutKeyInvisible.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}


//==================================================================================================

ShortcutKeyInfoList::ShortcutKeyInfoList(void)
{
	AddedKey	=_None;
	DLLRoot		=NULL;
	DLLName		=NULL;
	DLLInst		=NULL;
	ObjPath		=NULL;
	ObjName		=NULL;
	Action		=_NoAction;
	Numb		=0;
	Shortcut	=NULL;
}
ShortcutKeyInfoList::~ShortcutKeyInfoList(void)
{
	if(DLLRoot!=NULL){
		delete	[]DLLRoot;
	}
	if(DLLName!=NULL){
		delete	[]DLLName;
	}
	if(DLLInst!=NULL){
		delete	[]DLLInst;
	}
	if(ObjPath!=NULL){
		delete	[]ObjPath;
	}
	if(ObjName!=NULL){
		delete	[]ObjName;
	}
	DLLRoot		=NULL;
	DLLName		=NULL;
	ObjPath		=NULL;
	ObjName		=NULL;
	if(Shortcut!=NULL){
		delete	Shortcut;
	}
}
void	ShortcutKeyInfoList::SlotActivateKey()
{
	emit	SignalActivateKey(ID);
}

bool	ShortcutKeyInfoList::Save(QIODevice *f)
{
	int32	Ver=0x55AAFF00;
	if(::Save(f,Ver)==false)
		return false;
	BYTE	d=(BYTE)AddedKey;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,KeyCode.QtKeyCode)==false)
		return false;
	if(::Save(f,KeyCode.WinKeyCode)==false)
		return false;
	bool	ExistDLLRoot=(DLLRoot!=NULL)?true:false;
	if(::Save(f,ExistDLLRoot)==false)
		return false;
	if(ExistDLLRoot==true){
		int64	Len=strlen(DLLRoot)+1;
		if(::Save(f,Len)==false)
			return false;
		if(::Save(f,DLLRoot,Len)==false)
			return false;
	}
	bool	ExistDLLName=(DLLName!=NULL)?true:false;
	if(::Save(f,ExistDLLName)==false)
		return false;
	if(ExistDLLName==true){
		int64	Len=strlen(DLLName)+1;
		if(::Save(f,Len)==false)
			return false;
		if(::Save(f,DLLName,Len)==false)
			return false;
	}
	bool	ExistDLLInst=(DLLInst!=NULL)?true:false;
	if(::Save(f,ExistDLLInst)==false)
		return false;
	if(ExistDLLInst==true){
		int64	Len=strlen(DLLInst)+1;
		if(::Save(f,Len)==false)
			return false;
		if(::Save(f,DLLInst,Len)==false)
			return false;
	}
	bool	ExistObjPath=(ObjPath!=NULL)?true:false;
	if(::Save(f,ExistObjPath)==false)
		return false;
	if(ExistObjPath==true){
		int64	Len=strlen(ObjPath)+1;
		if(::Save(f,Len)==false)
			return false;
		if(::Save(f,ObjPath,Len)==false)
			return false;
	}
	bool	ExistObjName=(ObjName!=NULL)?true:false;
	if(::Save(f,ExistObjName)==false)
		return false;
	if(ExistObjName==true){
		int64	Len=strlen(ObjName)+1;
		if(::Save(f,Len)==false)
			return false;
		if(::Save(f,ObjName,Len)==false)
			return false;
	}

	d=(BYTE)Action;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,ExtraData,sizeof(ExtraData))==false)
		return false;
	return true;
}
bool	ShortcutKeyInfoList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	Ver &=0xFFFFFF00;
	if(Ver!=0x55AAFF00)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	AddedKey=(AdditionalKey)d;
	if(::Load(f,KeyCode.QtKeyCode)==false)
		return false;
	if(::Load(f,KeyCode.WinKeyCode)==false)
		return false;
	bool	ExistDLLRoot;
	if(::Load(f,ExistDLLRoot)==false)
		return false;
	if(ExistDLLRoot==true){
		int64	Len;
		if(::Load(f,Len)==false)
			return false;
		if(DLLRoot!=NULL)
			delete	[]DLLRoot;
		DLLRoot=new char[Len];
		int64 RetLen;
		if(::Load(f,DLLRoot,RetLen,Len)==false)
			return false;
	}
	bool	ExistDLLName;
	if(::Load(f,ExistDLLName)==false)
		return false;
	if(ExistDLLName==true){
		int64	Len;
		if(::Load(f,Len)==false)
			return false;
		if(DLLName!=NULL)
			delete	[]DLLName;
		DLLName=new char[Len];
		int64 RetLen;
		if(::Load(f,DLLName,RetLen,Len)==false)
			return false;
	}
	bool	ExistDLLInst;
	if(::Load(f,ExistDLLInst)==false)
		return false;
	if(ExistDLLInst==true){
		int64	Len;
		if(::Load(f,Len)==false)
			return false;
		if(DLLInst!=NULL)
			delete	[]DLLInst;
		DLLInst=new char[Len];
		int64 RetLen;
		if(::Load(f,DLLInst,RetLen,Len)==false)
			return false;
	}
	bool	ExistObjPath;
	if(::Load(f,ExistObjPath)==false)
		return false;
	if(ExistObjPath==true){
		int64	Len;
		if(::Load(f,Len)==false)
			return false;
		if(ObjPath!=NULL)
			delete	[]ObjPath;
		ObjPath=new char[Len];
		int64 RetLen;
		if(::Load(f,ObjPath,RetLen,Len)==false)
			return false;
	}
	bool	ExistObjName;
	if(::Load(f,ExistObjName)==false)
		return false;
	if(ExistObjName==true){
		int64	Len;
		if(::Load(f,Len)==false)
			return false;
		if(ObjName!=NULL)
			delete	[]ObjName;
		ObjName=new char[Len];
		int64 RetLen;
		if(::Load(f,ObjName,RetLen,Len)==false)
			return false;
	}
	if(::Load(f,d)==false)
		return false;
	Action=(ActionType)d;
	int64 RetLen;
	if(::Load(f,ExtraData,RetLen,sizeof(ExtraData))==false)
		return false;
	return true;
}
void	ShortcutKeyInfoList::CopyFrom(struct ShortcutKeyInfoList &Src)
{
	AddedKey	=Src.AddedKey;
	KeyCode		=Src.KeyCode;
	if(DLLRoot!=NULL)
		delete	[]DLLRoot;
	DLLRoot=NULL;
	if(Src.DLLRoot!=NULL){
		DLLRoot=new char[strlen(Src.DLLRoot)+1];
		strcpy(DLLRoot,Src.DLLRoot);
	}
	if(DLLName!=NULL)
		delete	[]DLLName;
	DLLName=NULL;
	if(Src.DLLName!=NULL){
		DLLName=new char[strlen(Src.DLLName)+1];
		strcpy(DLLName,Src.DLLName);
	}
	if(DLLInst!=NULL)
		delete	[]DLLInst;
	DLLInst=NULL;
	if(Src.DLLInst!=NULL){
		DLLInst=new char[strlen(Src.DLLInst)+1];
		strcpy(DLLInst,Src.DLLInst);
	}
	if(ObjPath!=NULL)
		delete	[]ObjPath;
	ObjPath=NULL;
	if(Src.ObjPath!=NULL){
		ObjPath=new char[strlen(Src.ObjPath)+1];
		strcpy(ObjPath,Src.ObjPath);
	}
	if(ObjName!=NULL)
		delete	[]ObjName;
	ObjName=NULL;
	if(Src.ObjName!=NULL){
		ObjName=new char[strlen(Src.ObjName)+1];
		strcpy(ObjName,Src.ObjName);
	}
	Action	=Src.Action;
	memcpy(ExtraData,Src.ExtraData,sizeof(ExtraData));
}

QWidget	*Find(QWidget *f, QStringList &LList ,int Point)
{
	if(LList.count()<=Point)
		return f;
	QObjectList	PList=f->children();
	QString	Str=LList[Point];
	for(int i=0;i<PList.count();i++){
		QObject	*o=PList[i];
		QWidget	*w=dynamic_cast<QWidget *>(o);
		if(w!=NULL && o->objectName()==Str){
			return Find(w, LList ,Point+1);
		}
	}
	return NULL;
}

QWidget	*ShortcutKeyInfoList::GetControl(LayersBase *Base,QWidget *MainWidget)
{
	GUIFormBase	*f=Base->FindByName(DLLRoot,DLLName,DLLInst);
	if(f==NULL)
		return NULL;
	QStringList	LList=QString(ObjPath).split('\\');
	QWidget	*d=Find(f,LList,0);
	return d;
}

void	ShortcutKeyInfoList::Execute(GUIFormBase *W)
{
	QPushButton	*LPush;
	QCheckBox	*LCheck;

	QWidget	*w=GetControl(W->GetLayersBase(),W->GetLayersBase()->GetMainWidget());
	if(w!=NULL){
		switch(Action){
		case ShortcutKeyInfoList::_PushButton:
			LPush=dynamic_cast<QPushButton *>(w);
			if(LPush!=NULL){
				LPush->click();
			}
			break;
		case ShortcutKeyInfoList::_DoubleClickList		:
			break;
		case ShortcutKeyInfoList::_SelectComboboxList	:
			break;
		case ShortcutKeyInfoList::_Check				:	
			LCheck=dynamic_cast<QCheckBox *>(w);
			if(LCheck!=NULL){
				LCheck->setChecked(true);
			}
			break;
		case ShortcutKeyInfoList::_Uncheck				:
			LCheck=dynamic_cast<QCheckBox *>(w);
			if(LCheck!=NULL){
				LCheck->setChecked(false);
			}
			break;
		case ShortcutKeyInfoList::_ToggleCheck			:
			LCheck=dynamic_cast<QCheckBox *>(w);
			if(LCheck!=NULL){
				LCheck->toggle();
			}
			break;
		case ShortcutKeyInfoList::_InputInEdit			:
			break;
		case ShortcutKeyInfoList::_OutSequenceSystemWord:	
			break;

		}
	}
}




//==================================================================================================
	



//==================================================================================================

ShortcutKeyInvisible::ShortcutKeyInvisible(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	RegSysShortcutKey	=565;
	oSysShortcutKey		=NULL;

	if(CountOfShortcut==0){
		int	k=0;
		k=MakeDefaultKey(ShortcutKeyInfoList::_None,k);
		k=MakeDefaultKey(ShortcutKeyInfoList::_Ctrl,k);
		k=MakeDefaultKey(ShortcutKeyInfoList::_Shift,k);
		k=MakeDefaultKey(ShortcutKeyInfoList::_Alt,k);
		k=MakeDefaultKey(ShortcutKeyInfoList::_CtrlShift,k);
		k=MakeDefaultKey(ShortcutKeyInfoList::_AltShift,k);
		k=MakeDefaultKey(ShortcutKeyInfoList::_AltCtrl,k);
		CountOfShortcut=k;
	}
		
	GetParamGUI()->SetParam(&KeyArray, /**/"ShortcutKeyInvisible", /**/"KeyArray"		
											 , "Keycode array"		);
		
	bool	Ret=(connect(GetParamGUI(),SIGNAL(SignalExecuteForByteArray(const QString & ,const QString & ,QByteArray &)),this,SLOT(SlotExecuteForByteArray(const QString & ,const QString & ,QByteArray &))))?true:false;

	resize(32,32);
}

ShortcutKeyInvisible::~ShortcutKeyInvisible(void)
{
}

void	ShortcutKeyInvisible::Prepare(void)
{
	if(KeyArray.count()!=0){
		QBuffer	Buff(&KeyArray);
		Buff.open(QIODevice::ReadWrite);
		int	iCountOfShortcut;
		::Load(&Buff,iCountOfShortcut);
		for(int i=0;i<iCountOfShortcut;i++){
			ShortcutKeyInfoList	Tmp;
			if(Tmp.Load(&Buff)==false)
				break;
			for(int j=0;j<CountOfShortcut;j++){
				if(ShortcutKeyDim[j].KeyCode.QtKeyCode==Tmp.KeyCode.QtKeyCode
				&& ShortcutKeyDim[j].AddedKey==Tmp.AddedKey){
					ShortcutKeyDim[j].CopyFrom(Tmp);
					break;
				}
			}
		}
	}
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqLocalParam	*Param=(SeqLocalParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			oSysShortcutKey	=new SignalOperandInt(this,RegSysShortcutKey,/**/"ShortcutKeyInvisible:oSysShortcutKey");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(oSysShortcutKey,&Error)==false){
				oSysShortcutKey->ShowErrorMessage(Error);
			}
		}
	}
	for(int i=0;i<CountOfShortcut;i++){
		ShortcutKeyDim[i].ID=i;
	}
	bool	Ret;
	for(int i=0;i<CountOfShortcut;i++){
		if(ShortcutKeyDim[i].KeyCode.QtKeyCode!=0 && ShortcutKeyDim[i].Action!=ShortcutKeyInfoList::_NoAction){
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_None)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode),this);
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_Ctrl)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode | Qt::CTRL),this);
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_Shift)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode | Qt::SHIFT),this);
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_Alt)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode | Qt::ALT),this);
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_CtrlShift)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode | Qt::CTRL | Qt::SHIFT),this);
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_AltShift)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode | Qt::ALT | Qt::SHIFT),this);
			if(ShortcutKeyDim[i].AddedKey==ShortcutKeyInfoList::_AltCtrl)
				ShortcutKeyDim[i].Shortcut=new QShortcut(QKeySequence(ShortcutKeyDim[i].KeyCode.QtKeyCode | Qt::ALT | Qt::CTRL),this);
			Ret=(connect(ShortcutKeyDim[i].Shortcut,SIGNAL(activated()),&ShortcutKeyDim[i],SLOT(SlotActivateKey())))?true:false;
			Ret=(connect(&ShortcutKeyDim[i],SIGNAL(SignalActivateKey(int)),this,SLOT(SlotActivateKey(int))))?true:false;
		}
	}
}

void	ShortcutKeyInvisible::SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	DefineShortcutKeyDialog	D(ShortcutKeyDim , CountOfShortcut , GetLayersBase());
	D.exec();

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,CountOfShortcut);
	for(int i=0;i<CountOfShortcut;i++){
		ShortcutKeyDim[i].Save(&Buff);
	}
	KeyArray=Buff.buffer();
	data=KeyArray;
}

static	int		Key;

void	ShortcutKeyInvisible::SlotActivateKey(int ID)
{
	Key=1;
	if(0<=ID && ID<CountOfShortcut){
		struct	ShortcutKeyInfoList	*K=&ShortcutKeyDim[ID];
		K->Execute(this);
	}
}

