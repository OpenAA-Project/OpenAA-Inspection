#ifndef USAGECONPONENTLISTFORM_H
#define USAGECONPONENTLISTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "NList.h"

namespace Ui {
class UsageConponentListForm;
}

class	GUIItemInstance;
class	EditGUI;

class UsageConponentListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    EditGUI	*Parent;

public:
    class	GUIItemInstancePointerList : public NPList<GUIItemInstancePointerList>
    {
    public:
        GUIItemInstance	*Point;

        GUIItemInstancePointerList(GUIItemInstance *p):Point(p){}
    };

    NPListPack<GUIItemInstancePointerList>	ItemListContainer;

public:
    explicit UsageConponentListForm(EditGUI *p,LayersBase *base,QWidget *parent = 0);
    ~UsageConponentListForm();
    
private slots:
    void MListSectionClicked (int);
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonMakeCopyBAT_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonExcludedListOut_clicked();

private:
    Ui::UsageConponentListForm *ui;
    virtual	void	resizeEvent ( QResizeEvent * event ) override;
	void ShowList(void);
};

#endif // USAGECONPONENTLISTFORM_H
