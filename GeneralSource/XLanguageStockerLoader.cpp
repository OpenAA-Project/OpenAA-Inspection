#include "XTypeDef.h"
#include "XLanguageStockerLoader.h"
#include "XGeneralFunc.h"
#include "XLanguageClass.h"
#include <QTextCodec>
#include <QTableWidget>
#include <QTabWidget>
#include <QComboBox>

//------------------------------------------------------------

LanguagePackage::LanguageComponent::CompString::~CompString(void)
{
	if(Str!=NULL){
		for(int i=0;i<AllocStrCount;i++){
			delete	[]Str[i];
		}
		delete	[]Str;
	
		Str=NULL;
		AllocStrCount=0;
	}
}

void	LanguagePackage::LanguageComponent::CompString::AllocStr(int count)
{
	if(Str!=NULL){
		for(int i=0;i<AllocStrCount;i++){
			delete	[]Str[i];
		}
		delete	[]Str;
	
		Str=NULL;
		AllocStrCount=0;
	}
	AllocStrCount=count;
	Str=new char *[AllocStrCount];
	for(int i=0;i<AllocStrCount;i++){
		Str[i]=NULL;
	}
}

void	LanguagePackage::LanguageComponent::CompString::SetStr(int n ,char *s)
{
	if(n<AllocStrCount){
		if(Str[n]!=NULL){
			delete	[]Str[n];
		}
		Str[n]=new char[strlen(s)+1];
		strcpy(Str[n],s);
	}
}

bool	LanguagePackage::LanguageComponent::CompString::Save(QIODevice *f)
{
	int32	Ver=1;
	
	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,FileID)==false){
		return false;
	}
	if(::Save(f,ID)==false){
		return false;
	}
	if(::Save(f,AllocStrCount)==false){
		return false;
	}
	for(int i=0;i<AllocStrCount;i++){
		if(::Save(f,Str[i],strlen(Str[i])+1)==false){
			return false;
		}
	}
	return true;
}

bool	LanguagePackage::LanguageComponent::CompString::Load(QIODevice *f)
{
	int32	Ver;
	
	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,FileID)==false){
		return false;
	}
	if(::Load(f,ID)==false){
		return false;
	}
	if(Str!=NULL){
		for(int i=0;i<AllocStrCount;i++){
			delete	[]Str[i];
		}
		delete	[]Str;
	}
	if(::Load(f,AllocStrCount)==false){
		return false;
	}
	Str=new char *[AllocStrCount];
	for(int i=0;i<AllocStrCount;i++){
		Str[i]=NULL;
	}
	for(int i=0;i<AllocStrCount;i++){
		char	Buff[16384];
		int64	Len;
		if(::Load(f,Buff,Len,sizeof(Buff))==false){
			return false;
		}
		Str[i]=new char[strlen(Buff)+2];
		strcpy(Str[i],Buff);
	}
	return true;
}

//------------------------------------------------------------

			
LanguagePackage::LanguageComponent::UIString::UIString(void)
{	
	UIClassName		=NULL;
	ClassTypeName	=NULL;
	ControlName		=NULL;
	PropertyName	=NULL;

	Str=NULL;	
	AllocStrCount=0;	
}


LanguagePackage::LanguageComponent::UIString::~UIString(void)
{
	if(UIClassName!=NULL){
		delete	[]UIClassName;
		UIClassName		=NULL;
	}
	if(ClassTypeName!=NULL){
		delete	[]ClassTypeName;
		ClassTypeName	=NULL;
	}
	if(ControlName!=NULL){
		delete	[]ControlName;
		ControlName		=NULL;
	}
	if(PropertyName!=NULL){
		delete	[]PropertyName;
		PropertyName	=NULL;
	}

	if(Str!=NULL){
		for(int i=0;i<AllocStrCount;i++){
			delete	[]Str[i];
		}
		delete	[]Str;

		Str=NULL;
		AllocStrCount=0;
	}
}

void	LanguagePackage::LanguageComponent::UIString::SetName(	 char *_UIClassName
																,char *_ClassTypeName
																,char *_ControlName
																,char *_PropertyName)
{
	if(UIClassName!=NULL){
		delete	[]UIClassName;
		UIClassName		=NULL;
	}
	if(ClassTypeName!=NULL){
		delete	[]ClassTypeName;
		ClassTypeName	=NULL;
	}
	if(ControlName!=NULL){
		delete	[]ControlName;
		ControlName		=NULL;
	}
	if(PropertyName!=NULL){
		delete	[]PropertyName;
		PropertyName	=NULL;
	}
	UIClassName		=new char[strlen(_UIClassName)+1];
	strcpy(UIClassName,_UIClassName);

	ClassTypeName	=new char[strlen(_ClassTypeName)+1];
	strcpy(ClassTypeName,_ClassTypeName);

	ControlName		=new char[strlen(_ControlName)+1];
	strcpy(ControlName,_ControlName);

	PropertyName	=new char[strlen(_PropertyName)+1];
	strcpy(PropertyName,_PropertyName);
}

void	LanguagePackage::LanguageComponent::UIString::AllocStr(int count)
{
	if(Str!=NULL){
		for(int i=0;i<AllocStrCount;i++){
			delete	[]Str[i];
		}
		delete	[]Str;
	
		Str=NULL;
		AllocStrCount=0;
	}
	AllocStrCount=count;
	Str=new char *[AllocStrCount];
	for(int i=0;i<AllocStrCount;i++){
		Str[i]=NULL;
	}
}

void	LanguagePackage::LanguageComponent::UIString::SetStr(int n ,char *s)
{
	if(n<AllocStrCount){
		if(Str[n]!=NULL){
			delete	[]Str[n];
		}
		Str[n]=new char[strlen(s)+1];
		strcpy(Str[n],s);
	}
}


bool	LanguagePackage::LanguageComponent::UIString::Save(QIODevice *f)
{
	int32	Ver=1;
	
	if(::Save(f,Ver)==false){
		return false;
	}
	if(UIClassName!=NULL){
		if(::Save(f,UIClassName,strlen(UIClassName)+1)==false){
			return false;
		}
	}
	else{
		return false;
	}
	if(ClassTypeName!=NULL){
		if(::Save(f,ClassTypeName,strlen(ClassTypeName)+1)==false){
			return false;
		}
	}
	else{
		return false;
	}
	if(ControlName!=NULL){
		if(::Save(f,ControlName,strlen(ControlName)+1)==false){
			return false;
		}
	}
	else{
		return false;
	}
	if(PropertyName!=NULL){
		if(::Save(f,PropertyName,strlen(PropertyName)+1)==false){
			return false;
		}
	}
	else{
		return false;
	}

	if(::Save(f,AllocStrCount)==false){
		return false;
	}
	for(int i=0;i<AllocStrCount;i++){
		if(::Save(f,Str[i],strlen(Str[i])+1)==false){
			return false;
		}
	}
	return true;
}

bool	LanguagePackage::LanguageComponent::UIString::Load(QIODevice *f)
{
	int32	Ver;
	
	if(::Load(f,Ver)==false){
		return false;
	}
	char	Buff[16384];
	int64	Len;

	if(UIClassName!=NULL){
		delete	[]UIClassName;
		UIClassName		=NULL;
	}
	if(ClassTypeName!=NULL){
		delete	[]ClassTypeName;
		ClassTypeName	=NULL;
	}
	if(ControlName!=NULL){
		delete	[]ControlName;
		ControlName		=NULL;
	}
	if(PropertyName!=NULL){
		delete	[]PropertyName;
		PropertyName	=NULL;
	}

	if(::Load(f,Buff,Len,sizeof(Buff))==false){
		return false;
	}
	UIClassName	=new char[strlen(Buff)+2];
	strcpy(UIClassName,Buff);

	if(::Load(f,Buff,Len,sizeof(Buff))==false){
		return false;
	}
	ClassTypeName	=new char[strlen(Buff)+2];
	strcpy(ClassTypeName,Buff);

	if(::Load(f,Buff,Len,sizeof(Buff))==false){
		return false;
	}
	ControlName	=new char[strlen(Buff)+2];
	strcpy(ControlName,Buff);

	if(::Load(f,Buff,Len,sizeof(Buff))==false){
		return false;
	}
	PropertyName	=new char[strlen(Buff)+2];
	strcpy(PropertyName,Buff);

	if(Str!=NULL){
		for(int i=0;i<AllocStrCount;i++){
			delete	[]Str[i];
		}
		delete	[]Str;
	}
	if(::Load(f,AllocStrCount)==false){
		return false;
	}
	Str=new char *[AllocStrCount];
	for(int i=0;i<AllocStrCount;i++){
		if(::Load(f,Buff,Len,sizeof(Buff))==false){
			return false;
		}
		Str[i]=new char[strlen(Buff)+2];
		strcpy(Str[i],Buff);
	}
	return true;
}

//------------------------------------------------------------

QString	LanguagePackage::LanguageComponent::GetString(int FileID ,int LID)
{
	for(CompString *a=CompStringContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FileID==FileID && a->ID==LID){
			char	*p=a->Str[Parent->LanguageCode];
			if(*p==0){
				return Parent->CurrentCodec->toUnicode(a->Str[0]);
			}
			//return QString::fromLocal8Bit(p);
			return Parent->CurrentCodec->toUnicode(p);
		}
	}
	return /**/"";
}

void	LanguagePackage::LanguageComponent::SetUIInner(QWidget *W ,const QString &UIClassName ,const QString &ObjName)
{
	char	*Str;
	QString	TableStr;

	for(UIString *a=UIStringContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(UIClassName==a->UIClassName && ObjName==a->ControlName){
			if(Parent->GetLanguageCode()<a->AllocStrCount){
				Str=a->Str[Parent->GetLanguageCode()];
			}
			else{
				if(a->Str!=NULL){
					Str=a->Str[0];
				}
				else{
					continue;
				}
			}
			if(strlen(Str)==0){
				if(a->Str!=NULL){
					Str=a->Str[0];
				}
			}
			if(Str==NULL){
				continue;
			}
			QString	HStr= Parent->CurrentCodec->toUnicode(Str);

			if(strlen(a->PropertyName)!=0){
				//if(strcmp(a->ClassTypeName,"QTableWidget")==0){
					QTableWidget	*TableW=dynamic_cast<QTableWidget *>(W);
					if(TableW!=NULL){
						for(int j=0;j<TableW->columnCount();j++){
							QTableWidgetItem	*f=TableW->horizontalHeaderItem(j);
							if(f!=NULL){
								QString	HLabel=f->text();
#if	QT_VERSION<0x050000
								QTextCodec::setCodecForTr (Parent->FirstCodec);
#else
								QTextCodec::setCodecForLocale(Parent->FirstCodec);
#endif
								//TableStr=QObject::tr(a->Str[0]);
								TableStr=Parent->CurrentCodec->toUnicode(a->Str[0]);
#if	QT_VERSION<0x050000
								QTextCodec::setCodecForTr (Parent->CurrentCodec);
#else
								QTextCodec::setCodecForLocale(Parent->CurrentCodec);
#endif
								if(HLabel==TableStr){
									f->setText(HStr);
									f->setStatusTip(/**/"Languaged");
								}
							}
						}
						for(int j=0;j<TableW->rowCount();j++){
							QTableWidgetItem	*f=TableW->verticalHeaderItem(j);
							if(f!=NULL){
								QString	VLabel=f->text();
								QTextCodec::setCodecForLocale(Parent->FirstCodec);
								//TableStr=QObject::tr(a->Str[0]);
								TableStr=Parent->CurrentCodec->toUnicode(a->Str[0]);
								QTextCodec::setCodecForLocale(Parent->CurrentCodec);
								if(VLabel==TableStr){
									f->setText(HStr);
									f->setStatusTip(/**/"Languaged");
								}
							}
						}					}

				//}
				else{
					QComboBox	*ComboW=dynamic_cast<QComboBox *>(W);
					if(ComboW!=NULL){
						for(int j=0;j<ComboW->count();j++){
							QString	HLabel=ComboW->itemText(j);
							QTextCodec::setCodecForLocale(Parent->FirstCodec);
							//TableStr=QObject::tr(a->Str[0]);
							TableStr=Parent->CurrentCodec->toUnicode(a->Str[0]);
							QTextCodec::setCodecForLocale(Parent->CurrentCodec);
							if(HLabel==TableStr){
								ComboW->setItemText(j,HStr);
							}
						}
					}
					else{
						W->setProperty(a->PropertyName,HStr);
						W->setStatusTip(/**/"Languaged");
					}
				}
			}
			else{
				if(W->parentWidget()!=NULL){
					QTabWidget	*ETab=dynamic_cast<QTabWidget *>(W->parentWidget()->parentWidget());
					if(ETab!=NULL){
						for(int j=0;j<ETab->count();j++){
							QWidget	*C=ETab->widget(j);
							QString	TbName=C->objectName();
							if(TbName==QString(a->ControlName)){
								ETab->setTabText(j,HStr);
								break;
							}
						}
					}
				}
			}
		}
	}
	QObjectList WList=W->children ();
	for(int i=0;i<WList.count();i++){
		QWidget	*w=dynamic_cast<QWidget	*>(WList.value(i));
		if(w!=NULL){
			SetUIInner(w ,UIClassName,w->objectName());
		}
	}
}

void	LanguagePackage::LanguageComponent::Add(LanguagePackage::LanguageComponent::CompString *h)
{
	CompStringContainer.AppendList(h);
}

void	LanguagePackage::LanguageComponent::Add(LanguagePackage::LanguageComponent::UIString *h)
{
	UIStringContainer.AppendList(h);
}

bool	LanguagePackage::LanguageComponent::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,IDName)==false){
		return false;
	}
	if(CompStringContainer.Save(f)==false){
		return false;
	}
	if(UIStringContainer.Save(f)==false){
		return false;
	}
	return true;
}
bool	LanguagePackage::LanguageComponent::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,IDName)==false){
		return false;
	}
	if(CompStringContainer.Load(f)==false){
		return false;
	}
	if(UIStringContainer.Load(f)==false){
		return false;
	}
	return true;
}

//------------------------------------------------------------

LanguagePackage::CodecList::~CodecList(void)
{
	if(CodecStr!=NULL){
		delete	[]CodecStr;
		CodecStr=NULL;
	}
	CurrentCodec=NULL;
}
bool	LanguagePackage::CodecList::Save(QIODevice *f)
{
	if(::Save(f,CodecStr,strlen(CodecStr)+1)==false){
		return false;
	}
	return true;
}

bool	LanguagePackage::CodecList::Load(QIODevice *f)
{
	char	Buff[16384];
	int64	Len;

	if(::Load(f,Buff,Len,sizeof(Buff))==false){
		return false;
	}
	if(CodecStr!=NULL){
		delete	[]CodecStr;
	}
	CodecStr=new char[strlen(Buff)+2];
	strcpy(CodecStr,Buff);
	
	CurrentCodec= QTextCodec::codecForName(Buff);

	return true;
}

//------------------------------------------------------------

LanguagePackage::LanguagePackage(void)
	:LanguageComponents(this)
{
	FirstCodec		=NULL;
	CurrentCodec	=NULL;

	LastLanguageCode=-1;
	LanguageCode	=0;	//0～

	CodecPushedCount		=0;
#if	QT_VERSION<0x050000
	DefaultCodecCString		=QTextCodec::codecForCStrings ();
	DefaultCodecLocale		=QTextCodec::codecForLocale ();
	DefaultCodecTr			=QTextCodec::codecForTr ();
#else
	DefaultCodecCString = QTextCodec::codecForLocale();
	DefaultCodecLocale	= QTextCodec::codecForLocale();
	DefaultCodecTr		= QTextCodec::codecForLocale();
#endif

	CurrentCodecCString		=NULL;
	CurrentCodecLocale		=NULL;
	CurrentCodecTr			=NULL;
}
LanguagePackage::~LanguagePackage(void)
{
	LanguageComponents	.RemoveAll();
	CodecStocker		.RemoveAll();
	FirstCodec		=NULL;
	CurrentCodec	=NULL;
}

void	LanguagePackage::Clear(void)
{
	LanguageComponents	.RemoveAll();
	CodecStocker		.RemoveAll();
	FirstCodec		=NULL;
	CurrentCodec	=NULL;
}

bool	LanguagePackage::SetLanguage(int LangCode)
{
	if(LanguageCode!=LangCode){
		LanguageCode=LangCode;
		return InitialCodec();
	}
	return true;
}
void	LanguagePackage::AddLanguageCodec(char *s)
{
	CodecList	*c=new CodecList();
	c->CodecStr=new char[strlen(s)+1];
	strcpy(c->CodecStr,s);
	CodecStocker.AppendList(c);
}

void	LanguagePackage::AddComponent(LanguagePackage::LanguageComponent *DestL)
{
	LanguageComponents.AppendList(DestL);
}

bool	LanguagePackage::SaveSolution(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(LanguageComponents.Save(f)==false){
		return false;
	}
	if(CodecStocker.Save(f)==false){
		return false;
	}
	return true;
}

bool	LanguagePackage::LoadSolution(QIODevice *f)
{
	int32	Ver=1;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(LanguageComponents.Load(f)==false){
		return false;
	}
	if(CodecStocker.Load(f)==false){
		return false;
	}
	LanguageCode=0;
	if(InitialCodec()==false){
		return false;
	}
	return true;
}

bool	LanguagePackage::LoadSolutionFromFile(const QString &LNGFileName)
{
	QFile	File(LNGFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		return LoadSolution(&File);
	}
	return false;
}

LanguagePackage::LanguageComponent	*LanguagePackage::GetComponent(const QString &idName)
{
	for(LanguageComponent *a=LanguageComponents.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IDName==idName){
			return a;
		}
	}
	return NULL;
}

bool	LanguagePackage::InitialCodec(void)
{
	char	*c;

	if(LastLanguageCode!=LanguageCode){
		LastLanguageCode=LanguageCode;

		CodecList	*FirstC		=CodecStocker[0];
		if(LanguageCode>=CodecStocker.GetCount()){
			return false;
		}
		CodecList	*CurrentC	=CodecStocker[LanguageCode];
			
		FirstCodec	= FirstC	->CurrentCodec;
		CurrentCodec= CurrentC	->CurrentCodec;
		QTextCodec* C = NULL;
		QByteArray	CName;
		if(CurrentCodec!=NULL){
#if	QT_VERSION<0x050000
			QTextCodec::setCodecForCStrings(CurrentCodec);
			QTextCodec::setCodecForLocale (CurrentCodec);
			QTextCodec::setCodecForTr (CurrentCodec);
#else
			QTextCodec::setCodecForLocale(CurrentCodec);

			C = QTextCodec::codecForLocale();
			if (C != NULL) {
				CName = C->name();
			}
			C = QTextCodec::codecForLocale();
#endif
		}
		else{				
			QList<QByteArray> L=QTextCodec::availableCodecs ();
			for(int i=0;i<L.count();i++){
				QByteArray	a=L.value(i);
				c=a.data();
				if(strcmp(c,CurrentC->CodecStr)==0){
					c=a.data();
					CurrentCodec = QTextCodec::codecForName(c);
					if(CurrentCodec!=NULL){
#if	QT_VERSION<0x050000
						QTextCodec::setCodecForCStrings(CurrentCodec);
						QTextCodec::setCodecForLocale (CurrentCodec);
						QTextCodec::setCodecForTr (CurrentCodec);
#else
						QTextCodec::setCodecForLocale(CurrentCodec);
#endif
					}
				}
			}
		}
	}
	return true;
}

void	LanguagePackage::SetDefaultCodec(void)
{
	if(CodecPushedCount==0){
#if	QT_VERSION<0x050000
		CurrentCodecCString	=QTextCodec::codecForCStrings();
		CurrentCodecLocale	=QTextCodec::codecForLocale();
		CurrentCodecTr		=QTextCodec::codecForTr();
#else
		CurrentCodecCString = QTextCodec::codecForLocale();
		CurrentCodecLocale	= QTextCodec::codecForLocale();
		CurrentCodecTr		= QTextCodec::codecForLocale();
#endif

#if	QT_VERSION<0x050000
		QTextCodec::setCodecForCStrings	(DefaultCodecCString);
		QTextCodec::setCodecForLocale	(DefaultCodecLocale);
		QTextCodec::setCodecForTr		(DefaultCodecTr);
#else
		QTextCodec::setCodecForLocale(DefaultCodecLocale);
#endif
	}
	CodecPushedCount++;
}

void	LanguagePackage::RestoreCodec(void)
{
	if(CodecPushedCount==1){
#if	QT_VERSION<0x050000
		QTextCodec::setCodecForCStrings	(CurrentCodecCString);
		QTextCodec::setCodecForLocale	(CurrentCodecLocale);
		QTextCodec::setCodecForTr		(CurrentCodecTr);
#else
		QTextCodec::setCodecForLocale(CurrentCodecLocale);
#endif
	}
	CodecPushedCount--;
}
