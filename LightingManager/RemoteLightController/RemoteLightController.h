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

#ifndef REMOTELIGHTCONTROLLER_H
#define REMOTELIGHTCONTROLLER_H

#include <QMainWindow>
#include <QPushButton>
#include "ui_RemoteLightController.h"
#include "XRemoteLightController.h"
#include "XRemoteLightLocalHost.h"
#include "XServiceForLayers.h"
#include <QTimer>

class	LightItemButton : public QPushButton ,public NPList<LightItemButton>
{
	Q_OBJECT

	RemoteLightItem		*Item;
public:
	LightItemButton(RemoteLightItem *item , QWidget *parent):QPushButton(parent),Item(item){}

	RemoteLightItem		*GetItem(void)	{	return Item;	}
signals:
	void	SignalClicked(int ID);

private slots:
	void	SlotClicked();
};

class	LightList : public NPList<LightList>
{
public:
	int ID;
	QString Name;
	QString Remark;

	LightList(int id, const QString &name ,const QString &remark)
		:ID(id),Name(name),Remark(remark){}
};


class RemoteLightController : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QString		LoadedFileName;
	NPListPack<LightItemButton>	Buttons;
	RemoteLightContainer		RemoteLightData;
	FromProgram					FromProgramHost;
	QTimer	TM;
public:
	RemoteLightController(LayersBase *Base 
						 ,const QString &LoadedFile,bool StartON ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~RemoteLightController();

	void	PutButtons(void);
	bool	LoadFromFile(const QString &FileName);
	bool	LoadFromFile(QIODevice &File);
	bool	SaveToFile(QIODevice &File);

	void	ShowLightList(void);

	NPListPack<LightList>	LightListContainer;
	int		CurrentRowOnList;
	int		LastCurrentLightID;

	void	SetLightID(int lightID);
	void	SetLightOn(bool lightOn);
	void	SetLightRequest(BYTE *ReqData,int ReqDataLength);

protected:
	virtual	void	moveEvent ( QMoveEvent * event )	override;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	QString	GetPositionFileName(void)	{	return QString(/**/"RemoteLightControllerPosition.dat");	}
	void	SavePosition(void);
	

private slots:
    void on_pushButtonSetting_clicked();
    void on_toolButtonOnOff_clicked();
    void on_pushButtonSaveAll_clicked();
    void on_pushButtonLoadAll_clicked();
    void on_pushButtonClose_clicked();
	void	SlotClicked(int ID);

    void on_pushButtonUpdate_clicked();
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_2_clicked();
    void on_pushButtonDelete_clicked();

    void on_toolButtonManagementMode_clicked();
	void	SlotTimerBreak();
private:
	Ui::RemoteLightControllerClass ui;

	void	LoadRowData(int Row);
};

#endif // REMOTELIGHTCONTROLLER_H