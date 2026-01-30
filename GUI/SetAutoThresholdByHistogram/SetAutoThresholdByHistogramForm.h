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

#ifndef SETAUTOTHRESHOLDBYHISTOGRAMFORM_H
#define SETAUTOTHRESHOLDBYHISTOGRAMFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class SetAutoThresholdByHistogramForm;
}

class SetAutoThresholdByHistogramForm : public GUIFormBase
{
    Q_OBJECT
public:
    int32   LibType;
    int32   LibID;
    IntList HistID;
    int32   Strength;
	QString	ButtonName;

    explicit SetAutoThresholdByHistogramForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~SetAutoThresholdByHistogramForm();

    virtual void	ReadyParam(void)    override;
    virtual void	BuildForShow(void)  override;
	virtual	bool	SaveContent(QIODevice *f)   override;
	virtual	bool	LoadContent(QIODevice *f)   override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_horizontalSliderStrength_valueChanged(int value);
    void on_toolButton_clicked();

private:
    Ui::SetAutoThresholdByHistogramForm *ui;

	void    ShowStrength(void);
	void    ShowSlider(void);
	void    UpdateThresholdByHistogram(void);
};

class	GUICmdSetAutoThresholdByHistogram: public GUICmdPacketBase
{
public:
    int32   LibType;
    int32   LibID;
    IntList HistID;
    int32   Strength;

	GUICmdSetAutoThresholdByHistogram(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SETAUTOTHRESHOLDBYHISTOGRAMFORM_H