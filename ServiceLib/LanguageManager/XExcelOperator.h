#if	!defined(XEXCELOPERATOR_H)
#define	XEXCELOPERATOR_H

#include <QString>
#include "XCSV.h"


class	QStringListListXLSX : public QStringListListCSV
{
public:
	QStringListListXLSX(void){}

	bool	LoadFromXLSXFile(int sheetNo ,const QString &FileName);
	bool	SaveFromXLSXFile(QStringListListXLSX &Sheet1,const QString &FileName
							,wchar_t **ExcelFont,int FontCount);
};


#endif