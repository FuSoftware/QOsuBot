#ifndef QTAIKOBOTASYNC_H
#define QTAIKOBOTASYNC_H

#include <QObject>
#include <QVector>
#include <QTimer>

#include "qtaikobot.h"
#include "qtaikobotworker.h"

class QTaikoBotAsync : public QTaikoBot
{
    Q_OBJECT
public:
    QTaikoBotAsync(QString process, QObject *parent = nullptr);

signals:

public slots:
    void start();
    void processed(int state, QTaikoBotWorker *sender);

private:
    bool isRunning = false;

    QVector<QTaikoBotWorker*> w;
};

#endif // QTAIKOBOTASYNC_H
