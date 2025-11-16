#ifndef LISTBOXUNCOVEREDAREAFORM_H
#define LISTBOXUNCOVEREDAREAFORM_H

#include "XGUIFormBase.h"
#include "ui_ListboxUncoveredAreaForm.h"
#include<QString>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"

class	UncoveredAreaList : public NPList<UncoveredAreaList>
{
public:
	int		GlobalPage;
	int		X1,Y1,X2,Y2;	//Local Position
	DWORD	DotCounts;

	UncoveredAreaList(void){}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	void	GetCenter(int &Cx, int &Cy);
	UncoveredAreaList	&operator=(UncoveredAreaList &src);
};

class	UncoveredAreaContainer : public NPListPack<UncoveredAreaList>
{
public:
	UncoveredAreaContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	UncoveredAreaContainer	&operator=(UncoveredAreaContainer &src);
	UncoveredAreaContainer	&operator+=(UncoveredAreaContainer &src);
};

//====================================================================

class ListboxUncoveredAreaForm : public GUIFormBase
{
	Q_OBJECT

	UncoveredAreaContainer	AreaList;
public:
	QString	ImagePanelName;
	int32	MaxRowCount;

	ListboxUncoveredAreaForm(LayersBase *Base ,QWidget *parent = 0);
	~ListboxUncoveredAreaForm();

private:
	Ui::ListboxUncoveredAreaFormClass ui;

	void ShowGrid(void);

private slots:
	void on_pushButtonUpdate_clicked();
	void on_tableWidget_clicked(const QModelIndex &);
	void	ResizeAction();
};

class	GUICmdReqUncoveredAreaList : public GUICmdPacketBase
{
public:

	GUICmdReqUncoveredAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendUncoveredAreaList : public GUICmdPacketBase
{
public:
	UncoveredAreaContainer	AreaList;

	GUICmdSendUncoveredAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // LISTBOXUNCOVEREDAREAFORM_H
