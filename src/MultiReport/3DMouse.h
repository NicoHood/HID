#pragma once

#include <Arduino.h>
#include "HID.h"
#include "HID-Settings.h"
#include "../HID-APIs/3DMouseAPI.h"


class 3DMouse_ : public 3DMouseAPI
{
public:
    3DMouse_(void);

protected: 
    virtual inline void SendReport(void* data, int length) override;
};
extern 3DMouse_ 3DMouse;

