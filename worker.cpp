#include "worker.h"
#include "utils.h"
#include <filesystem>
#include <fstream>
#include <unordered_set>

namespace fs = std::filesystem;

void processar(const Config& cfg) {
    std::unordered_set<std::string> copiados;

    std::ifstream log(getLogPath());
    std::string line;
    while (std::getline(log, line))
        copiados.insert(line);

    std::string origem = cfg.origemBase + "\\" + getAnoMesAtual();

    if (!fs::exists(origem)) return;

    for (auto& f : fs::directory_iterator(origem)) {
        if (!f.is_regular_file()) continue;

        std::string full = f.path().string();
        std::string hash = sha256(full);
        std::string registro = full + ":" + hash;

        if (copiados.find(registro) != copiados.end())
            continue;

        fs::copy_file(full,
            cfg.destino + "\\" + f.path().filename().string(),
            fs::copy_options::overwrite_existing);

        std::ofstream out(getLogPath(), std::ios::app);
        out << registro << "\n";
    }
}    while (true) {
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
