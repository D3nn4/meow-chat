#include "uiclient.hpp"
#include "ui_uiclient.h"
#include <functional>
#include <iostream>

using std::placeholders::_1;

UiClient::UiClient(Client &client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiClient),
    c(client)
{
    ui->setupUi(this);

    std::function<void(std::string)> func= std::bind( &UiClient::display_new_msg, this, _1 );
    c.setReadCallback(func);
}

UiClient::~UiClient()
{
    delete ui;
}

void UiClient::on_pushButton_username_clicked()
{
    QString username = ui->lineEdit_username->text();
    ui->statusBar->showMessage(username);
    std::string utf8_username = username.toUtf8().constData();
    c.pseudo = utf8_username;
    ui->lineEdit_username->clear();
}

void UiClient::on_lineEdit_message_returnPressed()
{
    //std::cout << "new message" << std::endl;
    QString msg = ui->lineEdit_message->text();
    std::string utf8_msg = msg.toUtf8().constData();
    std::cout << "new message to send: " << utf8_msg << std::endl;
    c.createMsg(utf8_msg);
    ui->lineEdit_message->clear();
}

void UiClient::display_new_msg(std::string entry)
{
    std::cout << "new message to display: " << entry << std::endl;
    ui->DisplayChat->append(QString::fromStdString(entry));
}
