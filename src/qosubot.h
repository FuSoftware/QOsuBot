#ifndef QOSUBOT_H
#define QOSUBOT_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QTime>
#include <QVector>
#include <QDebug>

#include "keysender.h"

#include "windowhandler.h"
#include "windowhandlerworker.h"

struct Coord{
    Coord(){}
    Coord(int x, int y, int key){
        this->x = x;
        this->y = y;
        this->key = key;
    }

    int x = 0;
    int y = 0;
    int key = 0;
};

class QOsuBot : public QObject
{
    Q_OBJECT
public:
    QOsuBot(long pid, QObject *parent = nullptr);
    void setup(QVector<Coord> coords);
    void setCoords(QVector<Coord> coords);

    QColor getPixel(int x, int y, int id = 0);
    static bool isRed(qreal r, qreal b);
    static bool isBlue(qreal r, qreal b);

signals:
    void running(bool);
    void finished();
    void pixelRead(int, QPixmap);
    void scanTime(long);
    void press(int key, int delay, int wait);

public slots:
    void run();
    void hardRun();

private:
    QVector<int> r_keys;
    QVector<int> b_keys;

    bool isRunning = false;
    KeySender *s;
    WindowHandler *w;
    QVector<Coord> coords;
};

#endif // QOSUBOT_H
