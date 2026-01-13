#pragma once
#include <string>

struct Config {
    std::string baseOrigem;
    std::string destino;
    int intervaloMs;
};

bool loadConfig(Config& cfg);
void createConfigWizard(Config& cfg);
std::string getConfigPath();
