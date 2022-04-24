#include "inc/ui_connectionwitharduino.hh"
#include "inc/connectionwitharduino.hh"

ConnectionWithArduino::ConnectionWithArduino(QWidget *parent):QDialog(parent){
    ui.setupUi(this);
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo devicesTab : devices){
        ui.PortComboBox->addItem(devicesTab.portName() + "\t" + devicesTab.description());
    }
    connect(ui.ConnectPushButton, SIGNAL(clicked()), this, SLOT(changePortName()));
    connect(ui.DisconnectPushButton, SIGNAL(clicked()), parent, SLOT(DisconnectDevices()));
}

void ConnectionWithArduino::changePortName(){
    QString portName = ui.PortComboBox->currentText().split("\t").first();
    emit SendTo(portName);
}

