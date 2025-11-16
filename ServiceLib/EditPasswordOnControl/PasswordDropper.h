#ifndef PASSWORDDROPPER_H
#define PASSWORDDROPPER_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

namespace Ui {
class PasswordDropper;
}

class	GUIInstancePack;
class	QDrag;
class	QMimeData;

class	DragLabel : public QLabel
{
public:
    DragLabel(QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget):QLabel(parent,f){}

    virtual	void mousePressEvent(QMouseEvent *event)	override;
};

class PasswordDropper : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit PasswordDropper(LayersBase *Base,QWidget *parent = 0);
    ~PasswordDropper();

    DragLabel	*dragLabel;
    GUIInstancePack *GUIPack;
private slots:
    void on_pushButtonLoadDefault_clicked();
    void on_pushButtonSaveDefault_clicked();
    void on_pushButtonDeleteControl_clicked();
    void on_pushButtonDeletPassword_clicked();
    void on_pushButtonCreatePassword_clicked();
    void on_pushButtonModifyPassword_clicked();
    void on_pushButtonDeleteClass_clicked();
    void on_pushButtonCreateClass_clicked();
    void on_pushButtonModifyClass_clicked();
    void on_listWidgetClass_clicked(const QModelIndex &index);
    void on_listWidgetPassword_doubleClicked(const QModelIndex &index);
    void on_listWidgetClass_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetDropFilter_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonSave_clicked();
    void SlotDropped ( QObject * newTarget );

private:
    Ui::PasswordDropper *ui;

    void ShowList(void);
    void ClicklistWidgetClass(void);
    int32	GetPasswordClassID(void);
    void SlotDroppedQWidget( QObject * newTarget );
};

#endif // PASSWORDDROPPER_H
