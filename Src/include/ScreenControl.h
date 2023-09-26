#ifndef SCREEN_CONTROL_H
#define SCREEN_CONTROL_H

//#include <vector>

#include <stm32g474xx.h>

#include "Label.h"
#include "Font.h"

#include "FONT_A.h"

#include "SPI_Connection.h"

//add pages later

class ScreenControl{
private:
    SPI_Connection* connection = nullptr;

    uint8_t labelNum = 4;
    Label* labels[4] = {nullptr, nullptr, nullptr, nullptr}; //tmp, remove

    const uint16_t dataLen = 256*64/2;
    uint8_t visualData[256*64/2] = {0};

public:
    ScreenControl(SPI_Connection* c){
        connection = c;

        //testing
        /*
        Label l1(8, 0, 0);
        Label l2(8, 0, 32);
        Label l3(8, 8, 0);
        Label l4(8, 8, 32);

        labels[0] = &l1;
        labels[1] = &l2;
        labels[2] = &l3;
        labels[3] = &l4;
        */
    }
    ~ScreenControl(){
        delete connection;
        //delete[] labels;
    }

    void addLabel(Font* font, const char* text, uint8_t len, uint8_t x, uint8_t y){
        //labels.emplace_back(Label(font, text, len, x, y));
    }

    void assembleFrame(){
        for(uint16_t i = 0; i < dataLen; i++){

        }
    }

    void draw(){
        connection->SSD1322_write_C2D(0x15, 28, 91);    // set column address, start, end
        connection->SSD1322_write_C2D(0x75, 0, 63);     // set row address, moved out of the loop (issue 302)
        connection->SSD1322_write_C(0x5C);              // Запись в RAM

        for(uint16_t i = 0; i < dataLen; i++){
            connection->SSD1322_write_D(visualData[i]);
        }

    }

    void clearScreen(){
        for(uint16_t i = 0; i < dataLen; i++){
            visualData[i] = 0b00000000;
        }
    }
};

#endif
