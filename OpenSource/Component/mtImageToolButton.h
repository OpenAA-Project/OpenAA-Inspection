#ifndef MTIMAGETOOLBUTTON_H
#define MTIMAGETOOLBUTTON_H

#include <QToolButton>
#include <QImage>

#include "mtImageButtonBase.h"

class mtImageToolButton : public QToolButton, public mtImageButtonBase
{
	Q_OBJECT

public:
	explicit	mtImageToolButton(QWidget *parent, bool checked = true);
	explicit	mtImageToolButton(const QImage &_img, QWidget *parent, bool checked = true);
	~mtImageToolButton();

	void setImageBmp(const QImage &_img);

	void Exec(void);
	void Cancel(void);

	void setChecked ( bool );
	bool isChecked ()	const;

protected:
	int nDrawX;
	int nDrawY;

	virtual void paintEvent(QPaintEvent *evt)			override;
	virtual void mousePressEvent(QMouseEvent *evt)		override;
	virtual void mouseMoveEvent(QMouseEvent *evt)		override;
	virtual void mouseReleaseEvent(QMouseEvent *evt)	override;
	virtual void closeEvent(QCloseEvent *evt)			override;
	virtual void showEvent ( QShowEvent * event )		override;

	void OnPressed(bool checked);

public slots:
	virtual	void SlotClicked(bool checked);
	void	click ();

private slots:
	void SlotReleased();

signals:
	void SignalClicked(bool checked=false);

private:
	bool	vChecked;
};

#endif // MTIMAGETOOLBUTTON_H
