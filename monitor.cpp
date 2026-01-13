#include "config.h"
#include "worker.h"
#include <windows.h>
#include <shlobj.h>
<<<<<<< HEAD
#include <iostream>
=======
>>>>>>> 0708694 (Refatorar configuração e lógica de processamento de arquivos)

bool selecionarPasta(std::string& out) {
    BROWSEINFOA bi{};
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (!pidl) return false;

    char path[MAX_PATH];
    SHGetPathFromIDListA(pidl, path);
    out = path;
    return true;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Config cfg;
    if (!loadConfig(cfg)) {
        MessageBoxA(nullptr, "Selecione a pasta BASE de origem", "Config", MB_OK);
        if (!selecionarPasta(cfg.origemBase)) return 0;

        MessageBoxA(nullptr, "Selecione a pasta DESTINO", "Config", MB_OK);
        if (!selecionarPasta(cfg.destino)) return 0;

        saveConfig(cfg);
    }

    while (true) {
<<<<<<< HEAD
        __try {
            processar(cfg);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            // watchdog: ignora crash e continua
        }
=======
        try {
            processar(cfg);
        } catch (...) {
        }
>>>>>>> 0708694 (Refatorar configuração e lógica de processamento de arquivos)
        Sleep(15000);
    }
}
