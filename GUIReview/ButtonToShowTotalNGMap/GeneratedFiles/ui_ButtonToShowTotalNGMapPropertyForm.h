/********************************************************************************
** Form generated from reading UI file 'ButtonToShowTotalNGMapPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONTOSHOWTOTALNGMAPPROPERTYFORM_H
#define UI_BUTTONTOSHOWTOTALNGMAPPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ButtonToShowTotalNGMapPropertyClass
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *OK;
    QPushButton *Cancel;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *cbIgnoreResultError;
    QGroupBox *gbNGView;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QComboBox *cbDrawShape;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpinBox *sbNGDrawSize;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *lbNGColorSample;
    QToolButton *tbNGColor;
    QGroupBox *gbSplitCount;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *sbSplitCountX;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *sbSplitCountY;

    void setupUi(QDialog *ButtonToShowTotalNGMapPropertyClass)
    {
        if (ButtonToShowTotalNGMapPropertyClass->objectName().isEmpty())
            ButtonToShowTotalNGMapPropertyClass->setObjectName(QString::fromUtf8("ButtonToShowTotalNGMapPropertyClass"));
        ButtonToShowTotalNGMapPropertyClass->resize(359, 227);
        gridLayout_3 = new QGridLayout(ButtonToShowTotalNGMapPropertyClass);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        OK = new QPushButton(ButtonToShowTotalNGMapPropertyClass);
        OK->setObjectName(QString::fromUtf8("OK"));

        horizontalLayout->addWidget(OK);

        Cancel = new QPushButton(ButtonToShowTotalNGMapPropertyClass);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));

        horizontalLayout->addWidget(Cancel);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        cbIgnoreResultError = new QCheckBox(ButtonToShowTotalNGMapPropertyClass);
        cbIgnoreResultError->setObjectName(QString::fromUtf8("cbIgnoreResultError"));

        horizontalLayout_7->addWidget(cbIgnoreResultError);


        gridLayout_3->addLayout(horizontalLayout_7, 1, 0, 1, 2);

        gbNGView = new QGroupBox(ButtonToShowTotalNGMapPropertyClass);
        gbNGView->setObjectName(QString::fromUtf8("gbNGView"));
        gridLayout_2 = new QGridLayout(gbNGView);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(gbNGView);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        cbDrawShape = new QComboBox(gbNGView);
        cbDrawShape->setObjectName(QString::fromUtf8("cbDrawShape"));

        horizontalLayout_6->addWidget(cbDrawShape);


        gridLayout_2->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(gbNGView);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        sbNGDrawSize = new QSpinBox(gbNGView);
        sbNGDrawSize->setObjectName(QString::fromUtf8("sbNGDrawSize"));

        horizontalLayout_5->addWidget(sbNGDrawSize);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(gbNGView);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lbNGColorSample = new QLabel(gbNGView);
        lbNGColorSample->setObjectName(QString::fromUtf8("lbNGColorSample"));

        horizontalLayout_4->addWidget(lbNGColorSample);

        tbNGColor = new QToolButton(gbNGView);
        tbNGColor->setObjectName(QString::fromUtf8("tbNGColor"));

        horizontalLayout_4->addWidget(tbNGColor);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        gridLayout_3->addWidget(gbNGView, 0, 1, 1, 1);

        gbSplitCount = new QGroupBox(ButtonToShowTotalNGMapPropertyClass);
        gbSplitCount->setObjectName(QString::fromUtf8("gbSplitCount"));
        gridLayout = new QGridLayout(gbSplitCount);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(gbSplitCount);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        sbSplitCountX = new QSpinBox(gbSplitCount);
        sbSplitCountX->setObjectName(QString::fromUtf8("sbSplitCountX"));
        sbSplitCountX->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sbSplitCountX->setMinimum(1);
        sbSplitCountX->setMaximum(999999999);
        sbSplitCountX->setValue(100);

        horizontalLayout_2->addWidget(sbSplitCountX);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(gbSplitCount);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        sbSplitCountY = new QSpinBox(gbSplitCount);
        sbSplitCountY->setObjectName(QString::fromUtf8("sbSplitCountY"));
        sbSplitCountY->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sbSplitCountY->setMinimum(1);
        sbSplitCountY->setMaximum(999999999);
        sbSplitCountY->setValue(100);

        horizontalLayout_3->addWidget(sbSplitCountY);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        gridLayout_3->addWidget(gbSplitCount, 0, 0, 1, 1);


        retranslateUi(ButtonToShowTotalNGMapPropertyClass);
        QObject::connect(OK, SIGNAL(clicked()), ButtonToShowTotalNGMapPropertyClass, SLOT(accept()));
        QObject::connect(Cancel, SIGNAL(clicked()), ButtonToShowTotalNGMapPropertyClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(ButtonToShowTotalNGMapPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *ButtonToShowTotalNGMapPropertyClass)
    {
        ButtonToShowTotalNGMapPropertyClass->setWindowTitle(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "ButtonToShowTotalNGMapForm", nullptr));
        OK->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "OK", nullptr));
        Cancel->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "Cancel", nullptr));
        cbIgnoreResultError->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "Ignore 'MaxError' and 'TimeOut'", nullptr));
        gbNGView->setTitle(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "NGView", nullptr));
        label_5->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "Draw shape", nullptr));
        label_4->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "Draw size", nullptr));
        label_3->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "Color", nullptr));
        lbNGColorSample->setText(QString());
        tbNGColor->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "...", nullptr));
        gbSplitCount->setTitle(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "SplitCount", nullptr));
        label->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "X", nullptr));
        label_2->setText(QCoreApplication::translate("ButtonToShowTotalNGMapPropertyClass", "Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonToShowTotalNGMapPropertyClass: public Ui_ButtonToShowTotalNGMapPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONTOSHOWTOTALNGMAPPROPERTYFORM_H
