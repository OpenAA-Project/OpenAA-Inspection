#ifndef SHOWMARKLISTFORM_H
#define SHOWMARKLISTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlignmentFlexArea.h"

namespace Ui {
class ShowMarkListForm;
}

class ShowMarkListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	AlignmentFlexAreaItemListPack	*PageDim;
public:
    explicit ShowMarkListForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowMarkListForm();

	void Initial(int AreaID ,int LibID);

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonClose_clicked();

private:
    Ui::ShowMarkListForm *ui;
};

#endif // SHOWMARKLISTFORM_H
