#include "inc/ui_connectionwitharduino.hh"
#include "inc/ConnectionDialog.hh"

/*!
 * \brief Konstruktor klasy ConnectionDialog ktory ustawia Ui oraz sprawdza dostepne porty i wstawia
 * to do listy.
 * \param parent - klasa bazowa
 */
ConnectionDialog::ConnectionDialog(QWidget *parent):QDialog(parent){
    ui.setupUi(this);
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo devicesTab : devices){
        ui.PortComboBox->addItem(devicesTab.portName() + "\t" + devicesTab.description());
    }
    connect(ui.ConnectPushButton, SIGNAL(clicked()), this, SLOT(setPortName()));
    connect(ui.DisconnectPushButton, SIGNAL(clicked()), parent, SLOT(DisconnectDevices()));
}

/*!
 * \brief Metoda odpowiedzialna za wyslanie wybranego portu
 */
void ConnectionDialog::setPortName(){
    QString portName = ui.PortComboBox->currentText().split("\t").first();
    emit SendTo(portName);
}

