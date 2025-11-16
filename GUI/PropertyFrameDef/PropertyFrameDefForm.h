#ifndef PROPERTYFrameDEFFORM_H
#define PROPERTYFrameDEFFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyFrameDefPacket.h"
#include "XFrameDef.h"

namespace Ui {
class PropertyFrameDefForm;
}

class PropertyFrameDefForm : public GUIFormBase
{
    Q_OBJECT
    FrameContainer		FrameGrid;
public:
    explicit PropertyFrameDefForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyFrameDefForm();
    
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	ShowItemGrid(void);

private slots:

    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonOverlap_clicked();

private:
    Ui::PropertyFrameDefForm *ui;
};



#endif // PROPERTYFrameDEFFORM_H
