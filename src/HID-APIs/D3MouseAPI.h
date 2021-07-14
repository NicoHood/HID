#pragma once

#include <Arduino.h>
#include "HID-Settings.h"

typedef union {
    uint8_t whole8[0];
    uint16_t whole16[0];
    uint32_t whole32[0];

    struct
    {
        uint8_t button0 : 1;
        uint8_t button1 : 1;
        uint8_t button2 : 1;
        int16_t xAxis : 15;
        int16_t yAxis : 15;
        int16_t zAxis : 15;
        int16_t xRot : 15;
        int16_t yRot : 15;
        int16_t zRot : 15;
    };
} HID_D3MouseReport_Data_t;

class D3MouseAPI
{
  public:
    inline D3MouseAPI(void);
    inline void begin(void);
    inline void end(void);
    inline void click(int button);
    inline void rotate(String axis, int16_t rotation);
    inline void move(String axis, int16_t len);
    inline void press(int button);
    inline void release(int button);
    inline void releaseAll(void);
    inline bool isPressed(int button);
    inline void update(void);

    virtual void SendReport(void *data, int length) = 0;

  protected:
    bool _button0;
    inline void button0(bool b);

    bool _button1;
    inline void button1(bool b);

    bool _button2;
    inline void button2(bool b);

    int16_t _xRot;
    inline void xRot(int16_t rotation);

    int16_t _yRot;
    inline void yRot(int16_t rotation);

    int16_t _zRot;
    inline void zRot(int16_t rotation);

    int16_t _x;
    inline void xAxis(int16_t pos);

    int16_t _y;
    inline void yAxis(int16_t pos);

    int16_t _z;
    inline void zAxis(int16_t pos);
};

#include "D3MouseAPI.hpp"
