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
<<<<<<< HEAD

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
=======
    if (!fs::exists(origem)) return;
>>>>>>> 0708694 (Refatorar configuração e lógica de processamento de arquivos)

    for (auto& f : fs::directory_iterator(origem)) {
        if (!f.is_regular_file()) continue;

        std::string full = f.path().string();
        std::string hash = sha256(full);
        std::string registro = full + ":" + hash;

        if (copiados.find(registro) != copiados.end())
            continue;

        fs::copy_file(
            full,
            cfg.destino + "\\" + f.path().filename().string(),
            fs::copy_options::overwrite_existing
        );

        std::ofstream out(getLogPath(), std::ios::app);
        out << registro << "\n";
    }
}
