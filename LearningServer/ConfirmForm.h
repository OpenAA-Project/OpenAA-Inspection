#ifndef CONFIRMFORM_H
#define CONFIRMFORM_H

#include <QWidget>
#include <QLabel>
#include "NList.h"

namespace Ui {
class ConfirmForm;
}

class LearningInDB;
class LearningParamInDB;
class ItemPanel;
class ConfirmForm;
class LearningServer;
class LogicDLL;
class AlgorithmComponentWindow;

#define     LearningConfirmItemTitlePanelHeight 24
#define     LearningConfirmItemImagePanelWidth  128
#define     LearningConfirmItemImagePanelHeight 128
#define     LearningConfirmItemMessageHeight    64
#define     LearningConfirmItemPanelWidth       128
#define     LearningConfirmItemPanelHeight  (LearningConfirmItemTitlePanelHeight+LearningConfirmItemImagePanelHeight+LearningConfirmItemMessageHeight)
#define     LearningConfirmItemMergin           3


class ItemPanelImage : public QLabel
{
	Q_OBJECT

    ItemPanel   *Parent;

public:
	ItemPanelImage(ItemPanel *parent);

private slots:
    void    EditAction();
    void    RemoveAction();

private:
	virtual	void mouseReleaseEvent(QMouseEvent *ev)	override;
};


class ItemPanel : public QWidget , public NPList<ItemPanel>
{
    friend  class ConfirmForm;

    ConfirmForm     *Parent;
    LearningInDB    *LearningInDBPoint;
    LearningParamInDB   *Param;
    QImage	        TargetImage;

    QLabel          Title;
    ItemPanelImage  Panel;
    QLabel          Message;
    int	            Result;
public:
	ItemPanel(int LayerNumb,ConfirmForm *parent,LearningInDB *b,LearningParamInDB *p);

    void    ShowResult(void);
    void    ShowItemInWindow(void);
    void    ShowAll(void);
    void    EditAction();
    void    RemoveAction();
};

class ConfirmForm : public QWidget
{
    Q_OBJECT

    friend  class LearningServer;
    friend  class ItemPanel;

    LearningServer          *Parent;
    NPListPack<ItemPanel>   OKItems;
    NPListPack<ItemPanel>   NGItems;
    int     LibType;
    int     LibID;

    QWidget *OKWindow;
    QWidget *NGWindow;
    LogicDLL    *LogicDLLInst;
    AlgorithmComponentWindow    *AdjustWindow;

    int XNumb;
    int LayerNumb;
public:
    explicit ConfirmForm(int LayerNumb ,LearningServer *parent ,LogicDLL *L,AlgorithmComponentWindow *w,QWidget *p = nullptr);
    ~ConfirmForm();

    void    SetLibrary(int LibType,int LibID);
    void    ShowResult(void);
    void    ShowItemInWindow(ItemPanel *From);
    void    SetShowAndSetItems(AlgorithmComponentWindow *w);
    void    RemoveItem(int LearningID);
private:
    Ui::ConfirmForm *ui;

    virtual void    resizeEvent(QResizeEvent *event)    override;
    virtual void    closeEvent(QCloseEvent *event)      override;
private slots:
    void    SlotChangeValue();
    void    SlotOKScrollBarChanged(int);
    void    SlotNGScrollBarChanged(int);
};

#endif // CONFIRMFORM_H
