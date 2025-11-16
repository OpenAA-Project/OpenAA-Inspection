#ifndef PROPERTYPIECEFORREVIEWFORM_H
#define PROPERTYPIECEFORREVIEWFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPieceForReview.h"

namespace Ui {
    class PropertyPieceForReviewForm;
}

class PropertyPieceForReviewForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyPieceForReviewForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyPieceForReviewForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonOverlap_clicked();

private:
    Ui::PropertyPieceForReviewForm *ui;

	ItemsContainerPieceForReview	ListData;
};

#endif // PROPERTYPIECEFORREVIEWFORM_H
