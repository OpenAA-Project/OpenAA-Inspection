#include "XExcelStringList.h"
#include "swap.h"
#include <QFile>
#include "XGeneralFunc.h"

#include <OpenXLSX.hpp>

using namespace std;
using namespace OpenXLSX;


//================================================================================
bool	QStringListListXLSX::LoadFromXLSXFile(int sheetNo ,const QString &FileName)
{
    XLDocument doc;
    
	const std::string	Str=FileName.toStdString();
	
	doc.open(Str);
	XLWorkbook wb=doc.workbook();

	if((doc.workbook().sheetCount()+1)>=sheetNo){
		auto sheet = doc.workbook().worksheet(sheetNo+1);	//1-based

		int	LastRow=sheet.rowCount();
		int	LastCol=sheet.columnCount();
		for(int row=0;row<=LastRow;row++){
			QStringList	ColList;
			for(int col=0;col<=LastCol;col++){
				XLCellAssignable a=sheet.cell(row+1, col+1);

				if(a.empty()==false){
					if(a.value().type()==XLValueType::String){
						std::string	S=a.value().get<std::string>();
						QString	H=QString::fromStdString (S);
						ColList.append(H);
					}
					else if(a.value().type()==XLValueType::Float){
						double	D=a.value().get<double>();
						ColList.append(QString::number(D));
					}
					else if(a.value().type()==XLValueType::Integer){
						int	D=a.value().get<int>();
						ColList.append(QString::number(D));
					}
					else{
						std::string	S=a.value().get<std::string>();
						QString	H=QString::fromStdString (S);
						ColList.append(H);
					}
				}
				else{
					ColList.append("");
				}
			}
			append(ColList);
        }
		doc.close();
		return true;
	}
	doc.close();

	return false;
}

#include "xlsxwriter.h"

bool	QStringListListXLSX::SaveFromXLSXFile(QStringListListXLSX &SheetExcel1,const QString &FileName
											 ,wchar_t **ExcelFont ,int FontCount)
{
	char	FileNameStr[2048];
	::QString2Char(FileName, FileNameStr, sizeof(FileNameStr));
	
	lxw_workbook  *workbook  = workbook_new(FileNameStr);
    if (!workbook) {
		return false;
	}

	lxw_format *LangEN = workbook_add_format(workbook);
	if (LangEN) {
        format_set_font_name(LangEN, "Arial");
    }
	lxw_format	**LangOnj	=new lxw_format*[FontCount];
	for(int i=0;i<FontCount;i++){
		LangOnj[i]	=workbook_add_format(workbook);
		if (LangOnj[i]) {
			QString ExcelFont_unicode = QString::fromWCharArray(ExcelFont[i]);
			char	*FontChar=ExcelFont_unicode.toUtf8().data();
			format_set_font_name(LangOnj[i], FontChar);
		}
	}

	lxw_worksheet *sheet = workbook_add_worksheet(workbook,"Language");
	bool	UIMode=false;
	for(int row=0;row<count();row++){
		QStringList	LList=at(row);
		for(int col=0;col<LList.count();col++){
			char	*FontChar=LList[col].toUtf8().data();

			if(LList[0]==/**/"UI"){
				UIMode=true;
			}
			if(UIMode==false){
				int	n=col-2;
				if(n<FontCount){
					worksheet_write_string(sheet,(lxw_row_t)row,(lxw_col_t)col,FontChar,LangOnj[n]);
				}
				else{
					worksheet_write_string(sheet,(lxw_row_t)row,(lxw_col_t)col,FontChar,LangEN);
				}
			}
			else{
				int	n=col-4;
				if(n<FontCount){
					worksheet_write_string(sheet,(lxw_row_t)row,(lxw_col_t)col,FontChar,LangOnj[n]);
				}
				else{
					worksheet_write_string(sheet,(lxw_row_t)row,(lxw_col_t)col,FontChar,LangEN);
				}
			}
		}
	}

	lxw_worksheet *sheet2 = workbook_add_worksheet(workbook,"Define");
	for(int row=0;row<SheetExcel1.count();row++){
		QStringList	LList=SheetExcel1.at(row);
		for(int col=0;col<LList.count();col++){
			char	*FontChar=LList[col].toUtf8().data();
			worksheet_write_string(sheet2,(lxw_row_t)row,(lxw_col_t)col,FontChar,LangEN);
		}
	}

	int result = workbook_close(workbook);
	if(result!=0){
		return false;
	}

	return true;
}

