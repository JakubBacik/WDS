#include "inc/ui_connectionwitharduino.hh"
#include "inc/ConnectionDialog.hh"

/*!
 * \brief Konstruktor
 * Konstruktor klasy ConnectionDialog który ustawia Ui oraz sprawdza dostępne porty i wstawia
 * je do listy devices.
 * \param[in] parent - klasa bazowa
 */
ConnectionDialog::ConnectionDialog(QWidget *parent):QDialog(parent){
    setAttribute(Qt::WA_DeleteOnClose);
    ui.setupUi(this);
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo devicesTab : devices){
        ui.PortComboBox->addItem(devicesTab.portName() + " " + devicesTab.description());
    }
    connect(ui.ConnectPushButton, SIGNAL(clicked()), this, SLOT(setPortName()));
    connect(ui.DisconnectPushButton, SIGNAL(clicked()), parent, SLOT(DisconnectDevices()));
}

/*!
 * \brief Ustawienie nazwy portu
 * Metoda odpowiedzialna za wysłanie nazwy wybranego portu np. ttyACM0
 */
void ConnectionDialog::setPortName(){
    QString portName = ui.PortComboBox->currentText().split(" ").first();
    emit SendTo(portName);
}

/*!
 * \brief Zamknięcie okna
 * Metoda wywołana podczas zamykania okna.
 * \param[in] event - parametr klasy QCloseEvent
 */
void ConnectionDialog::closeEvent(QCloseEvent *event){
    emit ChangeNumberOfWindow();
    event->accept();
}


