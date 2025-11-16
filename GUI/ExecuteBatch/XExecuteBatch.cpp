#include "XExecuteBatch.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"

bool	BatchLine::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	BYTE	d=(BYTE)DLLType;
	if(::Save(f,d)==false)
		return false;

	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(::Save(f,CommandStr)==false)
		return false;
	if(::Save(f,ArgValues)==false)
		return false;
	return true;
}

bool	BatchLine::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	DLLType	=(__DLLType)d;

	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(::Load(f,CommandStr)==false)
		return false;
	if(::Load(f,ArgValues)==false)
		return false;
	return true;
}
	
bool	BatchLine::SaveText(QTextStream &Txt)
{
	if(DLLType==_DLL_GUI)
		Txt<</**/"DLL_GUI";
	else if(DLLType==_DLL_Algorithm)
		Txt<</**/"DLL_Algorithm";
	else if(DLLType==_DLL_Result)
		Txt<</**/"DLL_Result";
	else
		return false;
	Txt<<',';
	Txt<<DLLRoot<<',';
	Txt<<DLLName<<',';
	Txt<<CommandStr<<',';
	for(int i=0;i<ArgValues.count();i++){
		QString	s=ArgValues[i];
		if(s.isEmpty()==true)
			break;
		Txt<<s<<',';
	}
	Txt<</**/"\r\n";
	return true;
}

bool	BatchLine::LoadText(QTextStream &Txt)
{
	QString	SLine=Txt.readLine(10000);
	QStringList	List=SLine.split(',');
	if(List.count()<4)
		return false;
	QString	StrDLLType=List[0];
	if(StrDLLType==/**/"DLL_GUI")
		DLLType=_DLL_GUI;
	else if(StrDLLType==/**/"DLL_Algorithm")
		DLLType=_DLL_Algorithm;
	else if(StrDLLType==/**/"DLL_Result")
		DLLType=_DLL_Result;

	DLLRoot		=List[1];
	DLLName		=List[2];
	CommandStr	=List[3];
	for(int i=4;i<List.count();i++){
		ArgValues.append(List[i]);
	}

	return true;
}

bool	BatchLine::ExecuteLine(LayersBase *Base)
{
	QStringList	ParamArg=ArgValues;

	for(int i=0;i<ParamArg.count();i++){
		if(ParamArg[i].left(1)==/**/"@"){
			QString	s=ParamArg[i].mid(1);
			if(s.isEmpty()==false){
				bool	ok;
				int	n=s.toInt(&ok);
				if(ok==true){
					if(Parent->ParamFromArg.count()>n){
						ParamArg[i]=Parent->ParamFromArg[n];
					}
				}
			}
		}
	}

	if(DLLType==_DLL_GUI){
		GUIFormBase	*f=Base->FindByName(DLLRoot ,DLLName ,/**/"");
		if(f==NULL){
			return false;
		}
		bool	ExeReturn;
		return f->ExecuteMacro(CommandStr,ParamArg,ExeReturn);
	}
	else if(DLLType==_DLL_Algorithm){
		AlgorithmBase	*f=Base->GetAlgorithmBase(DLLRoot ,DLLName);
		if(f==NULL){
			return false;
		}
		bool	ExeReturn;
		return f->ExecuteMacro(CommandStr,ParamArg,ExeReturn);
	}
	return false;
}
void	BatchLine::ReplaceParam(const QString &Keyword ,const QString &ReplacedStr)
{
	for(int i=0;i<ArgValues.count();i++){
		if(ArgValues[i].toUpper()==Keyword.toUpper()){
			ArgValues[i]=ReplacedStr;
		}
	}
}

BatchLine	&BatchLine::operator=(BatchLine &src)
{
	DLLType		=src.DLLType;

	DLLRoot	=src.DLLRoot;
	DLLName	=src.DLLName;
	CommandStr	=src.CommandStr;
	ArgValues	=src.ArgValues;
	return *this;
}

	
bool	BatchContainer::SaveText(QIODevice *f)
{
	QTextStream		Txt(f);

	Txt<<QString(/**/"Version,")<<QString::number(2)<<QString(/**/"\r\n");
	for(BatchLine *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->SaveText(Txt)==false)
			return false;
	}
	return true;
}

bool	BatchContainer::LoadText(QIODevice *f)
{
	QTextStream		Txt(f);

	QString	S=Txt.readLine();
	QStringList	VerStrList=S.split(',');
	bool	ok;
	int	Ver=VerStrList[1].toInt(&ok);
	if(ok==false)
		return false;
	RemoveAll();
	if(Ver==2){
		for(;;){
			BatchLine *L=new BatchLine(this);
			if(L->LoadText(Txt)==true){
				AppendList(L);
			}
			else{
				delete	L;
				break;
			}
		}
	}
	return true;
}

bool	BatchContainer::AppendText(QIODevice *f)
{
	QTextStream		Txt(f);

	QString	S=Txt.readLine();
	QStringList	VerStrList=S.split(',');
	bool	ok;
	int	Ver=VerStrList[1].toInt(&ok);
	if(ok==false)
		return false;
	if(Ver==2){
		for(;;){
			BatchLine *L=new BatchLine(this);
			if(L->LoadText(Txt)==true){
				AppendList(L);
			}
			else{
				delete	L;
				break;
			}
		}
	}
	return true;
}

void	BatchContainer::ReplaceParam(const QString &Keyword ,const QString &ReplacedStr)
{
	for(BatchLine *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->ReplaceParam(Keyword ,ReplacedStr);
	}
}
