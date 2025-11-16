#ifndef EDITOCRITEMDIALOG_H
#define EDITOCRITEMDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XColorSpace.h"

namespace Ui {
class EditOCRItemDialog;
}

class EditOCRItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditOCRItemDialog(LayersBase *Base, QWidget *parent = 0);
    ~EditOCRItemDialog();

	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	QString		ItemName;
	int			RegNumber;
	bool		InspectMatching;
	bool		SaveIntoResult;
	bool		OKByFailingRecognition;
	QStringList		CorrectList;

	void	ReflectToWindow(void);
	void	FromWindow(void);

private slots:
    void on_listWidgetMatchingList_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddMatchingList_clicked();
    void on_pushButtonSubMatchingList_clicked();
    void on_ButtonSaveNewItem_clicked();
    void on_ButtonUpdateItem_clicked();
    void on_pushButtonClose_clicked();

    void on_ButtonDeleteItem_clicked();

    void on_pushButtonPickupColor_clicked();

    void on_pushButtonPickupBrightness_clicked();

    void on_pushButtonRotation0_clicked();

    void on_pushButtonRotation90_clicked();

    void on_pushButton180_clicked();

    void on_pushButton270_clicked();

private:
    Ui::EditOCRItemDialog *ui;
};

#endif // EDITOCRITEMDIALOG_H
