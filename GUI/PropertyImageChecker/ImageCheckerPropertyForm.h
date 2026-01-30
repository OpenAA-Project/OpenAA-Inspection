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

#ifndef IMAGECHECKERPROPERTYFORM_H
#define IMAGECHECKERPROPERTYFORM_H

#include "ui_ImageCheckerPropertyForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XImageChecker.h"
#include <QTabBar>

class ImageCheckerPropertyForm : public GUIFormBase
{
	Q_OBJECT

	QTabBar		PageTab;
	ImageCheckerRegData	*CurrentRegData;
public:
	ImageCheckerPropertyForm(LayersBase *Base ,QWidget *parent = 0);
	~ImageCheckerPropertyForm();

	bool	ModeLightWhole;
	bool	ModeParamEntry;
	bool	ModeCamZ;
	bool	ModeResolution;
	bool	ModeSlide;
	bool	ModeIncline;

	//virtual	void	BuildForShow(void);
	void	CalcOnShow(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void GetFromWindow(ImageCheckerRegData &Data);
	void SetToWindow(ImageCheckerRegData &Data);
	void SetValueToWindow(ImageCheckerRegData &Data);

	void SetDrawMode(void);
	void	GetRegDataInPage(int Page,struct ImageCheckerRegData &Data);
	void	SetRegDataInPage(int Page,struct ImageCheckerRegData &Data);

	QString		GetInitialFileName(void);
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private:
	Ui::ImageCheckerPropertyFormClass ui;

private slots:
	void on_toolButtonParamEntry_clicked();
	void on_toolButtonIncline_clicked();
	void on_toolButtonSlide_clicked();
	void on_toolButtonResolution_clicked();
	void on_pushButtonSetRegData_clicked();
	void on_pushButtonMeasue_clicked();
	void on_toolButtonLightWhole_clicked();
	void on_toolButtonCamZ_clicked();
	void SlotTabChanged ( int index ) ;
};

//============================================================================

class	GUICmdAddManual : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	ImageCheckerThreshold::__ImageCheckerRegMode		Mode;

	GUICmdAddManual(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetRegData : public GUICmdPacketBase
{
public:
	struct	ImageCheckerRegData	RegData;

	GUICmdSetRegData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqRegData : public GUICmdPacketBase
{
public:

	GUICmdReqRegData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendRegData : public GUICmdPacketBase
{
public:
	ImageCheckerRegData	RegData;

	GUICmdSendRegData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqValue : public GUICmdPacketBase
{
public:
	GUICmdReqValue(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckValue : public GUICmdPacketBase
{
public:
	bool				Effective;
	ImageCheckerRegData	RegData;

	GUICmdAckValue(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeDrawMode : public GUICmdPacketBase
{
public:
	ImageCheckerThreshold::__ImageCheckerRegMode		Mode;

	GUICmdChangeDrawMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // IMAGECHECKERPROPERTYFORM_H