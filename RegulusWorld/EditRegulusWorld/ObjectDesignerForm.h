#ifndef OBJECTDESIGNERFORM_H
#define OBJECTDESIGNERFORM_H

#include <QWidget>

namespace Ui {
class ObjectDesignerForm;
}
class EditRegulusWorld;

class ObjectDesignerForm : public QWidget
{
    Q_OBJECT

    EditRegulusWorld    *Parent;
public:
    explicit ObjectDesignerForm(EditRegulusWorld *p,QWidget *parent = nullptr);
    ~ObjectDesignerForm();

private:
    Ui::ObjectDesignerForm *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // OBJECTDESIGNERFORM_H
