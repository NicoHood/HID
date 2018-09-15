/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Include guard
#pragma once

#include <Arduino.h>
#include "HID.h"
#include "HID-Settings.h"
#include "../HID-APIs/DefaultKeyboardAPI.h"


class BootKeyboard_ : public PluggableUSBModule, public DefaultKeyboardAPI
{
public:
    BootKeyboard_(void);
    uint8_t getLeds(void);
    uint8_t getProtocol(void);
    void wakeupHost(void);
    
    void setFeatureReport(void* report, int length){
        if(length > 0){
            featureReport = (uint8_t*)report;
            featureLength = length;
            
            // Disable feature report by default
            disableFeatureReport();
        }
    }
    
    int availableFeatureReport(void){
        if(featureLength < 0){
            return featureLength & ~0x8000;
        }
        return 0;
    }
    
    void enableFeatureReport(void){
        featureLength &= ~0x8000;
    }
    
    void disableFeatureReport(void){
        featureLength |= 0x8000;
    }
    
    virtual int send(void) final;

protected:
    // Implementation of the PUSBListNode
    int getInterface(uint8_t* interfaceCount);
    int getDescriptor(USBSetup& setup);
    bool setup(USBSetup& setup);
    
    EPTYPE_DESCRIPTOR_SIZE epType[1];
    uint8_t protocol;
    uint8_t idle;
    
    uint8_t leds;
    
    uint8_t* featureReport;
    int featureLength;
};
extern BootKeyboard_ BootKeyboard;


