#pragma once

#include <Arduino.h>
#include "HID.h"
#include "HID-Settings.h"
#include "../HID-APIs/D3MouseAPI.h"

class D3Mouse_ : public D3MouseAPI
{
  public:
    D3Mouse_(void);

  protected:
    virtual inline void SendReport(void *data, int length) override;
};
extern D3Mouse_ D3Mouse;
