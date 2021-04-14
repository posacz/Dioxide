/********************************************************************************
** Form generated from reading UI file 'animationcontrollerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONCONTROLLERDIALOG_H
#define UI_ANIMATIONCONTROLLERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "exponentialspinbox.h"

QT_BEGIN_NAMESPACE

class Ui_AnimationControllerDialog
{
public:
    QVBoxLayout *mainLayout;
    QGroupBox *controlGroupBox;
    QGridLayout *gridLayout_2;
    omnetpp::qtenv::ExponentialSpinBox *minSpeedSpinBox;
    QLabel *minSpeedLabel;
    QComboBox *profileComboBox;
    QLabel *playbackSpeedLabel;
    QLabel *maxSpeedLabel;
    omnetpp::qtenv::ExponentialSpinBox *playbackSpeedSpinBox;
    omnetpp::qtenv::ExponentialSpinBox *maxSpeedSpinBox;
    QLabel *profileLabel;
    QLabel *noteLabel;
    QGroupBox *readingsGroupBox;
    QGridLayout *gridLayout;
    QLabel *refreshDisplayCountValueLabel;
    QLabel *animationTimeValueLabel;
    QLabel *animationSpeedValueLabel;
    QLabel *animationSpeedLabel;
    QLabel *simulationSpeedLabel;
    QLabel *refreshDisplayCountLabel;
    QLabel *currentFpsLabel;
    QLabel *currentFpsValueLabel;
    QLabel *simulationSpeedValueLabel;
    QLabel *animationTimeLabel;
    QLabel *holdTimeLabel;
    QLabel *holdTimeValueLabel;
    QSpacerItem *bottomVerticalSpacer;

    void setupUi(QDialog *AnimationControllerDialog)
    {
        if (AnimationControllerDialog->objectName().isEmpty())
            AnimationControllerDialog->setObjectName(QString::fromUtf8("AnimationControllerDialog"));
        AnimationControllerDialog->resize(413, 411);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AnimationControllerDialog->sizePolicy().hasHeightForWidth());
        AnimationControllerDialog->setSizePolicy(sizePolicy);
        mainLayout = new QVBoxLayout(AnimationControllerDialog);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(6, 6, 6, 6);
        controlGroupBox = new QGroupBox(AnimationControllerDialog);
        controlGroupBox->setObjectName(QString::fromUtf8("controlGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(controlGroupBox->sizePolicy().hasHeightForWidth());
        controlGroupBox->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(controlGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        minSpeedSpinBox = new omnetpp::qtenv::ExponentialSpinBox(controlGroupBox);
        minSpeedSpinBox->setObjectName(QString::fromUtf8("minSpeedSpinBox"));
        minSpeedSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        minSpeedSpinBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        minSpeedSpinBox->setKeyboardTracking(false);
        minSpeedSpinBox->setMaximum(1000000000000000000.000000000000000);

        gridLayout_2->addWidget(minSpeedSpinBox, 2, 1, 1, 1);

        minSpeedLabel = new QLabel(controlGroupBox);
        minSpeedLabel->setObjectName(QString::fromUtf8("minSpeedLabel"));

        gridLayout_2->addWidget(minSpeedLabel, 2, 0, 1, 1);

        profileComboBox = new QComboBox(controlGroupBox);
        profileComboBox->setObjectName(QString::fromUtf8("profileComboBox"));
        sizePolicy.setHeightForWidth(profileComboBox->sizePolicy().hasHeightForWidth());
        profileComboBox->setSizePolicy(sizePolicy);
        profileComboBox->setMinimumSize(QSize(150, 0));

        gridLayout_2->addWidget(profileComboBox, 0, 1, 1, 1);

        playbackSpeedLabel = new QLabel(controlGroupBox);
        playbackSpeedLabel->setObjectName(QString::fromUtf8("playbackSpeedLabel"));

        gridLayout_2->addWidget(playbackSpeedLabel, 1, 0, 1, 1);

        maxSpeedLabel = new QLabel(controlGroupBox);
        maxSpeedLabel->setObjectName(QString::fromUtf8("maxSpeedLabel"));

        gridLayout_2->addWidget(maxSpeedLabel, 3, 0, 1, 1);

        playbackSpeedSpinBox = new omnetpp::qtenv::ExponentialSpinBox(controlGroupBox);
        playbackSpeedSpinBox->setObjectName(QString::fromUtf8("playbackSpeedSpinBox"));
        playbackSpeedSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        playbackSpeedSpinBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        playbackSpeedSpinBox->setKeyboardTracking(false);
        playbackSpeedSpinBox->setMaximum(1000000000000000000.000000000000000);

        gridLayout_2->addWidget(playbackSpeedSpinBox, 1, 1, 1, 1);

        maxSpeedSpinBox = new omnetpp::qtenv::ExponentialSpinBox(controlGroupBox);
        maxSpeedSpinBox->setObjectName(QString::fromUtf8("maxSpeedSpinBox"));
        maxSpeedSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        maxSpeedSpinBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        maxSpeedSpinBox->setKeyboardTracking(false);
        maxSpeedSpinBox->setMaximum(1000000000000000000.000000000000000);

        gridLayout_2->addWidget(maxSpeedSpinBox, 3, 1, 1, 1);

        profileLabel = new QLabel(controlGroupBox);
        profileLabel->setObjectName(QString::fromUtf8("profileLabel"));

        gridLayout_2->addWidget(profileLabel, 0, 0, 1, 1);

        noteLabel = new QLabel(controlGroupBox);
        noteLabel->setObjectName(QString::fromUtf8("noteLabel"));
        sizePolicy1.setHeightForWidth(noteLabel->sizePolicy().hasHeightForWidth());
        noteLabel->setSizePolicy(sizePolicy1);
        noteLabel->setWordWrap(true);

        gridLayout_2->addWidget(noteLabel, 4, 0, 1, 2);

        gridLayout_2->setColumnStretch(0, 3);
        gridLayout_2->setColumnStretch(1, 2);

        mainLayout->addWidget(controlGroupBox);

        readingsGroupBox = new QGroupBox(AnimationControllerDialog);
        readingsGroupBox->setObjectName(QString::fromUtf8("readingsGroupBox"));
        gridLayout = new QGridLayout(readingsGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        refreshDisplayCountValueLabel = new QLabel(readingsGroupBox);
        refreshDisplayCountValueLabel->setObjectName(QString::fromUtf8("refreshDisplayCountValueLabel"));
        refreshDisplayCountValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(refreshDisplayCountValueLabel, 6, 1, 1, 1);

        animationTimeValueLabel = new QLabel(readingsGroupBox);
        animationTimeValueLabel->setObjectName(QString::fromUtf8("animationTimeValueLabel"));
        animationTimeValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(animationTimeValueLabel, 0, 1, 1, 1);

        animationSpeedValueLabel = new QLabel(readingsGroupBox);
        animationSpeedValueLabel->setObjectName(QString::fromUtf8("animationSpeedValueLabel"));
        animationSpeedValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(animationSpeedValueLabel, 2, 1, 1, 1);

        animationSpeedLabel = new QLabel(readingsGroupBox);
        animationSpeedLabel->setObjectName(QString::fromUtf8("animationSpeedLabel"));

        gridLayout->addWidget(animationSpeedLabel, 2, 0, 1, 1);

        simulationSpeedLabel = new QLabel(readingsGroupBox);
        simulationSpeedLabel->setObjectName(QString::fromUtf8("simulationSpeedLabel"));

        gridLayout->addWidget(simulationSpeedLabel, 3, 0, 1, 1);

        refreshDisplayCountLabel = new QLabel(readingsGroupBox);
        refreshDisplayCountLabel->setObjectName(QString::fromUtf8("refreshDisplayCountLabel"));

        gridLayout->addWidget(refreshDisplayCountLabel, 6, 0, 1, 1);

        currentFpsLabel = new QLabel(readingsGroupBox);
        currentFpsLabel->setObjectName(QString::fromUtf8("currentFpsLabel"));

        gridLayout->addWidget(currentFpsLabel, 7, 0, 1, 1);

        currentFpsValueLabel = new QLabel(readingsGroupBox);
        currentFpsValueLabel->setObjectName(QString::fromUtf8("currentFpsValueLabel"));
        sizePolicy1.setHeightForWidth(currentFpsValueLabel->sizePolicy().hasHeightForWidth());
        currentFpsValueLabel->setSizePolicy(sizePolicy1);
        currentFpsValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentFpsValueLabel, 7, 1, 1, 1);

        simulationSpeedValueLabel = new QLabel(readingsGroupBox);
        simulationSpeedValueLabel->setObjectName(QString::fromUtf8("simulationSpeedValueLabel"));
        simulationSpeedValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(simulationSpeedValueLabel, 3, 1, 1, 1);

        animationTimeLabel = new QLabel(readingsGroupBox);
        animationTimeLabel->setObjectName(QString::fromUtf8("animationTimeLabel"));

        gridLayout->addWidget(animationTimeLabel, 0, 0, 1, 1);

        holdTimeLabel = new QLabel(readingsGroupBox);
        holdTimeLabel->setObjectName(QString::fromUtf8("holdTimeLabel"));

        gridLayout->addWidget(holdTimeLabel, 1, 0, 1, 1);

        holdTimeValueLabel = new QLabel(readingsGroupBox);
        holdTimeValueLabel->setObjectName(QString::fromUtf8("holdTimeValueLabel"));
        holdTimeValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(holdTimeValueLabel, 1, 1, 1, 1);

        gridLayout->setColumnStretch(0, 3);

        mainLayout->addWidget(readingsGroupBox);

        bottomVerticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mainLayout->addItem(bottomVerticalSpacer);

        mainLayout->setStretch(2, 1);
        QWidget::setTabOrder(profileComboBox, playbackSpeedSpinBox);
        QWidget::setTabOrder(playbackSpeedSpinBox, minSpeedSpinBox);
        QWidget::setTabOrder(minSpeedSpinBox, maxSpeedSpinBox);

        retranslateUi(AnimationControllerDialog);

        QMetaObject::connectSlotsByName(AnimationControllerDialog);
    } // setupUi

    void retranslateUi(QDialog *AnimationControllerDialog)
    {
        AnimationControllerDialog->setWindowTitle(QApplication::translate("AnimationControllerDialog", "Animation Parameters", nullptr));
        controlGroupBox->setTitle(QApplication::translate("AnimationControllerDialog", "Control", nullptr));
#ifndef QT_NO_TOOLTIP
        minSpeedSpinBox->setToolTip(QApplication::translate("AnimationControllerDialog", "Enforce minimum animation speed: overrides speed requested by the model.", nullptr));
#endif // QT_NO_TOOLTIP
        minSpeedSpinBox->setSpecialValueText(QApplication::translate("AnimationControllerDialog", "none", nullptr));
        minSpeedLabel->setText(QApplication::translate("AnimationControllerDialog", "Min animation speed:", nullptr));
        playbackSpeedLabel->setText(QApplication::translate("AnimationControllerDialog", "Playback speed:", nullptr));
        maxSpeedLabel->setText(QApplication::translate("AnimationControllerDialog", "Max animation speed:", nullptr));
#ifndef QT_NO_TOOLTIP
        playbackSpeedSpinBox->setToolTip(QApplication::translate("AnimationControllerDialog", "Corresponds to speed slider on the toolbar.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        maxSpeedSpinBox->setToolTip(QApplication::translate("AnimationControllerDialog", "Enforce maximum animation speed: overrides speed requested by the model.", nullptr));
#endif // QT_NO_TOOLTIP
        maxSpeedSpinBox->setSpecialValueText(QApplication::translate("AnimationControllerDialog", "none", nullptr));
        profileLabel->setText(QApplication::translate("AnimationControllerDialog", "Profile:", nullptr));
        noteLabel->setText(QApplication::translate("AnimationControllerDialog", "Note: Animation speed maps simulation time to animation time. Playback speed maps animation time to real time.", nullptr));
        readingsGroupBox->setTitle(QApplication::translate("AnimationControllerDialog", "Current Readings", nullptr));
        refreshDisplayCountValueLabel->setText(QString());
        animationTimeValueLabel->setText(QString());
        animationSpeedValueLabel->setText(QString());
        animationSpeedLabel->setText(QApplication::translate("AnimationControllerDialog", "Animation speed:", nullptr));
        simulationSpeedLabel->setText(QApplication::translate("AnimationControllerDialog", "Simulation speed:", nullptr));
        refreshDisplayCountLabel->setText(QApplication::translate("AnimationControllerDialog", "Num. refreshDisplay() calls:", nullptr));
        currentFpsLabel->setText(QApplication::translate("AnimationControllerDialog", "Frames per sec:", nullptr));
        currentFpsValueLabel->setText(QString());
        simulationSpeedValueLabel->setText(QString());
        animationTimeLabel->setText(QApplication::translate("AnimationControllerDialog", "Animation time:", nullptr));
        holdTimeLabel->setText(QApplication::translate("AnimationControllerDialog", "Hold time:", nullptr));
        holdTimeValueLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AnimationControllerDialog: public Ui_AnimationControllerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONCONTROLLERDIALOG_H
