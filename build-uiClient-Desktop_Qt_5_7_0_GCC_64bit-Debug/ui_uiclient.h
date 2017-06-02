/********************************************************************************
** Form generated from reading UI file 'uiclient.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UICLIENT_H
#define UI_UICLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiClient
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *DisplayChat;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_message;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UiClient)
    {
        if (UiClient->objectName().isEmpty())
            UiClient->setObjectName(QStringLiteral("UiClient"));
        UiClient->resize(600, 400);
        centralWidget = new QWidget(UiClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 60, 258, 225));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        DisplayChat = new QTextBrowser(layoutWidget);
        DisplayChat->setObjectName(QStringLiteral("DisplayChat"));

        verticalLayout->addWidget(DisplayChat);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_message = new QLineEdit(layoutWidget);
        lineEdit_message->setObjectName(QStringLiteral("lineEdit_message"));

        horizontalLayout_2->addWidget(lineEdit_message);


        verticalLayout->addLayout(horizontalLayout_2);

        UiClient->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(UiClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 20));
        UiClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UiClient);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        UiClient->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(UiClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UiClient->setStatusBar(statusBar);

        retranslateUi(UiClient);

        QMetaObject::connectSlotsByName(UiClient);
    } // setupUi

    void retranslateUi(QMainWindow *UiClient)
    {
        UiClient->setWindowTitle(QApplication::translate("UiClient", "UiClient", 0));
    } // retranslateUi

};

namespace Ui {
    class UiClient: public Ui_UiClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UICLIENT_H
