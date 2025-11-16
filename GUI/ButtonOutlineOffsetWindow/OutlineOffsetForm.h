#ifndef OUTLINEOFFSETFORM_H
#define OUTLINEOFFSETFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "EditOutlineOffset.h"
#include "XDataInLayer.h"

namespace Ui {
class OutlineOffsetForm;
}

class OutlineOffsetForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	EditOutlineOffset	*WTabFormOutlineOffset;
	XYData				*SavedData[100];
public:
    explicit OutlineOffsetForm(LayersBase *base ,QWidget *parent = 0);
    ~OutlineOffsetForm();

	virtual	void	showEvent (QShowEvent * event)	override;
private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void SlotReflect();
private:
    Ui::OutlineOffsetForm *ui;
};

#endif // OUTLINEOFFSETFORM_H
