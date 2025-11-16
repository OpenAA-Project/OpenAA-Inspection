/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCSV.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XCSV.h"
#include <QTextStream>
#include <QTableWidget>
#include <QFile>
#include "XGeneralFunc.h"


bool	SaveCSV(QIODevice *f ,QTableWidget *W)
{
	QTextStream	F(f);

	int	ColumnCount=W->columnCount();
	for(int Row=0;Row<W->rowCount();Row++){
		for(int c=0;c<ColumnCount;c++){	
			QTableWidgetItem *r=W->item (Row, c);
			if(r!=NULL){
				if(c!=0){
					F<<",";
				}
				F<<"\"";
				F<<r->text();
				F<<"\"";
			}
		}
		F<<"\n";
	}
	return true;
}
