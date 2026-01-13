#include "config.h"
#include <windows.h>
<<<<<<< HEAD
=======
#include <shlobj.h>
>>>>>>> 0708694 (Refatorar configuração e lógica de processamento de arquivos)
#include <fstream>

static std::string getConfigPath() {
    char path[MAX_PATH];
    SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, path);
    return std::string(path) + "\\monitor_config.ini";
}

bool loadConfig(Config& cfg) {
    std::ifstream f(getConfigPath());
    if (!f.is_open()) return false;

    std::getline(f, cfg.origemBase);
    std::getline(f, cfg.destino);
    return true;
}

void saveConfig(const Config& cfg) {
    std::ofstream f(getConfigPath(), std::ios::trunc);
    f << cfg.origemBase << "\n";
    f << cfg.destino << "\n";
}
