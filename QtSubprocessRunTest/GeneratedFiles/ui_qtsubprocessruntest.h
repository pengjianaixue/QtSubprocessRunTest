/********************************************************************************
** Form generated from reading UI file 'qtsubprocessruntest.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSUBPROCESSRUNTEST_H
#define UI_QTSUBPROCESSRUNTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtSubprocessRunTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_Stop;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_clean;
    QPushButton *pushButton_resume;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtSubprocessRunTestClass)
    {
        if (QtSubprocessRunTestClass->objectName().isEmpty())
            QtSubprocessRunTestClass->setObjectName(QString::fromUtf8("QtSubprocessRunTestClass"));
        QtSubprocessRunTestClass->resize(600, 400);
        centralWidget = new QWidget(QtSubprocessRunTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_Stop = new QPushButton(centralWidget);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));

        gridLayout->addWidget(pushButton_Stop, 2, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 4, 0, 1, 2);

        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));

        gridLayout->addWidget(pushButton_Start, 1, 0, 1, 1);

        pushButton_pause = new QPushButton(centralWidget);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));

        gridLayout->addWidget(pushButton_pause, 1, 1, 1, 1);

        pushButton_clean = new QPushButton(centralWidget);
        pushButton_clean->setObjectName(QString::fromUtf8("pushButton_clean"));

        gridLayout->addWidget(pushButton_clean, 3, 1, 1, 1);

        pushButton_resume = new QPushButton(centralWidget);
        pushButton_resume->setObjectName(QString::fromUtf8("pushButton_resume"));

        gridLayout->addWidget(pushButton_resume, 2, 1, 1, 1);

        QtSubprocessRunTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtSubprocessRunTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        QtSubprocessRunTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtSubprocessRunTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtSubprocessRunTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtSubprocessRunTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtSubprocessRunTestClass->setStatusBar(statusBar);

        retranslateUi(QtSubprocessRunTestClass);

        QMetaObject::connectSlotsByName(QtSubprocessRunTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtSubprocessRunTestClass)
    {
        QtSubprocessRunTestClass->setWindowTitle(QApplication::translate("QtSubprocessRunTestClass", "QtSubprocessRunTest", nullptr));
        pushButton_Stop->setText(QApplication::translate("QtSubprocessRunTestClass", "Stop", nullptr));
        pushButton_Start->setText(QApplication::translate("QtSubprocessRunTestClass", "Start", nullptr));
        pushButton_pause->setText(QApplication::translate("QtSubprocessRunTestClass", "pause", nullptr));
        pushButton_clean->setText(QApplication::translate("QtSubprocessRunTestClass", "Clean", nullptr));
        pushButton_resume->setText(QApplication::translate("QtSubprocessRunTestClass", "resume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtSubprocessRunTestClass: public Ui_QtSubprocessRunTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSUBPROCESSRUNTEST_H
