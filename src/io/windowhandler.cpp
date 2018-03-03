#include "windowhandler.h"

WindowHandler::WindowHandler(unsigned long pid, QObject *parent) : QObject(parent)
{
    s = QGuiApplication::primaryScreen();
    this->pid = pid;
    refreshHWND();
}

void WindowHandler::refreshHWND(){
    GetWindowsOfProcess(this->pid, this->vecWindows);
    if(vecWindows.size() > 0)
        this->window = (unsigned long)this->vecWindows[0];
    else
        this->window = 0;
}

QPixmap WindowHandler::getProcessScreen()
{
    return s->grabWindow(this->window);
}

QPixmap WindowHandler::getPixel(int x, int y)
{
    return s->grabWindow(this->window,x,y,1,1);
}

void WindowHandler::setPid(unsigned long pid)
{
    this->pid = pid;
    this->refreshHWND();
}

unsigned long WindowHandler::getPid()
{
    return this->pid;
}

void WindowHandler::GetWindowsOfProcess(DWORD dwId, std::vector<HWND>& vecWindows)
{
    struct WindowsOfProcess
    {
        std::vector<HWND>*  pvecWindows;
        DWORD               dwProcId;

        static BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam)
        {
            DWORD dwProcId;
            GetWindowThreadProcessId(hWnd, &dwProcId);
            if (dwProcId == reinterpret_cast<WindowsOfProcess*>(lParam)->dwProcId)
                reinterpret_cast<WindowsOfProcess*>(lParam)->pvecWindows->push_back(hWnd);
            return TRUE;
        }

        WindowsOfProcess(DWORD dwId, std::vector<HWND>* pvec): dwProcId(dwId), pvecWindows(pvec)
        {
            EnumWindows(EnumProc, reinterpret_cast<LPARAM>(this));
        }
    };
    WindowsOfProcess wop(dwId, &vecWindows);
}
