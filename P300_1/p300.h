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

   void paintEvent(QPaintEvent *e);

    QTimer *timer;

    QUdpSocket *udpSocket;


private:
    Ui::p300 *ui;

    int count;
    int count1;
    int rand;
    int shapeTime;
    int repeat;
    bool start;
    int flashingTime;
    int interval;
    int nontarget;
    int x,y,x1,y1;
    int radius, radius1;
    int p1,p2;
    bool firstpattern;
    bool dark;
    bool circle;
    bool circle1;


public slots:

  void datagram();
  void timeTick();



};

#endif // P300_H
