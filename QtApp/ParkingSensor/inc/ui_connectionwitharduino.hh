/********************************************************************************
** Form generated from reading UI file 'connectionwitharduino.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONWITHARDUINO_H
#define UI_CONNECTIONWITHARDUINO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectionWithArduino
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *PortLabel;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *PortComboBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ConnectPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *DisconnectPushButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *ConnectionWithArduino)
    {
        if (ConnectionWithArduino->objectName().isEmpty())
            ConnectionWithArduino->setObjectName(QString::fromUtf8("ConnectionWithArduino"));
        ConnectionWithArduino->resize(259, 167);
        verticalLayout_3 = new QVBoxLayout(ConnectionWithArduino);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PortLabel = new QLabel(ConnectionWithArduino);
        PortLabel->setObjectName(QString::fromUtf8("PortLabel"));

        horizontalLayout->addWidget(PortLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        PortComboBox = new QComboBox(ConnectionWithArduino);
        PortComboBox->setObjectName(QString::fromUtf8("PortComboBox"));

        horizontalLayout->addWidget(PortComboBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ConnectPushButton = new QPushButton(ConnectionWithArduino);
        ConnectPushButton->setObjectName(QString::fromUtf8("Connect"));

        horizontalLayout_2->addWidget(ConnectPushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        DisconnectPushButton = new QPushButton(ConnectionWithArduino);
        DisconnectPushButton->setObjectName(QString::fromUtf8("Disconnect"));

        horizontalLayout_2->addWidget(DisconnectPushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_3);


        retranslateUi(ConnectionWithArduino);

        QMetaObject::connectSlotsByName(ConnectionWithArduino);
    } // setupUi

    void retranslateUi(QDialog *ConnectionWithArduino)
    {
        ConnectionWithArduino->setWindowTitle(QApplication::translate("ConnectionWithArduino", "Okno połączenia", nullptr));
        PortLabel->setText(QApplication::translate("ConnectionWithArduino", "Port:", nullptr));
        ConnectPushButton->setText(QApplication::translate("ConnectionWithArduino", "Połącz", nullptr));
        DisconnectPushButton->setText(QApplication::translate("ConnectionWithArduino", "Rozłącz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectionWithArduinoClass: public Ui_ConnectionWithArduino {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONWITHARDUINO_H
