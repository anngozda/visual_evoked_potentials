#ifndef SENDBROADCASTTHREAD_H
#define SENDBROADCASTTHREAD_H
#include <QtCore>
#include <QUdpSocket>


class SendBroadcastThread : public QThread
{
public:
    SendBroadcastThread();
    void run();
    QUdpSocket *udpSocket;

};

#endif // SENDBROADCASTTHREAD_H
