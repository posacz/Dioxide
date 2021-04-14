/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionOneStep;
    QAction *actionRun;
    QAction *actionSetUpConfiguration;
    QAction *actionStop;
    QAction *actionFastRun;
    QAction *actionExpressRun;
    QAction *actionRunUntil;
    QAction *actionLoadNedFile;
    QAction *actionConcludeSimulation;
    QAction *actionEventlogRecording;
    QAction *actionFindInspectObjects;
    QAction *actionVerticalLayout;
    QAction *actionHorizontalLayout;
    QAction *actionTimeline;
    QAction *actionPreferences;
    QAction *actionSetUpUnconfiguredNetwork;
    QAction *actionOpenPrimaryIniFile;
    QAction *actionCreate_Snapshot;
    QAction *actionDebugNextEvent;
    QAction *actionRebuildNetwork;
    QAction *actionNetwork;
    QAction *actionScheduledEvents;
    QAction *actionSimulation;
    QAction *actionNedComponentTypes;
    QAction *actionRegisteredClasses;
    QAction *actionNED_Functions;
    QAction *actionRegistered_Enums;
    QAction *actionSupportedConfigurationOption;
    QAction *actionInspectByPointer;
    QAction *actionStatusDetails;
    QAction *actionFlipWindowLayout;
    QAction *actionAbout_OMNeT_Qtenv;
    QAction *actionRecordVideo;
    QAction *actionShowAnimationParams;
    QAction *actionDebugOnErrors;
    QAction *actionClassDescriptors;
    QAction *actionResultFilters;
    QAction *actionResultRecorders;
    QAction *actionMessagePrinters;
    QAction *actionDebugNow;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *toolBarArea;
    QHBoxLayout *topStatusRow;
    QLabel *nextEventLabel;
    QLabel *nextModuleLabel;
    QLabel *nextTimeLabel;
    QSplitter *mainSplitter;
    QWidget *timeLine;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QWidget *treeView;
    QWidget *objectInspector;
    QSplitter *splitter_2;
    QWidget *mainArea;
    QWidget *logInspector;
    QHBoxLayout *statusBar;
    QLabel *labelConfigName;
    QLabel *labelMessageStats;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSimulate;
    QMenu *menuInspect;
    QMenu *menuAvailable_Components;
    QMenu *menuView;
    QMenu *menuHelp;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(939, 673);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/logo/logo128m"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        actionOneStep = new QAction(MainWindow);
        actionOneStep->setObjectName(QString::fromUtf8("actionOneStep"));
        actionOneStep->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/tools/step"), QSize(), QIcon::Normal, QIcon::Off);
        actionOneStep->setIcon(icon1);
        actionOneStep->setShortcutContext(Qt::ApplicationShortcut);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        actionRun->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/tools/run"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon2);
        actionRun->setShortcutContext(Qt::ApplicationShortcut);
        actionSetUpConfiguration = new QAction(MainWindow);
        actionSetUpConfiguration->setObjectName(QString::fromUtf8("actionSetUpConfiguration"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/tools/newrun"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetUpConfiguration->setIcon(icon3);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/tools/stop"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon4);
        actionStop->setShortcutContext(Qt::ApplicationShortcut);
        actionFastRun = new QAction(MainWindow);
        actionFastRun->setObjectName(QString::fromUtf8("actionFastRun"));
        actionFastRun->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/tools/fast"), QSize(), QIcon::Normal, QIcon::Off);
        actionFastRun->setIcon(icon5);
        actionFastRun->setShortcutContext(Qt::ApplicationShortcut);
        actionExpressRun = new QAction(MainWindow);
        actionExpressRun->setObjectName(QString::fromUtf8("actionExpressRun"));
        actionExpressRun->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/tools/express"), QSize(), QIcon::Normal, QIcon::Off);
        actionExpressRun->setIcon(icon6);
        actionExpressRun->setShortcutContext(Qt::ApplicationShortcut);
        actionRunUntil = new QAction(MainWindow);
        actionRunUntil->setObjectName(QString::fromUtf8("actionRunUntil"));
        actionRunUntil->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/tools/until"), QSize(), QIcon::Normal, QIcon::Off);
        actionRunUntil->setIcon(icon7);
        actionRunUntil->setShortcutContext(Qt::ApplicationShortcut);
        actionLoadNedFile = new QAction(MainWindow);
        actionLoadNedFile->setObjectName(QString::fromUtf8("actionLoadNedFile"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/tools/loadned"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadNedFile->setIcon(icon8);
        actionConcludeSimulation = new QAction(MainWindow);
        actionConcludeSimulation->setObjectName(QString::fromUtf8("actionConcludeSimulation"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/tools/finish"), QSize(), QIcon::Normal, QIcon::Off);
        actionConcludeSimulation->setIcon(icon9);
        actionEventlogRecording = new QAction(MainWindow);
        actionEventlogRecording->setObjectName(QString::fromUtf8("actionEventlogRecording"));
        actionEventlogRecording->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/tools/recordeventlog"), QSize(), QIcon::Normal, QIcon::Off);
        actionEventlogRecording->setIcon(icon10);
        actionFindInspectObjects = new QAction(MainWindow);
        actionFindInspectObjects->setObjectName(QString::fromUtf8("actionFindInspectObjects"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/tools/findobj"), QSize(), QIcon::Normal, QIcon::Off);
        actionFindInspectObjects->setIcon(icon11);
        actionVerticalLayout = new QAction(MainWindow);
        actionVerticalLayout->setObjectName(QString::fromUtf8("actionVerticalLayout"));
        actionVerticalLayout->setCheckable(true);
        actionVerticalLayout->setChecked(false);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/tools/vertical"), QSize(), QIcon::Normal, QIcon::Off);
        actionVerticalLayout->setIcon(icon12);
        actionHorizontalLayout = new QAction(MainWindow);
        actionHorizontalLayout->setObjectName(QString::fromUtf8("actionHorizontalLayout"));
        actionHorizontalLayout->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/tools/horizontal"), QSize(), QIcon::Normal, QIcon::Off);
        actionHorizontalLayout->setIcon(icon13);
        actionTimeline = new QAction(MainWindow);
        actionTimeline->setObjectName(QString::fromUtf8("actionTimeline"));
        actionTimeline->setCheckable(true);
        actionTimeline->setChecked(false);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/objects/fes"), QSize(), QIcon::Normal, QIcon::Off);
        actionTimeline->setIcon(icon14);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/tools/config"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon15);
        actionSetUpUnconfiguredNetwork = new QAction(MainWindow);
        actionSetUpUnconfiguredNetwork->setObjectName(QString::fromUtf8("actionSetUpUnconfiguredNetwork"));
        actionOpenPrimaryIniFile = new QAction(MainWindow);
        actionOpenPrimaryIniFile->setObjectName(QString::fromUtf8("actionOpenPrimaryIniFile"));
        actionCreate_Snapshot = new QAction(MainWindow);
        actionCreate_Snapshot->setObjectName(QString::fromUtf8("actionCreate_Snapshot"));
        actionDebugNextEvent = new QAction(MainWindow);
        actionDebugNextEvent->setObjectName(QString::fromUtf8("actionDebugNextEvent"));
        actionRebuildNetwork = new QAction(MainWindow);
        actionRebuildNetwork->setObjectName(QString::fromUtf8("actionRebuildNetwork"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/tools/rebuild"), QSize(), QIcon::Normal, QIcon::Off);
        actionRebuildNetwork->setIcon(icon16);
        actionNetwork = new QAction(MainWindow);
        actionNetwork->setObjectName(QString::fromUtf8("actionNetwork"));
        actionScheduledEvents = new QAction(MainWindow);
        actionScheduledEvents->setObjectName(QString::fromUtf8("actionScheduledEvents"));
        actionSimulation = new QAction(MainWindow);
        actionSimulation->setObjectName(QString::fromUtf8("actionSimulation"));
        actionNedComponentTypes = new QAction(MainWindow);
        actionNedComponentTypes->setObjectName(QString::fromUtf8("actionNedComponentTypes"));
        actionRegisteredClasses = new QAction(MainWindow);
        actionRegisteredClasses->setObjectName(QString::fromUtf8("actionRegisteredClasses"));
        actionNED_Functions = new QAction(MainWindow);
        actionNED_Functions->setObjectName(QString::fromUtf8("actionNED_Functions"));
        actionRegistered_Enums = new QAction(MainWindow);
        actionRegistered_Enums->setObjectName(QString::fromUtf8("actionRegistered_Enums"));
        actionSupportedConfigurationOption = new QAction(MainWindow);
        actionSupportedConfigurationOption->setObjectName(QString::fromUtf8("actionSupportedConfigurationOption"));
        actionInspectByPointer = new QAction(MainWindow);
        actionInspectByPointer->setObjectName(QString::fromUtf8("actionInspectByPointer"));
        actionStatusDetails = new QAction(MainWindow);
        actionStatusDetails->setObjectName(QString::fromUtf8("actionStatusDetails"));
        actionStatusDetails->setCheckable(true);
        actionFlipWindowLayout = new QAction(MainWindow);
        actionFlipWindowLayout->setObjectName(QString::fromUtf8("actionFlipWindowLayout"));
        actionAbout_OMNeT_Qtenv = new QAction(MainWindow);
        actionAbout_OMNeT_Qtenv->setObjectName(QString::fromUtf8("actionAbout_OMNeT_Qtenv"));
        actionRecordVideo = new QAction(MainWindow);
        actionRecordVideo->setObjectName(QString::fromUtf8("actionRecordVideo"));
        actionRecordVideo->setCheckable(true);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/tools/recordvideo"), QSize(), QIcon::Normal, QIcon::Off);
        actionRecordVideo->setIcon(icon17);
        actionShowAnimationParams = new QAction(MainWindow);
        actionShowAnimationParams->setObjectName(QString::fromUtf8("actionShowAnimationParams"));
        actionShowAnimationParams->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/tools/props"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowAnimationParams->setIcon(icon18);
        actionDebugOnErrors = new QAction(MainWindow);
        actionDebugOnErrors->setObjectName(QString::fromUtf8("actionDebugOnErrors"));
        actionDebugOnErrors->setCheckable(true);
        actionClassDescriptors = new QAction(MainWindow);
        actionClassDescriptors->setObjectName(QString::fromUtf8("actionClassDescriptors"));
        actionResultFilters = new QAction(MainWindow);
        actionResultFilters->setObjectName(QString::fromUtf8("actionResultFilters"));
        actionResultRecorders = new QAction(MainWindow);
        actionResultRecorders->setObjectName(QString::fromUtf8("actionResultRecorders"));
        actionMessagePrinters = new QAction(MainWindow);
        actionMessagePrinters->setObjectName(QString::fromUtf8("actionMessagePrinters"));
        actionDebugNow = new QAction(MainWindow);
        actionDebugNow->setObjectName(QString::fromUtf8("actionDebugNow"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 6);
        toolBarArea = new QWidget(centralWidget);
        toolBarArea->setObjectName(QString::fromUtf8("toolBarArea"));

        verticalLayout->addWidget(toolBarArea);

        topStatusRow = new QHBoxLayout();
        topStatusRow->setSpacing(1);
        topStatusRow->setObjectName(QString::fromUtf8("topStatusRow"));
        nextEventLabel = new QLabel(centralWidget);
        nextEventLabel->setObjectName(QString::fromUtf8("nextEventLabel"));
        nextEventLabel->setStyleSheet(QString::fromUtf8("QLabel { border: 1px solid palette(mid); }"));
        nextEventLabel->setMargin(1);

        topStatusRow->addWidget(nextEventLabel);

        nextModuleLabel = new QLabel(centralWidget);
        nextModuleLabel->setObjectName(QString::fromUtf8("nextModuleLabel"));
        nextModuleLabel->setStyleSheet(QString::fromUtf8("QLabel { border: 1px solid palette(mid); }"));
        nextModuleLabel->setMargin(1);

        topStatusRow->addWidget(nextModuleLabel);

        nextTimeLabel = new QLabel(centralWidget);
        nextTimeLabel->setObjectName(QString::fromUtf8("nextTimeLabel"));
        nextTimeLabel->setStyleSheet(QString::fromUtf8("QLabel { border: 1px solid palette(mid); }"));
        nextTimeLabel->setMargin(1);

        topStatusRow->addWidget(nextTimeLabel);


        verticalLayout->addLayout(topStatusRow);

        mainSplitter = new QSplitter(centralWidget);
        mainSplitter->setObjectName(QString::fromUtf8("mainSplitter"));
        mainSplitter->setOrientation(Qt::Vertical);
        timeLine = new QWidget(mainSplitter);
        timeLine->setObjectName(QString::fromUtf8("timeLine"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timeLine->sizePolicy().hasHeightForWidth());
        timeLine->setSizePolicy(sizePolicy1);
        mainSplitter->addWidget(timeLine);
        splitter_3 = new QSplitter(mainSplitter);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        sizePolicy.setHeightForWidth(splitter_3->sizePolicy().hasHeightForWidth());
        splitter_3->setSizePolicy(sizePolicy);
        splitter_3->setMinimumSize(QSize(100, 100));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setMinimumSize(QSize(100, 100));
        splitter->setOrientation(Qt::Vertical);
        treeView = new QWidget(splitter);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy2);
        treeView->setMinimumSize(QSize(100, 100));
        treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        splitter->addWidget(treeView);
        objectInspector = new QWidget(splitter);
        objectInspector->setObjectName(QString::fromUtf8("objectInspector"));
        sizePolicy2.setHeightForWidth(objectInspector->sizePolicy().hasHeightForWidth());
        objectInspector->setSizePolicy(sizePolicy2);
        objectInspector->setMinimumSize(QSize(100, 100));
        splitter->addWidget(objectInspector);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setMinimumSize(QSize(100, 100));
        splitter_2->setOrientation(Qt::Vertical);
        mainArea = new QWidget(splitter_2);
        mainArea->setObjectName(QString::fromUtf8("mainArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mainArea->sizePolicy().hasHeightForWidth());
        mainArea->setSizePolicy(sizePolicy3);
        mainArea->setMinimumSize(QSize(100, 100));
        splitter_2->addWidget(mainArea);
        logInspector = new QWidget(splitter_2);
        logInspector->setObjectName(QString::fromUtf8("logInspector"));
        sizePolicy2.setHeightForWidth(logInspector->sizePolicy().hasHeightForWidth());
        logInspector->setSizePolicy(sizePolicy2);
        logInspector->setMinimumSize(QSize(100, 100));
        splitter_2->addWidget(logInspector);
        splitter_3->addWidget(splitter_2);
        mainSplitter->addWidget(splitter_3);

        verticalLayout->addWidget(mainSplitter);

        statusBar = new QHBoxLayout();
        statusBar->setSpacing(1);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        labelConfigName = new QLabel(centralWidget);
        labelConfigName->setObjectName(QString::fromUtf8("labelConfigName"));
        labelConfigName->setStyleSheet(QString::fromUtf8("QLabel { border: 1px solid palette(mid); }"));
        labelConfigName->setMargin(1);

        statusBar->addWidget(labelConfigName);

        labelMessageStats = new QLabel(centralWidget);
        labelMessageStats->setObjectName(QString::fromUtf8("labelMessageStats"));
        labelMessageStats->setStyleSheet(QString::fromUtf8("QLabel { border: 1px solid palette(mid); }"));
        labelMessageStats->setMargin(1);

        statusBar->addWidget(labelMessageStats);


        verticalLayout->addLayout(statusBar);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 939, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSimulate = new QMenu(menuBar);
        menuSimulate->setObjectName(QString::fromUtf8("menuSimulate"));
        menuInspect = new QMenu(menuBar);
        menuInspect->setObjectName(QString::fromUtf8("menuInspect"));
        menuAvailable_Components = new QMenu(menuInspect);
        menuAvailable_Components->setObjectName(QString::fromUtf8("menuAvailable_Components"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setContextMenuPolicy(Qt::NoContextMenu);
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::TopToolBarArea);
        mainToolBar->setIconSize(QSize(30, 19));
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSimulate->menuAction());
        menuBar->addAction(menuInspect->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSetUpConfiguration);
        menuFile->addSeparator();
        menuFile->addAction(actionLoadNedFile);
        menuFile->addAction(actionSetUpUnconfiguredNetwork);
        menuFile->addSeparator();
        menuFile->addAction(actionOpenPrimaryIniFile);
        menuFile->addSeparator();
        menuFile->addAction(actionCreate_Snapshot);
        menuFile->addSeparator();
        menuFile->addAction(actionPreferences);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuSimulate->addAction(actionOneStep);
        menuSimulate->addSeparator();
        menuSimulate->addAction(actionRun);
        menuSimulate->addAction(actionFastRun);
        menuSimulate->addAction(actionExpressRun);
        menuSimulate->addAction(actionRunUntil);
        menuSimulate->addSeparator();
        menuSimulate->addAction(actionDebugNow);
        menuSimulate->addAction(actionDebugNextEvent);
        menuSimulate->addAction(actionDebugOnErrors);
        menuSimulate->addSeparator();
        menuSimulate->addAction(actionStop);
        menuSimulate->addSeparator();
        menuSimulate->addAction(actionEventlogRecording);
        menuSimulate->addAction(actionRecordVideo);
        menuSimulate->addSeparator();
        menuSimulate->addAction(actionConcludeSimulation);
        menuSimulate->addAction(actionRebuildNetwork);
        menuInspect->addAction(actionNetwork);
        menuInspect->addAction(actionScheduledEvents);
        menuInspect->addAction(actionSimulation);
        menuInspect->addSeparator();
        menuInspect->addAction(menuAvailable_Components->menuAction());
        menuInspect->addSeparator();
        menuInspect->addAction(actionFindInspectObjects);
        menuInspect->addAction(actionInspectByPointer);
        menuAvailable_Components->addAction(actionNedComponentTypes);
        menuAvailable_Components->addAction(actionRegisteredClasses);
        menuAvailable_Components->addAction(actionClassDescriptors);
        menuAvailable_Components->addAction(actionNED_Functions);
        menuAvailable_Components->addAction(actionRegistered_Enums);
        menuAvailable_Components->addAction(actionSupportedConfigurationOption);
        menuAvailable_Components->addAction(actionResultFilters);
        menuAvailable_Components->addAction(actionResultRecorders);
        menuAvailable_Components->addAction(actionMessagePrinters);
        menuView->addAction(actionStatusDetails);
        menuView->addAction(actionTimeline);
        menuView->addAction(actionShowAnimationParams);
        menuView->addSeparator();
        menuView->addAction(actionFlipWindowLayout);
        menuView->addSeparator();
        menuHelp->addAction(actionAbout_OMNeT_Qtenv);
        mainToolBar->addAction(actionSetUpConfiguration);
        mainToolBar->addAction(actionLoadNedFile);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOneStep);
        mainToolBar->addAction(actionRun);
        mainToolBar->addAction(actionFastRun);
        mainToolBar->addAction(actionExpressRun);
        mainToolBar->addAction(actionRunUntil);
        mainToolBar->addAction(actionStop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionConcludeSimulation);
        mainToolBar->addAction(actionRebuildNetwork);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionEventlogRecording);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionFindInspectObjects);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionVerticalLayout);
        mainToolBar->addAction(actionHorizontalLayout);
        mainToolBar->addAction(actionTimeline);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPreferences);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionRecordVideo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OMNeT++ Qtenv", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "E&xit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionOneStep->setText(QApplication::translate("MainWindow", "One &Step", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOneStep->setToolTip(QApplication::translate("MainWindow", "Execute one event (F4)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOneStep->setShortcut(QApplication::translate("MainWindow", "F4", nullptr));
#endif // QT_NO_SHORTCUT
        actionRun->setText(QApplication::translate("MainWindow", "&Run", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRun->setToolTip(QApplication::translate("MainWindow", "Run with full animation (F5)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRun->setShortcut(QApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        actionSetUpConfiguration->setText(QApplication::translate("MainWindow", "&Set Up a Configuration...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSetUpConfiguration->setToolTip(QApplication::translate("MainWindow", "Set up an inifile configuration", nullptr));
#endif // QT_NO_TOOLTIP
        actionStop->setText(QApplication::translate("MainWindow", "S&top Execution", nullptr));
#ifndef QT_NO_TOOLTIP
        actionStop->setToolTip(QApplication::translate("MainWindow", "Stop running simulation (F8)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionStop->setShortcut(QApplication::translate("MainWindow", "F8", nullptr));
#endif // QT_NO_SHORTCUT
        actionFastRun->setText(QApplication::translate("MainWindow", "&Fast Run (rare display updates)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFastRun->setToolTip(QApplication::translate("MainWindow", "Run faster: no animation and rare inspector updates (F6)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionFastRun->setShortcut(QApplication::translate("MainWindow", "F6", nullptr));
#endif // QT_NO_SHORTCUT
        actionExpressRun->setText(QApplication::translate("MainWindow", "E&xpress Run (tracing off)", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExpressRun->setToolTip(QApplication::translate("MainWindow", "Run at full speed: no text output, animation or inspector updates (F7)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionExpressRun->setShortcut(QApplication::translate("MainWindow", "F7", nullptr));
#endif // QT_NO_SHORTCUT
        actionRunUntil->setText(QApplication::translate("MainWindow", "Run &Until...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRunUntil->setToolTip(QApplication::translate("MainWindow", "Run until time or event number (Ctrl+F5)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRunUntil->setShortcut(QApplication::translate("MainWindow", "Ctrl+F5", nullptr));
#endif // QT_NO_SHORTCUT
        actionLoadNedFile->setText(QApplication::translate("MainWindow", "&Load NED File...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionLoadNedFile->setToolTip(QApplication::translate("MainWindow", "Load NED file for compound module definitions", nullptr));
#endif // QT_NO_TOOLTIP
        actionConcludeSimulation->setText(QApplication::translate("MainWindow", "&Conclude Simulation", nullptr));
#ifndef QT_NO_TOOLTIP
        actionConcludeSimulation->setToolTip(QApplication::translate("MainWindow", "Conclude simulation", nullptr));
#endif // QT_NO_TOOLTIP
        actionEventlogRecording->setText(QApplication::translate("MainWindow", "&Eventlog Recording", nullptr));
#ifndef QT_NO_TOOLTIP
        actionEventlogRecording->setToolTip(QApplication::translate("MainWindow", "Eventlog recording on/off (Ctrl+G)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionEventlogRecording->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", nullptr));
#endif // QT_NO_SHORTCUT
        actionFindInspectObjects->setText(QApplication::translate("MainWindow", "&Find/Inspect Objects...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFindInspectObjects->setToolTip(QApplication::translate("MainWindow", "Find and inspect modules, messages, queues and other objects (Ctrl+S)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionFindInspectObjects->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionVerticalLayout->setText(QApplication::translate("MainWindow", "Vertical Main Window Layout", nullptr));
#ifndef QT_NO_TOOLTIP
        actionVerticalLayout->setToolTip(QApplication::translate("MainWindow", "Vertical main window layout", nullptr));
#endif // QT_NO_TOOLTIP
        actionHorizontalLayout->setText(QApplication::translate("MainWindow", "Horizontal Main Window Layout", nullptr));
        actionTimeline->setText(QApplication::translate("MainWindow", "&Timeline", nullptr));
#ifndef QT_NO_TOOLTIP
        actionTimeline->setToolTip(QApplication::translate("MainWindow", "Show/hide timeline (Ctrl+T)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionTimeline->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", nullptr));
#endif // QT_NO_SHORTCUT
        actionPreferences->setText(QApplication::translate("MainWindow", "&Preferences...", nullptr));
        actionSetUpUnconfiguredNetwork->setText(QApplication::translate("MainWindow", "Set Up an &Unconfigured Network...", nullptr));
        actionOpenPrimaryIniFile->setText(QApplication::translate("MainWindow", "Open Primary &Ini File", nullptr));
        actionCreate_Snapshot->setText(QApplication::translate("MainWindow", "&Create Snapshot...", nullptr));
        actionDebugNextEvent->setText(QApplication::translate("MainWindow", "&Debug Next Event", nullptr));
#ifndef QT_NO_SHORTCUT
        actionDebugNextEvent->setShortcut(QApplication::translate("MainWindow", "Ctrl+F9", nullptr));
#endif // QT_NO_SHORTCUT
        actionRebuildNetwork->setText(QApplication::translate("MainWindow", "Re&build Network", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRebuildNetwork->setToolTip(QApplication::translate("MainWindow", "Rebuild network", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRebuildNetwork->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+R", nullptr));
#endif // QT_NO_SHORTCUT
        actionNetwork->setText(QApplication::translate("MainWindow", "&Network", nullptr));
        actionScheduledEvents->setText(QApplication::translate("MainWindow", "Scheduled &Events (FES)", nullptr));
        actionSimulation->setText(QApplication::translate("MainWindow", "&Simulation", nullptr));
        actionNedComponentTypes->setText(QApplication::translate("MainWindow", "NED Component &Types", nullptr));
        actionRegisteredClasses->setText(QApplication::translate("MainWindow", "Registered &Classes", nullptr));
        actionNED_Functions->setText(QApplication::translate("MainWindow", "NED &Functions", nullptr));
        actionRegistered_Enums->setText(QApplication::translate("MainWindow", "Registered &Enums", nullptr));
        actionSupportedConfigurationOption->setText(QApplication::translate("MainWindow", "Supported Configuration &Options", nullptr));
        actionInspectByPointer->setText(QApplication::translate("MainWindow", "Inspect by &Pointer...", nullptr));
        actionStatusDetails->setText(QApplication::translate("MainWindow", "&Status Details", nullptr));
#ifndef QT_NO_SHORTCUT
        actionStatusDetails->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        actionFlipWindowLayout->setText(QApplication::translate("MainWindow", "&Flip Window Layout", nullptr));
        actionAbout_OMNeT_Qtenv->setText(QApplication::translate("MainWindow", "&About OMNeT++/Qtenv", nullptr));
        actionRecordVideo->setText(QApplication::translate("MainWindow", "&Video Recording", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRecordVideo->setToolTip(QApplication::translate("MainWindow", "Record Video (Ctrl+M)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRecordVideo->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_NO_SHORTCUT
        actionShowAnimationParams->setText(QApplication::translate("MainWindow", "Animation Parameters", nullptr));
#ifndef QT_NO_TOOLTIP
        actionShowAnimationParams->setToolTip(QApplication::translate("MainWindow", "Show Animation Parameters (Ctrl+N)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionShowAnimationParams->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionDebugOnErrors->setText(QApplication::translate("MainWindow", "Debug On Errors", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDebugOnErrors->setToolTip(QApplication::translate("MainWindow", "Break into the debugger upon runtime errors", nullptr));
#endif // QT_NO_TOOLTIP
        actionClassDescriptors->setText(QApplication::translate("MainWindow", "Class &Descriptors", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClassDescriptors->setToolTip(QApplication::translate("MainWindow", "Class Descriptors", nullptr));
#endif // QT_NO_TOOLTIP
        actionResultFilters->setText(QApplication::translate("MainWindow", "Result Fi&lters", nullptr));
#ifndef QT_NO_TOOLTIP
        actionResultFilters->setToolTip(QApplication::translate("MainWindow", "Result Filters", nullptr));
#endif // QT_NO_TOOLTIP
        actionResultRecorders->setText(QApplication::translate("MainWindow", "Result &Recorders", nullptr));
#ifndef QT_NO_TOOLTIP
        actionResultRecorders->setToolTip(QApplication::translate("MainWindow", "Result Recorders", nullptr));
#endif // QT_NO_TOOLTIP
        actionMessagePrinters->setText(QApplication::translate("MainWindow", "Message &Printers", nullptr));
#ifndef QT_NO_TOOLTIP
        actionMessagePrinters->setToolTip(QApplication::translate("MainWindow", "Message Printers", nullptr));
#endif // QT_NO_TOOLTIP
        actionDebugNow->setText(QApplication::translate("MainWindow", "Debug Now", nullptr));
#ifndef QT_NO_WHATSTHIS
        toolBarArea->setWhatsThis(QApplication::translate("MainWindow", "The mainToolBar will be moved into this widget at runtime, along with a layout containing the animation speed slider and the event labels.", nullptr));
#endif // QT_NO_WHATSTHIS
        nextEventLabel->setText(QApplication::translate("MainWindow", "Next: n/a", nullptr));
        nextModuleLabel->setText(QApplication::translate("MainWindow", "In: n/a", nullptr));
        nextTimeLabel->setText(QApplication::translate("MainWindow", "At: n/a", nullptr));
#ifndef QT_NO_TOOLTIP
        labelConfigName->setToolTip(QApplication::translate("MainWindow", "Current inifile configuration, run number, network name, and potential scheduler information", nullptr));
#endif // QT_NO_TOOLTIP
        labelConfigName->setText(QApplication::translate("MainWindow", "(No network set up)", nullptr));
#ifndef QT_NO_TOOLTIP
        labelMessageStats->setToolTip(QApplication::translate("MainWindow", "Number of events (messages) currently scheduled /\n"
"Number of existing message objects, including scheduled ones /\n"
"Total number of messages created since start of the simulation", nullptr));
#endif // QT_NO_TOOLTIP
        labelMessageStats->setText(QApplication::translate("MainWindow", "Msg stats: 0 scheduled / 0 existing / 0 created", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        menuSimulate->setTitle(QApplication::translate("MainWindow", "&Simulate", nullptr));
        menuInspect->setTitle(QApplication::translate("MainWindow", "&Inspect", nullptr));
        menuAvailable_Components->setTitle(QApplication::translate("MainWindow", "Available &Components", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "Qtenv toolbar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
