#include "keysender.h"

KeySender::KeySender(QObject *parent) : QObject(parent)
{

}

KeySender::KeySender(int code, QObject *parent) : QObject(parent)
{
    this->code = code;
}

void KeySender::sendKey()
{
    this->sendKey(this->code);
}

bool KeySender::isPressed(int code)
{
    return pressed[code];
}

void KeySender::sendKey(int code, int delay, int wait)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; //Hardware code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    QThread::msleep(delay);

    // Press the key
    ip.ki.wVk = code; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    pressed[code] = true;

    QThread::msleep(wait);

    // Release thennn key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
    pressed[code] = false;
}
