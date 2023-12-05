// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    input = ui->lineEdit;
    display = ui->textEdit;
    send = ui->pushButton;
     input->setPlaceholderText("Enter message...");
      display->setReadOnly(true);

    transmitSocket = new QUdpSocket(this);
      transmitSocket->bind(QHostAddress::LocalHost, 3514);


    receiveSocket = new QUdpSocket(this);
      receiveSocket->bind(QHostAddress::LocalHost, 3515);

   connect(receiveSocket, &QUdpSocket::readyRead, this, &MainWindow::receivedMessage);

      connect(send, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(input, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);
}

void MainWindow::sendMessage() {
    QString message = ui->lineEdit->text();
    QByteArray datagram = message.toUtf8();
    transmitSocket->writeDatagram(datagram, QHostAddress::LocalHost, 3514);

    if (!message.isEmpty()) {
    ui->textEdit->append("Me: " + message);
        input->clear();
    }

}
void MainWindow::receivedMessage() {

    QByteArray datagram;
    datagram.resize(receiveSocket->pendingDatagramSize());

    receiveSocket->readDatagram(datagram.data(), datagram.size());
    QString msg = QString(datagram);
    if(!msg.isEmpty())
    {
    ui->textEdit->append("Received: " + QString(datagram));
    }

}

void MainWindow::addMessage() {
    QString message = input->text();
    if (!message.isEmpty()) {
        display->append(message);
        input->clear();
    }
}
MainWindow::~MainWindow() {
    delete ui;
    delete transmitSocket;
    delete receiveSocket;
}
