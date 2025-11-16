
#include "XStepFile.h"
#include <QTextStream>

static	QString	RemoveDelimiter(const QString &s)
{
	int	Index=s.lastIndexOf(';');
	if(Index>=0){
		return s.left(Index);
	}
	return s;
}

//==========================================================
StepFileEntity::~StepFileEntity(void)
{
	for(int i=0;i<ArgCount && i<sizeof(ArgPoint)/sizeof(ArgPoint[0]);i++){
		if(ArgPoint[i]!=NULL){
			delete	ArgPoint[i];
			ArgPoint[i]=NULL;
		}
	}
	ArgCount=0;
}

//==========================================================

StepFileEntityArg::StepFileEntityArg(const QString &aname)
	:ArgLabel(aname)
{
	ArgType		=_None;
	NumericValue=0;
	IndexNumber	=-1;
	IndexEntity	=NULL;

	if(aname.at(0)=='#'){
		IndexNumber=0;
		int	Len=aname.count();
		for(int i=1;i<Len;i++){
			QChar	c=aname.at(i);
			int	t=c.digitValue();
			if(t<0)
				break;
			IndexNumber*=10;
			IndexNumber+=t;
		}
		ArgType=_Index;
	}
	else
	if(aname.at(0)=='\''){
		int	LastApo=aname.lastIndexOf('\'');
		StringValue=aname.mid(1,LastApo-1);
		ArgType=_String;
	}
	else
	if(aname==".T."){
		ArgType=_True;
	}
	else
	if(aname==".F."){
		ArgType=_False;
	}
	else
	if(aname.at(0)=='.'){
		int	LastApo=aname.lastIndexOf('.');
		StringValue=aname.mid(1,LastApo-1);
		ArgType=_SpecialString;
	}
	else
	if(aname=='*'){
		ArgType=_Star;
	}
	else
	if(aname.count()==0){
		ArgType=_None;
	}
	else{
		int	k=0;
		int	Sign=1;
		if(aname.at(0)=='-'){
			Sign=-1;
			k++;
		}
		else
		if(aname.at(0)=='+'){
			Sign=1;
			k++;
		}
		double	tNumericValue=0;

		int	Len=aname.count();
		int	i=k;
		for(;i<Len;i++){
			QChar	c=aname.at(i);
			if(c=='.'){
				i++;
				break;
			}
			int	t=c.digitValue();
			if(t<0)
				break;
			tNumericValue*=10.0;
			tNumericValue+=t;
		}
		double	SmallN=0.1;
		for(;i<Len;i++){
			QChar	c=aname.at(i);
			int	t=c.digitValue();
			if(t<0)
				break;
			tNumericValue+=t*SmallN;
			SmallN*=0.1;
		}
		if(Sign>0){
			NumericValue=tNumericValue;
		}
		else{
			NumericValue=-tNumericValue;
		}
		ArgType=_Numeric;
	}

}

//==========================================================

StepFileStructure::StepFileStructure(void)
{
}

static	QString	TrimString(const QString &s)
{
	return s.trimmed();
}

bool	StepFileStructure::LoadStepFile(QIODevice *f)
{
	QTextStream	TextStream(f);
	QString LStr;

	bool	LoadedVersion	=false;
	bool	LoadedHeader	=false;
	bool	LoadedData		=false;

	while(TextStream.atEnd()==false){
		LStr=TextStream.readLine(32769);
		LStr=TrimString(LStr);
		if(LStr.isEmpty()==false){
			Version=RemoveDelimiter(LStr);
			LoadedVersion=true;
			break;
		}
	}
	Header.clear();
	if(TextStream.atEnd()==false){
		LStr=TextStream.readLine(32769);
		LStr=TrimString(LStr);
		if(LStr.isEmpty()==false){
			LStr=RemoveDelimiter(LStr);
			if(LStr==/**/"HEADER"){
				while(TextStream.atEnd()==false){
					LStr=TextStream.readLine(32769);
					LStr=TrimString(LStr);
					if(LStr.isEmpty()==false){
						LoadedHeader=true;
						if(LStr==/**/"ENDSEC"){
							break;
						}
						LStr=RemoveDelimiter(LStr);
						Header.append(LStr);
					}
				}
			}
		}
	}
	if(TextStream.atEnd()==false){
		LStr=TextStream.readLine(32769);
		LStr=TrimString(LStr);
		if(LStr.isEmpty()==false){
			LStr=RemoveDelimiter(LStr);
			if(LStr==/**/"DATA"){
				while(TextStream.atEnd()==false){
					LStr=TextStream.readLine(32769);
					LStr=TrimString(LStr);
					if(LStr.isEmpty()==false){
						LoadedData=true;
						if(LStr==/**/"ENDSEC"){
							break;
						}
						LoadEntityLine(LStr);
					}
				}
			}
		}
	}
	if(LoadedVersion==true	
	&& LoadedHeader	==true
	&& LoadedData	==true){
		return true;
	}
	return false;
}

QString	GetLineNo(const QString &LStr,int StartIndex,int &LineNo)
{
	LineNo=-1;
	for(int i=0;i<10;i++){
		QChar	c=LStr.at(StartIndex+i);
		if(c.isNumber()==false){
			return LStr.mid(i);
		}
		if(LineNo<0){
			LineNo=0;
		}
		LineNo*=10;
		int	num=c.digitValue();
		if(num<0){
			break;
		}
		LineNo+=num;
	}
	LineNo=-1;
	return LStr;
}

QString	AnalizeFunc(const QString &s ,QStringList &Args)
{
	int	FuncNumb=s.indexOf('(');
	if(FuncNumb<0){
		return /**/"";
	}
	QString	FuncName=s.left(FuncNumb);
	QString	ArgStr=s.mid(FuncNumb+1);
	int	ArgEnd=ArgStr.lastIndexOf(')');
	ArgStr=ArgStr.left(ArgEnd);

	int	Len=ArgStr.count();
	int	LeftPosition=0;
	int	Depth=0;
	for(int i=0;i<Len;i++){
		QChar	c=ArgStr.at(i);
		if(c=='('){
			Depth++;
		}
		else if(c==')'){
			Depth--;
		}
		else if(c==',' && Depth==0){
			Args.append(ArgStr.mid(LeftPosition,i-LeftPosition));
			LeftPosition=i+1;
		}
	}
	if(Len-LeftPosition>0){
		Args.append(ArgStr.mid(LeftPosition,Len-LeftPosition));
	}
	return FuncName;
}

QString	GetFuncSentense(const QString &s ,QString &RetFuncStr)
{
	int	Len=s.count();
	int	Depth=0;
	for(int i=0;i<Len;i++){
		QChar	c=s.at(i);
		if(c=='('){
			Depth++;
		}
		else if(c==')'){
			Depth--;
			if(Depth==0){
				RetFuncStr=s.left(i+1);
				return s.mid(i+1);
			}
		}
	}
	if(Depth!=0){
		return /**/"";
	}
	RetFuncStr=s;
	return /**/"";
}



bool	StepFileStructure::LoadEntityLine(const QString &LStr)
{
	if(LStr.at(0)!='#'){
		return true;
	}
	int	LineNo;
	QString	s=GetLineNo(LStr,1,LineNo);
	if(LineNo<0){
		return false;
	}
	s=TrimString(s);
	if(s.at(0)!='='){
		return false;
	}
	QString	SLine=TrimString(s.mid(1));

	while(true){
		QString	FuncStr;
		QString	s=GetFuncSentense(SLine ,FuncStr);
		if(FuncStr.isEmpty()==true)
			break;

		QStringList Args;
		QString	FuncName=AnalizeFunc(FuncStr,Args);
		StepFileEntity	*e=new StepFileEntity();
		e->LineNo	=LineNo;
		e->EntityName=FuncName;
		for(int i=0;i<Args.count();i++){
			QString	a=Args[i];
			e->ArgPoint[i]=new StepFileEntityArg(a);
			DataEntity.AppendList(e);
		}
	}
	return true;
}