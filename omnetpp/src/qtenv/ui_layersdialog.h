/********************************************************************************
** Form generated from reading UI file 'layersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYERSDIALOG_H
#define UI_LAYERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayersDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *intro;
    QGridLayout *gridLayout;
    QScrollArea *hideFigScrollArea;
    QWidget *hideFigWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *showFigures;
    QLabel *hideFigures;
    QScrollArea *showFigScrollArea;
    QWidget *showFigWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *note;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LayersDialog)
    {
        if (LayersDialog->objectName().isEmpty())
            LayersDialog->setObjectName(QString::fromUtf8("LayersDialog"));
        LayersDialog->resize(491, 366);
        verticalLayout = new QVBoxLayout(LayersDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        intro = new QLabel(LayersDialog);
        intro->setObjectName(QString::fromUtf8("intro"));
        intro->setWordWrap(true);

        verticalLayout->addWidget(intro);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hideFigScrollArea = new QScrollArea(LayersDialog);
        hideFigScrollArea->setObjectName(QString::fromUtf8("hideFigScrollArea"));
        hideFigScrollArea->setWidgetResizable(true);
        hideFigScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        hideFigWidget = new QWidget();
        hideFigWidget->setObjectName(QString::fromUtf8("hideFigWidget"));
        hideFigWidget->setGeometry(QRect(0, 0, 218, 225));
        verticalLayout_4 = new QVBoxLayout(hideFigWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        hideFigScrollArea->setWidget(hideFigWidget);

        gridLayout->addWidget(hideFigScrollArea, 1, 1, 1, 1);

        showFigures = new QLabel(LayersDialog);
        showFigures->setObjectName(QString::fromUtf8("showFigures"));

        gridLayout->addWidget(showFigures, 0, 0, 1, 1);

        hideFigures = new QLabel(LayersDialog);
        hideFigures->setObjectName(QString::fromUtf8("hideFigures"));

        gridLayout->addWidget(hideFigures, 0, 1, 1, 1);

        showFigScrollArea = new QScrollArea(LayersDialog);
        showFigScrollArea->setObjectName(QString::fromUtf8("showFigScrollArea"));
        showFigScrollArea->setWidgetResizable(true);
        showFigScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        showFigWidget = new QWidget();
        showFigWidget->setObjectName(QString::fromUtf8("showFigWidget"));
        showFigWidget->setGeometry(QRect(0, 0, 243, 225));
        verticalLayout_3 = new QVBoxLayout(showFigWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        showFigScrollArea->setWidget(showFigWidget);

        gridLayout->addWidget(showFigScrollArea, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        note = new QLabel(LayersDialog);
        note->setObjectName(QString::fromUtf8("note"));

        verticalLayout->addWidget(note);

        buttonBox = new QDialogButtonBox(LayersDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LayersDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LayersDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LayersDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LayersDialog);
    } // setupUi

    void retranslateUi(QDialog *LayersDialog)
    {
        LayersDialog->setWindowTitle(QApplication::translate("LayersDialog", "Select Layers", nullptr));
        intro->setText(QApplication::translate("LayersDialog", "Select which figures to display, based on the list of tags each figure contains.", nullptr));
        showFigures->setText(QApplication::translate("LayersDialog", "Show figures having any of the tags:", nullptr));
        hideFigures->setText(QApplication::translate("LayersDialog", "But hide those that also contain:", nullptr));
        note->setText(QApplication::translate("LayersDialog", "Note: Untagged figures are always shown.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LayersDialog: public Ui_LayersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERSDIALOG_H
