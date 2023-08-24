#ifndef GLYPH_H
#define GLYPH_H

#include <utility>

const uint32_t char_mask[] = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

class Glyph {
private:
    //const char* character;
    const uint32_t* data;

public:
    Glyph(const char* d){
        data = std::move(d);
    }
    ~Glyph(){}

    void invertColor(){}
};

#endif
