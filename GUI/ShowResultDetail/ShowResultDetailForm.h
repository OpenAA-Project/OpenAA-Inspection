#ifndef SHOWRESULTDETAILFORM_H
#define SHOWRESULTDETAILFORM_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XTypeDef.h"
#include "NListComp.h"

namespace Ui {
class ShowResultDetailForm;
}

class LayersBase;

class ResultDetailList : public NPListSaveLoad<ResultDetailList>
{
public:
    int     Phase;
    int     Page;
    int     Layer;
    int     ItemID;
    int     LibType;
    int     LibID;
    int     PosX,PosY;
    QString Message;
    QString Res1;
    QString Res2;
    QString Res3;

    ResultDetailList(void){}
    ResultDetailList(const ResultDetailList &src);

    ResultDetailList    &operator=(const ResultDetailList &src);
	virtual	bool	Save(QIODevice *f)  override;
	virtual	bool	Load(QIODevice *f)  override;

};

class ResultDetailListContainer : public NPListPackSaveLoad<ResultDetailList>
{
public:
    ResultDetailListContainer(void){}
    ResultDetailListContainer(const ResultDetailListContainer &src);

    virtual	ResultDetailList	*Create(void)   override;
    ResultDetailListContainer   &operator=(const ResultDetailListContainer &src);
    ResultDetailListContainer   &operator+=(const ResultDetailListContainer &src);
};

class ShowResultDetailForm : public GUIFormBase
{
    Q_OBJECT

    ResultDetailListContainer   ResultContainer;
public:
    QString FileName;
    bool    AutoWrite;

    explicit ShowResultDetailForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowResultDetailForm();

    virtual void	ShowInPlayer		(int64 shownInspectionID=-1)    override;
private slots:
    void on_pushButtonWriteResult_clicked();
	void	ResizeAction();
private:
    Ui::ShowResultDetailForm *ui;

    QString MakePathFile(void);
    bool    WriteOut(const QString &FileName);
};

//============================================================================
class	GUICmdReqResultDetailList : public GUICmdPacketBase
{
public:
	GUICmdReqResultDetailList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)  override{   return true;    }
	virtual	bool	Save(QIODevice *f)  override{   return true;    }
    void    MakeList(ResultDetailListContainer &ResultContainer ,LayersBase *Base,int localPage);
    void    MakeListShadowTree(ResultDetailListContainer &ResultContainer ,LayersBase *Base,int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)  override;	
};
class	GUICmdAckResultDetailList : public GUICmdPacketBase
{
public:
    ResultDetailListContainer   ResultContainer;

	GUICmdAckResultDetailList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)  override;
	virtual	bool	Save(QIODevice *f)  override;

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)  override{}	
};

#endif // SHOWRESULTDETAILFORM_H
