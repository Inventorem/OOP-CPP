#include <sstream>
#include "SoundEditorFactory.h"

SoundEditor * SoundEdtiorFactory::create(const std::string& command, std::ifstream inputFile){
    std::stringstream ss(command);
    std::string param;
    ss >> param;
    if(param == "mute") {
        return new SoundEditorMute(inputFile);
    }
    if(param == "mix") {
        return new SoundEditorMix(inputFile);
    }
    if(param == "clip") {
        return new SoundEditorClip(inputFile);
    }
}