#include "p100.h"
#include "ui_p100.h"
#include "sendbroadcastthread.h"

p100::p100(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::p100)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    this->setFixedSize(900,500);            //1366x768

    timer = new QTimer(this);

    flashTime = 20;                 //czas błysku = 20ms
    repeat = 110;                   //ilość błysków w jednej serii
    counter = 0;                    //do zliczania czy osiagnięto zadaną ilość błysków
    tick = 0;
    size = 90;
    rows = 15;

    udpSocket = new QUdpSocket(this);
    udpSocket ->bind(1234);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeTick()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(releaseRectangle()));
}

p100::~p100()
{
    delete ui;
}

/*
//blyski
void p100::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(black)
    {
       painter.fillRect(0,0,900,500,Qt::black);
    }
    else
    {
       painter.fillRect(0,0,900,500,Qt::white);
    }
}
*/


//szachownica
void p100::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    bool isNextWhite = false;

    if(black)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                if (!isNextWhite)
                {
                    painter.fillRect(i*size,j*size,size,size,Qt::black);
                    if (!(rows%2==0) || !(j == rows - 1))
                    {
                        isNextWhite = true;
                    }
                }
                else
                {
                    painter.fillRect(i*size,j*size,size,size,Qt::white);
                    if (!(rows%2==0) || !(j == rows - 1))
                    {
                        isNextWhite = false;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                if (!isNextWhite)
                {
                    painter.fillRect(i*size,j*size,size,size,Qt::white);
                    if (!(rows%2==0) || !(j == rows - 1))
                    {
                        isNextWhite = true;
                    }
                }
                else
                {
                    painter.fillRect(i*size,j*size,size,size,Qt::black);
                    if (!(rows%2==0) || !(j == rows - 1))
                    {
                        isNextWhite = false;
                    }
                }
            }
        }
    }
}


void p100::timeTick()
{
    tick++;

    if(tick < time)                 //time = tick<0,time-1>
    {
        black = true;
    }
    else                            //flashTime = tick<time,flashTime-1>
    {
        black = false;
    }

    if(tick == time)                //wysłanie flagi o wystąpieniu błysku
    {
        QByteArray ByteDataF3;
        ByteDataF3.append("F3");
        QHostAddress address;
        address.setAddress("192.168.0.105");
        udpSocket->writeDatagram(ByteDataF3, address, 1235);
    }

    if(tick == (time + flashTime-1))
    {
        tick = 0;
        counter++;

        if (counter < repeat)
        {
            time = static_cast <int> ((qrand()%((10+1)-9)+9)) * 100;
        }
        else
        {
            timer->stop();
            this->hide();
            counter = 0;
        }
    }
    this->update();
}

void p100::releaseRectangle()
{
    QByteArray datagram;
    bool stop = false;

    do{
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);

        if (datagram == "1")
        {
            stop = true;
            time = static_cast <int> ((qrand()%((10+1)-9)+9)) * 100;
            this->show();
            this->timer->start(1);
        }

        if (datagram == "0")
        {
            stop = true;
            counter = 0;
            tick = 0;
            this->hide();
            this->timer->stop();
        }

        if (datagram == "2")
        {
            stop = true;
            QApplication::quit();
        }
    }
    while (!stop);
}
