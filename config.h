#pragma once
#include <string>

struct Config {
    std::string origemBase;
    std::string destino;
};
<<<<<<< HEAD
=======

bool loadConfig(Config& cfg);
void saveConfig(const Config& cfg);
>>>>>>> 0708694 (Refatorar configuração e lógica de processamento de arquivos)
