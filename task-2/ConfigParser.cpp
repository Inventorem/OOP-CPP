#include <sstream>
#include <iostream>
#include "ConfigParser.h"

ConfigParser::ConfigParser(const std::string& configFileName, std::string outputFile, std::vector<std::string> inputFiles) :
        config(configFileName) , inputFiles(inputFiles), outputFile(outputFile) {
    if (!this->config.is_open())
        throw std::exception();
    if (inputFiles.empty())
        throw std::exception();
}

int ConfigParser::parse_command(std::string * command) {
    std::string string;
    if(!std::getline(config, string))
        return 1;
    int flag = 0;
    if (string[0] == '#'){
        flag = 1;
        while ( std::getline(config, string)){
            if (string[0] != '#'){
                flag = 0;
                break;
            }

        }
    }
    if (flag){
        return 1;
    }
    *command = string;
    return 0;
}

ConfigParser::~ConfigParser() {
    for(std::ifstream*& file : this->files) {
        delete file;
    }
}


std::ifstream ConfigParser::getInput() {
    std::ifstream inputFile(this->inputFiles[0], std::ios::binary);
    return inputFile;
}

std::string ConfigParser::getConfigLore() {
    return "Some config format lore";
}

