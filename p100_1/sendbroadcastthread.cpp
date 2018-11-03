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
    QByteArray ByteData;
    ByteData.append("F3");
    udpSocket->writeDatagram(ByteData, QHostAddress::Broadcast, 1234);
    qDebug() << "Wysyłam" <<  ByteData;
    this->exit();
}
