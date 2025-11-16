#ifndef NGIMAGEDIALOG_H
#define NGIMAGEDIALOG_H

#include <QDialog>
#include <QWidget>
#include "XIntClass.h"
#include "PQSystemService.h"

namespace Ui {
class NGImageDialog;
}
class NGImageListForm;
class IntegNGImage;
class NGListByMaster;
class NGPanel;
class NGImageDialog;


class NGImagePanel : public ImagePanel
{
	NGPanel	*Parent;
public:
	IntegNGImage	*Pointer;
	int		Importance;

	NGImagePanel(NGPanel *p);
	~NGImagePanel(){}

protected:
	virtual	void	paintEvent(QPaintEvent *event)	override;
	virtual	void	mouseReleaseEvent(QMouseEvent *event)	override;
};

class NGPanel : public ScrollPanel , public NPList<NGPanel>
{
	NGImageDialog	*Parent;
public:
	int		MachineID;
	NGListByMaster		*Pointer;

	NGPanel(NGImageDialog *p,QWidget *parent = nullptr);
	~NGPanel();

	virtual	ImagePanel	*CreatePanel(void);
	void	Set(NGListByMaster *p);

	void	SetImportance(NGImagePanel *panel);
};


class NGImageDialog : public QDialog
{
    Q_OBJECT
    NGImageListForm	*Parent;

	NPListPack<NGPanel>	NGPanelData;

public:
    explicit NGImageDialog(NGImageListForm *p ,QWidget *parent = 0);
    ~NGImageDialog();
    
	int	GetImportance(void);
private slots:
    void on_tableWidgetSelectID_itemSelectionChanged();
    void on_tableWidgetSelectID_doubleClicked(const QModelIndex &index);

private:
    Ui::NGImageDialog *ui;

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // NGIMAGEDIALOG_H
