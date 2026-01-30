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

#ifndef SHOWTOTALCOUNTFORM_H
#define SHOWTOTALCOUNTFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowTotalCountForm;
}

class ShowTotalCountForm : public GUIFormBase
{
    Q_OBJECT

    int64   TotalCount  ;
    int64   OKCount     ;
    int64   NGCount     ;
    int64   LotTotalCount  ;
    int64   LotOKCount     ;
    int64   LotNGCount     ;
public:
    explicit ShowTotalCountForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowTotalCountForm();

    virtual void	ShowInPlayer(int64 shownInspectionID)   override;
    virtual void	StartLot	(void)  override;
private slots:
    void on_pushButtonReset_clicked();
    void	ResizeAction();
private:
    Ui::ShowTotalCountForm *ui;

    void    ShowCounter(void);
};

//=====================================================================================

class	GUICmdReqResult : public GUICmdPacketBase
{
public:
	int64		ShownInspectionID;

	GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendResult : public GUICmdPacketBase
{
public:
	bool	ResultOK;

	GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // SHOWTOTALCOUNTFORM_H