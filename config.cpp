#include "config.h"
#include "utils.h"
#include <windows.h>

std::string getConfigPath() {
    return getAppDataDir() + "\\config.ini";
}

bool loadConfig(Config& cfg) {
    std::string path = getConfigPath();

    if (GetFileAttributesA(path.c_str()) == INVALID_FILE_ATTRIBUTES)
        return false;

    char buffer[MAX_PATH];

    GetPrivateProfileStringA("Paths", "BaseOrigem", "", buffer, MAX_PATH, path.c_str());
    cfg.baseOrigem = buffer;

    GetPrivateProfileStringA("Paths", "Destino", "", buffer, MAX_PATH, path.c_str());
    cfg.destino = buffer;

    cfg.intervaloMs = GetPrivateProfileIntA("Settings", "IntervaloMs", 15000, path.c_str());

    return !cfg.baseOrigem.empty() && !cfg.destino.empty();
}

void createConfigWizard(Config& cfg) {
    cfg.baseOrigem = selectFolderDialog("Selecione a pasta BASE da origem");
    cfg.destino    = selectFolderDialog("Selecione a pasta DESTINO");
    cfg.intervaloMs = 15000;

    std::string path = getConfigPath();

    WritePrivateProfileStringA("Paths", "BaseOrigem", cfg.baseOrigem.c_str(), path.c_str());
    WritePrivateProfileStringA("Paths", "Destino", cfg.destino.c_str(), path.c_str());
    WritePrivateProfileStringA("Settings", "IntervaloMs", "15000", path.c_str());
}
