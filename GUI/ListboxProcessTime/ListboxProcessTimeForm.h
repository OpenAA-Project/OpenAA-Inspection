/*
 * Copyright (C) 2014
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

#ifndef LISTBOXPROCESSTIMEFORM_H
#define LISTBOXPROCESSTIMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ListboxProcessTimeForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDataAlgorithm.h"

class	ExecuteTimeAlgorithm : public ExecuteTimeClass
{
public:
	QString	DLLRoot;
	QString	DLLName;

	ExecuteTimeAlgorithm(void){}

	virtual	bool    Save(QIODevice *f);
    virtual	bool    Load(QIODevice *f);
	virtual	ExecuteTimeClass	&operator=(ExecuteTimeClass &src);
};



class ListboxProcessTimeForm : public GUIFormBase
{
	Q_OBJECT

public:
	ListboxProcessTimeForm(LayersBase *Base ,QWidget *parent = 0);
	~ListboxProcessTimeForm();

	int		AlgorithmCount;
	ExecuteTimeAlgorithm	**ListByPage;
private:
	Ui::ListboxProcessTimeFormClass ui;

private slots:
	void on_tableWidgetAlgorithm_clicked(const QModelIndex &);
	void on_pushButtonClear_clicked();
	void on_pushButtonView_clicked();
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqProcessTime : public GUICmdPacketBase
{
public:

	GUICmdReqProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendProcessTime : public GUICmdPacketBase
{
public:
	int						AlgorithmCount;
	ExecuteTimeAlgorithm	*ExecuteTimeData;
	DWORD					FilterTime;	

	GUICmdSendProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendProcessTime(void);

	void	MakeData(int localPage);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqClearProcessTime : public GUICmdPacketBase
{
public:

	GUICmdReqClearProcessTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif // LISTBOXPROCESSTIMEFORM_H