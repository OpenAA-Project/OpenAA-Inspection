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

#ifndef BUTTONCHANGESERVERFORM_H
#define BUTTONCHANGESERVERFORM_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XChangeServerInfo.h"

namespace Ui {
class ButtonChangeServerForm;
}

class ButtonChangeServerForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	QString	Msg;
	QFont	CFont;

    explicit ButtonChangeServerForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonChangeServerForm();
    
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	ExeChangeServer(ChangeServerInfo *d);
	virtual	void	RxSync(QByteArray &f)	override;
private slots:
    void on_pushButton_clicked();
	void	ResizeAction();

private:
    Ui::ButtonChangeServerForm *ui;
};

class	GUICmdChangeServer : public GUICmdPacketBase
{
public:
	ChangeServerInfo	ServerData;

	GUICmdChangeServer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCHANGESERVERFORM_H