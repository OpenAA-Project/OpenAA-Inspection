#pragma once

#include "buttonreplacecolorinlibid_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonReplaceColorInLibID : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	bool		ModeMasterImage;
	QString		AlgoRoot;
	QString		AlgoName;
	int			NeighborLength;
	int			LibID;
	int			PickUpColorRL;
	int			PickUpColorGL;
	int			PickUpColorBL;
	int			PickUpColorRH;
	int			PickUpColorGH;
	int			PickUpColorBH;
	int			ReplaceColorR;
	int			ReplaceColorG;
	int			ReplaceColorB;


	ButtonReplaceColorInLibID(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

class	GUICmdReplaceColorInLibID : public GUICmdPacketBase
{
public:
	bool		ModeMasterImage	;
	QString		AlgoRoot		;
	QString		AlgoName		;
	int			NeighborLength	;
	int			LibID			;
	int			PickUpColorRL	;
	int			PickUpColorGL	;
	int			PickUpColorBL	;
	int			PickUpColorRH	;
	int			PickUpColorGH	;
	int			PickUpColorBH	;
	int			ReplaceColorR	;
	int			ReplaceColorG	;
	int			ReplaceColorB	;

	GUICmdReplaceColorInLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	PickupByColorZone(BYTE **BMap,int XLen ,int YLen
							,ImagePointerContainer &Images,FlexArea &Area);

};
