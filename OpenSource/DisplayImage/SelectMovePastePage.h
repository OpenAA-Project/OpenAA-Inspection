/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectMovePastePage.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTMOVEPASTEPAGE_H
#define SELECTMOVEPASTEPAGE_H

#include <QDialog>
#include <QScrollArea>
#include <QLabel>
#include <QCheckBox>
#include <QFrame>
#include "XIntClass.h"

namespace Ui {
class SelectMovePastePage;
}

class	LayersBase;

class	SelectMovePastePageFrame	//移動・貼り付け時のページ選択ダイアログでの、選択項目ごとのデータクラス
{
    QFrame	PageFrame;
    QLabel	SourceLabel;
    QCheckBox	DestPage1;
    QCheckBox	DestPage2;
    IntList *PageList;

public:
    int		SourcePage;

    SelectMovePastePageFrame(void):PageList(NULL),SourcePage(0){}
    void	Initial(int N,QWidget *parent,IntList *_PageList);
    void	LodFromWindow(void);
};
class SelectMovePastePage : public QDialog
{
    Q_OBJECT

    QScrollArea	SArea;
    int			FrameCount;
    SelectMovePastePageFrame	*Frames;
    IntList *PageList;
    int		PageCount;

public:
    explicit SelectMovePastePage(LayersBase *Base,IntList *_PageList,int PageCount,QWidget *parent = 0);
    ~SelectMovePastePage();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::SelectMovePastePage *ui;
};

#endif // SELECTMOVEPASTEPAGE_H
