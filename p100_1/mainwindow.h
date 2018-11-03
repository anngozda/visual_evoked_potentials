#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <p100.h>
#include <QtGui>
#include <QtCore>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer *myTimer;
    bool flashOn;
    void delay(int n);

public:
    p100 *fl;
    QUdpSocket *udpSocket;

public slots:
    void timeTick();

private slots:
    void on_START_clicked();
    void on_STOP_clicked();
    void on_EXIT_clicked();
};

#endif // MAINWINDOW_H
