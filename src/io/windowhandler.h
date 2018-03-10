#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <windows.h>
#include <tlhelp32.h>
#include <cstdio>
#include <iostream>

#include <QScreen>
#include <QPixmap>
#include <QtGui>

#include <QDebug>

class WindowHandler : public QObject
{
    Q_OBJECT
public:
    WindowHandler(QString process, QObject *parent = 0);

    bool handleLoaded();

    QPixmap getProcessScreen();
    QPixmap getPixel(int x, int y);
    QPixmap getArea(int x, int y, int w, int h);
    QPixmap getWindow();

    void setPid(unsigned long pid);
    unsigned long getPid();

    static void GetWindowsOfProcess(DWORD dwId, std::vector<HWND>& vecWindows);
    static DWORD GetPID(std::string name);

public slots:
    void refreshHWND();

private:
    std::vector<HWND> vecWindows;
    unsigned long pid = 0;
    unsigned long window = 0;
    int width;
    int height;
    QScreen *s = 0;
};

#endif // WINDOWHANDLER_H
