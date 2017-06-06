#include "uiclient.hpp"
#include "ui_uiclient.h"
#include <functional>
#include <QInputDialog>
#include <iostream>
#include <QTextBlock>
#include <QTextCursor>
#include <QMetaType>
#include <QScrollBar>

using std::placeholders::_1;

UiClient::UiClient(Client &client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiClient),
    c(client)
{
    ui->setupUi(this);
    qRegisterMetaType<QTextBlock>("QTextBlock");
    qRegisterMetaType<QTextCursor>("QTextCursor");
    bool ok = false;
    QString username = "";
    while(!ok || username.isEmpty()){
        username = QInputDialog::getText(this, "MeowChat",
                                                "Enter your username", QLineEdit::Normal,
                                                "", &ok);

    }
    c.pseudo = username.toUtf8().constData();
    ui->statusBar->showMessage(username);
    std::function<void(std::string)> func= std::bind( &UiClient::display_new_msg, this, _1 );
    c.setReadCallback(func);
    ui->lineEdit_message->setFocus();
}

UiClient::~UiClient()
{
    delete ui;
}

 void UiClient::on_lineEdit_message_returnPressed()
{
    //std::cout << "new message" << std::endl;
    QString msg = ui->lineEdit_message->text();
    //std::cout << "recuperation new message" << std::endl;
    std::string utf8_msg = msg.toUtf8().constData();
    //std::cout << "new message to send: " << utf8_msg << std::endl;
    c.createMsg(utf8_msg);
    //std::cout << "new message sent" << std::endl;
    ui->lineEdit_message->clear();
    //std::cout << "clear input line" << std::endl;
}

void UiClient::display_new_msg(std::string entry)
{
    //std::cout << "new message to display: " << entry << std::endl;
    ui->DisplayChat->append(QString::fromStdString(entry));
    QScrollBar* sb = ui->DisplayChat->verticalScrollBar();
    sb->setValue(sb->maximum());
    //std::cout << "new message displayed !" << std::endl;
}
