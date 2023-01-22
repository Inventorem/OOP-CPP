#include <iostream>
#include <sstream>
#include "SoundEditor.h"

SoundEditor::SoundEditor(std::ifstream &file) {
    channel = getWAVReader(file);
}

SoundEditorMix::SoundEditorMix(std::ifstream &file) : SoundEditor(file) {
}


SoundEditorMute::SoundEditorMute(std::ifstream &file) : SoundEditor(file) {
}

SoundEditorClip::SoundEditorClip(std::ifstream &file) : SoundEditor(file) {
}


void SoundEditorMute::apply(std::string command, ConfigParser * parser) {
    if (channel == nullptr)
        throw std::logic_error("Wrong sound editor state state");
    std::string param;
    std::string startS;
    std::string stopS;
    std::stringstream ss(command);
    ss>>param;
    ss >> startS >> stopS;
    int start = std::stoi(startS);
    int stop = std::stoi(stopS);
    channel = getMuteChannel(channel, start, stop);
}

void SoundEditorMix::apply(std::string command, ConfigParser * parser) {
    if (channel == nullptr)
        throw std::logic_error("Wrong sound editor state state");
    std::stringstream ss(command);
    std::string channelS;
    std::string startS;
    std::string param;
    ss>>param;
    ss >> channelS >> startS;
    if (channelS[0] != '$') {
        throw std::exception();
    }
    channelS.erase(0, 1);
    int channelNumber = std::stoi(channelS) - 1;
    int start = std::stoi(startS);
    if (channelNumber >= parser->inputFiles.size())
        throw std::exception();
    std::ifstream* file = new std::ifstream(parser->inputFiles[channelNumber], std::ios::binary);
    parser->files.push_back(file);
    WAVChannel* additional = getWAVReader(*file);
    channel = getMixerChannel(channel, additional, start);
}

void SoundEditorClip::apply(std::string command, ConfigParser * parser) {
    if (channel == nullptr)
        throw std::logic_error("Wrong sound editor state state");
    std::string startS;
    std::string stopS;
    std::stringstream ss(command);
    std::string param;
    ss>>param;
    ss >> startS >> stopS;
    int start = std::stoi(startS);
    int stop = std::stoi(stopS);
    channel = getClipChannel(channel, start, stop);
}


void SoundEditor::write(std::ofstream& out) {
    if (channel == nullptr)
        throw std::logic_error("Wrong sound editor state state");
    WAVWriter* writer = getWAVWriter(channel, out);
    writer->write();
    writer->close();
    channel = nullptr;
}

SoundEditor::~SoundEditor() {
    if (channel != nullptr)
        delete channel;
}

void SoundEditor::apply(const std::string command, ConfigParser *parser) noexcept(false) {
}
