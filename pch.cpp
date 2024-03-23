// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include <Psapi.h>
#include <string>

using namespace std;

//用于检查指定进程是否有窗口，如果窗口不可见则返回false
bool HasWindow(DWORD processID) {
    HWND hwnd = NULL;
    do {
        hwnd = FindWindowEx(NULL, hwnd, NULL, NULL);
        DWORD windowProcessID = 0;
        GetWindowThreadProcessId(hwnd, &windowProcessID);
        if (windowProcessID == processID) {
            if (IsWindowVisible(hwnd)) {
                // 检查窗口是否可见
                return true;
            }
        }
    } while (hwnd != NULL);
    return false;
}

// 检查指定的进程是否在前台
bool IsProcessForeground(DWORD processId) {
    HWND hWnd = GetForegroundWindow();
    DWORD foregroundProcessId;
    GetWindowThreadProcessId(hWnd, &foregroundProcessId);
    return foregroundProcessId == processId;
}

// 杀死进程的函数
bool KillProcess(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    if (hProcess != NULL) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
        return true;
    }
    return false;
}
