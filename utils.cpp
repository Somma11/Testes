#include "utils.h"
#include <windows.h>
<<<<<<< HEAD
=======
#include <shlobj.h>
>>>>>>> 0708694 (Refatorar configuração e lógica de processamento de arquivos)
#include <sstream>
#include <iomanip>
#include <ctime>
#include <wincrypt.h>
#include <fstream>

std::string getAnoMesAtual() {
    time_t t = time(nullptr);
    tm tm{};
    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << (tm.tm_year + 1900)
        << std::setw(2) << std::setfill('0')
        << (tm.tm_mon + 1);
    return oss.str();
}

std::string getLogPath() {
    char path[MAX_PATH];
    SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, path);
    return std::string(path) + "\\monitor_log.txt";
}

std::string sha256(const std::string& file) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE hash[32];
    DWORD hashLen = 32;

    CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);

    std::ifstream f(file, std::ios::binary);
    char buf[4096];
    while (f.read(buf, sizeof(buf)) || f.gcount())
        CryptHashData(hHash, (BYTE*)buf, (DWORD)f.gcount(), 0);

    CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0);

    std::ostringstream oss;
    for (int i = 0; i < 32; i++)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return oss.str();
}
