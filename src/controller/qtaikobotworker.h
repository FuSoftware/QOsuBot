#ifndef QTaikoBotASYNC_H
#define QTaikoBotASYNC_H

#include <QObject>
#include <QThread>

#include "io/qscreenscanner.h"
#include "io/keysender.h"

namespace QTaiko{
    enum Validate{
        RED = 1,
        BLUE = 2,
        RUNNING = 4,
        SPINNER = 8,
        SLIDER = 16
    };
}

class QTaikoBotWorker;
typedef int (*FValidator)(QPixmap p, QTaikoBotWorker *worker);

class QTaikoBotWorker : public QObject
{
    Q_OBJECT
public:
    QTaikoBotWorker(WindowHandler *handler, int x, int y, int stateCheck, QObject *parent = nullptr);
    QTaikoBotWorker(WindowHandler *handler, int x, int y, int w, int h, int stateCheck, QObject *parent = nullptr);
    void setProcessFunc(FValidator v);

    QPixmap getLastPixmap();
    int getStateCheck();
    bool hasStateCheck(int state);

    static bool isRed(qreal r, qreal g, qreal b);
    static bool isBlue(qreal r, qreal g, qreal b);

    static int screenValidator(QPixmap p);
    static int pixelValidator(QPixmap p, QTaikoBotWorker *stateCheck);

signals:
    void validated(int,QTaikoBotWorker*);

public slots:
    void start();
    void stop();
    void process(QPixmap p);

private:
    QPixmap p;
    QScreenScanner *s;

    int stateCheck = 0;
    FValidator v;
};

#endif // QTaikoBotASYNC_H
