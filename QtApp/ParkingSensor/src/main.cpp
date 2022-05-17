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
    /*const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ParkingSensor_en_150" + QLocale(locale).name();
          qDebug() << baseName;
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
*/
    MainWindow w;
    w.show();

    int toReturn = a.exec();
    w._myQThread->wait();
    return toReturn;
}
