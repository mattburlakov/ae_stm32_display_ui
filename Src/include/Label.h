#ifndef LABEL_H
#define LABEL_H

class Label{
private:

public:
    uint8_t* data = nullptr;

    uint8_t dataLen      = 0;
    uint8_t width        = 0;
    uint8_t height       = 0;

    uint8_t xPos = 0;
    uint8_t yPos = 0;

    Label(uint8_t* d, uint8_t dL, uint8_t w, uint8_t h, uint8_t x, uint8_t y){
        data = d;

        dataLen = dL;

        width   = w;
        height  = h;

        xPos    = x;
        yPos    = y;

    }

    ~Label(){}

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
