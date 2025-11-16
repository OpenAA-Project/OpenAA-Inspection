/********************************************************************************
** Form generated from reading UI file 'WholeImageForReviewPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHOLEIMAGEFORREVIEWPROPERTYFORM_H
#define UI_WHOLEIMAGEFORREVIEWPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_WholeImageForReviewPropertyClass
{
public:
    QGridLayout *gridLayout_6;
    QGroupBox *gbRotation;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cbFrontRotation;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *cbBackRotation;
    QLabel *label_4;
    QFrame *line;
    QGridLayout *gridLayout_3;
    QGroupBox *gbFrontBackOrientation;
    QGridLayout *gridLayout;
    QRadioButton *rbFrontBackHoriaontal;
    QRadioButton *rbFrontBackVertical;
    QGroupBox *gbPhaseOrientation;
    QGridLayout *gridLayout_2;
    QRadioButton *rbPhaseHoriaontal;
    QRadioButton *rbPhaseVertical;
    QGridLayout *gridLayout_4;
    QCheckBox *cbNGNailCrossView;
    QCheckBox *cbNGPointView;
    QCheckBox *cbOnlyCurrentNailView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbOk;
    QPushButton *pbApply;
    QPushButton *pbCancel;

    void setupUi(QDialog *WholeImageForReviewPropertyClass)
    {
        if (WholeImageForReviewPropertyClass->objectName().isEmpty())
            WholeImageForReviewPropertyClass->setObjectName(QString::fromUtf8("WholeImageForReviewPropertyClass"));
        WholeImageForReviewPropertyClass->resize(446, 264);
        gridLayout_6 = new QGridLayout(WholeImageForReviewPropertyClass);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gbRotation = new QGroupBox(WholeImageForReviewPropertyClass);
        gbRotation->setObjectName(QString::fromUtf8("gbRotation"));
        gridLayout_5 = new QGridLayout(gbRotation);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(gbRotation);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        cbFrontRotation = new QComboBox(gbRotation);
        cbFrontRotation->addItem(QString());
        cbFrontRotation->addItem(QString());
        cbFrontRotation->addItem(QString());
        cbFrontRotation->addItem(QString());
        cbFrontRotation->setObjectName(QString::fromUtf8("cbFrontRotation"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbFrontRotation->sizePolicy().hasHeightForWidth());
        cbFrontRotation->setSizePolicy(sizePolicy);
        cbFrontRotation->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_2->addWidget(cbFrontRotation);

        label_3 = new QLabel(gbRotation);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        gridLayout_5->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(gbRotation);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        cbBackRotation = new QComboBox(gbRotation);
        cbBackRotation->addItem(QString());
        cbBackRotation->addItem(QString());
        cbBackRotation->addItem(QString());
        cbBackRotation->addItem(QString());
        cbBackRotation->setObjectName(QString::fromUtf8("cbBackRotation"));
        sizePolicy.setHeightForWidth(cbBackRotation->sizePolicy().hasHeightForWidth());
        cbBackRotation->setSizePolicy(sizePolicy);
        cbBackRotation->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(cbBackRotation);

        label_4 = new QLabel(gbRotation);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 1, 1, 1);


        gridLayout_6->addWidget(gbRotation, 0, 0, 1, 1);

        line = new QFrame(WholeImageForReviewPropertyClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gbFrontBackOrientation = new QGroupBox(WholeImageForReviewPropertyClass);
        gbFrontBackOrientation->setObjectName(QString::fromUtf8("gbFrontBackOrientation"));
        gridLayout = new QGridLayout(gbFrontBackOrientation);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rbFrontBackHoriaontal = new QRadioButton(gbFrontBackOrientation);
        rbFrontBackHoriaontal->setObjectName(QString::fromUtf8("rbFrontBackHoriaontal"));

        gridLayout->addWidget(rbFrontBackHoriaontal, 0, 0, 1, 1);

        rbFrontBackVertical = new QRadioButton(gbFrontBackOrientation);
        rbFrontBackVertical->setObjectName(QString::fromUtf8("rbFrontBackVertical"));
        rbFrontBackVertical->setChecked(true);

        gridLayout->addWidget(rbFrontBackVertical, 1, 0, 1, 1);


        gridLayout_3->addWidget(gbFrontBackOrientation, 0, 0, 1, 1);

        gbPhaseOrientation = new QGroupBox(WholeImageForReviewPropertyClass);
        gbPhaseOrientation->setObjectName(QString::fromUtf8("gbPhaseOrientation"));
        gridLayout_2 = new QGridLayout(gbPhaseOrientation);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rbPhaseHoriaontal = new QRadioButton(gbPhaseOrientation);
        rbPhaseHoriaontal->setObjectName(QString::fromUtf8("rbPhaseHoriaontal"));
        rbPhaseHoriaontal->setChecked(true);

        gridLayout_2->addWidget(rbPhaseHoriaontal, 0, 0, 1, 1);

        rbPhaseVertical = new QRadioButton(gbPhaseOrientation);
        rbPhaseVertical->setObjectName(QString::fromUtf8("rbPhaseVertical"));

        gridLayout_2->addWidget(rbPhaseVertical, 1, 0, 1, 1);


        gridLayout_3->addWidget(gbPhaseOrientation, 0, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 2, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        cbNGNailCrossView = new QCheckBox(WholeImageForReviewPropertyClass);
        cbNGNailCrossView->setObjectName(QString::fromUtf8("cbNGNailCrossView"));

        gridLayout_4->addWidget(cbNGNailCrossView, 0, 0, 1, 1);

        cbNGPointView = new QCheckBox(WholeImageForReviewPropertyClass);
        cbNGPointView->setObjectName(QString::fromUtf8("cbNGPointView"));
        cbNGPointView->setChecked(true);

        gridLayout_4->addWidget(cbNGPointView, 0, 1, 1, 1);

        cbOnlyCurrentNailView = new QCheckBox(WholeImageForReviewPropertyClass);
        cbOnlyCurrentNailView->setObjectName(QString::fromUtf8("cbOnlyCurrentNailView"));
        cbOnlyCurrentNailView->setChecked(true);

        gridLayout_4->addWidget(cbOnlyCurrentNailView, 0, 2, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbOk = new QPushButton(WholeImageForReviewPropertyClass);
        pbOk->setObjectName(QString::fromUtf8("pbOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_128.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbOk->setIcon(icon);

        horizontalLayout->addWidget(pbOk);

        pbApply = new QPushButton(WholeImageForReviewPropertyClass);
        pbApply->setObjectName(QString::fromUtf8("pbApply"));

        horizontalLayout->addWidget(pbApply);

        pbCancel = new QPushButton(WholeImageForReviewPropertyClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbCancel->setIcon(icon1);

        horizontalLayout->addWidget(pbCancel);


        gridLayout_6->addLayout(horizontalLayout, 4, 0, 1, 1);

        QWidget::setTabOrder(rbFrontBackHoriaontal, rbFrontBackVertical);
        QWidget::setTabOrder(rbFrontBackVertical, rbPhaseHoriaontal);
        QWidget::setTabOrder(rbPhaseHoriaontal, rbPhaseVertical);
        QWidget::setTabOrder(rbPhaseVertical, cbNGNailCrossView);
        QWidget::setTabOrder(cbNGNailCrossView, pbOk);
        QWidget::setTabOrder(pbOk, pbCancel);

        retranslateUi(WholeImageForReviewPropertyClass);
        QObject::connect(pbOk, SIGNAL(clicked()), WholeImageForReviewPropertyClass, SLOT(accept()));
        QObject::connect(pbCancel, SIGNAL(clicked()), WholeImageForReviewPropertyClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(WholeImageForReviewPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *WholeImageForReviewPropertyClass)
    {
        WholeImageForReviewPropertyClass->setWindowTitle(QCoreApplication::translate("WholeImageForReviewPropertyClass", "WholeImageForReviewForm", nullptr));
        gbRotation->setTitle(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Image Rotation", nullptr));
        label->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Front", nullptr));
        cbFrontRotation->setItemText(0, QCoreApplication::translate("WholeImageForReviewPropertyClass", "0", nullptr));
        cbFrontRotation->setItemText(1, QCoreApplication::translate("WholeImageForReviewPropertyClass", "90", nullptr));
        cbFrontRotation->setItemText(2, QCoreApplication::translate("WholeImageForReviewPropertyClass", "180", nullptr));
        cbFrontRotation->setItemText(3, QCoreApplication::translate("WholeImageForReviewPropertyClass", "270", nullptr));

        label_3->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "deg", nullptr));
        label_2->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Back", nullptr));
        cbBackRotation->setItemText(0, QCoreApplication::translate("WholeImageForReviewPropertyClass", "0", nullptr));
        cbBackRotation->setItemText(1, QCoreApplication::translate("WholeImageForReviewPropertyClass", "90", nullptr));
        cbBackRotation->setItemText(2, QCoreApplication::translate("WholeImageForReviewPropertyClass", "180", nullptr));
        cbBackRotation->setItemText(3, QCoreApplication::translate("WholeImageForReviewPropertyClass", "270", nullptr));

        label_4->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "deg", nullptr));
        gbFrontBackOrientation->setTitle(QCoreApplication::translate("WholeImageForReviewPropertyClass", "FrontBackOrientation", nullptr));
        rbFrontBackHoriaontal->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Horiaontal", nullptr));
        rbFrontBackVertical->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Vertical", nullptr));
        gbPhaseOrientation->setTitle(QCoreApplication::translate("WholeImageForReviewPropertyClass", "PhaseImageOrientation", nullptr));
        rbPhaseHoriaontal->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Horiaontal", nullptr));
        rbPhaseVertical->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Vertical", nullptr));
        cbNGNailCrossView->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "NGNailCrossView", nullptr));
        cbNGPointView->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "NGPointView", nullptr));
        cbOnlyCurrentNailView->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "OnlyCurrentNailView", nullptr));
        pbOk->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "OK", nullptr));
        pbApply->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Apply", nullptr));
        pbCancel->setText(QCoreApplication::translate("WholeImageForReviewPropertyClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WholeImageForReviewPropertyClass: public Ui_WholeImageForReviewPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHOLEIMAGEFORREVIEWPROPERTYFORM_H
