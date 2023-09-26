#ifndef LABEL_H
#define LABEL_H

#include "Font.h"

class Label{
private:
    uint8_t* data  = nullptr;
    Font* font;

    uint8_t width   = 0;
    uint8_t length  = 0;
    uint8_t dataLen = 0;

    uint8_t xPos = 0;
    uint8_t yPos = 0;

public:
    Label(Font* f, const char* text, uint8_t len, uint8_t x, uint8_t y){
        font    = f;
        width   = len * font->width;
        length  = len;
        dataLen = len * font->height;

        xPos = x;
        yPos = y;

        setData(text);
    }

    Label(uint8_t len, uint8_t x, uint8_t y){
        dataLen = len * 8;
        length  = len;
        width   = len * 4;
        xPos    = x;
        yPos    = y;

    }

    ~Label(){
        delete data;
    }

    void setData(const char* text){
        data = new uint8_t[dataLen]; // attention

        for(uint8_t i = 0; i < length; i++){
            for(uint8_t j = 0; j < font->height; j++){
                data[i] = font->data[text[i] + j - 20];
            }
        }
    }

    uint8_t* getData(){
        return data;
    }

    void invert(){
        for(uint8_t i = 0; i < dataLen; i++){
            data[i] ^= 0b00000000;
        }
    }
};

#endif
