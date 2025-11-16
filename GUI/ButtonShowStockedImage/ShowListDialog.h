#ifndef SHOWLISTDIALOG_H
#define SHOWLISTDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "mtGraphicUnit.h"
#include "ButtonShowStockedImage.h"

namespace Ui {
class ShowListDialog;
}

class	ShowListDialog;
class	ButtonShowStockedImage;

class	ChildImagePanel : public mtGraphicUnit,public ServiceForLayers
{
	Q_OBJECT

	ShowListDialog	*Parent;
	QImage		*Img;
public:

protected:
	ImageBufferWithInfo	*Buffer;

public:

	ChildImagePanel(LayersBase *Base,ShowListDialog *parent);
	virtual	~ChildImagePanel(void);
	
	void	SetImage(ImageBufferWithInfo *buff);

private slots:
	void	SlotOnPaint(QPainter &pnt);
};


class ShowListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ChildImagePanel	Panel;
public:
	ButtonShowStockedImage	*Parent;
	NPListPack<ImageBufferWithInfoPointerContainer> List;

    explicit ShowListDialog(ButtonShowStockedImage *p,LayersBase *Base ,QWidget *parent = 0);
    ~ShowListDialog();
    
private slots:
    void on_tableWidgetShotList_clicked(const QModelIndex &index);
    void on_tableListInOneShot_clicked(const QModelIndex &index);

private:
    Ui::ShowListDialog *ui;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // SHOWLISTDIALOG_H
