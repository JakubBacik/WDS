#include "inc/Mainwindow.hh"
#include "inc/ui_connectionwitharduino.hh"
#include "inc/CommunicationAndMyQThread.hh"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QList>
#include <QDialog>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    MainWindow w;

    w.show();
    int toReturn = a.exec();
    w._myQThread->wait();

    return toReturn;
}
