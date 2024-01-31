#ifndef LABEL_H
#define LABEL_H

#include "FONT_A.h"

class Label{    //separate into geometry and text obj later
private:

public:
    uint8_t* data = nullptr;

    uint8_t dataLen      = 0;
    uint8_t width        = 0;
    uint8_t height       = 0;

    uint8_t xPos = 0;
    uint8_t yPos = 0;

    bool selected = false;

    Label(uint8_t* d, uint8_t dL, uint8_t w, uint8_t h, uint8_t x, uint8_t y){
        data = d;

        dataLen = dL;

        width   = w;
        height  = h;

        xPos    = x;
        yPos    = y;

        setGlyph(eng::char_V, 3, 8, 1, 1);
        setGlyph(eng::char_O, 3, 8, 4, 1);
        setGlyph(eng::char_L, 3, 8, 7, 1);
        setGlyph(eng::char_T, 3, 8, 10, 1);
        setGlyph(eng::char_A, 3, 8, 13, 1);
        setGlyph(eng::char_G, 3, 8, 16, 1);
        setGlyph(eng::char_E, 3, 8, 19, 1);


        //invert();

    }

    ~Label(){}

    uint8_t* getData(){
        return data;
    }

    void setGlyph(const uint8_t* g, uint8_t w, uint8_t h, uint8_t x, uint8_t y){
        for(uint8_t i = 0; i < h; i++){
            for(uint8_t j = 0; j < w; j++){
                data[x + width/2*(i + y) + j] = g[i*w + j];
            }
        }
    }

    void invert(){
        for(uint16_t i = 0; i < dataLen; i++){
            data[i] ^= 0xFF;
        }
    }
};

#endif
