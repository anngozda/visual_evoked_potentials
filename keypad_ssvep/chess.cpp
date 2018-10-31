#include "chess.h"
#include "ui_chess.h"
#include "sendbroadcastthread.h"
#include <QtDebug>
#include <QTimer>
#include <QThread>
#include <QPainter>
#include <QStyle>
#include <QDesktopWidget>

chess::chess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chess)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(1200,720);       //predzej 950 x 700
    setAttribute(Qt::WA_TranslucentBackground);
//    this->hide();
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
    timer1 = new QTimer(this);
    timer2= new QTimer(this);
    timer3= new QTimer(this);
    timer4= new QTimer(this);
    timer5= new QTimer(this);
    timer6 = new QTimer(this);
    timer7 = new QTimer(this);
    timer8= new QTimer(this);
    timer9= new QTimer(this);
    timer10= new QTimer(this);
    timer11= new QTimer(this);
    timer12= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeTick()));
    connect(timer1, SIGNAL(timeout()), this, SLOT(timeTick1()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(timeTick2()));
    connect(timer3, SIGNAL(timeout()), this, SLOT(timeTick3()));
    connect(timer4, SIGNAL(timeout()), this, SLOT(timeTick4()));
    connect(timer5, SIGNAL(timeout()), this, SLOT(timeTick5()));
    connect(timer6, SIGNAL(timeout()), this, SLOT(timeTick6()));
    connect(timer7, SIGNAL(timeout()), this, SLOT(timeTick7()));
    connect(timer8, SIGNAL(timeout()), this, SLOT(timeTick8()));
    connect(timer9, SIGNAL(timeout()), this, SLOT(timeTick9()));
    connect(timer10, SIGNAL(timeout()), this, SLOT(timeTick10()));
    connect(timer11, SIGNAL(timeout()), this, SLOT(timeTick11()));
    connect(timer12, SIGNAL(timeout()), this, SLOT(timeTick12()));

    num = 0;
    pause = 0;
    count = 0;      // licznik migania
    repeat = 180;
    shapeTime=0;    // czas trwania każdego mrugania (5 sekund)
    pomoc=false;

    start = false;
    flashingTime = i_interval;

    ui->label_2->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_3->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_4->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_5->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_6->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_7->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_8->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_9->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_11->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_12->setStyleSheet("QLabel{background:transparent}") ;
    ui->label_13->setStyleSheet("QLabel{background:transparent}") ;

    for(int i=0; i<12; i++)
    {
       wylosowane[i]=0;
    }

     wylosowanych = 0;

    udpSocket = new QUdpSocket(this);
    udpSocket ->bind(1234);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(datagram()));

    do{
        int liczba = wylosuj();
        if( czyBylaWylosowana( liczba, wylosowane, wylosowanych ) == false )  //spr czy liczba nie zostala juz wylosowana
        {
            wylosowane[ wylosowanych ] = liczba;
            wylosowanych++;
        }
      } while( wylosowanych < 12 );  //wykonuj tak dlugo az wylosuje 12 niepowtarzajacych sie liczb

    wylosowanych = 0;

}

chess::~chess()
{
    delete ui;
}

double chess::get_s(double f, double i_ms)
{
    double s;

         s =  sin(2*M_PI*f*(i_ms/60))>=0.0 ? 1.0:0.0; // jezeli wieksze od 0 to 1, jezeli nie to 0

    return s;
}

void chess::datagram()
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
            this->timer->start(flashingTime);
            this->timer1->start(flashingTime);
            this->timer2->start(flashingTime);
            this->timer3->start(flashingTime);
            this->timer4->start(17);
            this->timer5->start(flashingTime);
            this->timer6->start(flashingTime);
            this->timer7->start(flashingTime);
            this->timer8->start(flashingTime);
            this->timer9->start(flashingTime);
            this->timer10->start(flashingTime);
            this->timer11->start(flashingTime);
            this->timer12->start(flashingTime);

            count = 0;
        }

        if (data == "0")
        {
            stop = true;
            count = 0;
            qDebug() << "Stop button";
            this->hide();
            this->timer->stop();
            this->timer1->stop();
            this->timer2->stop();
            this->timer3->stop();
            this->timer4->stop();
            this->timer5->stop();
            this->timer6->stop();
            this->timer7->stop();
            this->timer8->stop();
            this->timer9->stop();
            this->timer10->stop();
            this->timer11->stop();
            this->timer12->stop();
        }

        if (data == "2")
        {
            stop = true;
            qDebug() << "Exit button";
            QApplication::quit();
        }
    } while(!stop);

}

bool chess::czyBylaWylosowana( int iLiczba, int tab[], int ile )
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

int chess:: wylosuj()
{
    int temp=qrand() % ((12+1)-1)+1;
 //   qDebug() << temp;
    return  temp;
}

void chess::timeTick()
{

    double ff = 7;
    double lum =  get_s(ff,i_ms);
    i_ms += 1;

    ui->label_2->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));

    if(flag==1) ui->label_2->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick1()
{

    double ff = 7.5;
    double lum =get_s(ff,i_ms1);
    i_ms1 += 1;

    ui->label_3->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));

    if(flag==2) ui->label_3->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick2()
{
    double ff = 8;
    double lum =get_s(ff,i_ms2);
    i_ms2 += 1;
                                             //255,255,255
    ui->label_4->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

    if(flag==3) ui->label_4->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick3()
{
    double ff =8.5;
    double lum =get_s(ff,i_ms3);
    i_ms3 += 1;
                                                    //(255,255,255)
    ui->label_5->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

    if(flag==4) ui->label_5->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick5()
{
     double ff = 9;
     double lum =get_s(ff,i_ms4);
     i_ms4 += 1;

     ui->label_8->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

     if(flag==5) ui->label_8->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                              +"border: 4px solid red; ");
}

void chess::timeTick6()
{
    double ff =9.5;
    double lum =get_s(ff,i_ms5);
    i_ms5 += 1;
    ui->label_9->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));

    if(flag==6) ui->label_9->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}
void chess::timeTick7()
{
    double ff =10;
    double lum =get_s(ff,i_ms6);
    i_ms6 += 1;
    ui->label_7->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));

    if(flag==7) ui->label_7->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick8()
{
    double ff =10.5;
    double lum =get_s(ff,i_ms7);
     i_ms7 += 1;
    ui->label_6->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));

    if(flag==8) ui->label_6->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");
}

void chess::timeTick9()     //15Hz
{

    double ff =11;
    double lum =get_s(ff,i_ms8);
    i_ms8 += 1;
    ui->label_12->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

    if(flag==9) ui->label_12->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick10()
{

    double ff = 11.5;
    double lum = get_s(ff,i_ms9);
    i_ms9 += 1;
    ui->label_13->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

    if(flag==10) ui->label_13->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick11()
{

    double ff =12;
    double lum =get_s(ff,i_ms10);
    i_ms10 += 1;
    ui->label_11->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

    if(flag==11) ui->label_11->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}

void chess::timeTick12()
{

    double ff =12.5;
    double lum =get_s(ff,i_ms11);
      i_ms11 += 1;
    ui->label_10->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255));  //red    fuchsia    aqua

    if(flag==12) ui->label_10->setStyleSheet(QString("background-color:rgba(255,255,255,%1);").arg(lum*255)
                                          +"border: 4px solid red; ");

}


void chess::timeTick4()

{    if(!start)
    {
        start = true;
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
        QByteArray ByteDataF5F6;  //flaga na komputer z EEG
        ByteDataF5F6.append("F5F6");
        QByteArray ByteDataF7F8;  //flaga na komputer z EEG
        ByteDataF7F8.append("F7F8");

        QString host_ip = "192.168.0.107";
        if(flag == 1)     //|| flag==5 || flag==9)
       { udpSocket->writeDatagram(ByteDataF1, QHostAddress(host_ip), 1235);} // qDebug() << "F1"; }  //12
        else if (flag == 2) // || flag==6 || flag==10)
       { udpSocket->writeDatagram(ByteDataF2, QHostAddress(host_ip), 1235);}
        else if (flag == 3) // || flag==7 || flag==11)
       { udpSocket->writeDatagram(ByteDataF3, QHostAddress(host_ip), 1235);}
        else if (flag == 4)  // || flag==8 || flag==12)
       { udpSocket->writeDatagram(ByteDataF4, QHostAddress(host_ip), 1235);}
        else if (flag == 5)  // || flag==6 || flag==10)
       { udpSocket->writeDatagram(ByteDataF5, QHostAddress(host_ip), 1235);} // qDebug() << "F5"; }  //15
        else if (flag == 6)  //|| flag==7 || flag==11)
       { udpSocket->writeDatagram(ByteDataF6, QHostAddress(host_ip), 1235);} // qDebug() << "F6"; }  //8
        else if (flag == 7)  // || flag==8 || flag==12)
       { udpSocket->writeDatagram(ByteDataF7, QHostAddress(host_ip), 1235);} // qDebug() << "F7";}  //10
        else if (flag == 8)   //|| flag==6 || flag==10)
       { udpSocket->writeDatagram(ByteDataF8, QHostAddress(host_ip), 1235);} // qDebug() << "F8"; }  //15
        else if (flag == 9)// || flag==7 || flag==11)
       { udpSocket->writeDatagram(ByteDataF1F2, QHostAddress(host_ip), 1235);} // qDebug() << "F9"; }  //8
        else if (flag == 10) // || flag==8 || flag==12)
       { udpSocket->writeDatagram(ByteDataF3F4, QHostAddress(host_ip), 1235);} // qDebug() << "F10";}  //10
        else if (flag == 11) // || flag==6 || flag==10)
       { udpSocket->writeDatagram(ByteDataF5F6, QHostAddress(host_ip), 1235);} // qDebug() << "F11"; }  //15
        else if (flag == 12)  // || flag==7 || flag==11)
       { udpSocket->writeDatagram(ByteDataF7F8, QHostAddress(host_ip), 1235);} // qDebug() << "F12"; }  //8
    }

    shapeTime++;

    if(shapeTime >= 236)        //5s migania z określoną częstotliwością
      {
        this->timer->stop();
        this->timer1->stop();
        this->timer2->stop();
        this->timer3->stop();
        this->timer5->stop();
        this->timer6->stop();
        this->timer7->stop();
        this->timer8->stop();
        this->timer9->stop();
        this->timer10->stop();
        this->timer11->stop();
        this->timer12->stop();

        ui->label_2->setStyleSheet("border: transparent; ");
        ui->label_3->setStyleSheet("border: transparent; ");
        ui->label_4->setStyleSheet("border: transparent; ");
        ui->label_5->setStyleSheet("border: transparent; ");
        ui->label_8->setStyleSheet("border: transparent; ");
        ui->label_9->setStyleSheet("border: transparent; ");
        ui->label_7->setStyleSheet("border: transparent; ");
        ui->label_6->setStyleSheet("border: transparent; ");
        ui->label_13->setStyleSheet("border: transparent; ");
        ui->label_12->setStyleSheet("border: transparent; ");
        ui->label_11->setStyleSheet("border: transparent; ");
        ui->label_10->setStyleSheet("border: transparent; ");

          pause++;

          if(wylosowane[num] == 1)
          { ui->label_2->setStyleSheet("background-color:red;");
                            flag = 1;
                            }
          else if(wylosowane[num]==2) {
                            ui->label_3->setStyleSheet("background-color:red;");
                            flag = 2;
                           }
          else if(wylosowane[num]==3) {
                            ui->label_4->setStyleSheet("background-color:red;");
                            flag = 3;
                            }
          else if(wylosowane[num]==4) {
                            ui->label_5->setStyleSheet("background-color:red;");
                            flag = 4;
                            }
          else if(wylosowane[num]==5) {
                            ui->label_8->setStyleSheet("background-color:red;");
                            flag = 5;
                            }
          else if(wylosowane[num]==6) {
                            ui->label_9->setStyleSheet("background-color:red;");
                            flag = 6;
                            }
          else if(wylosowane[num]==7) {
                            ui->label_7->setStyleSheet("background-color:red;");
                            flag = 7;
                            }
          else if(wylosowane[num]==8) {
                            ui->label_6->setStyleSheet("background-color:red;");
                            flag = 8;
                            }
          else if(wylosowane[num]==9) {
                            ui->label_12->setStyleSheet("background-color:red;");
                            flag = 9;
                            }
          else if(wylosowane[num]==10) {
                            ui->label_13->setStyleSheet("background-color:red;");
                            flag = 10;
                            }
          else if(wylosowane[num]==11) {
                            ui->label_11->setStyleSheet("background-color:red;");
                            flag = 11;
                            }
          else if(wylosowane[num]==12) {
                            ui->label_10->setStyleSheet("background-color:red;");
                            flag = 12;
                            }

          if(pause == 59)
           {

               start = false;
               shapeTime = 0;
               count++;
               pause = 0;
               num++;
               if (num==12)
               {
                   num=0;

                  for(int i=0; i<12; i++)
                   {
                      wylosowane[i]=0;
                   }

                   wylosowanych =0 ;

                   do
                   {

                   int liczba = wylosuj();

                       if( czyBylaWylosowana( liczba, wylosowane, wylosowanych ) == false )
                        {
                            wylosowane[ wylosowanych ] = liczba;
                            wylosowanych++;
                        } //if

                   } while( wylosowanych < 12 );

               wylosowanych = 0;

               }

               this->timer->start(flashingTime);
               this->timer1->start(flashingTime);
               this->timer2->start(flashingTime);
               this->timer3->start(flashingTime);
               this->timer5->start(flashingTime);
               this->timer6->start(flashingTime);
               this->timer7->start(flashingTime);
               this->timer8->start(flashingTime);
               this->timer9->start(flashingTime);
               this->timer10->start(flashingTime);
               this->timer11->start(flashingTime);
               this->timer12->start(flashingTime);
           }
      }

      if(count > repeat)
      {
          this->hide();
          this->timer->stop();
          this->timer1->stop();
          this->timer2->stop();
          this->timer3->stop();
          this->timer4->stop();
          this->timer5->stop();
          this->timer6->stop();
          this->timer7->stop();
          this->timer8->stop();
          this->timer9->stop();
          this->timer10->stop();
          this->timer11->stop();
          this->timer12->stop();
          shapeTime = 0;
          count = 0;
      }
}



/*         QFile file;
       QFile file1;
       QFile file2;

     file.setFileName("C:/Users/Ania/Desktop/studia/praca magisterska/keypad2_ssvep/file");
       if(file.open(QIODevice::Append | QIODevice::Text )){ // metoda open w otwiera plik w trybie tylko do odczytu z zamianą znaków \r\n ma \n
           QTextStream out(&file);
           out << '\n' << '\n'; // zapis danych do pliku
           file.close(); }
       file1.setFileName("C:/Users/Ania/Desktop/studia/praca magisterska/keypad2_ssvep/file1");
       if(file1.open(QIODevice::Append | QIODevice::Text )){ // metoda open w otwiera plik w trybie tylko do odczytu z zamianą znaków \r\n ma \n
           QTextStream out(&file1);
           out << '\n' << '\n'; // zapis danych do pliku
           file1.close(); }
       file2.setFileName("C:/Users/Ania/Desktop/studia/praca magisterska/keypad2_ssvep/file2");
       if(file2.open(QIODevice::Append | QIODevice::Text )){ // metoda open w otwiera plik w trybie tylko do odczytu z zamianą znaków \r\n ma \n
           QTextStream out(&file2);
           out << '\n' << '\n'; // zapis danych do pliku
           file2.close(); }


*/

