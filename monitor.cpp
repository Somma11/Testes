#include <windows.h>
#include <string>
#include "worker.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmd, int) {

    if (std::string(cmd) == "worker") {
        runWorker();
        return 0;
    }

    while (true) {
        STARTUPINFOA si{ sizeof(si) };
        PROCESS_INFORMATION pi;

        char cmdLine[] = "monitor.exe worker";

        if (CreateProcessA(
            NULL,
            cmdLine,
            NULL, NULL, FALSE,
            CREATE_NO_WINDOW,
            NULL, NULL,
            &si, &pi
        )) {
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }

        Sleep(2000);
    }
}
