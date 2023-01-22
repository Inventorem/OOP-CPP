#pragma once
#include <fstream>
#include "../channel/WAVChannel.h"
#include "../ConfigParser.h"

class SoundEditor {
protected:
    WAVChannel* channel;
public:
    virtual void apply(std::string command, ConfigParser *parser) noexcept(false) = 0;;

    explicit SoundEditor(std::ifstream& file) noexcept(false);

    void write(std::ofstream& out) noexcept(false);

    ~SoundEditor();

};

class SoundEditorMix : public SoundEditor {
    void apply(std::string command, ConfigParser * parser) override;

public:
    explicit SoundEditorMix(std::ifstream &file);
};

class SoundEditorClip : public SoundEditor {
    void apply(std::string command, ConfigParser * parser) override;

public:
    explicit SoundEditorClip(std::ifstream &file);
};

class SoundEditorMute : public SoundEditor {
    void apply(std::string command, ConfigParser * parser) override;

public:
    explicit SoundEditorMute(std::ifstream &file);
};
