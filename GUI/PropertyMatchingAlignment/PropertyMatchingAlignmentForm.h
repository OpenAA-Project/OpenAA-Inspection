#ifndef PROPERTYMATCHINGALIGNMENTFORM_H
#define PROPERTYMATCHINGALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyMatchingAlignmentForm.h"
#include <QWidget>
#include "XGUIPacketForDLL.h"
#include "XFlexArea.h"

class	MatchingAlignmentBase;

class PropertyMatchingAlignmentForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyMatchingAlignmentForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyMatchingAlignmentForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowAreaGrid(void);
	MatchingAlignmentBase	*GetMatchingAlignmentBase(void);

private:
	Ui::PropertyMatchingAlignmentFormClass ui;

private slots:
	void on_pushButtonCreateSpecified_clicked();
	void on_toolButtonSpecified_clicked();
};

//=================================================================================

class	DisplayModeOfMatchingAlignment : public GUIDirectMessage
{
public:
	bool	ModeSpecified;
	DisplayModeOfMatchingAlignment(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddMatchingAlignmentArea : public GUICmdPacketBase
{
public:
	FlexArea		Area;
	IntList			LayerList;
	double			MatchingRate;
	int				SearchDot;

	GUICmdAddMatchingAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCreateSpecified : public GUICmdPacketBase
{
public:
	double	CoverRate;
	double	PickUpVar;
	int		BlockSize;

	GUICmdCreateSpecified(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PROPERTYMATCHINGALIGNMENTFORM_H
