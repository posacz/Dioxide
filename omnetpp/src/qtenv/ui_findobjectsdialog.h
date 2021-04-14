/********************************************************************************
** Form generated from reading UI file 'findobjectsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDOBJECTSDIALOG_H
#define UI_FINDOBJECTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindObjectsDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *searchLabel;
    QLineEdit *searchEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *comboLabel;
    QLabel *fullPathLabel;
    QLineEdit *fullPathEdit;
    QComboBox *comboBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QCheckBox *modulesCheckBox;
    QCheckBox *messagesCheckBox;
    QCheckBox *queuesCheckBox;
    QCheckBox *paramsCheckBox;
    QCheckBox *statisticsCheckBox;
    QCheckBox *gatesCheckBox;
    QCheckBox *watchesCheckBox;
    QCheckBox *otherCheckBox;
    QCheckBox *figuresCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *refresh;
    QWidget *listViewArea;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FindObjectsDialog)
    {
        if (FindObjectsDialog->objectName().isEmpty())
            FindObjectsDialog->setObjectName(QString::fromUtf8("FindObjectsDialog"));
        FindObjectsDialog->resize(757, 497);
        verticalLayout_2 = new QVBoxLayout(FindObjectsDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchLabel = new QLabel(FindObjectsDialog);
        searchLabel->setObjectName(QString::fromUtf8("searchLabel"));

        horizontalLayout->addWidget(searchLabel);

        searchEdit = new QLineEdit(FindObjectsDialog);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));

        horizontalLayout->addWidget(searchEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(FindObjectsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboLabel = new QLabel(groupBox);
        comboLabel->setObjectName(QString::fromUtf8("comboLabel"));

        gridLayout->addWidget(comboLabel, 0, 0, 1, 1);

        fullPathLabel = new QLabel(groupBox);
        fullPathLabel->setObjectName(QString::fromUtf8("fullPathLabel"));

        gridLayout->addWidget(fullPathLabel, 0, 1, 1, 1);

        fullPathEdit = new QLineEdit(groupBox);
        fullPathEdit->setObjectName(QString::fromUtf8("fullPathEdit"));

        gridLayout->addWidget(fullPathEdit, 1, 1, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(true);

        gridLayout->addWidget(comboBox, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(FindObjectsDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        modulesCheckBox = new QCheckBox(groupBox_2);
        modulesCheckBox->setObjectName(QString::fromUtf8("modulesCheckBox"));

        gridLayout_3->addWidget(modulesCheckBox, 0, 0, 1, 1);

        messagesCheckBox = new QCheckBox(groupBox_2);
        messagesCheckBox->setObjectName(QString::fromUtf8("messagesCheckBox"));

        gridLayout_3->addWidget(messagesCheckBox, 1, 0, 1, 1);

        queuesCheckBox = new QCheckBox(groupBox_2);
        queuesCheckBox->setObjectName(QString::fromUtf8("queuesCheckBox"));

        gridLayout_3->addWidget(queuesCheckBox, 0, 2, 1, 1);

        paramsCheckBox = new QCheckBox(groupBox_2);
        paramsCheckBox->setObjectName(QString::fromUtf8("paramsCheckBox"));

        gridLayout_3->addWidget(paramsCheckBox, 0, 1, 1, 1);

        statisticsCheckBox = new QCheckBox(groupBox_2);
        statisticsCheckBox->setObjectName(QString::fromUtf8("statisticsCheckBox"));

        gridLayout_3->addWidget(statisticsCheckBox, 0, 3, 1, 1);

        gatesCheckBox = new QCheckBox(groupBox_2);
        gatesCheckBox->setObjectName(QString::fromUtf8("gatesCheckBox"));

        gridLayout_3->addWidget(gatesCheckBox, 1, 1, 1, 1);

        watchesCheckBox = new QCheckBox(groupBox_2);
        watchesCheckBox->setObjectName(QString::fromUtf8("watchesCheckBox"));

        gridLayout_3->addWidget(watchesCheckBox, 1, 2, 1, 1);

        otherCheckBox = new QCheckBox(groupBox_2);
        otherCheckBox->setObjectName(QString::fromUtf8("otherCheckBox"));

        gridLayout_3->addWidget(otherCheckBox, 0, 4, 1, 1);

        figuresCheckBox = new QCheckBox(groupBox_2);
        figuresCheckBox->setObjectName(QString::fromUtf8("figuresCheckBox"));

        gridLayout_3->addWidget(figuresCheckBox, 1, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(FindObjectsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);

        refresh = new QPushButton(FindObjectsDialog);
        refresh->setObjectName(QString::fromUtf8("refresh"));
        refresh->setEnabled(true);
        refresh->setAutoDefault(true);

        horizontalLayout_2->addWidget(refresh);


        verticalLayout_2->addLayout(horizontalLayout_2);

        listViewArea = new QWidget(FindObjectsDialog);
        listViewArea->setObjectName(QString::fromUtf8("listViewArea"));

        verticalLayout_2->addWidget(listViewArea);

        buttonBox = new QDialogButtonBox(FindObjectsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setFocusPolicy(Qt::TabFocus);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(FindObjectsDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), FindObjectsDialog, SLOT(accept()));

        refresh->setDefault(true);


        QMetaObject::connectSlotsByName(FindObjectsDialog);
    } // setupUi

    void retranslateUi(QDialog *FindObjectsDialog)
    {
        FindObjectsDialog->setWindowTitle(QApplication::translate("FindObjectsDialog", "Find Objects", nullptr));
        searchLabel->setText(QApplication::translate("FindObjectsDialog", "Search inside:", nullptr));
        groupBox->setTitle(QApplication::translate("FindObjectsDialog", "Search by class and object name:", nullptr));
#ifndef QT_NO_TOOLTIP
        comboLabel->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        comboLabel->setText(QApplication::translate("FindObjectsDialog", "Class filter expression:", nullptr));
        fullPathLabel->setText(QApplication::translate("FindObjectsDialog", "Object full path filter, e.g. \"*.queue AND not length(0)\":", nullptr));
#ifndef QT_NO_TOOLTIP
        fullPathEdit->setToolTip(QApplication::translate("FindObjectsDialog", "Generic filter expression which matches the object full path by default.\n"
"\n"
"Wildcards (\"?\", \"*\") are allowed. \"{a-exz}\" matches any character in the\n"
"range \"a\"..\"e\", plus \"x\" and \"z\". You can match numbers: \"*.job{128..191}\"\n"
"will match objects named \"job128\", \"job129\", ..., \"job191\". \"job{128..}\"\n"
"and \"job{..191}\" are also understood. You can combine patterns with AND, OR\n"
"and NOT and parentheses (lowercase and, or, not are also OK). You can match\n"
"against other object fields such as queue length, message kind, etc., with\n"
"the syntax \"fieldname(pattern)\". Put quotation marks around a pattern if it\n"
"contains parentheses.\n"
"\n"
"HINT: You'll want to start the pattern with \"*.\" in most cases, to match\n"
"objects anywhere in the network!\n"
"\n"
"Examples:\n"
" *.destAddr\n"
"            matches all objects whose name is \"destAddr\" (likely module\n"
"            parameters)\n"
" *.subnet2.*.destAddr\n"
"            matches objects named \"destAddr\" in"
                        "side \"subnet2\"\n"
" *.node[8..10].*\n"
"            matches anything inside module node[8], node[9] and node[10]\n"
" className(cQueue) and not length(0)\n"
"            matches non-empty queue objects\n"
" className(cQueue) and length({10..})\n"
"            matches queue objects with length>=10\n"
" kind(3) or kind({7..9})\n"
"            matches messages with message kind equal to 3, 7, 8 or 9\n"
"            (Only messages have a \"kind\" attribute.)\n"
" className(IP*) and *.data-*\n"
"            matches objects whose class name begins with \"IP\" and\n"
"            name begins with \"data-\"\n"
" not className(cMessage) and byteLength({1500..})\n"
"            matches messages whose class is not cMessage, and byteLength is\n"
"            at least 1500. (Only messages have a \"byteLength\" attribute.)\n"
" \"*(*\" or \"*.msg(ACK)\"\n"
"            quotation marks needed when pattern is a reserved word or contains\n"
"            parentheses. (Note: *.msg(ACK) without parens would be interpreted\n"
" "
                        "           as some object having a \"*.msg\" attribute with the value \"ACK\"!)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        comboBox->setToolTip(QApplication::translate("FindObjectsDialog", "Generic filter expression which matches class name by default.\n"
"\n"
"Wildcards (\"?\", \"*\"), AND, OR, NOT and field matchers are accepted;\n"
"see Object Filter help for a more complete list.\n"
"\n"
"Examples:\n"
"  cQueue\n"
"            matches cQueue objects\n"
"  TCP* or (IP* and not IPDatagram)\n"
"            matches objects whose class name begins with TCP or IP,\n"
"            excluding IPDatagrams\n"
"  cMessage and kind(3)\n"
"            matches objects of class cMessage and message kind 3.", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("FindObjectsDialog", "Object categories:", nullptr));
        modulesCheckBox->setText(QApplication::translate("FindObjectsDialog", "Modules", nullptr));
        messagesCheckBox->setText(QApplication::translate("FindObjectsDialog", "Messages", nullptr));
        queuesCheckBox->setText(QApplication::translate("FindObjectsDialog", "Queues", nullptr));
        paramsCheckBox->setText(QApplication::translate("FindObjectsDialog", "Parameters", nullptr));
        statisticsCheckBox->setText(QApplication::translate("FindObjectsDialog", "Statistics", nullptr));
        gatesCheckBox->setText(QApplication::translate("FindObjectsDialog", "Gates, channels", nullptr));
        watchesCheckBox->setText(QApplication::translate("FindObjectsDialog", "Watches, FSMs", nullptr));
        otherCheckBox->setText(QApplication::translate("FindObjectsDialog", "Other", nullptr));
        figuresCheckBox->setText(QApplication::translate("FindObjectsDialog", "Canvases, figures", nullptr));
        label->setText(QApplication::translate("FindObjectsDialog", "Press Refresh to execute search", nullptr));
        refresh->setText(QApplication::translate("FindObjectsDialog", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindObjectsDialog: public Ui_FindObjectsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDOBJECTSDIALOG_H
