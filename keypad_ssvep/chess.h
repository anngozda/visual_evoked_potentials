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
    int i_ms = 0;
    int i_ms1 = 0;
    int i_ms2=0;
    int i_ms3=0;
    int i_ms4 = 0;
    int i_ms5 = 0;
    int i_ms6=0;
    int i_ms7=0;
    int i_ms8 = 0;
    int i_ms9 = 0;
    int i_ms10=0;
    int i_ms11=0;
    int i_ms12=0;
    int i_interval = 17;

    double get_s(double f, double i_ms);
    double get_sfi(int f, int i_ms, double fi);
    int wylosuj();

    bool czyBylaWylosowana( int iLiczba, int tab[], int ile );

private:
    Ui::chess *ui;
    int duration;
    int count;
    int shapeTime;
    bool pomoc;
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
    int flashingTime;
    int flashingTime1;
    int flashingTime2;
    int flashingTime3;
    int flashingTime5;
    int flashingTime6;
    int flashingTime7;
    int flashingTime8;
    int flashingTime9;
    int flashingTime10;
    int flashingTime11;
    int flashingTime12;
    int rowNumber;
    int squareSize;
    int pause;
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
