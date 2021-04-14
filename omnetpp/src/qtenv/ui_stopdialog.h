/********************************************************************************
** Form generated from reading UI file 'stopdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOPDIALOG_H
#define UI_STOPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StopDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *stopButton;
    QCheckBox *checkBox;
    QPushButton *updateButton;

    void setupUi(QDialog *StopDialog)
    {
        if (StopDialog->objectName().isEmpty())
            StopDialog->setObjectName(QString::fromUtf8("StopDialog"));
        StopDialog->resize(206, 152);
        verticalLayout = new QVBoxLayout(StopDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stopButton = new QPushButton(StopDialog);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);
        stopButton->setMinimumSize(QSize(188, 73));
        stopButton->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 48, 48); font-size: 20pt; font-weight: bold;"));

        verticalLayout->addWidget(stopButton);

        checkBox = new QCheckBox(StopDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        updateButton = new QPushButton(StopDialog);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(updateButton->sizePolicy().hasHeightForWidth());
        updateButton->setSizePolicy(sizePolicy1);
        updateButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(updateButton);


        retranslateUi(StopDialog);
        QObject::connect(stopButton, SIGNAL(clicked()), StopDialog, SLOT(onClickStop()));
        QObject::connect(updateButton, SIGNAL(clicked()), StopDialog, SLOT(onClickUpdate()));
        QObject::connect(checkBox, SIGNAL(stateChanged(int)), StopDialog, SLOT(applyAutoupdate()));

        QMetaObject::connectSlotsByName(StopDialog);
    } // setupUi

    void retranslateUi(QDialog *StopDialog)
    {
        StopDialog->setWindowTitle(QApplication::translate("StopDialog", "Running...", nullptr));
        stopButton->setText(QApplication::translate("StopDialog", "STOP!", nullptr));
        checkBox->setText(QApplication::translate("StopDialog", "auto-update inspectors", nullptr));
        updateButton->setText(QApplication::translate("StopDialog", "Update now", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StopDialog: public Ui_StopDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOPDIALOG_H
