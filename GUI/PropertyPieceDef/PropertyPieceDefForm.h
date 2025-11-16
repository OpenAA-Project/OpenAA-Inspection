#ifndef PROPERTYPIECEDEFFORM_H
#define PROPERTYPIECEDEFFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyPieceDefPacket.h"

namespace Ui {
class PropertyPieceDefForm;
}

class PropertyPieceDefForm : public GUIFormBase
{
    Q_OBJECT
    
	PieceDefInfoContainer	DefList;
public:
    explicit PropertyPieceDefForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyPieceDefForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	ShowItemGrid(void);

private slots:
    void on_pushButtonStartSearch_clicked();
    void on_tableWidgetResult_clicked(const QModelIndex &index);
    void on_pushButtonCopyByFoundItems_clicked();
    void on_pushButtonMatchClosed_clicked();

private:
    Ui::PropertyPieceDefForm *ui;
};



#endif // PROPERTYPIECEDEFFORM_H
