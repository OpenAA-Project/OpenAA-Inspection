#include "XTypeDef.h"
#include "PasswordDragFrame.h"
#include <QDrag>

PasswordDragFrame::PasswordDragFrame(QWidget *parent)
:QFrame(parent), m_FilePath(/**/""), startPos(0, 0), m_pfo(NULL)
{
	QFrame::setFrameShadow(QFrame::Raised);
	QFrame::setFrameShape(QFrame::Box);
}

//マウスを押したときに呼び出される仮想関数
void PasswordDragFrame::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
		startPos = event->pos();
	QFrame::mousePressEvent(event);
}

//ドラッグ開始時に呼び出される仮想関数
void PasswordDragFrame::mouseMoveEvent(QMouseEvent * event)
{
	if(event->buttons() & Qt::LeftButton){
		int distance = (event->pos() - startPos).manhattanLength();
		if(distance >= QApplication::startDragDistance())
			startDrag();//実際のドラッグ開始
	}
	QFrame::mouseMoveEvent(event);
}

//ドラッグ開始
void PasswordDragFrame::startDrag()
{
	QDrag *drag = new QDrag(this);
	PasswordMimeData *mimeData = new PasswordMimeData;

	//QString appPath = qApp->applicationFilePath();
	//appPath = appPath.left(appPath.findRev('.')) + ".pwd";

	mimeData->setText("Password");
	mimeData->setDragFrame(this);
	drag->setMimeData(mimeData);
	QPixmap pix(/**/"images/dragpict.png");
	drag->setPixmap(pix);
	drag->exec();
}

QString PasswordDragFrame::PasswordFilePath()
{
	QString passFileName = qApp->applicationFilePath();
	passFileName = passFileName.left(passFileName.lastIndexOf('.')) + /**/".pwd";
	return passFileName;
}

//描画イベント
void PasswordDragFrame::paintEvent(QPaintEvent* event)
{
	QPixmap pix(/**/"images/dragpict.png");

	QPainter paint;
	paint.begin(this);
	paint.drawPixmap(0, 0, pix);
	paint.end();

	QFrame::paintEvent(event);
}

void PasswordDragFrame::setPasswordFileOperator(PasswordFileOperator *pfo)
{
	m_pfo = pfo;
}

void PasswordDragFrame::addItem(QString objectName)
{
	m_pfo->addItem(objectName);
}