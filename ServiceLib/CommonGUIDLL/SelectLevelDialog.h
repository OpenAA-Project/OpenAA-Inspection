/*
 * Copyright (C) 2022
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

#ifndef SELECTLEVELDIALOG_H
#define SELECTLEVELDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QEvent>
#include <QMouseEvent>
#include "XServiceForLayers.h"

namespace Ui {
class SelectLevelDialog;
}

class LevelFolder;

class TreeWidgetRightClickEnabler : public QObject
{
    Q_OBJECT
public:
    TreeWidgetRightClickEnabler(QTreeWidget * w): QObject(w), _Widget(w) {
        w->installEventFilter(this);
    };

protected:
    inline bool eventFilter(QObject *watched, QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress)
        {
            auto mouseEvent = (QMouseEvent*)event;
            if (mouseEvent->button() == Qt::RightButton){
                //_button->click();
				emit	RightClicked(_Widget);
			}
        }
        return false;
    }

private:
    QTreeWidget* _Widget;
signals:
	void	RightClicked(QTreeWidget *obj);
};


class SelectLevelDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
    TreeWidgetRightClickEnabler * TreeWidgetEnabler;
public:
    explicit SelectLevelDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectLevelDialog();
    
signals:
    void    SignaSelected(int LevelID);

private slots:
    void on_treeWidgetLevel_clicked(const QModelIndex &index);
    void	SlotRightClicked(QTreeWidget *obj);

private:
    Ui::SelectLevelDialog *ui;

    virtual void resizeEvent(QResizeEvent *event)  override;
    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
};

#endif // SELECTLEVELDIALOG_H