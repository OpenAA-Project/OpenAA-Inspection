#ifndef DISPLAYNGLISTBUTTON_H
#define DISPLAYNGLISTBUTTON_H

#include "displaynglistbutton_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButton.h"
#include "NGListForm.h"
#include "XResult.h"
#include "XDisplayImage.h"
#include "time.h"
#include "GeneralTabSheet.h"

class NGListForm;

class	DisplayNGListButton : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButton	Button;
	int					WaitTime;

	GeneralTabSheet	*pGeneralTabSheet;

public:
	ErrorGroupPack	*ErrorGroupData;
	int				NGPointCount;
	QString			TargetImagePanelName;
	QStringList		RelatedPanel;
	bool			BlinkNG;
	int32			PopupFormX;
	int32			PopupFormY;
	int32			PopupFormWidth;
	int32			PopupFormHeight;
	bool			AnytimeShow;
	bool			Popup;
	bool			LocationInForm;
	QStringList		RelatedTabSheets;

	DisplayNGListButton(LayersBase *Base ,QWidget *parent);
	~DisplayNGListButton(void);

	virtual void	Prepare(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual	QStringList	GetRelatedForm(void){	return RelatedTabSheets;	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	NGListForm *GetNGListForm()						{	return NGListWindow;				}
	int		GetErrorGroupNumber(int phase)			{	return ErrorGroupNumber[phase];		}
	ErrorGroup *GetErrorGroupTable(int phase,int i)	{	return ErrorGroupTable[phase][i];	}
////////// test
	void	testPhase(int64 shownInspectionID);

	void	LoadNGColorInPlayer(void);

	int NGcount_Phase0;
//////////
protected:
	virtual	void	keyPressEvent	(QKeyEvent *event)	override;
	virtual	void	keyReleaseEvent	(QKeyEvent *event)	override;
	virtual	void	wheelEvent		(QWheelEvent *event)override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotNGListKeyEnter();
	void	SlotExecGeneralInfo2()			{	ExecGeneralInfo2();			}
	void	SlotExecGeneralInfo2Reverse()	{	ExecGeneralInfo2Reverse();	}
	void	SlotKeyDeleteRepeat()			{	ExecShowListHistory();		}
	void	SlotKeyDelete()					{	ExecDeleteListHistory();	}

private:
	NGListForm		*NGListWindow;
	int64			InspectionID;

	DisplayImage	*pDisplayTargetImagePanel;
	double	DisplayRatio;
	int		DisplayWidth,DisplayHeight;
	int		NGImageWidth,NGImageHeight,NGImageBevel;
	SeqControlParam	*Param;

	int		*ErrorGroupNumber;
	ErrorGroup ***ErrorGroupTable;

	void	Next	();
	void	Previous();
	void	ExecGeneralInfo2();
	void	ExecGeneralInfo2Reverse();
	int		ExecCmdPixelNGDrawMode(bool ShowDetail,bool ShowOnlyCircle);
	void	ExecShowListHistory();
	void	ExecDeleteListHistory();
	bool	ExecCmdPixelNGSize(int &NGSize,QColor &NGSizeColor);
};

//---------------------------------------------------------
class	GUICmdReqNGList : public GUICmdPacketBase
{
public:
	int		ShownInspectionID;
	bool	ShowCause;

	GUICmdReqNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGList : public GUICmdPacketBase
{
public:
	ErrorGroupPack	*ErrorGroupData;
	int				NGPointCount;

	GUICmdSendNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdSendNGList(void);

	void	Initial(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // DISPLAYNGLISTBUTTON_H
