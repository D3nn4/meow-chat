#include "uiclient.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UiClient w;
    w.show();

    return a.exec();
}
