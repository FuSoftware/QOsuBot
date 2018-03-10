#ifndef QTAIKOBOT_H
#define QTAIKOBOT_H

#include <QObject>

#include "io/qscreenscanner.h"
#include "io/keysender.h"

class QTaikoBot : public QObject
{
    Q_OBJECT
public:
    QTaikoBot(QString process, QObject *parent = nullptr);

signals:
    void finished();
    void running(bool);
    void pixelRead(int, QPixmap);
    void scanTime(int);
    void processTime(int);
    void press(int key, int delay, int wait);

public slots:
    virtual void start() = 0;

protected:
    static bool isRed(qreal r, qreal b, qreal g);
    static bool isBlue(qreal r, qreal b, qreal g);

    KeySender *s = 0;
    WindowHandler *h = 0;

    QVector<int> r_keys;
    QVector<int> b_keys;
    int i_r = 0;
    int i_b = 0;
};

#endif // QTAIKOBOT_H
