#include "MakeLanguageDialog.h"
#include "XGUILanguage.h"
#include "XGeneralFunc.h"
#include <OpenXLSX.hpp>

using namespace std;
using namespace OpenXLSX;
    
bool MakeLanguageDialog::LoadExcelFile(LanguagePack &LPack ,QString &ExcelFileName,GUILanguageContainer &LangC)
{
    XLDocument doc;
    
	const std::string	Str=ExcelFileName.toStdString();
	
	doc.open(Str);
	XLWorkbook wb=doc.workbook();
	int	sheetNo = 0;
	if((doc.workbook().sheetCount()+1)>=sheetNo){
		auto sheet = doc.workbook().worksheet(sheetNo+1);	//1-based

		for(GUILanguageList *g=LangC.GetFirst();g!=NULL;g=g->GetNext()){
			g->LanguageText.RemoveAll();
		}
		int	LastRow=sheet.rowCount();
		int	LastCol=sheet.columnCount();

		for(int row=1;row<=LastRow;row++){
			QString	DLLRoot		=QString::fromStdString (sheet.cell(row+1, 0+1).value().get<std::string>());
			QString	DLLName		=QString::fromStdString (sheet.cell(row+1, 1+1).value().get<std::string>());
			QString	InstName	=QString::fromStdString (sheet.cell(row+1, 2+1).value().get<std::string>());
			QString	MemberName	=QString::fromStdString (sheet.cell(row+1, 3+1).value().get<std::string>());

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
					QString	Text		=QString::fromStdString (sheet.cell(row+1, col+1).value().get<std::string>());

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
	doc.close();
	return true;
}

#include "xlsxwriter.h"
    
bool MakeLanguageDialog::SaveExcelFile(LanguagePack &LPack 
										,QString &ExcelFileName
										,GUILanguageContainer &LangC)
{
	char	FileNameStr[2048];
	::QString2Char(ExcelFileName, FileNameStr, sizeof(FileNameStr));
	
	lxw_workbook  *workbook  = workbook_new(FileNameStr);
    if (!workbook) {
		return false;
	}
	lxw_format *LangEN = workbook_add_format(workbook);
	if (LangEN) {
        format_set_font_name(LangEN, "Arial");
    }
	int	FontCount=LPack.GetCount();
	lxw_format	**LangOnj	=new lxw_format*[FontCount];
	for(int i=0;i<FontCount;i++){
		LanguageClass	*C=LPack[i];
		if(C->ExcelFont.isEmpty()==false){
			LangOnj[i]	=workbook_add_format(workbook);
			if(LangOnj[i]) {
				QString ExcelFont_unicode = C->ExcelFont;
				char	*FontChar=ExcelFont_unicode.toUtf8().data();
				format_set_font_name(LangOnj[i], FontChar);
			}
		}
	}

	lxw_worksheet *sheet = workbook_add_worksheet(workbook,"GUI");

	int	row=0;
	for(int col=0;col<(4+FontCount);col++){
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
		char	*FontChar=Str.toUtf8().data();
		worksheet_write_string(sheet,(lxw_row_t)row,(lxw_col_t)col,FontChar,LangEN);
	}
	row++;
	for(GUILanguageList *g=LangC.GetFirst();g!=NULL;g=g->GetNext(),row++){
		for(int col=0;col<(4+FontCount);col++){
			lxw_format	*Fmt=LangEN;

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
				Fmt=LangOnj[LanguageCode];

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
			char	*FontChar=Str.toUtf8().data();
			worksheet_write_string(sheet,(lxw_row_t)row,(lxw_col_t)col,FontChar,Fmt);
		}
	}
	int result = workbook_close(workbook);
	if(result!=0){
		return false;
	}

	return true;
}
