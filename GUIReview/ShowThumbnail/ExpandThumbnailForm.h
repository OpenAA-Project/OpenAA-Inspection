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

#if	!defined(ExpandThumbnailDialog_h)
#define	ExpandThumbnailDialog_h

#include <QDialog>
#include "ui_ExpandThumbnailForm.h"

class	ShowThumbnail;
class Thumbnail;


class ExpandThumbnailDialog : public QDialog
{
	Q_OBJECT

	ShowThumbnail *MainParent;
public:
	ExpandThumbnailDialog(ShowThumbnail *MainParent ,QWidget *parent=NULL, Qt::WindowFlags flags=0);

public:
	void setThumbnail(Thumbnail *thumbnail);
	Thumbnail *getThumbnail(void) const { return myThumbnail; };

	void	Initial(void);
	int		KeyCode;
	bool	KeyType;

protected:
	virtual	void paintEvent(QPaintEvent *event)		override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
	virtual	void keyPressEvent(QKeyEvent *event)	override;
	virtual	void mousePressEvent(QMouseEvent *event)override;

public:
	void updateImage(void);

private slots:
    void on_pushButtonSetKey_clicked();

private:
	Ui::ExpandThumbnailForm ui;
	Thumbnail *myThumbnail;
	bool reqUpdate;
	bool drawNG;
};

#endif