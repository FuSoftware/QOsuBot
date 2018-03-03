#ifndef QOSUBOTWIDGET_H
#define QOSUBOTWIDGET_H

#include <QtWidgets>
#include <QPixmap>
#include "controller/qosubot.h"

class QOsuBotWidget : public QWidget
{
    Q_OBJECT
public:
    QOsuBotWidget(QVector<Coord> coordinates, QWidget *parent = nullptr);

signals:

public slots:
    void onRunning(bool running);
    void onScan(long elapsed);
    void onPixel(int id, QPixmap value);
    void start();

private:
    QOsuBot *bot = 0;
    QLabel *running = 0;
    QLabel *scan = 0;
    QVector<QLabel*> pixels;
    QVector<Coord> coordinates;
};

#endif // QOSUBOTWIDGET_H
