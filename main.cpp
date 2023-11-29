#include "mainwindow.h"
#include <QApplication>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>  // Add this line for QHostAddress
#include <QDebug>                  // Add this line for qDebug()
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QUdpSocket udpSocket;
    udpSocket.bind(QHostAddress::LocalHost, 1234);
    QObject::connect(&udpSocket, &QUdpSocket::readyRead, [&]() {
        while (udpSocket.hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket.pendingDatagramSize());
            udpSocket.readDatagram(datagram.data(), datagram.size());

            // Process the received datagram
            qDebug() << "Received datagram:" << datagram;
        }
    });

    MainWindow w;
    w.show();
    return a.exec();
}
