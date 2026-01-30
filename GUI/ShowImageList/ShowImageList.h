/*
 * Copyright (C) 2021
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

#ifndef SHOWIMAGELIST_H
#define SHOWIMAGELIST_H

#include "showimagelist_global.h"
#include <QScrollBar>
#include <QTranslator>
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ShowImageList : public GUIFormBase
{
	Q_OBJECT

	QScrollBar	Scroller;
	QToolButton	SaveButton;
public:
	bool	HorizontalMode;
	int32	IconSize;
	int32	IconIsolation;	
	QStringList	Path;
	QString	SavedSuffix;
	class	FileList : public NPList<FileList>
	{
		ShowImageList	*Parent;
	public:
		QString	FileNameWithPath;
		QString	FileName;
		QString	Suffix;
		QImage	IconImage;
		bool	Selected;

		FileList(ShowImageList *p):Parent(p){	Selected=false;	}

		bool	LoadImageForIcon(int IconSize);
		bool	LoadImage(DataInPage *P);
	};
	NPListPack<FileList>	FileListContainer;
	int	SelectedNo;


	class	CmdSetPath : public GUIDirectMessage
	{
	public:
		QStringList Path;
		CmdSetPath(LayersBase *base):GUIDirectMessage(base){}
	};

	ShowImageList(LayersBase *Base ,QWidget *parent);
	~ShowImageList();

	virtual  void	Prepare(void)								override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowList(void);
	void	ScanFolders(void);
	void	AddedFolders(void);
	void	EmitSignalSelectFile(const QString &FileName);
private:
	virtual void paintEvent ( QPaintEvent * ) override;
	virtual	void mousePressEvent ( QMouseEvent * event )override; 
private slots:
	void	ResizeAction();
	void	SlotSliderMoved(int n);
	void	SlotSliderValueChanged(int n);
	void	SlotDeleteFile();
	void	SlotChangeName();
	void	SlotSaveClicked();
signals:
	void	SignalSelectFile(const QString &FileName);
};

class	CmdShowList : public GUIDirectMessage
{
public:
	CmdShowList(LayersBase *base):GUIDirectMessage(base){}
};



#endif // SHOWIMAGELIST_H