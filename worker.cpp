#include "worker.h"
#include "config.h"
#include "utils.h"

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <wincrypt.h>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "advapi32.lib")

namespace fs = std::filesystem;

std::string getLogPath() {
    return getAppDataDir() + "\\copiados.txt";
}

std::string sha256File(const std::string& path) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE hash[32];
    DWORD hashLen = 32;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        return "";

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return "";
    }

    std::ifstream file(path, std::ios::binary);
    char buffer[8192];
    while (file.read(buffer, sizeof(buffer)) || file.gcount())
        CryptHashData(hHash, (BYTE*)buffer, (DWORD)file.gcount(), 0);

    CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0);

    std::ostringstream oss;
    for (DWORD i = 0; i < hashLen; i++)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return oss.str();
}

void runWorker() {
    Config cfg;
    if (!loadConfig(cfg))
        createConfigWizard(cfg);

    std::unordered_set<std::string> copiados;
    std::ifstream logIn(getLogPath());
    std::string line;
    while (std::getline(logIn, line))
        copiados.insert(line);

    while (true) {
        std::string origem = cfg.baseOrigem + "\\" + getAnoMesAtual();

        if (fs::exists(origem)) {
            for (auto& f : fs::directory_iterator(origem)) {
                if (!f.is_regular_file())
                    continue;

                std::string nome = f.path().filename().string();
                std::string hash = sha256File(f.path().string());
                std::string registro = nome + ":" + hash;

                if (copiados.contains(registro))
                    continue;

                try {
                    fs::copy_file(
                        f.path(),
                        cfg.destino + "\\" + nome,
                        fs::copy_options::overwrite_existing
                    );

                    std::ofstream logOut(getLogPath(), std::ios::app);
                    logOut << registro << "\n";
                    copiados.insert(registro);
                }
                catch (...) {}
            }
        }

        Sleep(cfg.intervaloMs);
    }
}
