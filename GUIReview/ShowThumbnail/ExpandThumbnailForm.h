#if	!defined(ExpandThumbnailDialog_h)
#define	ExpandThumbnailDialog_h

#include <QDialog>
#include "ui_ExpandThumbnailForm.h"

class	ShowThumbnail;
class Thumbnail;


class ExpandThumbnailDialog : public QDialog
{
	Q_OBJECT

	ShowThumbnail *MainParent;
public:
	ExpandThumbnailDialog(ShowThumbnail *MainParent ,QWidget *parent=NULL, Qt::WindowFlags flags=0);

public:
	void setThumbnail(Thumbnail *thumbnail);
	Thumbnail *getThumbnail(void) const { return myThumbnail; };

	void	Initial(void);
	int		KeyCode;
	bool	KeyType;

protected:
	virtual	void paintEvent(QPaintEvent *event)		override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
	virtual	void keyPressEvent(QKeyEvent *event)	override;
	virtual	void mousePressEvent(QMouseEvent *event)override;

public:
	void updateImage(void);

private slots:
    void on_pushButtonSetKey_clicked();

private:
	Ui::ExpandThumbnailForm ui;
	Thumbnail *myThumbnail;
	bool reqUpdate;
	bool drawNG;
};

#endif
