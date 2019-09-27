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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtSubprocessRunTestClass
{
public:
    QWidget *centralWidget;
    QFormLayout *formLayout;
    QPushButton *pushButton_Start;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_Stop;
    QPushButton *pushButton_clean;
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
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pushButton_Start);

        horizontalSpacer = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(0, QFormLayout::FieldRole, horizontalSpacer);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, textBrowser);

        pushButton_Stop = new QPushButton(centralWidget);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));

        formLayout->setWidget(1, QFormLayout::LabelRole, pushButton_Stop);

        pushButton_clean = new QPushButton(centralWidget);
        pushButton_clean->setObjectName(QString::fromUtf8("pushButton_clean"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton_clean);

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
        pushButton_Start->setText(QApplication::translate("QtSubprocessRunTestClass", "Start", nullptr));
        pushButton_Stop->setText(QApplication::translate("QtSubprocessRunTestClass", "Stop", nullptr));
        pushButton_clean->setText(QApplication::translate("QtSubprocessRunTestClass", "Clean", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtSubprocessRunTestClass: public Ui_QtSubprocessRunTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSUBPROCESSRUNTEST_H
