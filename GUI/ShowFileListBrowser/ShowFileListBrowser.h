#ifndef SHOWFILELISTBROWSER_H
#define SHOWFILELISTBROWSER_H

#include "showfilelistbrowser_global.h"
#include <QScrollBar>
#include <QTranslator>
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QFileSystemModel>
#include <QListView>
#include <QStyledItemDelegate>
#include <QLabel>
#include <QIcon>
#include <QToolButton>
#include <QTimer>

class	ThumbViewDelegate;
class	ShowFileListBrowser;

class	QFileListListView : public QListView
{
	Q_OBJECT

	ShowFileListBrowser	*Parent;
	int	XPos,YPos;
	QTimer				TM;
public:
	QFileListListView(ShowFileListBrowser * parent );

protected:
	virtual	void	mouseReleaseEvent ( QMouseEvent * event ) override;
	virtual	void	dragEnterEvent ( QDragEnterEvent * event ) override;
	virtual	void	dropEvent ( QDropEvent * event ) override;

	virtual	bool event(QEvent *event)	 override;

private slots:
	void	SlotTimeOut();
};

class	QListViewPort : public QWidget
{
	ShowFileListBrowser	*Parent;
	int	XPos,YPos;
public:
	QListViewPort(ShowFileListBrowser *parent,QWidget *p);
protected:
	virtual	void	dragEnterEvent ( QDragEnterEvent * event ) override;
	virtual	void	dropEvent ( QDropEvent * event )	override;
	virtual	void	mouseMoveEvent(QMouseEvent *event)	override;//	Not work
};

class	ShowFileListBrowser : public GUIFormBase
{
	Q_OBJECT
		
	ThumbViewDelegate	*thumbviewDelegate;
	QImage		Pic;
	QListViewPort		*ViewPort;
public:
	QLabel				LabelPath;
	QFileSystemModel	Model;
	QFileListListView	View;
	QIcon				ButtonUpperIcon;
	QToolButton			ButtonUpper;
	QString				ImageType;
	QString				TransformImage;

	QString		Path;
	QStringList	Suffix;
	int32		IconWidth	;
	int32		IconHeight	;
	//QSize		IconSize;
	QFont		TextFont;
	bool		UpdatePageSizeMode;
	QPoint		ReleasedPoint;

	class	CmdSetPath : public GUIDirectMessage
	{
	public:
		QString Path;
		CmdSetPath(LayersBase *base):GUIDirectMessage(base){}
	};

	ShowFileListBrowser(LayersBase *Base ,QWidget *parent);
	~ShowFileListBrowser();

	virtual void	ReadyParam(void)							override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Repaint(void)								override;
signals:
	void	SignalDoubleClickedFile(const QString &FileName);
	void	SignalCopyPic();
private slots:
	void	ResizeAction();
	void	SlotDoubleClicked ( const QModelIndex & index );
	void	SlotButtonUpperClicked();
	void	SlotCopyPic();

	void	SlotDelete();
	void	SlotCopy();
	void	SlotPaste();
	void	SlotOpen();
	void	SlotChangeFileName();
private:
	bool	LoadImage(const QString &FileNameWithPath ,int page=-1);
};

class ThumbViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

	ShowFileListBrowser	*Parent;
public:
    ThumbViewDelegate(ShowFileListBrowser *p,QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;
};


class	CmdLoadImageInBrowser: public GUIDirectMessage
{
public:
	bool	Mastered;
	QString	FileName;
	int		LoadedPage;
	bool	Result;

	CmdLoadImageInBrowser(LayersBase *base):GUIDirectMessage(base)			{	LoadedPage=0;	}
	CmdLoadImageInBrowser(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	LoadedPage=0;	}
};

#endif // SHOWFILELISTBROWSER_H
