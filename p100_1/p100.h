#ifndef P100_H
#define P100_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QUdpSocket>
#include <QPainter>

namespace Ui {
class p100;
}

class p100 : public QWidget
{
    Q_OBJECT

public:
    explicit p100(QWidget *parent = 0);
    ~p100();

    QTimer *timer;
    QUdpSocket *udpSocket;
    void paintEvent(QPaintEvent *e);

private:
    Ui::p100 *ui;
    int tick;
    int time;
    int flashTime;
    int repeat;
    int counter;
    int black;
    int size;
    int rows;

public slots:
    void timeTick();
    void releaseRectangle();
};

#endif // P100_H
