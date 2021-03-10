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

#include "ImprovedKeylayouts.h"

static const uint16_t _asciimap[] PROGMEM =
{
    KEY_RESERVED,                   // NUL
    KEY_RESERVED,                   // SOH
    KEY_RESERVED,                   // STX
    KEY_RESERVED,                   // ETX
    KEY_RESERVED,                   // EOT
    KEY_RESERVED,                   // ENQ
    KEY_RESERVED,                   // ACK
    KEY_RESERVED,                   // BEL
    KEY_BACKSPACE,                  // BS   Backspace
    KEY_TAB,                        // TAB  Tab
    KEY_ENTER,                      // LF   Enter
    KEY_RESERVED,                   // VT
    KEY_RESERVED,                   // FF
    KEY_RESERVED,                   // CR
    KEY_RESERVED,                   // SO
    KEY_RESERVED,                   // SI
    KEY_RESERVED,                   // DEL
    KEY_RESERVED,                   // DC1
    KEY_RESERVED,                   // DC2
    KEY_RESERVED,                   // DC3
    KEY_RESERVED,                   // DC4
    KEY_RESERVED,                   // NAK
    KEY_RESERVED,                   // SYN
    KEY_RESERVED,                   // ETB
    KEY_RESERVED,                   // CAN
    KEY_RESERVED,                   // EM
    KEY_RESERVED,                   // SUB
    KEY_RESERVED,                   // ESC
    KEY_RESERVED,                   // FS
    KEY_RESERVED,                   // GS
    KEY_RESERVED,                   // RS
    KEY_RESERVED,                   // US

    KEY_SPACE,                      // ' ' Space
    KEY_1|MOD_LEFT_SHIFT,           // !
    KEY_QUOTE|MOD_LEFT_SHIFT,       // "
    KEY_3|MOD_LEFT_SHIFT,           // #
    KEY_4|MOD_LEFT_SHIFT,           // $
    KEY_5|MOD_LEFT_SHIFT,           // %
    KEY_7|MOD_LEFT_SHIFT,           // &
    KEY_QUOTE,                      // '
    KEY_9|MOD_LEFT_SHIFT,           // (
    KEY_0|MOD_LEFT_SHIFT,           // )
    KEY_8|MOD_LEFT_SHIFT,           // *
    KEY_EQUAL|MOD_LEFT_SHIFT,       // +
    KEY_COMMA,                      // ,
    KEY_MINUS,                      // -
    KEY_PERIOD,                     // .
    KEY_SLASH,                      // /
    KEY_0,                          // 0
    KEY_1,                          // 1
    KEY_2,                          // 2
    KEY_3,                          // 3
    KEY_4,                          // 4
    KEY_5,                          // 5
    KEY_6,                          // 6
    KEY_7,                          // 7
    KEY_8,                          // 8
    KEY_9,                          // 9
    KEY_SEMICOLON|MOD_LEFT_SHIFT,   // :
    KEY_SEMICOLON,                  // ;
    KEY_COMMA|MOD_LEFT_SHIFT,       // <
    KEY_EQUAL,                      // =
    KEY_PERIOD|MOD_LEFT_SHIFT,      // >
    KEY_SLASH|MOD_LEFT_SHIFT,       // ?
    KEY_2|MOD_LEFT_SHIFT,           // @
    KEY_A|MOD_LEFT_SHIFT,           // A
    KEY_B|MOD_LEFT_SHIFT,           // B
    KEY_C|MOD_LEFT_SHIFT,           // C
    KEY_D|MOD_LEFT_SHIFT,           // D
    KEY_E|MOD_LEFT_SHIFT,           // E
    KEY_F|MOD_LEFT_SHIFT,           // F
    KEY_G|MOD_LEFT_SHIFT,           // G
    KEY_H|MOD_LEFT_SHIFT,           // H
    KEY_I|MOD_LEFT_SHIFT,           // I
    KEY_J|MOD_LEFT_SHIFT,           // J
    KEY_K|MOD_LEFT_SHIFT,           // K
    KEY_L|MOD_LEFT_SHIFT,           // L
    KEY_M|MOD_LEFT_SHIFT,           // M
    KEY_N|MOD_LEFT_SHIFT,           // N
    KEY_O|MOD_LEFT_SHIFT,           // O
    KEY_P|MOD_LEFT_SHIFT,           // P
    KEY_Q|MOD_LEFT_SHIFT,           // Q
    KEY_R|MOD_LEFT_SHIFT,           // R
    KEY_S|MOD_LEFT_SHIFT,           // S
    KEY_T|MOD_LEFT_SHIFT,           // T
    KEY_U|MOD_LEFT_SHIFT,           // U
    KEY_V|MOD_LEFT_SHIFT,           // V
    KEY_W|MOD_LEFT_SHIFT,           // W
    KEY_X|MOD_LEFT_SHIFT,           // X
    KEY_Y|MOD_LEFT_SHIFT,           // Y
    KEY_Z|MOD_LEFT_SHIFT,           // Z
    KEY_LEFT_BRACE,                 // [
    KEY_BACKSLASH,                  // bslash
    KEY_RIGHT_BRACE,                // ]
    KEY_6|MOD_LEFT_SHIFT,           // ^
    KEY_MINUS|MOD_LEFT_SHIFT,       // _
    KEY_TILDE,                      // `
    KEY_A,                          // a
    KEY_B,                          // b
    KEY_C,                          // c
    KEY_D,                          // d
    KEY_E,                          // e
    KEY_F,                          // f
    KEY_G,                          // g
    KEY_H,                          // h
    KEY_I,                          // i
    KEY_J,                          // j
    KEY_K,                          // k
    KEY_L,                          // l
    KEY_M,                          // m
    KEY_N,                          // n
    KEY_O,                          // o
    KEY_P,                          // p
    KEY_Q,                          // q
    KEY_R,                          // r
    KEY_S,                          // s
    KEY_T,                          // t
    KEY_U,                          // u
    KEY_V,                          // v
    KEY_W,                          // w
    KEY_X,                          // x
    KEY_Y,                          // y
    KEY_Z,                          // z
    KEY_LEFT_BRACE|MOD_LEFT_SHIFT,  // {
    KEY_BACKSLASH|MOD_LEFT_SHIFT,   // |
    KEY_RIGHT_BRACE|MOD_LEFT_SHIFT, // }
    KEY_TILDE|MOD_LEFT_SHIFT,       // ~
    KEY_RESERVED                    // DEL
};
