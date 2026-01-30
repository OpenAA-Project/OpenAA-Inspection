/*
 * Copyright (C) 2023
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

#if	!defined(XGENERALDIALOG_H)
#define	XGENERALDIALOG_H

#include<QDialog>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	LibFolderForm;

class	GeneralDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	QWidget	*Client;
	QObject	*ClientParent;
	bool DeleteCliInClose;

public:
	GeneralDialog(LayersBase *Base,QWidget *cli ,QWidget * parent,bool _DeleteCliInClose=true);
	/*
	parent��NULL�ɂ����ƁA�e�q�֌W���Ȃ��Ȃ��ăE�C���h�E���T���Ȃ��Ȃ��̂Ńf�t�H���gNULL���p�~
	*/

	~GeneralDialog(void);

	virtual	void closeEvent ( QCloseEvent * event ) 	override;

protected:
	virtual	void resizeEvent ( QResizeEvent * event )	override;

private slots:
	void SlotClose();
};

class GeneralLibFolderForm : public QObject
{
	Q_OBJECT

	LibFolderForm	*pLibFolderForm;
public:
	GeneralLibFolderForm(int LibType,LayersBase *base,QWidget *parent);
	~GeneralLibFolderForm();

    int		CreateNewFolder(void);
    int		SetLibType(int libType);
    void	SetCurrentLibFolder(int LibFolderID);
    void	Show(void);
    void	Drop(int FolderParentID ,int LibFolderID , QWidget *w);
    void	FitToFrame(QWidget *ParentFrame);

	void	move(int x,int y);
	void	resize(int w ,int h);
signals:
    void	SelectLibFolder(int LibFolderID ,QString FolderName);
    void	SignalDrop(int FolderParentID ,int LibFolderID , QWidget *w);
private slots:
	void	SlotSelectLibFolder(int,QString s);
	void	SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w);
};

bool	ExeSelectLibFolderDialog(int LibType ,LayersBase * base, QWidget *parent
								 ,int	&RetSelectedLibFolderID
								 ,QString &RetSelectedFolderName);
bool	ExeSelectLibraryForm(int LibType ,LayersBase * base, QWidget *parent
								 ,int	&RetSelectedLibID
								 ,QString &RetSelectedLibName);

bool	ExeSelectPhasePageLayerDialog(LayersBase *base
									,int &RetSelectPhase
									,int &RetSelectPage
									,int &RetSelectLayer);
#endif