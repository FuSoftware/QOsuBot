#include "windowhandler.h"

WindowHandler::WindowHandler(QString process, QObject *parent) : QObject(parent)
{
    s = QGuiApplication::primaryScreen();
    setPid(GetPID(process.toStdString()));

    std::cout << "Loaded handler for " << process.toStdString() << " with PID " << this->pid << " and HWND " << this->window;
}

bool WindowHandler::handleLoaded()
{
    return this->window > 0;
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

QPixmap WindowHandler::getArea(int x, int y, int w, int h)
{
    return s->grabWindow(this->window,x,y,w,h);
}

QPixmap WindowHandler::getWindow()
{
    return s->grabWindow(this->window);
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

DWORD WindowHandler::GetPID(std::string name)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            std::wstring ws( entry.szExeFile );
            std::string wname( ws.begin(), ws.end() );

            if (stricmp(wname.c_str(), name.c_str()) == 0)
            {
                return entry.th32ProcessID;
            }
        }
    }

    CloseHandle(snapshot);
    return 0;
}
