/*
 * Copyright (C) 2021
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

#ifndef NGLISTFORM_H
#define NGLISTFORM_H

#include <QDialog>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "mtQTableWidget.h"
#include "XDisplayImage.h"
#include "DisplayNGListButton.h"
#include "GeneralTabSheet.h"

namespace Ui {
class NGListForm;
}

class	DisplayNGListButton;

class NGListForm : public QDialog
{
    Q_OBJECT
    
	LayersBase *LBase;
///	ErrorGroupPack	*ErrorGroupData;

	GeneralTabSheet	*pGeneralTabSheet;
	int		NGSize;

public:
	int32	WidthLineNumber;
	int32	WidthPageNumber;
	int32	WidthPosition;
	int32	WidthLocationName;
	int32	WidthCause;

    explicit NGListForm(LayersBase *Base ,QWidget *parent = 0);
    ~NGListForm();

	mtQTableWidget	*GetNGList()					{	return	twNGList;		}
	LayersBase *GetLayersBasePointer()				{	return	LBase;			}
	void	SetImagePanelName(QString Name)			{	ImagePanelName=Name;	}
///	void	SetErrorGroupData(ErrorGroupPack *Data);
	void	SetNGCount(int Value)					;
	void	SetNGPointCount(int Value)				;
	void	SetDisplayImage(DisplayImage *D)		{	DisplayTargetImagePanel=D;	}
	void	SetZoomRate(double Rate)				{	ZoomRate=Rate;			}
	void	SetGeneralTabSheet(GeneralTabSheet *p)	{	pGeneralTabSheet=p;		}
	void	SetNGSize(int Size)						{	NGSize=Size;			}

	void	SetThumbnailCount(int Cnt)				{	twNGList->SetThumbnailCount(Cnt);	}
	void	ConnectItemSelectionChanged(bool Enable);

signals:
	void	SignalClose();

private slots:
	void	twNGListKeyDown();
//	void	twNGListRowChanged(const QModelIndex &CIndex);	//NG���X�g��RowChanged�C�x���g
	void	twNGListitemSelectionChanged();	//NG���X�g��RowChanged�C�x���g

private:
    Ui::NGListForm *ui;

	mtQTableWidget		*twNGList;
	DisplayNGListButton	*pDisplayNGListButton;
	QWidget				*ParentWidget;

	QString ImagePanelName;	//TargetImagePanelName
	DisplayImage *DisplayTargetImagePanel;
	double	ZoomRate;
	int		PreviousRow;

	int		ThumbnailCount;

	QWidget	*GetParentWidget();
};

#endif // NGLISTFORM_H