#include "XExcelOperator.h"
#include "swap.h"
#include "libxl.h"
using namespace libxl;

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t	*ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

//================================================================================
bool	QStringListListXLSX::LoadFromXLSXFile(int sheetNo ,const QString &FileName)
{
    Book* XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);

	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	FileName.toWCharArray(FileNameStr);
	if(XLSXBook->load(FileNameStr)==false){
		const	char	*ErrorMsg=XLSXBook->errorMessage();
		return false;
	}
		
	Sheet* sheet = XLSXBook->getSheet(sheetNo);
	if(sheet){
		int	LastRow=sheet->lastRow();
		int	LastCol=sheet->lastCol();
		for(int row=0;row<=LastRow;row++){
			QStringList	ColList;
			for(int col=0;col<=LastCol;col++){
				const wchar_t	*pp= sheet->readStr(row, col);
				if(pp!=NULL){
					QString	H=QString::fromWCharArray (pp);
					ColList.append(H);
				}
				else{
					double	d=sheet->readNum(row, col);
					ColList.append(QString::number(d,'f'));
				}
			}
			append(ColList);
        }
        XLSXBook->release();
		//delete	XLSXBook;
		return true;
	}
	delete	XLSXBook;
	return false;
}

bool	QStringListListXLSX::SaveFromXLSXFile(QStringListListXLSX &SheetExcel1,const QString &FileName
											 ,wchar_t **ExcelFont ,int FontCount)
{
    Book* XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);

	Format	*LangEN	=XLSXBook->addFormat();
	Font	*FntEN	=XLSXBook->addFont();
	FntEN->setName(L"Arial");
	LangEN->setFont(FntEN);

	Format	**LangOnj	=new Format*[FontCount];
	Font	**FntObj	=new Font  *[FontCount];
	for(int i=0;i<FontCount;i++){
		LangOnj[i]	=XLSXBook->addFormat();
		FntObj[i]	=XLSXBook->addFont();
		if(ExcelFont[i]!=NULL){
			FntObj[i]->setName(ExcelFont[i]);
			LangOnj[i]->setFont(FntObj[i]);
		}
		else{
			LangOnj[i]->setFont(FntEN);
		}
	}

	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	FileName.toWCharArray(FileNameStr);

	bool	UIMode=false;
	Sheet	*sheet=XLSXBook->addSheet(L"Language");
	for(int row=0;row<count();row++){
		QStringList	LList=at(row);
		for(int col=0;col<LList.count();col++){
			wchar_t	Buff[20000];
			memset(Buff,0,sizeof(Buff));
			LList[col].toWCharArray(Buff);
			if(LList[0]==/**/"UI"){
				UIMode=true;
			}
			if(UIMode==false && col>=2){
				int	n=col-2;
				if(n<FontCount){
					sheet->setCellFormat(row, col,LangOnj[n]);
				}
				else{
					sheet->setCellFormat(row, col,LangEN);
				}
			}
			else if(col>=4){
				int	n=col-4;
				if(n<FontCount){
					sheet->setCellFormat(row, col,LangOnj[n]);
				}
				else{
					sheet->setCellFormat(row, col,LangEN);
				}
			}

			sheet->writeStr(row,col,Buff);
		}
	}

	Sheet	*sheet2=XLSXBook->addSheet(L"Define");
	for(int row=0;row<SheetExcel1.count();row++){
		QStringList	LList=SheetExcel1.at(row);
		for(int col=0;col<LList.count();col++){
			wchar_t	Buff[20000];
			memset(Buff,0,sizeof(Buff));
			LList[col].toWCharArray(Buff);
			sheet2->setCellFormat(row, col,LangEN);
			sheet2->writeStr(row,col,Buff);
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