#include "inc/mainwindow.hh"
#include "inc/ui_connectionwitharduino.hh"
#include "inc/WatekOdbioru.hh"

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
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ParkingSensor_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    int toReturn = a.exec();
    w.myQThread->wait();
    return toReturn;
}
