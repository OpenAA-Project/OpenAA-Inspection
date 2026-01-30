/*
 * Copyright (C) 2017
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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