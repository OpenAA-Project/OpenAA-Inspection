#ifndef SELECTAREAFORM_H
#define SELECTAREAFORM_H

#include <QDialog>
#include "mtGraphicUnit.h"
#include "XFlexArea.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectAreaForm;
}
class PQSystemRunner;

class SelectAreaForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    PQSystemRunner	*Parent;
	mtGraphicUnit	GPanel;
public:
    explicit SelectAreaForm(PQSystemRunner *runner ,QWidget *parent = 0);
    ~SelectAreaForm();
    
	FlexArea	SelectArea;

private slots:
    void on_comboBoxSelectSlave_currentIndexChanged(int index);
    void on_pushButtonSelectArea_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseWheel(int delta ,int x,int y);
	void	SlotDrawEnd(void);
protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;

private:
    Ui::SelectAreaForm *ui;
};

#endif // SELECTAREAFORM_H
