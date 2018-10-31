#include "sendbroadcastthread.h"
#include <QtCore>
#include <QUdpSocket>
#include <QDebug>

SendBroadcastThread::SendBroadcastThread()
{
    udpSocket = new QUdpSocket(this);
}

void SendBroadcastThread::run()
{
QString host_ip = "192.168.0.105";
    QByteArray ByteDataF3F4;  //flaga na komputer z EEG
    ByteDataF3F4.append("F3F4");
//    QByteArray ByteData;
//    ByteData.append("F3");
    udpSocket->writeDatagram(ByteDataF3F4,QHostAddress(host_ip), 1235);    // QHostAddress::Broadcast, 1234);
    qDebug() << "Wysyłam";
    this->exit();
}
