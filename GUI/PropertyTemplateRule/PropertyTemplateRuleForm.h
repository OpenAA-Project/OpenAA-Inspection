/*
 * Copyright (C) 2024
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

#ifndef PROPERTYTEMPLATERULEFORM_H
#define PROPERTYTEMPLATERULEFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XTemplateRule.h"

namespace Ui {
class PropertyTemplateRuleForm;
}

class PropertyTemplateRuleForm : public GUIFormBase
{
    Q_OBJECT

    IntList     AlgorithLibTypeList;
    int         RetSelectedLibFolderID;
public:
    explicit PropertyTemplateRuleForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyTemplateRuleForm();

    virtual void	TransmitDirectly(GUIDirectMessage *packet)  override;

private slots:
    void on_tableWidgetItemList_clicked(const QModelIndex &index);
    void on_tableWidgetItemList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetAlgorithmType_clicked(const QModelIndex &index);
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();

private:
    Ui::PropertyTemplateRuleForm *ui;

    TemplateRuleBase	*GetTemplateRuleBase(void);
    void	ShowLibList(void);
};

#endif // PROPERTYTEMPLATERULEFORM_H