/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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