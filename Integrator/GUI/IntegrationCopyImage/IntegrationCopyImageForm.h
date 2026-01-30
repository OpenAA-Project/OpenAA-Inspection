/*
 * Copyright (C) 2020
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

#ifndef INTEGRATIONCOPYIMAGEFORM_H
#define INTEGRATIONCOPYIMAGEFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class IntegrationCopyImageForm;
}

class IntegrationCopyImageForm :  public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit IntegrationCopyImageForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationCopyImageForm();
    virtual	void	Prepare(void)	override;

	void	ExecuteCopy(void);
private slots:
    void on_PushButtonCopy_clicked();
	void	ResizeAction();
private:
    Ui::IntegrationCopyImageForm *ui;
};

//===========================================================================

class	IntegrationCmdCopyImage: public IntegrationCmdPacketBase
{
public:

	IntegrationCmdCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // INTEGRATIONCOPYIMAGEFORM_H