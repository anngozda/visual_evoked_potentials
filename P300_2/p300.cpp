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
   this->setFixedSize(1200,720);
    setAttribute(Qt::WA_TranslucentBackground);
    this->hide();
    setStyleSheet("background:black;");

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeTick()));

    count = 0;
    p=0;
    repeat =90;
    nontarget = 10;
    p1=0;
    p2=0;


    x=40;
    y=40;
    x1 = 20;
    y1 = 20;
    radius = 1;
    radius1 = 2;
    start = false;
    interval = 300;   //1000 ms beetwen

    udpSocket = new QUdpSocket(this);
    udpSocket ->bind(1234);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(datagram()));

    for(int i=0; i<9; i++)
    {
       wylosowane[i]=0;
    }

     wylosowanych = 0;


do{
    int liczba = wylosuj();   //losuje liczbe sposrod 12
    if( czyBylaWylosowana( liczba, wylosowane, wylosowanych ) == false )  //spr czy taka liczba wczesniej juz nie padla
    {
        wylosowane[ wylosowanych ] = liczba;
        wylosowanych++;
    } //if
  } while( wylosowanych < 9 );  //wykonuj petla tak dlugo az wylosuje 12 niepowtarzajacych sie licz

wylosowanych = 0;

}

p300::~p300()
{
    delete ui;
}
bool p300::czyBylaWylosowana( int iLiczba, int tab[], int ile )
{
    if( ile <= 0 )
         return false;

    int i = 0;
    do  //jesli liczba byla juz wylosowana
    {
        if( tab[ i ] == iLiczba )
             return true;

        i++;
    } while( i < ile );

    return false;
}


int p300:: wylosuj()
{
    int temp=qrand() % ((9+1)-1)+1;
    return  temp;
}

void p300::timeTick()     //paintEvent(QPaintEvent *)
{
    //QPainter painter(this);

    QByteArray ByteDataF1;  //flaga na komputer z EEG
    ByteDataF1.append("F1");
    QByteArray ByteDataF2;  //flaga na komputer z EEG
    ByteDataF2.append("F2");
    QByteArray ByteDataF3;  //flaga na komputer z EEG
    ByteDataF3.append("F3");
    QByteArray ByteDataF4;  //flaga na komputer z EEG
    ByteDataF4.append("F4");
    QByteArray ByteDataF5;  //flaga na komputer z EEG
    ByteDataF5.append("F5");
    QByteArray ByteDataF6;  //flaga na komputer z EEG
    ByteDataF6.append("F6");
    QByteArray ByteDataF7;  //flaga na komputer z EEG
    ByteDataF7.append("F7");
    QByteArray ByteDataF8;  //flaga na komputer z EEG
    ByteDataF8.append("F8");
    QByteArray ByteDataF1F2;  //flaga na komputer z EEG
    ByteDataF1F2.append("F1F2");
    QByteArray ByteDataF3F4;  //flaga na komputer z EEG
    ByteDataF3F4.append("F3F4");

    QString host_ip = "192.168.0.105";


if(!dark)
{
     ui->label_2->setStyleSheet("background-color:gray;");
     ui->label_3->setStyleSheet("background-color:gray;");
     ui->label_4->setStyleSheet("background-color:gray;");
     ui->label_7->setStyleSheet("background-color:gray;");
     ui->label_8->setStyleSheet("background-color:gray;");
     ui->label_9->setStyleSheet("background-color:gray;");
     ui->label_11->setStyleSheet("background-color:gray;");
     ui->label_12->setStyleSheet("background-color:gray;");
     ui->label_13->setStyleSheet("background-color:gray;");


        if (wylosowane[p]==1) {target = false; nont=1; udpSocket->writeDatagram(ByteDataF1, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==2) {target = false; nont=2; udpSocket->writeDatagram(ByteDataF2, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==3) {target = false; nont=3; udpSocket->writeDatagram(ByteDataF3, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==4) {target = false; nont=4; udpSocket->writeDatagram(ByteDataF4, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==5) {target = false; nont=5; udpSocket->writeDatagram(ByteDataF5, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==6) {target = false; nont=6; udpSocket->writeDatagram(ByteDataF6, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==7) {target = false; nont=7; udpSocket->writeDatagram(ByteDataF7, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==8) {target = false; nont=8; udpSocket->writeDatagram(ByteDataF8, QHostAddress(host_ip), 1235);} // p=p+1; }
        else if (wylosowane[p]==9) {target = false; nont=9; udpSocket->writeDatagram(ByteDataF1F2, QHostAddress(host_ip), 1235);} // p=p+1; }

        if(nont==1)  ui->label_2->setStyleSheet("background-color:red;");  //painter.fillRect(250,50,150,150, Qt::red);   // green // red
        else if(nont==2) ui->label_3->setStyleSheet("background-color:red;");
        else if(nont==3) ui->label_4->setStyleSheet("background-color:red;");
        else if(nont==4) ui->label_7->setStyleSheet("background-color:red;");
        else if(nont==5) ui->label_8->setStyleSheet("background-color:red;");
        else if(nont==6) ui->label_9->setStyleSheet("background-color:red;");
        else if(nont==7) ui->label_11->setStyleSheet("background-color:red;");
        else if(nont==8) ui->label_12->setStyleSheet("background-color:red;");
        else if(nont==9) ui->label_13->setStyleSheet("background-color:red;");
        p++;
        dark = true;

} else
{
    ui->label_2->setStyleSheet("background-color:gray;");
    ui->label_3->setStyleSheet("background-color:gray;");
    ui->label_4->setStyleSheet("background-color:gray;");
    ui->label_7->setStyleSheet("background-color:gray;");
    ui->label_8->setStyleSheet("background-color:gray;");
    ui->label_9->setStyleSheet("background-color:gray;");
    ui->label_11->setStyleSheet("background-color:gray;");
    ui->label_12->setStyleSheet("background-color:gray;");
    ui->label_13->setStyleSheet("background-color:gray;");
    dark = false;

}

if(p==9)
{
     p1++;   //liczba rund targetow - dla kazdego klawisza
     count++;
    if(p1==10)
    {
         QThread::msleep(1000);
         udpSocket->writeDatagram(ByteDataF3F4, QHostAddress(host_ip), 1235);
         QThread::msleep(1000);

         p1=0;
    }

    p=0;


    for(int i=0; i<9; i++)
    {
       wylosowane[i]=0;
    }

     wylosowanych = 0;


do{
    int liczba = wylosuj();   //losuje liczbe sposrod 12
    if( czyBylaWylosowana( liczba, wylosowane, wylosowanych ) == false )  //spr czy taka liczba wczesniej juz nie padla
    {
        wylosowane[ wylosowanych ] = liczba;
        wylosowanych++;
    } //if
  } while( wylosowanych < 9 );  //wykonuj petla tak dlugo az wylosuje 12 niepowtarzajacych sie licz

wylosowanych = 0;

}

      if(count > repeat)
      {
            this->hide();
            this->timer->stop();
            count = 0;

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
            qDebug() << "Start button";
            this->show();
            this->timer->start(interval);

            if(!start)
            {

                QString host_ip = "192.168.0.102";
                start = true;
                dark = true;
                qDebug() << "start";

            }
        }

        if (data == "0")
        {
            stop = true;
            count = 0;

            qDebug() << "Stop button";
            this->hide();
            this->timer->stop();

        }

        if (data == "2")
        {
            stop = true;
            qDebug() << "Exit button";
            QApplication::quit();
        }
    } while(!stop);

}



