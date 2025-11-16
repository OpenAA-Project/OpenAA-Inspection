#pragma once

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPushButton>

class ControlInfoDialog : public QDialog
{
	Q_OBJECT

public:
	ControlInfoDialog(QWidget *parent=NULL)
		:QDialog(parent),m_InfoCount(0),m_mainLayout(new QGridLayout),m_pbLayout(new QHBoxLayout),m_pbOk(new QPushButton("Close")),m_dataChanged(false)
	{
		setWindowTitle("Control Infomation Form");

		m_pbLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding));
		m_pbLayout->addWidget(m_pbOk);

		connect(m_pbOk, SIGNAL(clicked()), this, SLOT(clickedOK()));

		setLayout(m_mainLayout);
	};

public:
	void append(QString key, QString InfoStr)
	{
		QLabel *keyLabel = new QLabel(key);
		QLabel *InfoLabel = new QLabel(InfoStr);

		keyLabel->setScaledContents(true);
		InfoLabel->setScaledContents(true);

		keyLabel->setAlignment(Qt::AlignCenter);
		InfoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

		m_mainLayout->removeItem(m_pbLayout);

		if(m_InfoCount!=0){
			QFrame *line = new QFrame;
			line->setFrameShape(QFrame::HLine);
			line->setFrameShadow(QFrame::Sunken);
			m_mainLayout->addWidget(line, m_InfoCount, 0, 1, 3);
			m_InfoCount++;
		}

		m_mainLayout->addWidget(keyLabel, m_InfoCount, 0);

		QFrame *line = new QFrame;
		line->setFrameShape(QFrame::VLine);
		line->setFrameShadow(QFrame::Sunken);
		m_mainLayout->addWidget(line, m_InfoCount, 1);

		m_mainLayout->addWidget(InfoLabel, m_InfoCount, 2);
		m_InfoCount++;

		//m_mainLayout->addWidget(m_pbOk, m_InfoCount+1, 2, 1, 1);
		m_mainLayout->addLayout(m_pbLayout, m_InfoCount+1, 0, 1, m_mainLayout->columnCount());

		m_dataChanged = true;
	};

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override{
		QDialog::paintEvent(event);
		if(m_dataChanged==true){
			setMinimumSize(0, 0);
			setMaximumSize(INT_MAX, INT_MAX);

			updateGeometry();

			setFixedSize(geometry().width(), geometry().height());

			m_dataChanged = false;
		}
	}

private:
	void updateLayout();

private slots:
	void clickedOK(){
		setVisible(false);
	};
	
private:
	int m_InfoCount;
	QGridLayout *m_mainLayout;
	QHBoxLayout *m_pbLayout;
	QPushButton *m_pbOk;

	bool m_dataChanged;
};