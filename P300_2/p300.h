#ifndef P300_H
#define P300_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QUdpSocket>
#include <QtGui>
#include <QGraphicsScene>

namespace Ui {
class p300;
}

class p300 : public QWidget
{
    Q_OBJECT
public:
    explicit p300(QWidget *parent = 0);
    ~p300();

  // void paintEvent(QPaintEvent *e);

   int wylosowane [9];
   int wylosowanych=0;
    QTimer *timer;

    QUdpSocket *udpSocket;


private:
    Ui::p300 *ui;



    int count;
    int nont;
    int p;
    int shapeTime;
    int repeat;
    bool start;
    int flashingTime;
    int interval;
    int nontarget;
    int x,y,x1,y1;
    int radius, radius1;
    int p1,p2;
    bool target;
    bool dark;



public slots:

  void datagram();
  void timeTick();

  int wylosuj();

  bool czyBylaWylosowana( int iLiczba, int tab[], int ile );


};

#endif // P300_H
