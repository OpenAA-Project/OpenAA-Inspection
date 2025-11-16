#include "SelectLotForReviewResource.h"
#include "ResultLotLoadForm.h"

ResultLotLoadForm::ResultLotLoadForm(QWidget *parent, Qt::WindowFlags f)
	:QDialog(parent, f)
{
	ui.setupUi(this);

	ui.twResultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
	ui.twResultTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

void ResultLotLoadForm::setValue(quint32 FrontNGCount, quint32 FrontOKCount, quint32 BackNGCount, quint32 BackOKCount, bool isOtherErrorExist)
{
	ui.twResultTable->clearContents();

	QTableWidgetItem *fNGItem, *fOKItem, *bNGItem, *bOKItem, *fSumItem, *bSumItem;

	QFont itemFont = font();
	itemFont.setPointSize(28);

	fNGItem = new QTableWidgetItem(QString::number(FrontNGCount));
	fNGItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
	fNGItem->setFont(itemFont);

	fOKItem = new QTableWidgetItem(QString::number(FrontOKCount));
	fOKItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
	fOKItem->setFont(itemFont);
	
	fSumItem = new QTableWidgetItem(QString::number(FrontNGCount+FrontOKCount));
	fSumItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
	fSumItem->setFont(itemFont);

	bNGItem = new QTableWidgetItem(QString::number(BackNGCount));
	bNGItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
	bNGItem->setFont(itemFont);
	
	bOKItem = new QTableWidgetItem(QString::number(BackOKCount));
	bOKItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
	bOKItem->setFont(itemFont);
	
	bSumItem = new QTableWidgetItem(QString::number(BackNGCount+BackOKCount));
	bSumItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
	bSumItem->setFont(itemFont);

	ui.twResultTable->setItem(0, 0, fNGItem);
	ui.twResultTable->setItem(1, 0, fOKItem);
	ui.twResultTable->setItem(2, 0, fSumItem);
	ui.twResultTable->setItem(0, 1, bNGItem);
	ui.twResultTable->setItem(1, 1, bOKItem);
	ui.twResultTable->setItem(2, 1, bSumItem);

	if((FrontNGCount+FrontOKCount)!=(BackNGCount+BackOKCount)){
		ui.twResultTable->item(2, 0)->setTextColor(QColor(Qt::red));
		ui.twResultTable->item(2, 1)->setTextColor(QColor(Qt::red));
		ui.lbResultText->setText(/**/"Error");
		QPalette p;
		p.setColor(QPalette::ColorRole::WindowText, QColor(Qt::red));
		p.setColor(QPalette::ColorRole::Text, QColor(Qt::red));
		ui.lbResultText->setPalette(p);
	}else{
		QPalette p;
		if(isOtherErrorExist==false){
			ui.twResultTable->item(2, 0)->setTextColor(p.color(QPalette::ColorRole::Text));
			ui.twResultTable->item(2, 1)->setTextColor(p.color(QPalette::ColorRole::Text));
			ui.lbResultText->setText(/**/"OK");
			p.setColor(QPalette::ColorRole::WindowText, QColor(Qt::blue));
			p.setColor(QPalette::ColorRole::Text, QColor(Qt::blue));
			ui.lbResultText->setPalette(p);
		}else{
			ui.twResultTable->item(2, 0)->setTextColor(QColor(Qt::red));
			ui.twResultTable->item(2, 1)->setTextColor(QColor(Qt::red));
			ui.lbResultText->setText(/**/"Error");
			QPalette p;
			p.setColor(QPalette::ColorRole::WindowText, QColor(Qt::red));
			p.setColor(QPalette::ColorRole::Text, QColor(Qt::red));
			ui.lbResultText->setPalette(p);
		}
	}
}