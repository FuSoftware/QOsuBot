#ifndef QTaikoBot_H
#define QTaikoBot_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QTime>
#include <QVector>
#include <QDebug>

#include "io/keysender.h"
#include "io/windowhandler.h"
#include "io/qscreenscanner.h"

#include "qtaikobot.h"

class QTaikoBotSync : public QTaikoBot
{
    Q_OBJECT
public:
    QTaikoBotSync(QString process, QObject *parent = nullptr);

    QColor getPixel(int x, int y, int id = 0);

    int getMeanScan();
    int getMeanProcess();

signals:

public slots:
    void start();

private:
    QVector<int> scan_time;
    QVector<int> process_time;

    bool isRunning = false;
};

#endif // QTaikoBot_H
