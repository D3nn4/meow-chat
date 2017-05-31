#include "uiclient.hpp"
#include "ui_uiclient.h"

UiClient::UiClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiClient)
{
    ui->setupUi(this);
}

UiClient::~UiClient()
{
    delete ui;
}

void UiClient::on_pushButton_username_clicked()
{
    QString username = ui->lineEdit_username->text();
    std::string utf8_username = username.toUtf8().constData();
    //c.pseudo = utf8_username;
    ui->lineEdit_username->clear();
    ui->statusBar->showMessage(username);

}

void UiClient::on_lineEdit_message_returnPressed()
{
    QString msg = ui->lineEdit_message->text();
    std::string utf8_msg = msg.toUtf8().constData();
    //c.createMessage(utf8_msg);
    //ui->DisplayChat->append(QString::fromStdString(utf8_msg));
    ui->lineEdit_message->clear();
}

void UiClient::display_new_msg(std::string entry)
{
    ui->DisplayChat->append(QString::fromStdString(entry));
}
