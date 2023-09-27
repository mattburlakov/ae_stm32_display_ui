#ifndef SCREEN_CONTROL_H
#define SCREEN_CONTROL_H

//#include <vector>

#include <stm32g474xx.h>

#include "Label.h"

#include "SPI_Connection.h"

//add pages later

        uint8_t t = 8 * 32 / 2;
        uint8_t testData[8*32/2] = {0b11111111};

        Label l1(testData, t, 32, 8, 0, 0);
        Label l2(testData, t, 32, 8, 0, 32);
        Label l3(testData, t, 32, 8, 64, 0);
        Label l4(testData, t, 32, 8, 64, 32);

class ScreenControl{
private:
    SPI_Connection* connection = nullptr;

    const uint8_t labelNum = 4;
    Label* page_1[4] = {nullptr, nullptr, nullptr, nullptr};

    const uint16_t dataLen = 256*64/2;
    uint8_t visualData[256*64/2] = {0};

    const uint8_t screenWidth   = 256/2;
    const uint8_t screenHeight  = 64;

public:
    ScreenControl(SPI_Connection* c){
        connection = c;

        //testing

        page_1[0] = &l1;
        page_1[1] = &l2;
        page_1[2] = &l3;
        page_1[3] = &l4;

    }
    ~ScreenControl(){}

    void placeLabel(Label* label){
        uint8_t row = 0;
        for(uint8_t i = 0; i < label->height; i++){
            for(uint8_t j = 0; j < label->width/2; j++){
                visualData[dataLen - 1 - (label->xPos/2 + label->yPos*screenWidth + screenWidth*i + j)] = 0b11111111;
            }
        }
    }

    void assembleFrame(){ //combine /w placeLabel()
        for(uint16_t i = 0; i < labelNum; i++){
            placeLabel(page_1[i]);
        }
    }

    void draw(){
        assembleFrame();

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
