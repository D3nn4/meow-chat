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

private slots:



    void on_lineEdit_message_returnPressed();

private:
    Ui::UiClient *ui;
    Client& c;
};

#endif // UICLIENT_HPP
