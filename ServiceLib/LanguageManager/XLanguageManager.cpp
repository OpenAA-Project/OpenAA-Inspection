#include "XLanguageManager.h"
#include "XGeneralFunc.h"
#include "XExcelOperator.h"
#include <QFileInfo>
#include <QProgressBar>

QString	SolutionLanguage::DefaultFileName	=/**/"LangSolution.lsn";


//---------------------------------------------------------------------------------

QString	ProjectLanguage::GetLngFileName(void)
{
	QFileInfo	Info(OutputLNGFile);
	return Info.fileName();
}

bool	ProjectLanguage::Save(QIODevice *f)
{
	if(::Save(f,ProjectName)==false)
		return false;
	if(::Save(f,ExcelFiles)==false)
		return false;
	if(::Save(f,OutputLNGFile)==false)
		return false;
	return true;
}
	
bool	ProjectLanguage::Load(QIODevice *f)
{
	if(::Load(f,ProjectName)==false)
		return false;
	if(::Load(f,ExcelFiles)==false)
		return false;
	if(::Load(f,OutputLNGFile)==false)
		return false;
	return true;
}

static	int	DbgCount=446;
static	int	DbgC=0;

bool	ProjectLanguage::Execute(LanguagePack &LangPack ,QProgressBar *Bar ,QString &ErrorMsg)
{
	char	Buff[2000];

	LangPack.AllocCodec();

	LPackage.Clear();
	int	MaxColumnNo=0;
	for(LanguageClass *L=LangPack.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->ColumnNo>MaxColumnNo){
			MaxColumnNo=L->ColumnNo;
		}
	}
	for(int CNo=0;CNo<=MaxColumnNo;CNo++){
		bool	Found=false;
		for(LanguageClass *L=LangPack.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->ColumnNo==CNo){
				QString2Char(L->QtCotec,Buff ,sizeof(Buff));
				LPackage.AddLanguageCodec(Buff);
				Found=true;
				break;
			}
		}
		if(Found==false){
			LPackage.AddLanguageCodec(/**/"Arial");
		}
	}
	Bar->setMaximum(ExcelFiles.count());
	Bar->setValue(0);

	for(int i=0;i<ExcelFiles.count();i++){
		if(i==DbgCount)
			DbgC++;
		LanguagePackage::LanguageComponent	*DestL=new LanguagePackage::LanguageComponent(&LPackage);
		if(LoadExcel(ExcelFiles[i],LangPack,DestL)==true){
			LPackage.AddComponent(DestL);
		}
		else{
			ErrorMsg=ExcelFiles[i]+QString(/**/" : not loaded");
			return false;
		}
		Bar->setValue(i);
	}

	QFile	File(OutputLNGFile);
	if(File.open(QIODevice::WriteOnly)==false){
		ErrorMsg=OutputLNGFile+QString(/**/" : not written");
		return false;
	}
	if(LPackage.SaveSolution(&File)==false){
		ErrorMsg=OutputLNGFile+QString(/**/" : not written");
		return false;
	}
	Bar->setValue(0);
	return true;
}

class	DefineList : public NPList<DefineList>
{
public:
	QString		Str;
	int			Number;

	DefineList(void){}
};

bool	ProjectLanguage::LoadExcel(const QString &ExcelFileName ,LanguagePack &LangPack ,LanguagePackage::LanguageComponent *DestL)
{
	//char	Buff[20000];

	QStringListListXLSX		XLSDef;
	XLSDef.LoadFromXLSXFile(1,ExcelFileName);
	NPListPack<DefineList>	DefineListContainer;

	for(int Row=0;Row<XLSDef.GetRowCount();Row++){
		if(XLSDef.GetColumnCount(Row)<2){
			continue;
		}
		QString	Str=XLSDef.Get(0,Row);
		QString	Number=XLSDef.Get(1,Row);
		if(Str.isEmpty()==false && Number.isEmpty()==false){
			bool	ok;
			int	n=Number.toInt(&ok);
			if(ok==true){
				DefineList	*a=new DefineList();
				a->Str=Str;
				a->Number=n;
				DefineListContainer.AppendList(a);
			}
			else{
				double	nn=Number.toDouble(&ok);
				if(ok==true){
					DefineList	*a=new DefineList();
					a->Str=Str;
					a->Number=(int)nn;
					DefineListContainer.AppendList(a);
				}
			}
		}
	}

	QStringListListXLSX		XLS;
	XLS.LoadFromXLSXFile(0,ExcelFileName);
	QFileInfo	FInfo(ExcelFileName);
	DestL->IDName=FInfo.baseName();

	enum{
		_Mode_String
		,_Mode_UI
	}CurrentMode;

	CurrentMode=_Mode_String;

	for(int Row=0;Row<XLS.GetRowCount();Row++){
		if(XLS.Get(0,Row)==/**/"IDName"){
			DestL->IDName=XLS.Get(1,Row);
		}
		else if(XLS.Get(0,Row)==/**/"String"){
			CurrentMode=_Mode_String;
		}
		else if(XLS.Get(0,Row)==/**/"UI"){
			CurrentMode=_Mode_UI;
		}
		else{
			if(CurrentMode==_Mode_String){
				if(XLS.GetColumnCount(Row)<2){
					continue;
				}
				QString		FileIDStr=XLS.Get(0,Row);
				int			FileID=0;
				QString		IDStr	 =XLS.Get(1,Row);
				int			ID=0;
				for(DefineList *k=DefineListContainer.GetFirst();k!=NULL;k=k->GetNext()){
					if(k->Str==FileIDStr){
						FileID=k->Number;
					}
				}
				for(DefineList *k=DefineListContainer.GetFirst();k!=NULL;k=k->GetNext()){
					if(k->Str==IDStr){
						ID=k->Number;
					}
				}
				LanguagePackage::LanguageComponent::CompString	*h=new LanguagePackage::LanguageComponent::CompString(FileID,ID);
				int	AllocNumb=XLS.GetColumnCount(Row)-2;
				if(AllocNumb>0){
					h->AllocStr(AllocNumb);
					for(int i=0;i<AllocNumb;i++){
						LangPack.SetCodec(i);
						QString	CStr=XLS.Get(i+2,Row);
						//QString2Char(CStr,Buff ,sizeof(Buff));
						//h->SetStr(i,Buff);
						QByteArray	AStr;
						QBuffer	LBuff(&AStr);
						LBuff.open(QIODevice::WriteOnly);
						QTextStream	XStr(&LBuff);
						XStr<<CStr;
						XStr.flush();
						h->SetStr(i,AStr.data());
					}
					DestL->Add(h);
				}
			}
			else if(CurrentMode==_Mode_UI){
				if(XLS.GetColumnCount(Row)<4){
					continue;
				}
				QString	UIClassStr	=XLS.Get(0,Row);
				QString	ClassTypeStr=XLS.Get(1,Row);
				QString	ControlStr	=XLS.Get(2,Row);
				QString	PropertyStr	=XLS.Get(3,Row);
				char	LUIClassName[256];
				char	LClassTypeName[256];
				char	LControlName[256];
				char	LPropertyName[256];
				QString2Char(UIClassStr		,LUIClassName	,sizeof(LUIClassName));
				QString2Char(ClassTypeStr	,LClassTypeName	,sizeof(LClassTypeName));
				QString2Char(ControlStr		,LControlName	,sizeof(LControlName));
				QString2Char(PropertyStr	,LPropertyName	,sizeof(LPropertyName));

				LanguagePackage::LanguageComponent::UIString	*h=new LanguagePackage::LanguageComponent::UIString();
				h->SetName(	 LUIClassName
							,LClassTypeName
							,LControlName
							,LPropertyName);
				int	AllocNumb=XLS.GetColumnCount(Row)-4;
				if(AllocNumb>0){
					h->AllocStr(AllocNumb);
					if(ClassTypeStr==/**/"QTextEdit" && PropertyStr==/**/"html"){
						QFileInfo	FInfo(ExcelFileName);
						QString	FPath=FInfo.path();
						for(int i=0;i<AllocNumb;i++){
							LangPack.SetCodec(i);
							QString	HtmlFileName=FPath+QDir::separator()+XLS.Get(i+4,Row);
							QFile	HtmlFile(HtmlFileName);
							QString	CStr;
							if(HtmlFile.open(QIODevice::ReadOnly)==true){
								QTextStream	TStr(&HtmlFile);
								CStr=TStr.readAll();
							}
							else{
								CStr=XLS.Get(i+4,Row);
							}
							QByteArray	AStr;
							QBuffer	LBuff(&AStr);
							LBuff.open(QIODevice::WriteOnly);
							QTextStream	XStr(&LBuff);
							XStr<<CStr;
							XStr.flush();
							h->SetStr(i,AStr.data());
						}
					}
					else{
						for(int i=0;i<AllocNumb;i++){
							LangPack.SetCodec(i);
							QString	CStr=XLS.Get(i+4,Row);
							//QString2Char(CStr,Buff ,sizeof(Buff));
							QByteArray	AStr;
							QBuffer	LBuff(&AStr);
							LBuff.open(QIODevice::WriteOnly);
							QTextStream	XStr(&LBuff);
							XStr<<CStr;
							XStr.flush();
							h->SetStr(i,AStr.data());
						}
					}
					DestL->Add(h);
				}
			}
		}
	}
	return true;
}

//---------------------------------------------------------------------------------

void	SolutionLanguage::Clear(void)
{
	RemoveAll();
}

int		SolutionLanguage::Search(const QString &ProjName)
{
	int	Row=0;
	for(ProjectLanguage *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ProjectName==ProjName){
			return Row;
		}
		Row++;
	}
	return -1;
}

bool	SolutionLanguage::SaveDefault(void)
{
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::WriteOnly)==false){
		return false;
	}
	if(Save(&File)==false){
		return false;
	}
	return true;
}
bool	SolutionLanguage::LoadDefault(void)
{
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(Load(&File)==false){
		return false;
	}
	return true;
}

bool	SolutionLanguage::Save(QIODevice *f)
{
	if(NPListPackSaveLoad<ProjectLanguage>::Save(f)==false)
		return false;
	return true;
}
bool	SolutionLanguage::Load(QIODevice *f)
{
	if(NPListPackSaveLoad<ProjectLanguage>::Load(f)==false)
		return false;
	return true;
}
