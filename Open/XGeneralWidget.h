#pragma once

#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QTableWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include "XTypeDef.h"

class QPushButtonWithRightClick : public QPushButton
{
	Q_OBJECT

public:
	QPushButtonWithRightClick(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
	QPushButtonWithRightClick(const QString &text, QWidget *parent = nullptr);
	QPushButtonWithRightClick(QWidget *parent = nullptr);

private:
	virtual	void mouseReleaseEvent(QMouseEvent *e)	override;

signals:
	void	RightClicked();
};

class QToolButtonWithRightClick : public QToolButton
{
	Q_OBJECT

public:
	QToolButtonWithRightClick(QWidget *parent = nullptr);

private:
	virtual	void mouseReleaseEvent(QMouseEvent *e)	override;

signals:
	void	RightClicked();
};

class QCheckBoxWithRightClick : public QCheckBox
{
	Q_OBJECT

public:
	QCheckBoxWithRightClick(const QString &text, QWidget *parent = nullptr);
	QCheckBoxWithRightClick(QWidget *parent = nullptr);

private:
	virtual	void mouseReleaseEvent(QMouseEvent *e)	override;

signals:
	void	RightClicked();
};

class QRadioButtonWithRightClick : public QRadioButton
{
	Q_OBJECT

public:
	QRadioButtonWithRightClick(const QString &text, QWidget *parent = nullptr);
	QRadioButtonWithRightClick(QWidget *parent = nullptr);

private:
	virtual	void mouseReleaseEvent(QMouseEvent *e)	override;

signals:
	void	RightClicked();
};

class QComboBoxWithRightClick : public QComboBox
{
	Q_OBJECT

public:
	QComboBoxWithRightClick(QWidget *parent = nullptr);

private:
	virtual	void mouseReleaseEvent(QMouseEvent *e)	override;

signals:
	void	RightClicked();
};

class QTableWidgetWithRightClick : public QTableWidget
{
	Q_OBJECT
public:
	QTableWidgetWithRightClick(int rows, int columns, QWidget *parent = nullptr);
	QTableWidgetWithRightClick(QWidget *parent = nullptr);
	~QTableWidgetWithRightClick(void){}

signals:
	void	rightclicked(QTableWidgetItem *cell);

private:
	virtual	void mousePressEvent(QMouseEvent *event)	override;
};


class QListWidgetWithRightClick : public QListWidget
{
	Q_OBJECT
public:
	QListWidgetWithRightClick(QWidget *parent = nullptr);
	~QListWidgetWithRightClick(void){}

signals:
	void	rightclicked(QListWidgetItem *cell);

private:
	virtual	void mousePressEvent(QMouseEvent *event)	override;
};


class QTreeWidgetWithRightClick : public QTreeWidget
{
	Q_OBJECT
public:
	QTreeWidgetWithRightClick(QWidget *parent = nullptr);
	~QTreeWidgetWithRightClick(void){}

signals:
	void	rightclicked(QTreeWidgetItem *cell);

private:
	virtual	void mousePressEvent(QMouseEvent *event)	override;
};

