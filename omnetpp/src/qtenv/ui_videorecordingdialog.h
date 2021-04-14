/********************************************************************************
** Form generated from reading UI file 'videorecordingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEORECORDINGDIALOG_H
#define UI_VIDEORECORDINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VideoRecordingDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *containerFormatGroup;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *mp4;
    QRadioButton *mkv;
    QDialogButtonBox *buttonBox;
    QGroupBox *recordingAreaGroup;
    QVBoxLayout *verticalLayout;
    QRadioButton *window;
    QRadioButton *network;
    QRadioButton *border;
    QRadioButton *padding;
    QLabel *topLabel;
    QLabel *bottomLabel;
    QGroupBox *pixelFormatGroup;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *compatible;
    QRadioButton *sharper;
    QPushButton *copyButton;
    QLabel *middleLabel;
    QLabel *commandLabel;

    void setupUi(QDialog *VideoRecordingDialog)
    {
        if (VideoRecordingDialog->objectName().isEmpty())
            VideoRecordingDialog->setObjectName(QString::fromUtf8("VideoRecordingDialog"));
        gridLayout = new QGridLayout(VideoRecordingDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        containerFormatGroup = new QGroupBox(VideoRecordingDialog);
        containerFormatGroup->setObjectName(QString::fromUtf8("containerFormatGroup"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(containerFormatGroup->sizePolicy().hasHeightForWidth());
        containerFormatGroup->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(containerFormatGroup);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        mp4 = new QRadioButton(containerFormatGroup);
        mp4->setObjectName(QString::fromUtf8("mp4"));
        mp4->setChecked(true);

        verticalLayout_3->addWidget(mp4);

        mkv = new QRadioButton(containerFormatGroup);
        mkv->setObjectName(QString::fromUtf8("mkv"));

        verticalLayout_3->addWidget(mkv);


        gridLayout->addWidget(containerFormatGroup, 6, 0, 1, 1);

        buttonBox = new QDialogButtonBox(VideoRecordingDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 11, 1, 1, 1);

        recordingAreaGroup = new QGroupBox(VideoRecordingDialog);
        recordingAreaGroup->setObjectName(QString::fromUtf8("recordingAreaGroup"));
        sizePolicy.setHeightForWidth(recordingAreaGroup->sizePolicy().hasHeightForWidth());
        recordingAreaGroup->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(recordingAreaGroup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        window = new QRadioButton(recordingAreaGroup);
        window->setObjectName(QString::fromUtf8("window"));
        window->setChecked(true);

        verticalLayout->addWidget(window);

        network = new QRadioButton(recordingAreaGroup);
        network->setObjectName(QString::fromUtf8("network"));

        verticalLayout->addWidget(network);

        border = new QRadioButton(recordingAreaGroup);
        border->setObjectName(QString::fromUtf8("border"));

        verticalLayout->addWidget(border);

        padding = new QRadioButton(recordingAreaGroup);
        padding->setObjectName(QString::fromUtf8("padding"));

        verticalLayout->addWidget(padding);


        gridLayout->addWidget(recordingAreaGroup, 5, 0, 1, 3);

        topLabel = new QLabel(VideoRecordingDialog);
        topLabel->setObjectName(QString::fromUtf8("topLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topLabel->sizePolicy().hasHeightForWidth());
        topLabel->setSizePolicy(sizePolicy1);
        topLabel->setWordWrap(true);

        gridLayout->addWidget(topLabel, 0, 0, 1, 3);

        bottomLabel = new QLabel(VideoRecordingDialog);
        bottomLabel->setObjectName(QString::fromUtf8("bottomLabel"));
        sizePolicy1.setHeightForWidth(bottomLabel->sizePolicy().hasHeightForWidth());
        bottomLabel->setSizePolicy(sizePolicy1);
        bottomLabel->setWordWrap(true);

        gridLayout->addWidget(bottomLabel, 10, 0, 1, 3);

        pixelFormatGroup = new QGroupBox(VideoRecordingDialog);
        pixelFormatGroup->setObjectName(QString::fromUtf8("pixelFormatGroup"));
        sizePolicy.setHeightForWidth(pixelFormatGroup->sizePolicy().hasHeightForWidth());
        pixelFormatGroup->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(pixelFormatGroup);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        compatible = new QRadioButton(pixelFormatGroup);
        compatible->setObjectName(QString::fromUtf8("compatible"));
        compatible->setChecked(true);

        verticalLayout_2->addWidget(compatible);

        sharper = new QRadioButton(pixelFormatGroup);
        sharper->setObjectName(QString::fromUtf8("sharper"));

        verticalLayout_2->addWidget(sharper);


        gridLayout->addWidget(pixelFormatGroup, 6, 1, 1, 1);

        copyButton = new QPushButton(VideoRecordingDialog);
        copyButton->setObjectName(QString::fromUtf8("copyButton"));

        gridLayout->addWidget(copyButton, 9, 0, 1, 2, Qt::AlignRight);

        middleLabel = new QLabel(VideoRecordingDialog);
        middleLabel->setObjectName(QString::fromUtf8("middleLabel"));
        middleLabel->setWordWrap(true);

        gridLayout->addWidget(middleLabel, 7, 0, 1, 2);

        commandLabel = new QLabel(VideoRecordingDialog);
        commandLabel->setObjectName(QString::fromUtf8("commandLabel"));
        sizePolicy.setHeightForWidth(commandLabel->sizePolicy().hasHeightForWidth());
        commandLabel->setSizePolicy(sizePolicy);
        commandLabel->setStyleSheet(QString::fromUtf8("background-color: palette(base);"));
        commandLabel->setFrameShape(QFrame::StyledPanel);
        commandLabel->setWordWrap(true);
        commandLabel->setMargin(6);
        commandLabel->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(commandLabel, 8, 0, 1, 2);


        retranslateUi(VideoRecordingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VideoRecordingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VideoRecordingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VideoRecordingDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoRecordingDialog)
    {
        VideoRecordingDialog->setWindowTitle(QApplication::translate("VideoRecordingDialog", "Video Recording", nullptr));
        containerFormatGroup->setTitle(QApplication::translate("VideoRecordingDialog", "Container Format", nullptr));
        mp4->setText(QApplication::translate("VideoRecordingDialog", "MP4", nullptr));
        mkv->setText(QApplication::translate("VideoRecordingDialog", "MKV", nullptr));
        recordingAreaGroup->setTitle(QApplication::translate("VideoRecordingDialog", "Crop Area", nullptr));
        window->setText(QApplication::translate("VideoRecordingDialog", "Whole main window", nullptr));
        network->setText(QApplication::translate("VideoRecordingDialog", "Network (module) area", nullptr));
        border->setText(QApplication::translate("VideoRecordingDialog", "Network area with border", nullptr));
        padding->setText(QApplication::translate("VideoRecordingDialog", "Network area plus padding", nullptr));
        topLabel->setText(QApplication::translate("VideoRecordingDialog", "Video recording is performed by exporting a series of numbered PNG images of full window screenshots, starting with 'frames/${BASE}0000.png'. Screenshots can be assembled to videos using ffmpeg.", nullptr));
        bottomLabel->setText(QApplication::translate("VideoRecordingDialog", "Before continuing, make sure there is ample disk space available, because the raw frame output can grow quite large.<br/><br/>While recording, the size of the main Qtenv window will be adjusted to have its width and height both divisible by 2, to ensure compatibility with more video codec options.", nullptr));
        pixelFormatGroup->setTitle(QApplication::translate("VideoRecordingDialog", "Pixel Format", nullptr));
        compatible->setText(QApplication::translate("VideoRecordingDialog", "More compatible (yuv420p)", nullptr));
        sharper->setText(QApplication::translate("VideoRecordingDialog", "Sharper image (yuv444p)", nullptr));
        copyButton->setText(QApplication::translate("VideoRecordingDialog", "Copy to clipboard", nullptr));
        middleLabel->setText(QApplication::translate("VideoRecordingDialog", "Command line to encode captured frames into a video file (make sure that ffmpeg and x264 are installed on your system):", nullptr));
        commandLabel->setText(QApplication::translate("VideoRecordingDialog", "<html><head/><body><p><span style=\" font-family:'monospace'; font-weight:600;\">ffmpeg -r FPS -f image2 -i \"frames/CONFIGURATION#RUN_%04d.png\" -filter:v \"crop=WIDTH:HEIGHT:X:Y\" -vcodec libx264 -pix_fmt yuv420p CONFIGURATION#RUN.mp4</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoRecordingDialog: public Ui_VideoRecordingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEORECORDINGDIALOG_H
