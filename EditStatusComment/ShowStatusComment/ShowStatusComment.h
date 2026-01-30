/*
 * Copyright (C) 2025
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

#ifndef SHOWSTATUSCOMMENT_H
#define SHOWSTATUSCOMMENT_H

#include <QMainWindow>
#include "ui_ShowStatusComment.h"
#include <QLocalSocket>
#include <QTimer>

class ShowStatusComment : public QMainWindow 
{
	Q_OBJECT

	QLocalSocket	*Sock;
	QTimer	TM;
	bool	ConnectedOnce;
public:
	ShowStatusComment(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ShowStatusComment();

private:
	Ui::ShowStatusCommentClass ui;

	virtual	void resizeEvent ( QResizeEvent * event )	override;
	virtual	void closeEvent ( QCloseEvent * event )		override;
	virtual	void showEvent ( QShowEvent * event )		override;

	QString	GetPositionFileName(void)	{	return /**/"ShowStatusComment.dat";	}
	void	OutputPosition(void);
private slots:
	void	SlotDisconnected();
	void	SlotReadyRead() ;
	void	SlotTimeOut();
};

#endif // SHOWSTATUSCOMMENT_H