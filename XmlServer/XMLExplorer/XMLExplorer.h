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

#ifndef XMLEXPLORER_H
#define XMLEXPLORER_H

#include <QMainWindow>
#include "ui_XMLExplorer.h"
#include "XMLClient.h"
#include "XParamBase.h"	
#include "XRememberer.h"
#include "XServiceForLayers.h"

class	ExplorerParam : public ParamBase
{
public:
	ExplorerParam(void){}

	virtual	QString	GetSavedFileName(void)	override{	return QString("XMLExplorerSetting.dat");	}
	virtual	QString	GetDataText(void)		override{	return QString("XMLExplorerSetting");		}

	void	ShowClient(int id);
protected:
	virtual	QString	GetDefaultFileName(void)	override{	return QString("XMLExplorerSetting.dat");	}
};


class XMLExplorer : public QMainWindow,public ControlRememberer
{
	Q_OBJECT

	XMLServerHandle	*Server;
	QStringList	EnumResultList;
	ExplorerParam	EParam;

public:
	XMLExplorer(LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~XMLExplorer();

	XMLServerHandle	*GetServer(void)	{	return Server;	}
	ExplorerParam	&GetEParam(void)	{	return EParam;	}
	void	SaveDefault(void);

private:
	Ui::XMLExplorerClass ui;

	virtual	void	closeEvent ( QCloseEvent * event ) override;

public slots:
	void	SlotConnect();
	void	SlotOpenXMLOperation();
	void	SlotDup();
	void	slotCloseOperation();

	void	SlotInsertXML();
	void	slotUpdateXML();
	void	slotDeleteXML();
	void	slotInsUpdateAttr();
	void	slotDeleteAttr();
	void	slotSelect();
	void	slotSelectFirst();
	void	slotSelectLast();
	void	slotSelectNext();
	void	slotSelectPrev();
	void	slotChildSelect();
	void	slotChildSelectFirst();
	void	slotChildSelectLast();
	void	slotChildSelectNext();
	void	slotChildSelectPrev();
	void	slotEnumTable();

	void	SlotDisconnectFromServer();
private slots:

        void on_pushButtonCopyPointer_clicked();
        void on_listWidgetTableList_doubleClicked(const QModelIndex &index);
        void on_pushButtonSetting_clicked();
        void on_pushButtonExecuteDeleteMultiXML_clicked();
        void on_pushButtonBackup_clicked();
        void on_pushButtonRestore_clicked();
        void on_pushButtonRemove_clicked();
};



#endif // XMLEXPLORER_H