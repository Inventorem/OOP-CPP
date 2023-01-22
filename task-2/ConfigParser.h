#pragma once
#include <fstream>
#include <vector>

class ConfigParser {

public:
    std::ifstream config;

    ConfigParser(const std::string& configFileName, std::string outputFile, std::vector<std::string> inputFiles);

    int parse_command(std::string * command);

    static std::string getConfigLore();

    ~ConfigParser();

    std::ifstream getInput();

    std::vector<std::string> inputFiles;
    std::vector<std::ifstream*> files;
    std::string outputFile;
};