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