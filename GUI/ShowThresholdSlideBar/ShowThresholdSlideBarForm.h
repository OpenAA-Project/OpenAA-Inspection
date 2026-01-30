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

#ifndef SHOWTHRESHOLDSLIDEBARFORM_H
#define SHOWTHRESHOLDSLIDEBARFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowThresholdSlideBarForm;
}

class ShowThresholdSlideBarForm : public GUIFormBase
{
    Q_OBJECT

    AlgorithmBase   *ABase;
    bool            EnableChange;
public:
    QString Title;
    QString AlgoDLLRoot;
    QString AlgoDLLName;
    int32   Layer;
    int32   LibID;
    int32   MemberID;
    int32   MinimumValue;
    int32   MaximumValue;

    enum DisplayUnit
    {
        _None
        ,_D1    //mm
        ,_D2    //mm2
        ,_D3    //mm3
    }ModeDisplayUnit;
    QString DisplayUnitStr;


    explicit ShowThresholdSlideBarForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowThresholdSlideBarForm();

    virtual void	ReadyParam(void)    override;
    virtual void	BuildForShow(void)  override;

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_spinBoxValue_valueChanged(int arg1);

private:
    Ui::ShowThresholdSlideBarForm *ui;
    void ShowUnit(int d);

};

//=========================================================================================================================

class	GUICmdReqThresholdSlider : public GUICmdPacketBase
{
public:
    QString AlgoDLLRoot;
    QString AlgoDLLName;
    int32   Layer;
    int32   LibID;
    int32   MemberID;

	GUICmdReqThresholdSlider(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAckThresholdSlider : public GUICmdPacketBase
{
public:
    int32   ValueInt;

	GUICmdAckThresholdSlider(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdSetThresholdSlider : public GUICmdPacketBase
{
public:
    QString AlgoDLLRoot;
    QString AlgoDLLName;
    int32   Layer;
    int32   LibID;
    int32   MemberID;
    int32   ValueInt;

	GUICmdSetThresholdSlider(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};




#endif // SHOWTHRESHOLDSLIDEBARFORM_H