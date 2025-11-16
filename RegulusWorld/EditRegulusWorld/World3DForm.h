#ifndef WORLD3DFORM_H
#define WORLD3DFORM_H

#include <QWidget>
#include "XDisplayImage3D.h"
namespace Ui {
class World3DForm;
}
class EditRegulusWorld;

class World3DForm : public QWidget
{
    Q_OBJECT

    EditRegulusWorld    *Parent;
    XDisplayImage3D     DisplayImage3D;
public:
    explicit World3DForm(EditRegulusWorld *p,QWidget *parent = nullptr);
    ~World3DForm();

private:
    Ui::World3DForm *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // WORLD3DFORM_H
