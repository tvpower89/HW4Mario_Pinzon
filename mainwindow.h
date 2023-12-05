// mainwindow.h
#include <QMainWindow>
#include <QUdpSocket>
#include "ui_mainwindow.h"  // Include the generated UI header

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;  // Use the generated UI class pointer
    QUdpSocket *transmitSocket;
    QUdpSocket *receiveSocket;
    QLineEdit *input;
    QTextEdit *display;
    QPushButton *send;
    void sendMessage();
    void receivedMessage();
    void addMessage();
};
