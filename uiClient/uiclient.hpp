#ifndef UICLIENT_HPP
#define UICLIENT_HPP
#include <QMainWindow>
#include <string>
#include "client.hpp"

namespace Ui {
class UiClient;
}

class UiClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit UiClient(Client& client, QWidget *parent = 0);
    ~UiClient();
    void display_new_msg(std::string entry);
    void sendSignal(std::vector<std::string> users);

public slots:

     void display_users(std::vector<std::string> users);

signals:

    void clearSignal(std::vector<std::string> users);

private slots:

    void on_lineEdit_message_returnPressed();

private:
    Ui::UiClient *ui;
    Client& c;
    //std::vector<std::string> usersListTemp;
};

#endif // UICLIENT_HPP
