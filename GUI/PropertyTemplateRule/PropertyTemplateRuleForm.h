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
