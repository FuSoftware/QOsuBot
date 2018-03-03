#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QTime>
#include <QTimer>
#include "io/windowhandler.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void refreshScreen();
    void setPid();

private:
    QLineEdit *le = 0;
    QLabel *label = 0;
    QLabel *labelTime = 0;
    WindowHandler *w;
};

#endif // WIDGET_H
