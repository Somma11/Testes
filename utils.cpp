#include "utils.h"
#include <windows.h>
#include <shlobj.h>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getAppDataDir() {
    char* appdata = nullptr;
    size_t len = 0;
    _dupenv_s(&appdata, &len, "APPDATA");

    std::string path = std::string(appdata) + "\\FileMonitor";
    CreateDirectoryA(path.c_str(), NULL);

    free(appdata);
    return path;
}

std::string selectFolderDialog(const std::string& title) {
    BROWSEINFOA bi{};
    bi.lpszTitle = title.c_str();
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (!pidl) return "";

    char path[MAX_PATH];
    SHGetPathFromIDListA(pidl, path);
    CoTaskMemFree(pidl);

    return path;
}

std::string getAnoMesAtual() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << (tm.tm_year + 1900)
        << std::setw(2) << std::setfill('0') << (tm.tm_mon + 1);

    return oss.str();
}
