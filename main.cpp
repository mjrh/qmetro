#include "qmetro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qMetro w;
    w.show();

    return a.exec();
}
