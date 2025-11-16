#include "XTypeDef.h"
#include "XAuthentication.h"
#include "XAuthenticationInside.h"
#include "XGUIFormBase.h"
#include "XDataInLayer.h"
#include "XBoolList.h"

AuthenticationPaper::AuthenticationPaper(GUIFormBase *f ,const QString &_AuthenticationName)
{
	AuthenticationName	=_AuthenticationName;
	CodeInHasp			=-1;
	SpanSecFromInstall	=-1;
	Form				=f;
}
AuthenticationPaper::~AuthenticationPaper(void)
{
}

void		AuthenticationPaper::SetTerm(qint64 _SpanSecFromInstall)
{
	SpanSecFromInstall=_SpanSecFromInstall;
}
qint64	AuthenticationPaper::GetTerm(void)
{
	return SpanSecFromInstall;
}

void		AuthenticationPaper::SetCodeInHasp(int id)
{
	CodeInHasp=id;
}
int			AuthenticationPaper::GetCodeInHasp(void)
{
	return CodeInHasp;
}

//====================================================================================

AuthenticationInComponent::AuthenticationInComponent(LayersBase *base)
	:ServiceForLayers(base)
{
}

AuthenticationInComponent::~AuthenticationInComponent(void)
{
	ReleaseBook();
}

void	AuthenticationInComponent::ReleaseBook(void)
{
	AuthenticationBook.RemoveAll();
}

void	AuthenticationInComponent::AddAuthentication(GUIFormBase *f 
				,const QString &_AuthenticationName
				,qint64 SpanSecFromInstall
				,int id)
{
	AuthenticationPaper	*a=new AuthenticationPaper(f,_AuthenticationName);
	a->SetTerm(SpanSecFromInstall);
	a->SetCodeInHasp(id);
	AuthenticationBook.AppendList(a);
}
void	AuthenticationInComponent::DelAuthentication(GUIFormBase *f)
{
	for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;){
		if(a->Form==f){
			AuthenticationPaper *NextA=a->GetNext();
			AuthenticationBook.RemoveList(a);
			delete	a;
			a=NextA;
		}
		else{
			a=a->GetNext();
		}
	}
}

QString	AuthenticationInComponent::GetApplicationCode(void)
{
	return ApplicationCode;
}

void	AuthenticationInComponent::SetApplicationCode(const QString &code)
{
	ApplicationCode=code;
}
bool	AuthenticationInComponent::AddInitialHasp(const QString &HaspDLLFileName,const QString &Parameter)
{
	if(GetLayersBase()->GetAuthenticationInst()!=NULL){
		return GetLayersBase()->GetAuthenticationInst()->AddInitialHasp(HaspDLLFileName,Parameter);
	}
	return true;
}
bool	AuthenticationInComponent::IsAuthenticationPassed(GUIFormBase *f
														 ,QString &FailMessage
														 ,int &ErrorCode	//Described in XErrorCode.h
														 ,const QString &_AuthenticationName
														 ,const QString &_CurrentVersion)
{
	if(f==NULL){
		QString	ProgramCode=_AuthenticationName;
		if(ProgramCode.isEmpty()==true){
			ProgramCode=GetLayersBase()->GetApplicationCode();
		}
		Mutex.lock();
		bool	Ret=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassedByProgram(ProgramCode
																							,_CurrentVersion
																							,FailMessage
																							,ErrorCode	//Described in XErrorCode.h
																							);
		Mutex.unlock();
		return Ret;
	}
	else{
		QString	FDLLRoot=f->GetDLLRoot();
		QString	FDLLName=f->GetDLLName();
		for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Form!=NULL){
				GUIFormBase *p=a->Form;
				if(p->CheckDLL(FDLLRoot,FDLLName)==true){
					QString	AAuthenticationName	=a->AuthenticationName;
					if(AAuthenticationName==_AuthenticationName || _AuthenticationName.isEmpty()==true){
						if(GetLayersBase()->GetAuthenticationInst()!=NULL){
							Mutex.lock();
							bool	Ret=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassed(*a
																										,_CurrentVersion
																										,FailMessage
																										,ErrorCode	//Described in XErrorCode.h
																										);
							Mutex.unlock();
							return Ret;
						}
					}
				}
			}
		}
	}
	return true;		
}

bool	AuthenticationInComponent::IsAuthenticationPassed(QString &FailMessage
														 ,int &ErrorCode	//Described in XErrorCode.h
														 ,const QString &_AuthenticationName
														 ,const QString &_CurrentVersion)
{
	QString	ProgramCode=_AuthenticationName;
	if(ProgramCode.isEmpty()==true){
		ProgramCode=GetLayersBase()->GetApplicationCode();
	}
	ErrorCode=0;
	int	iErrorCode=0;
	bool	b1=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassedByProgram(ProgramCode
																						,_CurrentVersion
																						,FailMessage
																						,iErrorCode	//Described in XErrorCode.h
																						);
	if(iErrorCode!=0){
		ErrorCode=iErrorCode;
	}
	bool	b2=true;	
	for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AuthenticationName==_AuthenticationName || _AuthenticationName.isEmpty()==true){
			Mutex.lock();
			bool	b=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassed(*a
																						,_CurrentVersion
																						,FailMessage
																						,iErrorCode	//Described in XErrorCode.h
																						);
			if(iErrorCode!=0){
				ErrorCode=iErrorCode;
			}
			Mutex.unlock();
			if(b==false){
				b2=false;
			}
		}
	}
	if(b1==false && b2==false){
		return false;
	}
	return true;		
}
bool	AuthenticationInComponent::IsAuthenticationPassed(GUIFormBase *f
														 ,qint64 SpanSecFromInstall
														 ,QString &FailMessage
														 ,int &ErrorCode	//Described in XErrorCode.h
														 ,const QString &_AuthenticationName
														 ,const QString &_CurrentVersion)
{
	if(f==NULL){
		QString	ProgramCode=_AuthenticationName;
		if(ProgramCode.isEmpty()==true){
			ProgramCode=GetLayersBase()->GetApplicationCode();
		}
		Mutex.lock();
		bool	Ret=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassedByProgram(ProgramCode
																							,_CurrentVersion
																							,FailMessage
																							,ErrorCode	//Described in XErrorCode.h
																							);
		Mutex.unlock();
		return Ret;
	}
	else{
		for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Form!=NULL){
				if(a->Form->GetDLLRoot()==f->GetDLLRoot()
				&& a->Form->GetDLLName()==f->GetDLLName()
				&& (a->AuthenticationName==_AuthenticationName || _AuthenticationName.isEmpty()==true)){
					qint64	tmp=a->SpanSecFromInstall;
					a->SpanSecFromInstall=SpanSecFromInstall;
					Mutex.lock();
					bool	b=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassed(*a
																							,_CurrentVersion
																							,FailMessage
																							,ErrorCode	//Described in XErrorCode.h
																							);
					Mutex.unlock();
					a->SpanSecFromInstall=tmp;
					return b;
				}
			}
		}
	}
	return true;		
}
bool	AuthenticationInComponent::IsAuthenticationPassed(qint64 SpanSecFromInstall
														 ,QString &FailMessage
														 ,int &ErrorCode	//Described in XErrorCode.h
														 ,const QString &_AuthenticationName
														 ,const QString &_CurrentVersion)
{
	for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
		if((a->Form!=NULL && a->AuthenticationName==_AuthenticationName) || _AuthenticationName.isEmpty()==true){
			qint64	tmp=a->SpanSecFromInstall;
			a->SpanSecFromInstall=SpanSecFromInstall;
			Mutex.lock();
			bool	b=GetLayersBase()->GetAuthenticationInst()->IsAuthenticationPassed(*a
																						,_CurrentVersion
																						,FailMessage
																						,ErrorCode	//Described in XErrorCode.h
																						);
			Mutex.unlock();
			a->SpanSecFromInstall=tmp;
			if(b==false){
				return false;
			}
		}
	}
	return true;		
}

qint64	AuthenticationInComponent::GetSpanSecFromInstall(GUIFormBase *f 
								,const QString &_AuthenticationName
								,int id)
{
	if(f==NULL){
		qint64	MinSpan=999999999999999;
		for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Form!=NULL){
				if(a->AuthenticationName==_AuthenticationName || _AuthenticationName.isEmpty()==true){
					if(MinSpan>a->SpanSecFromInstall){
						MinSpan=a->SpanSecFromInstall;
					}
				}
			}
		}
		return MinSpan;
	}
	else{
		for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Form!=NULL){
				if(a->Form->GetDLLRoot()==f->GetDLLRoot()
				&& a->Form->GetDLLName()==f->GetDLLName()
				&& (a->AuthenticationName==_AuthenticationName || _AuthenticationName.isEmpty()==true)){
					return a->SpanSecFromInstall;
				}
			}
		}
	}
	return -1;
}

qint64	AuthenticationInComponent::GetSpanSecFromInstall(
								 const QString &_AuthenticationName
								,int id)
{
	qint64	MinSpan=999999999999999;
	for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AuthenticationName==_AuthenticationName || _AuthenticationName.isEmpty()==true){
			if(MinSpan>a->SpanSecFromInstall){
				MinSpan=a->SpanSecFromInstall;
			}
		}
	}
	return MinSpan;
}

void	AuthenticationInComponent::TransmitDirectly(GUIDirectMessage *packet)
{
	for(AuthenticationPaper *a=AuthenticationBook.GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
	GetLayersBase()->GetAuthenticationInst()->TransmitDirectly(packet);
}

//====================================================================================
HaspInterface::HaspInterface(LayersBase *base)
	:ServiceForLayers(base)
{
	DLL_GetDLLType	=NULL;
	DLL_GetName		=NULL;
	DLL_GetVersion	=NULL;
	DLL_GetExplain	=NULL;
	DLL_CheckCopyright=NULL;

	DLL_Initial		=NULL;
	DLL_Close		=NULL;
	Handle			=NULL;
}
HaspInterface::~HaspInterface(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;
	if(DLL_Close!=NULL && Handle!=NULL){
		DLL_Close(Handle);
		Handle=NULL;
	}
	if(DllLib.isLoaded()==true){
		DllLib.unload();	//Error occurs in final DLL unload
	}
	ReEntrantDLL=false;
}

bool	HaspInterface::Initial(const QString &HaspDLLFileName ,const QString &Parameter 
								,int32 &ErrorCode)
{
	QString	FileName;
	QFileInfo fi(HaspDLLFileName);
	if(fi.suffix().isEmpty()==true){
		FileName=GetLayersBase()->GetSystemPath()+GetSeparator()
				+HaspDLLFileName+QString(".")+GetDynamicFileExt();
	}
	else{
		FileName=GetLayersBase()->GetSystemPath()+GetSeparator()
				+HaspDLLFileName;
	}
	GetLayersBase()->TestLoadDLL(FileName);

	bool	Ret=LoadDLL(FileName ,ErrorCode);
	if(Ret==false){
		return false;
	}
	Handle=DLL_Initial(GetLayersBase(),Parameter);
	if(Handle==NULL){
		return false;
	}
	return true;
}
void	HaspInterface::TransmitDirectly(GUIDirectMessage *packet)
{
	if(Handle!=NULL){
		Handle->TransmitDirectly(packet);
	}
}
bool	HaspInterface::LoadDLL(const QString &filename ,int32 &ErrorCode)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		ErrorCode=Error_Hasp_NotLoaded;
		return(false);
	}
	HaspFileName=filename;

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_Hasp_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_Hasp_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");

	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_Hasp_NoFunc_DLL_GetVersion;
		return(false);
	}
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_Hasp_NoFunc_DLL_GetSystemVersion;
		return false;
	}
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			ErrorCode=Error_DLL_FalseInCopyright;
			return false;
		}
	}

	DLL_Initial			=(HaspHandleContainer *(*)(LayersBase *base,const QString &LightParamStr))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_Hasp_NoFunc_DLL_Initial;
		return(false);
	}

	DLL_Close			=(bool (*)(HaspHandleContainer *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_Hasp_NoFunc_DLL_Close;
		return(false);
	}

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	return true;
}

//====================================================================================

AuthenticationInside::AuthenticationInside(LayersBase *base)
	:ServiceForLayers(base)
{
}

AuthenticationInside::~AuthenticationInside(void)
{
	HaspContainer.RemoveAll();
}

bool	AuthenticationInside::AddInitialHasp(const QString &HaspDLLFileName,const QString &Parameter)
{
	HaspInterface	*hasp=new HaspInterface(GetLayersBase());
	int32 ErrorCode;
	if(hasp->Initial(HaspDLLFileName ,Parameter ,ErrorCode)==false){
		delete	hasp;
		return false;
	}
	HaspContainer.AppendList(hasp);
	return true;
}
void	AuthenticationInside::TransmitDirectly(GUIDirectMessage *packet)
{
	for(HaspInterface *hasp=HaspContainer.GetFirst();hasp!=NULL;hasp=hasp->GetNext()){
		hasp->TransmitDirectly(packet);
	}
}
bool	AuthenticationInside::IsAuthenticationPassed(AuthenticationPaper &d
													,const QString &_CurrentVersion
													,QString &FailMessage
													,int &ErrorCode	//Described in XErrorCode.h
													)
{
	QString	ProgramCode=GetLayersBase()->GetApplicationCode();
	QString	DLLRoot=d.GetGUIForm()->GetDLLRoot();
	QString	DLLName=d.GetGUIForm()->GetDLLName();
	Bool3List	Result;
	QString		iFailMessage;
	for(HaspInterface *hasp=HaspContainer.GetFirst();hasp!=NULL;hasp=hasp->GetNext()){
		for(HaspHandle *h=hasp->GetHandle()->GetFirst();h!=NULL;h=h->GetNext()){
			bool3	Ret1=h->PermitByDate(DLLRoot,DLLName 
										,d.GetTerm()
										,_CurrentVersion
										,iFailMessage
										,ErrorCode	//Described in XErrorCode.h
										);
			if(Ret1==true3){
				FailMessage=iFailMessage;
				return true;
			}
			Result.Add(Ret1);
			bool3	Ret2=h->PermitByProgram(ProgramCode,_CurrentVersion,iFailMessage,ErrorCode);
			if(Ret2==true3){
				FailMessage=iFailMessage;
				return true;
			}
			Result.Add(Ret2);
			if(d.GetCodeInHasp()>=0){
				bool3	Ret3=h->PermitByID(DLLRoot,DLLName,d.GetCodeInHasp(),_CurrentVersion,iFailMessage,ErrorCode);
				if(Ret3==true3){
					FailMessage=iFailMessage;
					return true;
				}
				Result.Add(Ret3);
			}
		}
	}
	if(Result.IsInclude(false3)==true){
		return false;
	}
	return true;
}
bool	AuthenticationInside::IsAuthenticationPassedByProgram(const QString &_AuthenticationName
																,const QString &_CurrentVersion
																,QString &FailMessage
																,int &ErrorCode	//Described in XErrorCode.h
																)
{
	Bool3List	Result;
	QString		iFailMessage;
	for(HaspInterface *hasp=HaspContainer.GetFirst();hasp!=NULL;hasp=hasp->GetNext()){
		for(HaspHandle *h=hasp->GetHandle()->GetFirst();h!=NULL;h=h->GetNext()){
			bool3	Ret2=h->PermitByProgram(_AuthenticationName
											,_CurrentVersion
											,iFailMessage
											,ErrorCode);
			if(Ret2==true3){
				FailMessage=iFailMessage;
				return true;
			}
			Result.Add(Ret2);
		}
	}
	if(Result.IsInclude(false3)==true){
		return false;
	}
	return true;
}