#pragma once

#include <QStackedWidget>
#include <QGridLayout>

#include "Thumbnail.h"

// ページ一枚分
// 単一のQGridLayoutを持ち、全体に表示する
// 
class ThumbnailPage : public QWidget
{
public:
	ThumbnailPage(QWidget *parent=NULL)
		:QWidget(parent)
	{
		mainLayout = new QGridLayout(this);
		mainLayout->setSpacing(6);
		mainLayout->setObjectName(QString::fromUtf8(/**/"mainLayout"));
	};
	~ThumbnailPage(){
		delete mainLayout;
	};

	void addThumnail(Thumbnail *item){
		mainLayout->addWidget(item, item->getRow(), item->getColumn(), 1, 1);
	};

	void removeThumbnail(Thumbnail *item){
		mainLayout->removeWidget(item);
	};

	int count() const { return mainLayout->count(); };

	inline const Thumbnail *item(int index) const {
		return dynamic_cast<Thumbnail *>(mainLayout->itemAt(index)->widget());
	};

	inline Thumbnail *item(int index) {
		return dynamic_cast<Thumbnail *>(mainLayout->itemAt(index)->widget());
	};

private:
	QGridLayout *mainLayout;
};
