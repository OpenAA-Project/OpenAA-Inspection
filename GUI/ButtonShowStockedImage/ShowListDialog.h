/*
 * Copyright (C) 2022
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

#ifndef SHOWLISTDIALOG_H
#define SHOWLISTDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "mtGraphicUnit.h"
#include "ButtonShowStockedImage.h"

namespace Ui {
class ShowListDialog;
}

class	ShowListDialog;
class	ButtonShowStockedImage;

class	ChildImagePanel : public mtGraphicUnit,public ServiceForLayers
{
	Q_OBJECT

	ShowListDialog	*Parent;
	QImage		*Img;
public:

protected:
	ImageBufferWithInfo	*Buffer;

public:

	ChildImagePanel(LayersBase *Base,ShowListDialog *parent);
	virtual	~ChildImagePanel(void);
	
	void	SetImage(ImageBufferWithInfo *buff);

private slots:
	void	SlotOnPaint(QPainter &pnt);
};


class ShowListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ChildImagePanel	Panel;
public:
	ButtonShowStockedImage	*Parent;
	NPListPack<ImageBufferWithInfoPointerContainer> List;

    explicit ShowListDialog(ButtonShowStockedImage *p,LayersBase *Base ,QWidget *parent = 0);
    ~ShowListDialog();
    
private slots:
    void on_tableWidgetShotList_clicked(const QModelIndex &index);
    void on_tableListInOneShot_clicked(const QModelIndex &index);

private:
    Ui::ShowListDialog *ui;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // SHOWLISTDIALOG_H