#if	!defined(XSaveCSVInReview_H)
#define	XSaveCSVInReview_H

#include <QString>
#include "XDateTime.h"

#include "XTypeDef.h"
#include "NList.h"
#include "ReviewStructureItems.h"

class	ForSaveTotalLot
{
public:
	int		InspectedMachine;
	int		MasterIDTop;
	int		MachineIDTop;
	QString	MasterNameTop;
	QString	LotTableNameTop;
	QString	LotNameTop;

	int		ReviewWorkerID;
	QString	ReviewWorkerName;

	int		MasterIDBack;
	int		MachineIDBack;
	QString	MasterNameBack;
	QString	LotTableNameBack;
	QString	LotNameBack;

	int		CountOK;
	int		CountNG;
	int		CountHalt;

	int		NGCountTop;
	int		NGCountBack;
	XDateTime	InspectionTimeFirst;
	XDateTime	InspectionTimeLast;

	NPListPack<ForSaveOneInspection>	HistryList;
	ForSaveNGPoint						*FocusPoint;

	int	CurrentRow;

	ForSaveTotalLot(void);

	bool	SaveCSV(const QString &FileName,ReviewPIBase *Parent);
	bool	LoadCSV(const QString &FileName);
	bool	AppendListing(const QString &ListingFileName ,const QString &CSVFileName);

	ForSaveOneInspection	*GetFirstInspection(void);
	ForSaveOneInspection	*GetLastInspection(void);

	XDateTime	GetFirstReviewTime(void);
	XDateTime	GetLastReviewTime(void);

	int	GetFKeyCount(int key);

	int	GetTopNGCount(void);
	int	GetBottomNGCount(void);

public:
	bool	PutListingTitle(const QString &ListingFileName);
};

#endif