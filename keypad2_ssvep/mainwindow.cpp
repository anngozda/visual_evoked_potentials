#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sendbroadcastthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chessboard = new chess(this);
    black = false;

    udpSocket = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_START_clicked()
{
    QByteArray ByteData;
    QByteArray ByteDataF3;
    ByteData.append("1");
    ByteDataF3.append("F3");

    udpSocket->writeDatagram(ByteData, QHostAddress::Broadcast, 1234);

}

void MainWindow::on_STOP_clicked()
{
    QByteArray ByteData;
    ByteData.append("0");
    udpSocket->writeDatagram(ByteData, QHostAddress::Broadcast, 1234);
}

void MainWindow::on_EXIT_clicked()
{
    QByteArray ByteData;
    ByteData.append("2");
    udpSocket->writeDatagram(ByteData, QHostAddress::Broadcast, 1234);
    QApplication::quit();
}

void MainWindow::delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}




