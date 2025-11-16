#include "XMergeXLSX.h"

	
CombinedXLSX::CombinedXLSX(QFileInfo &mDest ,QFileInfo &mSrc)
{
	DestFile=mDest;
	SourceFile=mSrc;
	Result	=false;
}

bool	CombinedXLSX::Load(void)
{
	Dest0.clear();
	Dest1.clear();
	Source.clear();

	if(Dest0.LoadFromXLSXFile(0,DestFile.absoluteFilePath())==false){
		return false;
	}
	if(Dest1.LoadFromXLSXFile(1,DestFile.absoluteFilePath())==false){
		return false;
	}
	if(Source.LoadFromXLSXFile(0,SourceFile.absoluteFilePath())==false){
		return false;
	}

	int	Row=0;
	while(Row<Dest0.count()){
		QString	s=Source.Get(0, Row);
		if(s==/**/"String"){
			Row++;
			break;
		}
		Row++;
	}

	StringLineContainer.RemoveAll();
	UILineContainer.RemoveAll();

	while(Row<Dest0.count()){
		QString	s=Dest0.Get(0, Row);
		if(s==/**/"UI"){
			Row++;
			break;
		}
		QString	h0=Dest0.Get(0, Row);
		QString	h1=Dest0.Get(1, Row);
		StringLine	*w=new StringLine();
		w->FileLS=h0;
		w->ID	 =h1;
		w->Row	 =Row;
		StringLineContainer.AppendList(w);
		Row++;
	}

	while(Row<Dest0.count()){
		QString	h0=Dest0.Get(0, Row);
		QString	h1=Dest0.Get(1, Row);
		QString	h2=Dest0.Get(2, Row);
		QString	h3=Dest0.Get(3, Row);
		QString	h4=Dest0.Get(4, Row);
		UILine	*w=new UILine();
		w->ClassName	=h0;
		w->TypeName		=h1;
		w->ObjectName	=h2;
		w->PropertyName	=h3;
		w->Str1			=h4;
		w->Row			=Row;
		UILineContainer.AppendList(w);
		Row++;
	}
	return true;
}

bool	CombinedXLSX::Merge(int LangNo)
{
	int	Row=0;

	while(Row<Source.count()){
		QString	s=Source.Get(0, Row);
		if(s==/**/"String"){
			Row++;
			break;
		}
		Row++;
	}
	while(Row<Source.count()){
		QString	s=Source.Get(0, Row);
		if(s==/**/"UI"){
			Row++;
			break;
		}
		QString	h0=Source.Get(0, Row);
		QString	h1=Source.Get(1, Row);

		StringLine	*w=SearchString(h0 ,h1);
		if(w!=NULL){
			QString	hm=Source.Get(2+LangNo, Row);
			if(hm.isEmpty()==false){
				Dest0.Set(2+LangNo,w->Row,hm);
			}
		}
		Row++;
	}
	while(Row<Source.count()){
		QString	h0=Source.Get(0, Row);
		QString	h1=Source.Get(1, Row);
		QString	h2=Source.Get(2, Row);
		QString	h3=Source.Get(3, Row);
		QString	h4=Source.Get(4, Row);

		UILine	*w=SearchUI(h0,h1,h2,h3,h4);
		if(w!=NULL){
			QString	hm=Source.Get(4+LangNo, Row);
			if(hm.isEmpty()==false){
				Dest0.Set(4+LangNo,w->Row,hm);
			}
		}
		Row++;
	}
	return true;
}

bool	CombinedXLSX::SaveToDest(LanguagePack &LangPack)
{
	int	LangCount=LangPack.GetCount();
	wchar_t **ExcelFont=new wchar_t *[LangCount];
	for(int i=0;i<LangCount;i++){
		ExcelFont[i]=NULL;
	}
	for(LanguageClass *f=LangPack.GetFirst();f!=NULL;f=f->GetNext()){
		wchar_t	WBuff[100];
		memset(WBuff,0,sizeof(WBuff));
		f->ExcelFont.toWCharArray(WBuff);
		if(f->ColumnNo<LangCount){
			int	Len = wcslen(WBuff);
			ExcelFont[f->ColumnNo]=new wchar_t[Len+1];
			*(ExcelFont[f->ColumnNo] +Len)=L'\0';
			wcscpy(ExcelFont[f->ColumnNo],WBuff);
		}
	}

	if(Dest0.SaveFromXLSXFile(Dest1,DestFile.absoluteFilePath(),ExcelFont,LangCount)==false){
		return false;
	}
	for(int i=0;i<LangCount;i++){
		if(ExcelFont[i]!=NULL){
			delete	[]ExcelFont[i];
		}
	}
	delete	[]ExcelFont;
	return true;
}


QString	CombinedXLSX::GetDestFileName(void)
{
	return DestFile.fileName();
}

QString	CombinedXLSX::GetSourceFileName(void)
{
	return SourceFile.fileName();
}

CombinedXLSX::StringLine	*CombinedXLSX::SearchString(QString &FileLS ,QString &ID)
{
	for(StringLine *s=StringLineContainer.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->FileLS==FileLS && s->ID==ID){
			return s;
		}
	}
	return NULL;
}
	
CombinedXLSX::UILine		*CombinedXLSX::SearchUI( QString &ClassName
													,QString &TypeName
													,QString &ObjectName
													,QString &PropertyName
													,QString &Str1)
{
	for(UILine *s=UILineContainer.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ClassName==ClassName && s->TypeName==TypeName && s->ObjectName==ObjectName && s->PropertyName==PropertyName){
			if(s->Str1==Str1){
				return s;
			}
		}
	}
	for(UILine *s=UILineContainer.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ClassName==ClassName && s->TypeName==TypeName && s->ObjectName==ObjectName && s->PropertyName==PropertyName){
			return s;
		}
	}
	return NULL;
}