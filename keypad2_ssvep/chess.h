#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QUdpSocket>

namespace Ui {
class chess;
}

class chess : public QWidget
{
    Q_OBJECT
public:
    explicit chess(QWidget *parent = 0);
    ~chess();

int wylosowane [12];
int wylosowanych;
    QTimer *timer;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;
    QTimer *timer6;
    QTimer *timer7;
    QTimer *timer8;
    QTimer *timer9;
    QTimer *timer10;
    QTimer *timer11;
    QTimer *timer12;

    QUdpSocket *udpSocket;

public:
    double i_ms = 0;
    double i_ms1 = 0;
    double i_ms2=0;
    double i_ms3=0;
    double i_ms4 = 0;
    double i_ms5 = 0;
    double i_ms6=0;
    double i_ms7=0;
    double i_ms8 = 0;
    double i_ms9 = 0;
    double i_ms10=0;
    double i_ms11=0;
    double i_ms12=0;
    int i_interval = 17;

    double get_s(double f, double i_ms);   //, double fi);
    int wylosuj();

    bool czyBylaWylosowana( int iLiczba, int tab[], int ile );


private:
    Ui::chess *ui;
    int duration;
    int count;
    int shapeTime;

    int tick;
    int tick1;
    int tick2;
    int tick3;
    int repeat;
    bool start;
    bool firstPattern;
    bool firstPattern1;
    bool firstPattern2;
    bool firstPattern3;
    bool firstPattern4;
    bool firstPattern5;
    bool firstPattern6;
    bool firstPattern7;
    bool firstPattern8;
    bool firstPattern9;
    bool firstPattern10;
    bool firstPattern11;
    double flashingTime;
    double flashingTime1;
    double flashingTime2;
    double flashingTime3;
    double flashingTime5;
    double flashingTime6;
    double flashingTime7;
    double flashingTime8;
    double flashingTime9;
    double flashingTime10;
    double flashingTime11;
    double flashingTime12;
    double rowNumber;
    double squareSize;
    double pause;
    int num, flag;

public slots:

    void datagram();
    void timeTick();
    void timeTick1();
    void timeTick2();
    void timeTick3();
    void timeTick4();
    void timeTick5();
    void timeTick6();
    void timeTick7();
    void timeTick8();
    void timeTick9();
    void timeTick10();
    void timeTick11();
    void timeTick12();

};

#endif // CHESS_H
