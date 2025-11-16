/********************************************************************************
** Form generated from reading UI file 'ShowSumTimerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSUMTIMERFORM_H
#define UI_SHOWSUMTIMERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowSumTimerForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbTitle;
    QLabel *lbTime;
    QProgressBar *progressBar;
    QPushButton *pbReset;

    void setupUi(GUIFormBase *ShowSumTimerForm)
    {
        if (ShowSumTimerForm->objectName().isEmpty())
            ShowSumTimerForm->setObjectName("ShowSumTimerForm");
        ShowSumTimerForm->resize(234, 146);
        ShowSumTimerForm->setMinimumSize(QSize(139, 102));
        verticalLayout = new QVBoxLayout(ShowSumTimerForm);
        verticalLayout->setObjectName("verticalLayout");
        lbTitle = new QLabel(ShowSumTimerForm);
        lbTitle->setObjectName("lbTitle");
        QFont font;
        font.setPointSize(20);
        lbTitle->setFont(font);
        lbTitle->setFrameShape(QFrame::NoFrame);
        lbTitle->setFrameShadow(QFrame::Plain);
        lbTitle->setTextFormat(Qt::AutoText);
        lbTitle->setScaledContents(false);
        lbTitle->setAlignment(Qt::AlignCenter);
        lbTitle->setWordWrap(false);

        verticalLayout->addWidget(lbTitle);

        lbTime = new QLabel(ShowSumTimerForm);
        lbTime->setObjectName("lbTime");
        QFont font1;
        font1.setPointSize(32);
        font1.setBold(true);
        lbTime->setFont(font1);
        lbTime->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbTime);

        progressBar = new QProgressBar(ShowSumTimerForm);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        pbReset = new QPushButton(ShowSumTimerForm);
        pbReset->setObjectName("pbReset");
        pbReset->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Refresh.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbReset->setIcon(icon);
        pbReset->setAutoRepeat(false);
        pbReset->setAutoExclusive(false);
        pbReset->setAutoDefault(false);
        pbReset->setFlat(false);

        verticalLayout->addWidget(pbReset);


        retranslateUi(ShowSumTimerForm);

        pbReset->setDefault(false);


        QMetaObject::connectSlotsByName(ShowSumTimerForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowSumTimerForm)
    {
        ShowSumTimerForm->setWindowTitle(QCoreApplication::translate("ShowSumTimerForm", "ShowSumTimerForm", nullptr));
        lbTitle->setText(QCoreApplication::translate("ShowSumTimerForm", "Title", nullptr));
        lbTime->setText(QCoreApplication::translate("ShowSumTimerForm", "00:00:00", nullptr));
        pbReset->setText(QCoreApplication::translate("ShowSumTimerForm", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSumTimerForm: public Ui_ShowSumTimerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSUMTIMERFORM_H
