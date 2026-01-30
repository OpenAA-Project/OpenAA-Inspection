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

#ifndef AUTOSAVEIMAGEVIEWLISTFORM_H
#define AUTOSAVEIMAGEVIEWLISTFORM_H

#include "XGUIFormBase.h"
#include "ui_AutoSaveImageViewListForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAutoSaveImage.h"
#include "XAutoSaveImagePacket.h"

class AutoSaveImageViewListForm : public GUIFormBase
{
	Q_OBJECT

public:
	AutoSaveImageViewListForm(LayersBase *Base ,QWidget *parent = 0);
	~AutoSaveImageViewListForm();

	virtual void BuildForShow(void)	override;

	SaveImageFileListContainer itmLst;
	SaveImageFileListContainer RawItmLst;
	int	LastMachineID;
		;
	//int itmCnt;
	QString	LotFilter;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	QStringList	PathLists;

private:
	Ui::AutoSaveImageViewListFormClass ui;

	AutoSaveImageBase	*GetAutoSaveImageBase(void);

	QString Drv1;
	QString Drv2;

	bool mkFileList(QStringList &PathList
					,SaveImageFileListContainer &ItmLst);
	void mkDrvList();
	bool chkImageExist(QString drv);

	void setPanelParam();
	QString defFnam;

	void dbgFileListPrt();

	int			CurrentMachineID;

private slots:
	void on_pushButton_Load_clicked();
	void on_pushButton_Save_clicked();
	void on_pushButtonUpdate_clicked();
	void on_tableWidget_clicked(const QModelIndex &);
	void ResizeAction(void);
};

class	GUICmdReqLoad : public GUICmdPacketBase
{
public:
	QString FileName;

	GUICmdReqLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLoad : public GUICmdPacketBase
{
public:
	QString FileName;

	GUICmdAckLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
#endif // AUTOSAVEIMAGEVIEWLISTFORM_H