#ifndef FONT_H
#define FONT_H

//[space]!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ start on 20; 95 chars

class Font{
private:

public:
    uint8_t* data;
    uint8_t width  = 8;
    uint8_t height = 8;

    Font(uint8_t* d){
        data = d;
    }

    ~Font(){
        delete[] data;
    }
};

#endif
