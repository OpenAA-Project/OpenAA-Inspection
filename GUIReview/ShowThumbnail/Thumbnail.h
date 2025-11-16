#pragma once

#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QLayout>
#include "ReviewStructureItems.h"
#include "ui_ThumbnailForm.h"

class	ShowThumbnail;
// QPixmapを張り付けるためのNGNailItem保有QLabelクラス
// サムネイルGUIに格子状のレイアウト(QGridLayout)に張り付けられる
class Thumbnail : public QWidget
{
	Q_OBJECT

	ShowThumbnail	*Parent;
public:
	Thumbnail(ShowThumbnail *p ,int row=-1, int column=-1, QWidget *parent=0);
	~Thumbnail();

public:
	void setData(NGNailItem NGNail, QPixmap MasterPieceImage){ setNGNailItem(NGNail); setMasterPieceImage(MasterPieceImage); };
	void setNGNailItem(NGNailItem item){ m_NGItem = item; m_drawFlag = true; updateData(); };
	void setMasterPieceImage(QPixmap MasterPieceImage){ m_MasterImage = MasterPieceImage; m_drawFlag = true; updateData(); };
	void setPosision(int page ,int row, int column){ Page=page	;m_row = row; m_column = column; };
	void setSide(Review::SideType side)		{	Side=side;	}
	void setIndexInLocal(int index){ m_indexInLocal = index; };
	void setIndexInGlobal(int index){ m_indexInGlobal = index; };
	void setFKeyColor(QColor FKeyColor)	{ m_FKeyColor = FKeyColor; };
	void setFKey(Review::FKey key)		{	m_NGItem.FKey=key;	}
	void clearFKeyColor(){ QPalette p; m_FKeyColor = p.window().color();};
	void setSelectedColor(QColor color){ m_selectedColor = color; };
	void setNGSignSize(int size){ if(m_NGSignSize == size)return; m_NGSignSize = size; m_drawFlag = true; updateData(); };
	void updateImage(){ m_drawFlag = true; updateData(); };
	void setChecked(bool ch){ m_NGItem.isChecked = ch; m_drawFlag = true; updateData(); };
	void setViewMasterImage(bool v){ ui.lbMasterImage->setVisible(v); m_viewMasterImage = v; m_drawFlag = true; updateData(); };
	void setDummy(bool v){ m_isDummy = v; m_drawFlag = true; updateData(); };
	void setDrawEdge(bool v){ m_isDrawEdge; };
	void setDrawNGSingEnable(bool enable){ if(ui.lbNGImage->isDrawNGSingEnable()!=enable){ ui.lbNGImage->setDrawNGSingEnable(enable); updateData(); } };

	NGNailItem getNGNailItem() const { return m_NGItem; };
	QPixmap getMasterPieceImage() const { return m_MasterImage; };
	int getRow()	const	{ return m_row; };
	int getColumn() const	{ return m_column; };
	int	getPage()	const	{	return Page;	}
	int getIndexInLocal() const { return m_indexInLocal; };
	int getIndexInGlobal() const { return m_indexInGlobal; };
	QColor getFKeyColor() const { return m_FKeyColor; };
	int getNGSignSize() const { return m_NGSignSize; };
	bool isChecked() const { return (isDummy()==true) ? true : m_NGItem.isChecked; };
	QColor getSelectedColor() const { return m_selectedColor; };
	bool getViewMasterImage() const { return m_viewMasterImage; };

	void setSelected(bool selected);
	bool isSelected() const { return m_isSelected; };
	bool isDummy() const { return m_isDummy; };
	bool isDrawNGSingEnable() const { return ui.lbNGImage->isDrawNGSingEnable(); };

	Thumbnail *createDup() const;
	void updateData(void);
	void SetNailInformation(NGNailItem NGItem);

protected:
	virtual	void mousePressEvent(QMouseEvent *event)	override;
	virtual	void paintEvent(QPaintEvent *event)			override;
	virtual	void enterEvent(QEvent *event)				override;
	virtual	void leaveEvent(QEvent *event)				override;

signals:
	void clicked(Thumbnail *self);
	void clicked(int row, int column);
	void entered(Thumbnail *self);
	void entered(int row, int column);
	void leaved(Thumbnail *self);
	void leaved(int row, int column);

private:
	Ui::ThumbnailClass ui;
	NGNailItem m_NGItem;
	QPixmap m_MasterImage;
	int m_row;
	int m_column;
	int m_indexInLocal;
	int m_indexInGlobal;
	bool m_isSelected;
	QColor m_FKeyColor;
	QColor m_defaultWindowColor;
	QColor m_selectedColor;
	bool m_drawFlag;
	int m_NGSignSize;
	bool m_viewMasterImage;
	bool m_isDummy;
	bool m_isDrawEdge;
	int		KeyCode;
	bool	KeyType;
	int		Page;
	Review::SideType	Side;
};

typedef QList<Thumbnail *> ThumbnailList;

class ThumbnailPageItem : public QList<Thumbnail *>
{
public:
	ThumbnailPageItem(int page):QList<Thumbnail *>(),m_page(page){};
	void deleteAll(void){
		for(QList<Thumbnail *>::Iterator it=this->begin(); it!=this->end(); it++){
			delete *it;
		}
	};
	int getPage(){ return m_page; };
	void setPage(int page){ m_page = page; };
private:
	int m_page;
};

typedef QList<ThumbnailPageItem> ThumbnailPageList;

//class IncludeWidget : public QDialog
//{
//public:
//	IncludeWidget(QWidget *parent=NULL, Qt::WindowFlags flags=0):QDialog(parent,flags),myWidget(NULL),autoDelete(false)
//	{
//		mainLayout = new QGridLayout;
//		setLayout(mainLayout);
//	};
//	~IncludeWidget()
//	{
//		deleteWidget();
//	};
//	void addWidget(QWidget *widget){
//		deleteWidget();
//		myWidget = widget;
//		mainLayout = new QGridLayout;
//		mainLayout->addWidget(widget);
//		setLayout(mainLayout);
//	};
//	void setAutoDelete(bool enable){ autoDelete = enable; };
//	void deleteWidget(){
//		if(myWidget==NULL)return;
//
//		mainLayout->removeWidget(myWidget);
//		if(autoDelete==true){
//			delete myWidget;
//		}
//		myWidget = NULL;
//	};
//
//private:
//	QWidget *myWidget;
//	QLayout *mainLayout;
//	bool autoDelete;
//};