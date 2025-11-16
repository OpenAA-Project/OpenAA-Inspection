#ifndef OBJECTLISTFORM_H
#define OBJECTLISTFORM_H

#include <QWidget>
#include <QSplitter>

namespace Ui {
class ObjectListForm;
}
class EditRegulusWorld;

class ObjectListForm : public QWidget
{
    Q_OBJECT

    EditRegulusWorld    *Parent;
    QSplitter			*Splitter;
public:
    explicit ObjectListForm(EditRegulusWorld *p,QWidget *parent = nullptr);
    ~ObjectListForm();

private:
    Ui::ObjectListForm *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // OBJECTLISTFORM_H
