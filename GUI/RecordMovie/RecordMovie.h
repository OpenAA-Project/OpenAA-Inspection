#ifndef RECORDMOVIE_H
#define RECORDMOVIE_H

#include "recordmovie_global.h"
#include <QToolButton>
#include <QThread>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XMainSchemeMemory.h"
#include "XMovieCommon.h"

class	AddImageForMovieThread;

class	RecordMovie : public GUIFormBase
{
	Q_OBJECT

	friend	class	AddImageForMovie;

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
	DWORD	LastTime;

	double	CurrentFPS;
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

	RecordMovie(LayersBase *Base ,QWidget *parent);
	~RecordMovie(void);
	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	Terminated(void)							override;

	double	GetFPS(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

public slots:
	void SlotClicked (bool checked);
	void	SlotMemoryOver();
	void	SlotWriteError();
private slots:
	void	ResizeAction();
	void	SlotTargetImageCaptured();
	void	SlotCaptured(int);

private:
	void	ReallocMovieXYPixels(void);
	EnumAVFormat	GetAVFormat(void);

	void	SetMovieSize(int Index);
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
