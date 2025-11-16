#include "MakeLanguageDialog.h"
#include "XGUILanguage.h"

#include "libxl.h"
using namespace libxl;

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t *ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

    
bool MakeLanguageDialog::LoadExcelFile(LanguagePack &LPack ,QString &ExcelFileName,GUILanguageContainer &LangC)
{
    Book* XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);

	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	ExcelFileName.toWCharArray(FileNameStr);
	if(XLSXBook->load(FileNameStr)==false){
		const	char	*ErrorMsg=XLSXBook->errorMessage();
		return false;
	}
	int	sheetNo=0;
	Sheet* sheet = XLSXBook->getSheet(sheetNo);
	if(sheet){
		for(GUILanguageList *g=LangC.GetFirst();g!=NULL;g=g->GetNext()){
			g->LanguageText.RemoveAll();
		}
		int	LastRow=sheet->lastRow();
		int	LastCol=sheet->lastCol();

		for(int row=1;row<=LastRow;row++){
			QString	DLLRoot;
			QString	DLLName;
			QString	InstName;
			QString	MemberName;
			const wchar_t	*pDLLRoot= sheet->readStr(row, 0);
			if(pDLLRoot!=NULL){
				DLLRoot=QString::fromWCharArray (pDLLRoot);
			}
			const wchar_t	*pDLLName= sheet->readStr(row, 1);
			if(pDLLName!=NULL){
				DLLName=QString::fromWCharArray (pDLLName);
			}
			const wchar_t	*pInstName= sheet->readStr(row, 2);
			if(pInstName!=NULL){
				InstName=QString::fromWCharArray (pInstName);
			}
			const wchar_t	*pMemberName= sheet->readStr(row, 3);
			if(pMemberName!=NULL){
				MemberName=QString::fromWCharArray (pMemberName);
			}
			if(DLLRoot.isEmpty()==false
			&& DLLName.isEmpty()==false
			&& InstName.isEmpty()==false
			&& MemberName.isEmpty()==false){
				GUILanguageList	*g=LangC.Find(	 DLLRoot
												,DLLName
												,InstName
												,MemberName);
				if(g==NULL){
					g=new GUILanguageList();
					g->DLLRoot	=DLLRoot;
					g->DLLName	=DLLName;
					g->InstName	=InstName;
					g->MemberName=MemberName;
					LangC.AppendList(g);
				}
				for(int col=4;col<=LastCol;col++){
					int	LanguageCode=col-4;
					const wchar_t	*pTxt= sheet->readStr(row, col);
					QString	Text;
					if(pTxt!=NULL){
						Text=QString::fromWCharArray (pTxt);
					}
					if(Text.isEmpty()==false){
						LanguageStringList	*s=g->LanguageText.FindLanguage(LanguageCode);
						if(s==NULL){
							s=new LanguageStringList();
							s->LanguageCode=LanguageCode;
							g->LanguageText.AppendList(s);
						}
						QStringList	LList=Text.split(/**/"\n");
						if(LList.count()==1){
							s->Text=Text;
						}
						else{
							s->TextList=LList;
						}
					}
				}
			}
		}
	}
	XLSXBook->release();
	return true;
}
    
bool MakeLanguageDialog::SaveExcelFile(LanguagePack &LPack 
										,QString &ExcelFileName
										,GUILanguageContainer &LangC)
{
    Book* XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);

	Format	*LangEN	=XLSXBook->addFormat();
	Font	*FntEN	=XLSXBook->addFont();
	FntEN->setName(L"Arial");
	LangEN->setFont(FntEN);

	int	FontCount=LPack.GetCount();
	Format	**LangOnj	=new Format*[FontCount];
	Font	**FntObj	=new Font  *[FontCount];
	for(int i=0;i<FontCount;i++){
		LanguageClass	*C=LPack[i];
		LangOnj[i]	=XLSXBook->addFormat();
		FntObj[i]	=XLSXBook->addFont();
		if(C->ExcelFont.isEmpty()==false){
			wchar_t	ExcelFontStr[256];
			memset(ExcelFontStr,0,sizeof(ExcelFontStr));
			C->ExcelFont.toWCharArray(ExcelFontStr);
			FntObj[i]->setName(ExcelFontStr);
			LangOnj[i]->setFont(FntObj[i]);
		}
		else{
			LangOnj[i]->setFont(FntEN);
		}
	}

	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	ExcelFileName.toWCharArray(FileNameStr);

	Sheet	*sheet=XLSXBook->addSheet(L"GUI");
	wchar_t	Buff[20000];

	int	row=0;
	for(int col=0;col<(4+FontCount);col++){
		sheet->setCellFormat(row, col,LangEN);
		memset(Buff,0,sizeof(Buff));
		QString	Str;
		if(col==0){
			Str="DLLRoot";
		}
		else if(col==1){
			Str="DLLName";
		}
		else if(col==2){
			Str="InstName";
		}
		else if(col==3){
			Str="MemberName";
		}
		else{
			LanguageClass	*C=LPack[col-4];
			Str=C->LanguageName;
		}
		memset(Buff,0,sizeof(Buff));
		Str.toWCharArray(Buff);
		sheet->writeStr(row,col,Buff);
	}
	row++;
	for(GUILanguageList *g=LangC.GetFirst();g!=NULL;g=g->GetNext(),row++){
		for(int col=0;col<(4+FontCount);col++){
			sheet->setCellFormat(row, col,LangEN);
			wchar_t	Buff[20000];
			memset(Buff,0,sizeof(Buff));
			QString	Str;
			if(col==0){
				Str=g->DLLRoot;
			}
			else if(col==1){
				Str=g->DLLName;
			}
			else if(col==2){
				Str=g->InstName;
			}
			else if(col==3){
				Str=g->MemberName;
			}
			else{
				int		LanguageCode=col-4;
				sheet->setCellFormat(row, col,LangOnj[LanguageCode]);
				LanguageClass	*C=LPack[LanguageCode];
				LanguageStringList	*s=g->LanguageText.FindLanguage(LanguageCode);
				if(s!=NULL){
					if(s->Text.isEmpty()==false){
						Str=s->Text;
					}
					else{
						int	ListCount=s->TextList.count();
						for(int n=0;n<ListCount;n++){
							Str+=s->TextList[n];
							if((n+1)<ListCount){
								Str+=/**/"\r\n";
							}
						}
					}
				}
			}
			memset(Buff,0,sizeof(Buff));
			Str.toWCharArray(Buff);
			sheet->writeStr(row,col,Buff);
		}
	}
	if(XLSXBook->save(FileNameStr)==false){
		delete	XLSXBook;
		delete	[]LangOnj;
		delete	[]FntObj;
		return false;
	}
	XLSXBook->release();
	//delete	XLSXBook;

	delete	[]LangOnj;
	delete	[]FntObj;

	return true;
}
