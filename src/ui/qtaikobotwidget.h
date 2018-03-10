#ifndef QTaikoBotWIDGET_H
#define QTaikoBotWIDGET_H

#include <QtWidgets>
#include <QPixmap>
#include "controller/qtaikobotsync.h"
#include "controller/qtaikobotasync.h"

class QTaikoBotWidget : public QWidget
{
    Q_OBJECT
public:
    QTaikoBotWidget(QString executable, QWidget *parent = nullptr);

signals:

public slots:
    void onRunning(bool running);
    void onScan(int elapsed);
    void onProcess(int elapsed);
    void onPixel(int id, QPixmap value);
    void start();

private:
    QTaikoBot *bot = 0;
    QLabel *running = 0;
    QLabel *scan = 0;
    QLabel *process = 0;
    QVector<QLabel*> pixels;
};

#endif // QTaikoBotWIDGET_H
