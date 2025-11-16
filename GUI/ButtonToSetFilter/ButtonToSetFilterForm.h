#ifndef BUTTONTOSETFILTERFORM_H
#define BUTTONTOSETFILTERFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class ButtonToSetFilterForm;
}

class ButtonToSetFilterForm : public GUIFormBase
{
    Q_OBJECT

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;

    explicit ButtonToSetFilterForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonToSetFilterForm();

	virtual	void	Prepare(void)	override;

private slots:
    void on_pushButtonFilter_clicked();
	void	ResizeAction();

private:
    Ui::ButtonToSetFilterForm *ui;
};

//===========================================================================

class	GUIFilterList : public NPListSaveLoad<GUIFilterList>
{
public:
	int	Line;
	QString	FilterName;

	GUIFilterList(void){	Line=-1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	GUIFilterListContainer : public NPListPackSaveLoad<GUIFilterList>
{
public:
	GUIFilterListContainer(void){}

	virtual	GUIFilterList	*Create(void)	{	return new GUIFilterList();	}
};

class	GUICmdReqFilterList : public GUICmdPacketBase
{
public:

	GUICmdReqFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckFilterList : public GUICmdPacketBase
{
public:
	GUIFilterListContainer	FList;

	GUICmdAckFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqFilterData : public GUICmdPacketBase
{
public:
	int	Line;
	GUICmdReqFilterData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckFilterData : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdAckFilterData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetFilterData : public GUICmdPacketBase
{
public:
	int			Line;
	QByteArray	Data;

	GUICmdSetFilterData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};



#endif // BUTTONTOSETFILTERFORM_H
