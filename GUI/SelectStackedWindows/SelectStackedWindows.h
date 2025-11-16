#ifndef SELECTSTACKEDWINDOWS_H
#define SELECTSTACKEDWINDOWS_H

#include "selectstackedwindows_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include <QString>
#include <QIODevice>
#include <QModelIndex>
#include <QPushButton>

class	SelectStackedWindows;

class	AllocationList : public QObject ,public NPListSaveLoad<AllocationList>
{
	Q_OBJECT
public:
	QString	ButtonMessage;
	QString	InstName;
	QString	PageName;

	QPushButton	Button;
	SelectStackedWindows	*Parent;

	AllocationList(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

public slots:
	void	SlotClicked();
};

class	AllocationListContainer : public NPListPackSaveLoad<AllocationList>
{
public:
	AllocationListContainer(void){}

	virtual	AllocationList	*Create(void)	{	return new AllocationList();	}
};


class	SelectStackedWindows:public GUIFormBase
{
	Q_OBJECT

	AllocationListContainer	MContainer;
public:
	QByteArray	MenuData;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	SelectStackedWindows(LayersBase *Base ,QWidget *parent = 0);
	~SelectStackedWindows(void);
	virtual void	Prepare(void) override;
	virtual	void	ReadyParam(void) override;
	virtual	bool	ShowQByteArrayDialog(const QString &VariableName) override;

	void	SlotClick(const QString &InstName,const QString &PageName);
public slots:
	void	ResizeAction();
private:

};



#endif // SELECTSTACKEDWINDOWS_H
