#include "ui_HistoryListErrorForm.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"

class HistoryListErrorDialog : public QDialog
{
public:
	HistoryListErrorDialog(QWidget *parent=NULL):QDialog(parent){
		ui.setupUi(this);
	};

public:
	void setHistory(OrganizedHistoryListPtr listPtr, Review::OrganizedSideType oside);
	bool hasError();

private:
	Ui::HistoryListErrorClass ui;
};