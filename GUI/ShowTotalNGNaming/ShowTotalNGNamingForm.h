#ifndef SHOWTOTALNGNAMINGFORM_H
#define SHOWTOTALNGNAMINGFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XNaming.h"
#include "XIntClass.h"

namespace Ui {
class ShowTotalNGNamingForm;
}

class ShowTotalNGNamingForm : public GUIFormBase
{
    Q_OBJECT
    
	int						InspectedCount;
	NGAreaListContainer		NGData;
	int						LastMasterID;
	IntList					LastLotAutoCountList;
	QStringList				NamingData;
	int						TotalNGCount;
	int						TotalOKCount;
	int						TotalCount;

public:
    explicit ShowTotalNGNamingForm(LayersBase *base,QWidget *parent = 0);
    ~ShowTotalNGNamingForm();

	virtual	void	BuildForShow(void)	override;
    virtual	void	ShowInPlayer(int64 shownInspectionID)	override;
	void	ShowAll(void);

private slots:
    void on_pushButtonReset_clicked();

private:
    Ui::ShowTotalNGNamingForm *ui;
};

//-----------------------------------------------------------------------------------------------------------

class	GUICmdReqNGNamingList : public GUICmdPacketBase
{
public:
	int32		ShownInspectionID;

	GUICmdReqNGNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGNamingList : public GUICmdPacketBase
{
public:
	NGAreaListContainer	NGData;

	GUICmdSendNGNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdReqNamingAreasList : public GUICmdPacketBase
{
public:
	GUICmdReqNamingAreasList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingAreasList : public GUICmdPacketBase
{
public:
	QStringList				NamingData;

	GUICmdSendNamingAreasList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
#endif // SHOWTOTALNGNAMINGFORM_H
