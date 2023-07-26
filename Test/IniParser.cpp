#include "IniParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, std::string> parseIniFile(const std::string& filename) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open " << filename << std::endl;
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            config[key] = value;
        }
    }

    file.close();
    return config;
}
