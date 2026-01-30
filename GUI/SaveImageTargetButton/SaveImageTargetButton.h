/*
 * Copyright (C) 2024
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


#ifndef SAVEIMAGETARGETBUTTON_H
#define SAVEIMAGETARGETBUTTON_H

#include "saveimagetargetbutton_global.h"
#include <QLabel>
#include <QTranslator>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ImageBuffer;
class	SaveImageTargetButton;

class	CmdReqSaveImage : public GUIDirectMessage
{
public:
	QString	FileName;
	enum	UsageImage
	{
		_SaveTargetImage	=0
		,_SaveRawImage		=1
		,_SaveCamImage		=2
	};
	UsageImage	UsageImageMode;
	bool	Success;
	int32	UseLayer;	//-1::Save all layers

	CmdReqSaveImage(LayersBase *base):GUIDirectMessage(base){	UsageImageMode=_SaveTargetImage;	}
	CmdReqSaveImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	UsageImageMode=_SaveTargetImage;	}
};

class	CmdReqSaveImageWithGeneralStocker : public GUIDirectMessage
{
public:
	bool	Success;

	CmdReqSaveImageWithGeneralStocker(LayersBase *base):GUIDirectMessage(base){	}
	CmdReqSaveImageWithGeneralStocker(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){		}
};

		
class	ThreadSave : public QThread ,public ServiceForLayers
{
	friend	class	SaveImageTargetButton;

	SaveImageTargetButton *Parent;
	CmdReqSaveImage::UsageImage CurrentTypeOfImage;
public:
	ImageBuffer	*IBuffer;
	volatile	bool	Saved;
	QString		FileName;
	volatile	bool	Terminated;
	int32		UseLayer;	//-1::Save all layers

	ThreadSave(QObject *ob,LayersBase *base,SaveImageTargetButton *parent);
	~ThreadSave(void);

	void	Allocate(void);
	ImageBuffer	*GetImageBuffer(int phase , int page ,int layer);

	bool	CopyFrom(CmdReqSaveImage::UsageImage TypeOfImage); 
	bool	SaveImage(QString FileName,CmdReqSaveImage::UsageImage TypeOfImage);

	virtual	void  run()	override;
};


class	SaveImageTargetButton : public GUIFormBase
{
	Q_OBJECT

	friend	class	ThreadSave;

	QPushButton	Button;
	ThreadSave	ThreadSaveInst;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	FileNameForSaving;
	bool	ShowProcessingWindow;
	bool	SaveInBackground;
	int32	UseLayer;	//-1::Save all layers

	SaveImageTargetButton(LayersBase *Base ,QWidget *parent);
	~SaveImageTargetButton(void);
	
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	bool SaveImage(QString FileName,CmdReqSaveImage::UsageImage TypeOfImage);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();

private:
	bool SaveImage	(QIODevice *f ,bool iShowProcessingWindow);
	bool SaveImageV3(QIODevice *f ,bool iShowProcessingWindow);
};

class	GUICmdReqSaveTargetImage : public GUICmdPacketBase
{
public:
	int	Phase;
	int	TopY;
	int	YCount;
	int	Layer;
	CmdReqSaveImage::UsageImage TypeOfImage;

	GUICmdReqSaveTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveTargetImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};




#endif // SAVEIMAGETARGETBUTTON_H