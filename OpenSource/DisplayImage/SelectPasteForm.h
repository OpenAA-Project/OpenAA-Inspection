/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectPasteForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SELECTPASTEFORM_H
#define SELECTPASTEFORM_H

#include <QWidget>
#include "XDateTime.h"
#include <QString>
#include "NList.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectPasteForm;
}

class	LayersBase;
class	DisplayImageWithAlgorithm;
#define	FileIDPasteData		0x0a500001

class SelectPasteForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

public:
    class	CopiedList : public NPList<CopiedList>
    {
        XDateTime	CopiedTime;
        int64		Counts;
        QString		AlgoRoot;
        QString		AlgoName;
        QString		Remark;

    public:
        CopiedList(void){}
        CopiedList(const CopiedList &src);
        CopiedList(const XDateTime &_CopiedTime
                    ,int64 _Counts
                    ,const QString &_AlgoRoot
                    ,const QString &_AlgoName
                    ,const QString &_Remark);

        CopiedList	&operator=(CopiedList &src);
        bool	Save(QIODevice *f);
        bool	Load(QIODevice *f);

        const XDateTime		&GetCopiedTime(void)	{	return CopiedTime;		}
        int64				GetCounts(void)			{	return Counts;			}
        const QString		&GetAlgoRoot(void)		{	return AlgoRoot;		}
        const QString		&GetAlgoName(void)		{	return AlgoName;		}
        const QString		&GetRemark(void)		{	return Remark;			}
    };
private:
    DisplayImageWithAlgorithm	*ParentPanel;
    NPListPack<CopiedList>	Lists;
public:
    int							RetMode;

public:
    explicit SelectPasteForm(DisplayImageWithAlgorithm *parentPanel ,LayersBase *Base ,QWidget *parent = 0);
    ~SelectPasteForm();

    bool	SaveLine(QIODevice *f,IntList	&RowList);
    bool	LoadLine(QIODevice *f);

    static	XDateTime	GetTopCopiedData(LayersBase *Base,QString &AlgoRoot ,QString &AlgoName);
    static	void		LoadPasteSameAlgorithm(LayersBase *Base,DisplayImageWithAlgorithm *Panel,const XDateTime &d ,int PastedLayer=-1);

signals:
    void	SignalClose(void);

private slots:
    void on_GridPaste_clicked(const QModelIndex &index);
    void on_ButtonPasteSameAlgoPosToSelectedLayer_clicked();
    void on_ButtonPasteSameAlgoPos_clicked();
    void on_pushButtonCutOnShape_clicked();
    void on_ButtonFixedPasteByShape_clicked();
    void on_ButtonFixedPasteForImage_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_CancelButton_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::SelectPasteForm *ui;

    void	ShowList(void);
    void	CreateList(void);
    static	void	CreateList(LayersBase *Base,NPListPack<CopiedList> &HLists);

};

//=============================================================================================================


inline	SelectPasteForm::CopiedList::CopiedList(const CopiedList &src)
{
    CopiedTime	=src.CopiedTime;
    Counts		=src.Counts;
    AlgoRoot	=src.AlgoRoot;
    AlgoName	=src.AlgoName;
    Remark		=src.Remark;
}

inline	SelectPasteForm::CopiedList::CopiedList(const XDateTime &_CopiedTime
                    ,int64 _Counts
                    ,const QString &_AlgoRoot
                    ,const QString &_AlgoName
                    ,const QString &_Remark)
{
    CopiedTime	=_CopiedTime;
    Counts		=_Counts;
    AlgoRoot	=_AlgoRoot;
    AlgoName	=_AlgoName;
    Remark		=_Remark;
}
#endif // SELECTPASTEFORM_H
