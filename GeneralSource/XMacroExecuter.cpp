#include "XTypeDef.h"
#include "XMacroExecuter.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XMacroFunction.h"

static	char	*SkipSpace(char *fp)
{
	while((*fp==' ') || (*fp=='\t')){
		fp++;
	}
	return fp;
}

static	char	*CutWord(char *fp,const char *sep,QString &Ret)
{
	char	Buff[1000];
	char	*cp;
	char	*hp;
	fp=SkipSpace(fp);
	if(*fp=='\"'){
		fp++;
		for(cp=fp;*cp!=0;cp++){
			if(*cp=='\"' && *(cp-1)!='\\'){
				break;
			}
		}
		if(*cp!='\"'){
			return NULL;
		}
		hp=cp-1;
		int	n=(int)(hp-fp);
		strncpy(Buff,fp,n);
		Buff[n]=0;
		Ret=Buff;
		cp++;
		cp=SkipSpace(cp);
		if(strchr(sep,*cp)!=NULL){
			return cp+1;
		}
		return NULL;
	}
	else{
		for(cp=fp;*cp!=0;cp++){
			const char	*r=strchr(sep,*cp);
			if(r!=NULL){
				break;
			}
		}
		for(hp=cp-1;hp>fp;hp--){
			if((*hp!=' ') && (*hp!='\t')){
				break;
			}
		}
		int	n=(int)(hp-fp+1);
		strncpy(Buff,fp,n);
		Buff[n]=0;
		Ret=Buff;
		if(*cp!=0){
			return cp+1;
		}
		return cp;
	}
}

bool	MacroFunction::LoadFromMacro(const QString &TextBuff)
{
	char	Buff[1000];

	QString2Char(TextBuff,Buff ,sizeof(Buff));

	char	*fp=Buff;
	fp=CutWord(fp,":",DLLRoot);
	if(fp==NULL){
		return false;
	}
	fp=CutWord(fp,":",DLLName);
	if(fp==NULL){
		return false;
	}
	fp=CutWord(fp,":",InstName);
	if(fp==NULL){
		return false;
	}
	fp=CutWord(fp," \t",FuncName);
	if(fp==NULL){
		return false;
	}
	if(FuncName.isEmpty()==true){
		return false;
	}
	fp=SkipSpace(fp);
	if(*fp==':'){
		return false;
	}

	while(*fp!=0){
		QString	Arg;
		fp=CutWord(fp,",\n",Arg);
		if(fp==NULL){
			return true;
		}
		Args.append(Arg);
	}
	return true;
}
QString	MacroFunction::GetTextLine(void)
{
	QString	Ret=DLLRoot+QString(":")
				+DLLName+QString(":")
				+InstName+QString(":")
				+FuncName;
	if(Args.count()!=0){
		Ret+=QString(" ");
		for(int i=0;i<Args.count();i++){
			if(i<Args.count()-1){
				Ret+=Args[i]+QString(",");
			}
			else{
				Ret+=Args[i];
			}
		}
	}
	return QString("Execute ")+Ret;
}
bool	MacroFunction::ExecuteLine(LayersBase *Base,bool &ExeReturn)
{
	GUIFormBase	*f=Base->FindByName(DLLRoot ,DLLName ,InstName);
	if(f==NULL){
		ExeReturn=false;
		return false;
	}
	return f->ExecuteMacro(FuncName,Args,ExeReturn);
}

//========================================================================

bool	MacroWait::LoadFromMacro(const QString &TextBuff)
{
	char	Buff[1000];

	QString2Char(TextBuff,Buff ,sizeof(Buff));

	char	*fp=Buff;
	fp=CutWord(fp,":",WaitCount);
	if(fp==NULL){
		return false;
	}
	return true;
}
QString	MacroWait::GetTextLine(void)
{
	return QString("Wait ")+WaitCount;
}
bool	MacroWait::ExecuteLine(LayersBase *Base,bool &ExeReturn)
{
	bool	ok;
	int	SCount=WaitCount.toInt(&ok);
	if(ok==true){
		GSleep(SCount);
		ExeReturn=true;
		return true;
	}
	return false;
}

//========================================================================
bool	MacroSentenseContainer::LoadFromMacro(QIODevice &TextFile,QString &ErrorLine)
{
	QTextStream	TextStr(&TextFile);
	char	Buff[1000];

	RemoveAll();
	while(TextStr.atEnd()!=true){
		QString	Str=TextStr.readLine();
		QString2Char(Str ,Buff ,sizeof(Buff));
		char	*fp=Buff;
		fp=SkipSpace(fp);
		char	*cp=fp;
		while((*cp!=' ') && (*cp!='\t') && (*cp!=0)){
			cp++;
		}
		if(*cp==0){
			continue;
		}
		*cp=0;
		QString	Command=fp;
		fp=SkipSpace(cp+1);
		if(QString::compare(Command,"Execute",Qt::CaseInsensitive)==0){
			MacroFunction	*a=new MacroFunction();
			if(a->LoadFromMacro(fp)==true){
				AppendList(a);
			}
			else{
				delete	a;
				ErrorLine=Str;
				return false;
			}
		}
		else if(QString::compare(Command,"Wait",Qt::CaseInsensitive)==0){
			MacroWait	*a=new MacroWait();
			if(a->LoadFromMacro(fp)==true){
				AppendList(a);
			}
			else{
				delete	a;
				ErrorLine=Str;
				return false;
			}
		}
	}

	return true;

}


//========================================================================
DLLMacroFunc::DLLMacroFunc(void)
{	
	MacroFunctions=NULL;
	MacroFunctionCount=0;
}
DLLMacroFunc::~DLLMacroFunc(void)
{
	if(MacroFunctions!=NULL){
		delete	[]MacroFunctions;
	}
	MacroFunctions=NULL;
}

ExportFuncForMacro	*DLLMacroFunc::SearchMacroFunc(const QString &FuncName)
{
	for(int i=0;i<MacroFunctionCount;i++){
		if(MacroFunctions[i].FuncName==FuncName){
			return &MacroFunctions[i];
		}
	}
	return NULL;
}

bool	DLLMacroFunc::ExecuteMacro(GUIFormBase *Instance
								,const QString &FunctionName ,const QString &Arg1
															 ,const QString &Arg2
															 ,const QString &Arg3
															 ,const QString &Arg4
															 ,const QString &Arg5
															 ,const QString &Arg6
															 ,const QString &Arg7
															 ,const QString &Arg8
															 ,const QString &Arg9
															 ,const QString &Arg10)
{
	for(int i=0;i<MacroFunctionCount;i++){
		if(MacroFunctions[i].FuncName==FunctionName){
			QStringList	Args;
			int	ArgNumb=MacroFunctions[i].ArgName.count();
			if(ArgNumb>=1)
				Args<<Arg1;
			if(ArgNumb>=2)
				Args<<Arg2;
			if(ArgNumb>=3)
				Args<<Arg3;
			if(ArgNumb>=4)
				Args<<Arg4;
			if(ArgNumb>=5)
				Args<<Arg5;
			if(ArgNumb>=6)
				Args<<Arg6;
			if(ArgNumb>=7)
				Args<<Arg7;
			if(ArgNumb>=8)
				Args<<Arg8;
			if(ArgNumb>=9)
				Args<<Arg9;
			if(ArgNumb>=10)
				Args<<Arg10;
			return MacroFunctions[i].DLL_ExcuteMacro(Instance,Args);
		}
	}
	return false;
}

void	DLLMacroFunc::SetupMacro(void)
{
	if(MacroFunctions!=NULL){
		delete	[]MacroFunctions;
		MacroFunctions=NULL;
		MacroFunctionCount=0;
	}
	ExportFuncForMacro Functions[1000];
	int MaxBuffer=sizeof(Functions)/sizeof(Functions[0]);
	MacroFunctionCount=RegistMacroFunction(Functions,MaxBuffer);
	MacroFunctions=new ExportFuncForMacro[MacroFunctionCount];
	RegistMacroFunction(MacroFunctions,MacroFunctionCount);
}

void	DLLMacroFunc::GetMacroNames(QStringList &Str)
{
	Str.clear();
	if(MacroFunctions==NULL){
		SetupMacro();
	}
	for(int i=0;i<MacroFunctionCount;i++){
		Str.append(MacroFunctions[i].FuncName);
	}
}