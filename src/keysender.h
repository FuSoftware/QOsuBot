#ifndef KEYSENDER_H
#define KEYSENDER_H

#include <QObject>
#include <QThread>
#include <windows.h>

class KeySender : public QObject
{
    Q_OBJECT
public:
    KeySender(QObject *parent = nullptr);
    KeySender(int code, QObject *parent = nullptr);

    bool isPressed(int code);

signals:

public slots:
    void sendKey(int code, int delay = 0, int sleep = 0);
    void sendKey();

private:
    int code;
    bool pressed[255];
};

#endif // KEYSENDER_H
