/*
 * Copyright (C) 2026
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

#ifndef RECORDMOVIE_H
#define RECORDMOVIE_H

#include "recordmovie_global.h"
#include <QToolButton>
#include <QThread>
#include <QLocalSocket>
#include <QLocalServer>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XMainSchemeMemory.h"
#include "XMovieCommon.h"
#include "XProcess.h"

class   AddImageForMovie;
class	AddImageForMovieThread;

class	RecordMovie : public GUIFormBase
{
	Q_OBJECT

	friend	class	AddImageForMovie;

	QLocalSocket	*Socket;
	QLocalServer	Server;

	QToolButton	Button;
	AddImageForMovie		*ThreadImage;
	GUIFormBase				*CycleTimePointer;

	QString	CurrentFileName;
	int		MovieSizeMode;
	int		MovieXSize;
	int		MovieYSize;
	float	TargetFrameRate;
	bool	DivideMovieFile;

	DWORD	CapturedTime[50];
	int		CapturedCount;
	int		CapturedWIndex;
	DWORD	StartTime;
	DWORD	LastTime;

	int					SharedAllocatedSize;
	QSharedMemory		*SharedMemForMovie;
	QSystemSemaphore	*Semaphore;
	volatile	bool	Running;
	double				CurrentFPS;
	bool3				Received;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MovieQuality;	//-1 , or 0-10000
	QString	AVFormatStr;
	EnumAVFormat	AVFormat;
	QString	DefaultSettingFileName;

	QString	SavedFolder;
	QString	FileNameFormat;
	int32	JpegQuality;
	int32	FPS;
	int32	UsePage;
	double	ZoomRate;

	QString			ProgramFileName;
	ProcessManager	ProcessExe;

	RecordMovie(LayersBase *Base ,QWidget *parent);
	~RecordMovie(void);
	virtual void	Prepare(void)		override;
	virtual void	AfterStartSequence(void)	override;

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	double	GetFPS(void);


	bool	StartRecording(const QString &filename
							, int width
							, int height
							, int fps
							, int bitrate);
	bool	RestartRecording(void);
	bool	HaltRecording(void);
	bool	EndRecording(void);
	bool	AddImage(void);


	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

public slots:
	void SlotClicked (bool checked);
	void	SlotMemoryOver();
	void	SlotWriteError();
	void	SlotReadyRead();
private slots:
	void	ResizeAction();
	void	SlotTargetImageCaptured();
	void	SlotCaptured(int);
	void	SlotNewConnection();
private:
	EnumAVFormat	GetAVFormat(void);

	void	SetMovieSize(int Index);
	bool	GetAckFromExe(qint64 WaitinMilisec=5000);

};

class	CmdStartRecordMovieWithFileName : public GUIDirectMessage
{
public:
	QString FileName;
	int		FPS;
	int		Quality;
	int		RecordPageNo;
	CmdStartRecordMovieWithFileName(LayersBase *base):GUIDirectMessage(base)	{	FPS=30;	RecordPageNo=0;	}
};

class	CmdStartRecordMovie : public GUIDirectMessage
{
public:
	QString RetFileName;
	CmdStartRecordMovie(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdEndRecordMovie : public GUIDirectMessage
{
public:
	CmdEndRecordMovie(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetRecordQuality : public GUIDirectMessage
{
public:
	int		Quality;	//0-100
	CmdSetRecordQuality(LayersBase* base) :GUIDirectMessage(base) {}
};

class	CmdSetRecordMovieSize : public GUIDirectMessage
{
public:
	int	MovieXSize;
	int	MovieYSize;
	int	MovieQuality;	//-1 , or 0-100
	double	ReturnFPS;

	CmdSetRecordMovieSize(LayersBase *base):GUIDirectMessage(base){	MovieQuality=-1;	}
};

class	CmdShowSettingRecordDialog: public GUIDirectMessage
{
public:
	CmdShowSettingRecordDialog(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdReqRecordMovieMaxTime : public GUIDirectMessage
{
public:
	int	MovieXSize;
	int	MovieYSize;
	int	MovieQuality;	//-1 , or 0-100
	double	FPS;
	int	RetMaxSecond;

	CmdReqRecordMovieMaxTime(LayersBase *base):GUIDirectMessage(base){	MovieQuality=-1;	}
};

#endif // RECORDMOVIE_H