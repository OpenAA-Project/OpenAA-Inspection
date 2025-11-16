#ifndef CHECKEVERYDAYRESULTHISTORYFORM_H
#define CHECKEVERYDAYRESULTHISTORYFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "XCheckEverydayCommon.h"

namespace Ui {
class CheckEverydayResultHistoryForm;
}

class	CheckEverydayResultHistoryForm;

class	ResultListOfCheckEveryday : public NPList<ResultListOfCheckEveryday>
{
public:
	XDateTime	ResultTime;
	double		CurrentValue;
	bool		Result;
	int64		InspectionID;

	ResultListOfCheckEveryday(void){}

	bool	SaveText(QTextStream &f);
};


class	HistoryListOfCheckEveryday : public NPList<HistoryListOfCheckEveryday>
{
	CheckEverydayResultHistoryForm	*Parent;
public:
	int32		Page;
	int32		Layer;
	int32		ID;
	NPListPack<ResultListOfCheckEveryday>	ResultContainer;

	HistoryListOfCheckEveryday(CheckEverydayResultHistoryForm *parent):Parent(parent){}

	bool	SaveText(QTextStream &f);
};


class CheckEverydayResultHistoryForm : public GUIFormBase
{
    Q_OBJECT

	CheckEverydayLightInfoContainer	InfoLight;
	CheckEverydayFocusInfoContainer	InfoFocus;

	NPListPack<HistoryListOfCheckEveryday>	HistoryList;

public:
    explicit CheckEverydayResultHistoryForm(LayersBase *Base ,QWidget *parent = 0);
    ~CheckEverydayResultHistoryForm();

	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	HistoryListOfCheckEveryday	*SearchHistory(int page ,int layer ,int ld);
	QString						SearchItemName(int page ,int layer ,int ld);

private slots:
    void on_pushButtonSaveButton_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);

private:
    Ui::CheckEverydayResultHistoryForm *ui;
};

//-----------------------------------------------------------------------------------------------------------


#endif // CHECKEVERYDAYRESULTHISTORYFORM_H
