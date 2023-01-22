#pragma once
#include "SoundEditor.h"

class SoundEdtiorFactory{
public:
    SoundEditor * create(const std::string& command, std::ifstream);
};