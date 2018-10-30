#include "p300.h"
#include "ui_p300.h"
#include "sendbroadcastthread.h"
#include <QtDebug>
#include <QTimer>
#include <QThread>
#include <QPainter>
#include <QStyle>
#include <QDesktopWidget>
#include <QPainterPath>
#include <QLabel>
#include <QGraphicsView>

p300::p300(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::p300)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(1366,768);
    setAttribute(Qt::WA_TranslucentBackground);
    this->hide();
    setStyleSheet("background:black;");

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeTick()));

    count = 0;      // licznik migania
    count1=0;
    repeat = 30;    // target
    nontarget =10;
    p1=0;
    p2=0;
    rand = 0;

    x=50;
    y=50;
    x1 = 20;
    y1 = 20;
    radius = 1;
    radius1 = 2;
    start = false;
    interval = 500;   //1000 ms beetwen

    udpSocket = new QUdpSocket(this);
    udpSocket ->bind(1234);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(datagram()));
}

p300::~p300()
{
    delete ui;
}

void p300::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    QByteArray ByteDataF1;  //flaga na komputer z EEG
    ByteDataF1.append("F1");
    QByteArray ByteDataF2;  //flaga na komputer z EEG
    ByteDataF2.append("F2");
    QByteArray ByteDataF3;  //flaga na komputer z EEG
    ByteDataF3.append("F3");
    QString host_ip = "192.168.0.105";\

    if((count1 == rand) && !dark)
    {
        rand = qrand() % ((nontarget+1)-1)+1;        //losowa liczba nontarget
   //     QColor yellow("#f0d048");
   //     QBrush brush(yellow);
        udpSocket->writeDatagram(ByteDataF1, QHostAddress(host_ip), 1235);  // QHostAddress::Broadcast
        p1 = p1+1;
        painter.setBrush(Qt::blue);  //red
        painter.drawRect(550,250,300,300);   //target 160 160    TARGET


        count++;
        dark = true;
        count1=0;
        p2=0;
    }
    else if((count1 != rand) && !dark)
    {
        int col = qrand() % ((7+1)-1)+1;
         count1 = count1+1;
    //     QColor yellow("#f0d048");
     //    QBrush brush(yellow);
       if (col==1)
       {

           udpSocket->writeDatagram(ByteDataF3, QHostAddress(host_ip), 1235);  //distractor
           painter.setBrush(Qt::yellow);   //yellow  blue
           painter.drawEllipse(550,250,300,300);

       }
         else
      {

           udpSocket->writeDatagram(ByteDataF2,QHostAddress(host_ip), 1235);
           painter.setBrush(Qt::green);
           painter.drawEllipse(550,250,300,300);

       }

         p2 = p2+1;
         dark = true;
    }
    else if (dark)
    {

          QColor black;
          QBrush brush(black);
          dark = false;
          painter.setBrush(brush);
          painter.drawEllipse(550,250,300,300);
    }

      if(count >= repeat)
      {
            this->hide();
            this->timer->stop();
            count = 0;
            count1=0;
            p2=0;
      }

}

void p300::datagram()
{
    QByteArray data;
    bool stop = false;

    do{
        data.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(data.data(),data.size(),&sender,&senderPort);

        if (data == "1")
        {
            stop = true;
            this->show();
            this->timer->start(interval);

            if(!start)
            {
                start = true;
                dark = false;
            }
        }

        if (data == "0")
        {
            stop = true;
            count = 0;
            this->hide();
            this->timer->stop();

        }

        if (data == "2")
        {
            stop = true;
            QApplication::quit();
        }
    } while(!stop);

}

void p300::timeTick()
{
    this->update();
}


