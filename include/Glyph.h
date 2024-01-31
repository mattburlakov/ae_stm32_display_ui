#ifndef GLYPH_H
#define GLYPH_H

#include <utility>
#include <Font.h>

class Glyph {
private:
    char* character;
    uint32_t* data;

    Font* font;

public:
    Glyph(char* d){

    }
    ~Glyph(){}

    void invertColor(){}
};

#endif
